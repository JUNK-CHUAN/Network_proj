#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>
#include <zconf.h>
#include "PakType.h"
#include "PakStuInfo.h"

#define PATHLEN 50U  // 输入路径的长度限制
#define PROTLEN 10U  // 协议的长度，即'student://'

//---------------------------------------文件操作函数--------------------------------
/*
 * 获取文件大小
 * 需要用sys/stat.h库，该方法仅限Linux
 */
int file_size(char * filename)
{
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;

    return size;
}

/*
 * 将文件加载到字节数组
 * 函数返回字符串char *
 */
char *loadfile(char * filename)
{
    printf("%s\n", filename);
    int fd = open(filename, O_RDONLY);
    printf("文件描述符： %d\n", fd);

    unsigned int FileLen = file_size(filename);
    char *buffer = (char *) malloc(sizeof(char) * FileLen); // 根据文件大小动态分配内存

    int readBytes = read(fd, buffer, sizeof(char) * FileLen);
    if (readBytes == sizeof(char) * FileLen)
    {
        printf("Read file successfully.\n");
        return buffer;
    } else
    {
        printf("The size of file: %d.\n", int(sizeof(char) * FileLen));
        printf("The Bytes actually read: %d.\n", readBytes);
        printf("Exit.\n");
        exit(0);
    }
}


//-------------------------------------I/O模块-----------------------------------
//输入字符串函数
int getline(char line[], int max)
{
    int ch;
    int i = 0;
    while (max > 0 &&
           (ch = getchar()) != EOF && ch != '\n')
    {
        line[i] = ch;
        i++;
        max--;
    }
    if (ch == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    if (i > 0)
    {
        return 1;
    }
    else
        return 0;
}

int main()
{
    printf("Please input the file you want to transfer with the protocol.\n");
    char * path = (char *)malloc(sizeof(char) * PATHLEN);
    getline(path, PATHLEN);                     // 获取输入的路径(带协议名)
    char *protocol;   // 创建一个protocol字符串储存输入的协议
    protocol = strprotocol(path, PROTLEN);      // 字符串分割，protocol储存协议，path储存地址
    strcpy(path, path + PROTLEN);
    int i = 0;
    while (path[i] != '\n')
        i++;
    path[i] = '\0';
    char standard[PROTLEN + 1] = "student://";  // 创建一个标准字符串，表示我们唯一可识别的协议
    if (strmatch(protocol, standard))           // 若协议符合学生协议的standard
    {
        char * data = loadfile(path);
        free(protocol);
        protocol = NULL;
        unsigned int DataSize = file_size(path);

        data = PackageTypeInfo(data, path, &DataSize);  // 实现顶层数据封装
        data = addIdInfo(data, DataSize);
        DataSize += 4;
        // printf("test: %s\n", data);
        // doing
    }
    else // 若协议与学生协议不符合
    {
        printf("We cannot recognize your protocol. Please use other dalao's program.\n");
        free(protocol);
        free(path);
        exit(0);
    }

    return 0;
}

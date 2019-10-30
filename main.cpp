#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/types.h>
#include <fcntl.h>
#include <zconf.h>
#include "PakType.h"

#define PATHLEN 50U  // 输入路径的长度限制
#define PROTLEN 10U  // 协议的长度，即'student://'

//----------------------------------字符串操作函数------------------------------------
/*
 * 字符串操作：
 * 系统库函数：
 *     char *strcat(char *str_des, char *str_sou);
 *     将字符串str_sou接在字符串str_des后面（放在str_des的最后字符和“\0”之间）
 * 自定义函数：
 *     字符串匹配函数int strmatch(char line[], char *mat)
 *     字符串切割函数char *strcut(char *str_des, unsigned int *size1, unsigned int *size2)
 */

/*
 * 自定义字符串切割函数
 * param.str_des:待分割字符串,函数执行后变为数组后半段
 * param.size1:分割后前半段的长度(不计'\0')
 * param.size2:待分割字符串的总的长度(不计'\0')
 * return:前半段字符串
 */
char *strprotocol(char *str_des, unsigned int size1)
{
    // 分配内存截取前半段字符串
    char  *str_pre = (char *)malloc(sizeof(char) * (size1 + 1));
    str_pre = strncpy(str_pre, str_des, size1);
    str_pre[size1] = '\0';
    // debug dump
    // printf("%s\n", str_pre);

    return str_pre;
}

/*
 * 字符串匹配函数
 * param.line: 输入字符串
 * param.mat: 匹配对应字符串
 * 完全相同返回1，
 * 否则返回0
 */
int strmatch(char line[], char *mat)
{
    assert(line);
    assert(mat);
    int i = strlen(line), j = 0, k = 0;
    if (i == strlen(mat))
    {
        for (; j < strlen(mat); j++, k++)
        {
            if (line[k] != *(mat + j))
                break;
        }
        if (*(mat + j) == '\0' && k>0)
            return 1;
    }
    return 0;
}


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
    char standard[PROTLEN + 1] = "student://";  // 创建一个标准字符串，表示我们唯一可识别的协议
    if (strmatch(protocol, standard))           // 若协议符合学生协议的standard
    {
        char * data = loadfile(path);
        printf("%s\n", protocol);
        printf("%s\n", path);
        printf("%s\n",data);
        free(data);
        // doing
    }
    else // 若协议与学生协议不符合
    {
        printf("We cannot recognize your protocol. Please use other dalao's program.\n");
        free(protocol);
        free(path);
        exit(0);
    }

    free(protocol);
    free(path);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <zconf.h>
#include <uuid/uuid.h>
#include "PakType.h"
#include "PakStuInfo.h"
#include "PakSlice.h"
#include "PakCheck.h"

#define PATHLEN 100U  // 输入路径的长度限制
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
    //printf("文件描述符： %d\n", fd);

    unsigned int FileLen = file_size(filename);
    char *buffer = (char *) malloc(sizeof(char) * FileLen); // 根据文件大小动态分配内存

    int readBytes = read(fd, buffer, sizeof(char) * FileLen);
    if (readBytes == sizeof(char) * FileLen)
    {
        printf("Read file successfully.\n");
        return buffer;
    } else
    {
        printf("The size of file: %d.\n", (int)(sizeof(char) * FileLen));
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

//-------------------------------------主函数---------------------------------
/*
 * 将读取的文件添加头部
 * 进行分组
 * 再添加校验码
 * 最后分块存入临时文件
 */

// BASE_DIR为临时文件存放的文件夹
const char BASE_DIR[PATHLEN] = "/home/junk_chuan/Desktop/temp/";
// 设置临时文件的后缀为.pak
const char POST_FIX[5] = ".pak";

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
        /* 若协议正确则读取文件数据 */
        char * data = loadfile(path);
        // 读取文件后释放内存
        free(protocol);
        protocol = NULL;
        unsigned int DataSize = file_size(path);

        // 自顶而下的第一层封装
        data = PackageTypeInfo(data, path, &DataSize);  // 实现顶层数据封装

        // 自顶而下的第二层封装
        data = addIdInfo(data, DataSize);
        DataSize += 4;

        // 自顶而下的第三层封装
        unsigned int piece = 0;
        unsigned int left = 0;
        // 将数据分组之后存入二维数组
        char **SliceData = PakSlice(data, &DataSize, &piece, &left);

        // 添加CRC校验码
        for (int i = 0; i < piece-1; ++i) {
            SliceData[i] = CRC(SliceData[i]);
        }
        SliceData[piece-1] = CRC(SliceData[piece-1], left);

        // 利用uuid生成唯一标识符，以免存储时文件名重复
        uuid_t uuid;
        char *filepath = (char *)malloc(sizeof(char) * PATHLEN);
        char str[37];
        int fd, count;
        for (int i = 0; i < piece-1; ++i)
        {
            // 生成唯一标识符
            uuid_generate(uuid);
            uuid_unparse(uuid, str);
            // 利用唯一标识符生成唯一的文件路径
            memset(filepath, '\0', sizeof(filepath));
            strcat(filepath, BASE_DIR);
            strcat(filepath, str);
            strcat(filepath, POST_FIX);
            // 创建文件并以读写方式打开
            fd = open(filepath, O_RDWR | O_CREAT, S_IRWXU | S_IRUSR | S_IWUSR);
            // 将每组数据写入临时文件
            count = write(fd, SliceData[i], 1004);
            close(fd);
        }

        // 生成唯一标识符
        uuid_generate(uuid);
        uuid_unparse(uuid, str);
        // 利用唯一标识符生成唯一的文件路径
        memset(filepath, '\0', sizeof(filepath));
        strcat(filepath, BASE_DIR);
        strcat(filepath, str);
        strcat(filepath, POST_FIX);
        // 创建文件并以读写方式打开
        fd = open(filepath, O_RDWR | O_CREAT, S_IRWXU | S_IRUSR | S_IWUSR);
        // 将每组数据写入临时文件
        count = write(fd, SliceData[piece-1], left+1);
        close(fd);
        for (int j = 0; j < piece; ++j) {
            free(SliceData[j]);
            SliceData[j] = NULL;
        }
        free(SliceData);
        SliceData = NULL;
        /* doing */
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

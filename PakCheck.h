//
// Created by junk_chuan on 2019/11/4.
//

#ifndef NETWORK_PROJ_PAKCHECK_H
#define NETWORK_PROJ_PAKCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
//CRC8校验
//ptr:要校验的数组
//len:数组长度
//返回值:CRC8码
//多项式0X31,LSB First，初始值0X00
//
//
//下方函数传入0x形式的十六进制数组与该数组长度，输出CRC计算结果
//如0x12,0x38的数组，长度为2
u_int8_t Get_Crc8(u_int8_t *ptr,u_int16_t len) {
    u_int8_t crc;
    u_int8_t i;
    crc = 0;
    while(len--) {
        crc ^= *ptr++;
        for(i = 0;i < 8;i++) {
            if(crc & 0x01) crc = (crc >> 1)^0x8C;
            else crc >>= 1;
        }
    }
    return crc;
}


//该函数为本层主功能，传入data的数据块，并传入其长度，默认填满，为1003
//该函数输出为首部加入CRC8的校验位
char* CRC(char *data, int length = 1003) {
    char *ptr = NULL;
    u_int8_t *p = NULL;
    int tempint;
    char tempchar[2];
    u_int8_t tempu;
    ptr = (char*)malloc((length + 1) * sizeof(char));//给即将分配给长度加一的数组做准备
    char a, b, c;
    // using the first byte and second byte of second layer head
    // and the first byte of second layer data
    a = data[0];
    b = data[1];
    c = data[2];
    u_int8_t pt[3] = {u_int8_t(int(a)),u_int8_t(int(b)),u_int8_t(int(c))};//传参方式
    p = pt;

    tempu = Get_Crc8(p,3);
    tempint = int(tempu);
    tempchar[0] = char(tempint);
    tempchar[1] = '\0';//结尾
    strcat(ptr, tempchar);
    strcat(ptr, data);
    printf("%s\n", ptr);
    free(data);
    data = NULL;
    return ptr;
}

#endif //NETWORK_PROJ_PAKCHECK_H

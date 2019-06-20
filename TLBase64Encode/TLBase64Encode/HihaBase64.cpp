//
//  HihaBase64.c
//  HihaBase64
//
//  Created by 突突兔 on 6/17/19.
//  Copyright © 2019 突突兔. All rights reserved.
//

#include "HihaBase64.h"



void HihaBase64_free(char *ptr)
{
    ::free(ptr);
}


char *HihaBase64_encode(const char *str)
{
    long len;
    long str_len;
    char *res;
    const uint8_t *ptr;
    int i,j;
    //定义base64编码表
    const char *base64_table= (const char *)"+NF5X8LnEJciYGAeD40qtCuBgw6pOmUb7ljP31HvshSyIZRKa9zdMkfro-2VTWxQ";
    
    ptr = (const uint8_t*)str;
    
    //计算经过base64编码后的字符串长度
    str_len=strlen(str);
    if(str_len % 3 == 0)
        len=str_len/3*4;
    else
        len=(str_len/3+1)*4;
    
    res=(char *)malloc(sizeof(char)*len+1);
    res[len]='\0';
    
    //以3个8位字符为一组进行编码
    for(i=0,j=0;i<len-2;j+=3,i+=4)
    {
        res[i]=base64_table[ptr[j]>>2]; //取出第一个字符的前6位并找出对应的结果字符
        res[i+1]=base64_table[(ptr[j]&0x3)<<4 | (ptr[j+1]>>4)]; //将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        res[i+2]=base64_table[(ptr[j+1]&0xf)<<2 | (ptr[j+2]>>6)]; //将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        res[i+3]=base64_table[ptr[j+2]&0x3f]; //取出第三个字符的后6位并找出结果字符
    }
    
    switch(str_len % 3)
    {
        case 1:
            res[i-2]='*';
            res[i-1]='*';
            break;
        case 2:
            res[i-1]='*';
            break;
    }
    
    return res;
}

char *HihaBase64_decode(const char *code)
{
    //根据base64表，以字符找到对应的十进制数据
    uint8_t table[]={
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00,
        0x12, 0x25, 0x3A, 0x24, 0x11, 0x03, 0x1A, 0x20, 0x05, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x0E, 0x17, 0x15, 0x10, 0x08, 0x02, 0x0D, 0x26, 0x2C, 0x09, 0x2F, 0x06, 0x34, 0x01, 0x1C,
        0x23, 0x3F, 0x2E, 0x2A, 0x3C, 0x1E, 0x3B, 0x3D, 0x04, 0x0C, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x30, 0x1F, 0x0A, 0x33, 0x0F, 0x36, 0x18, 0x29, 0x0B, 0x22, 0x35, 0x21, 0x1D, 0x07, 0x38,
        0x1B, 0x13, 0x37, 0x28, 0x14, 0x16, 0x27, 0x19, 0x3E, 0x2B, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    long len;
    long str_len;
     char *res;
    int i,j;
    
    //计算解码后的字符串长度
    len=strlen(code);
    //判断编码后的字符串后是否有=
    if(strstr(code,"=="))
        str_len=len/4*3-2;
    else if(strstr(code,"="))
        str_len=len/4*3-1;
    else
        str_len=len/4*3;
    
    res=(char *)malloc(sizeof( char)*str_len+1);
    res[str_len]='\0';
    
    //以4个字符为一位进行解码
    for(i=0,j=0;i < len-2;j+=3,i+=4)
    {
        res[j]=((unsigned char)table[code[i]])<<2 | (((unsigned char)table[code[i+1]])>>4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合
        res[j+1]=(((unsigned char)table[code[i+1]])<<4) | (((unsigned char)table[code[i+2]])>>2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合
        res[j+2]=(((unsigned char)table[code[i+2]])<<6) | ((unsigned char)table[code[i+3]]); //取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
    }
    
    return res;
    
}




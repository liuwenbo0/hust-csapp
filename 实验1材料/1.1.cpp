// 计算机系统实验1.1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
struct student {
    char  name[8];
    short age;
    float score;
    char  remark[200];  // 备注信息
};//student结构占用字节多   13*16+8=216 8+4(2)+4+200
student  old_s[3];    // old_s[0].name 为自己的姓名;
student  new_s[3];

int  pack_student_bytebybyte(student* s, int sno, char* buf);//逐字节压缩
int  pack_student_whole(student* s, int sno, char* buf);//不逐字节读入   使用strcpy
int  restore_student(char* buf, int len, student* s);//修复函数
int  coutmessage(char* buf, int len);//输出函数

int main()
{
    /*初始化*/
    int cnts = 0;
    char message[505];
    strcpy(old_s[0].name, "lwb");
    old_s[0].age = 18;
    old_s[0].score = 100;
    strcpy(old_s[0].remark, "good");
    strcpy(old_s[1].name, "ycx");
    old_s[1].age = 22;
    old_s[1].score = 100;
    strcpy(old_s[1].remark, "nice");
    strcpy(old_s[2].name, "lxy");
    old_s[2].age = 99;
    old_s[2].score = 55;
    strcpy(old_s[2].remark, "aha");
    //这里直接给出结构体的数据  避免了实验过程中多次的输入

    while (cnts < 3)
    {
        printf("name=%s\n", old_s[cnts].name);
        printf("age=%hd\n", old_s[cnts].age);
        printf("score=%f\n", old_s[cnts].score);
        printf("remark=%s\n", old_s[cnts].remark);
        printf("\n");
        cnts++;
    }//输出压缩前的结果
    
    cnts = 0;
    printf("压缩前存放数据的长度为%u\n\n", sizeof(student) * 3);//输出压缩前存放数据的长度

    int cntbuf = pack_student_bytebybyte(old_s, 1, message);//用第一种压缩函数压缩第一条数据

    cntbuf += pack_student_whole(old_s + 1, 2, message + cntbuf);//用第二种压缩函数压缩后两条数据

    coutmessage(message, cntbuf);//输出压缩后的数据
    printf("\n压缩后存放数据的长度为%d\n\n", cntbuf);//输出压缩后存放数据的长度
    int sno = restore_student(message, cntbuf, new_s);//用解压函数解压数据
    printf("数据已解压......输出如下\n");
    while (cnts < sno)
    {
        printf("name=%s\n", new_s[cnts].name);
        printf("age=%hd\n", new_s[cnts].age);
        printf("score=%f\n", new_s[cnts].score);
        printf("remark=%s\n", new_s[cnts].remark);
        printf("\n\n");
        cnts++;
    }//输出解压后的结果
    
    return 0;
}


int  pack_student_bytebybyte(student* s, int sno, char* buf)
{
    int cnts = 0, cntname = 0, cntage = 0, cntscore = 0, cntremark = 0, cntbuf = 0;
    char* p = (char*)s;
    char* p0 = buf;
    while (cnts < sno)
    {
        //读入name数组
        cntname = 0;
        while (cntname < 8)
        {
            if (*p)
            {
                *p0 = *p;
                cntname++;
                cntbuf++;
                p++;
                p0++;
            }
            else
            {
                *p0 = 0;
                cntbuf++;
                p += (8 - cntname);
                p0++;
                break;
            }
        }
        //读入short
        cntage = 0;
        while (cntage < 2)
        {
            *p0 = *p;
            cntage++;
            cntbuf++;
            p++;
            p0++;
        }
        p += 2;
        //读入float
        cntscore = 0;
        while (cntscore < 4)
        {
            *p0 = *p;
            cntscore++;
            cntbuf++;
            p++;
            p0++;
        }
        //读入remark数组
        cntremark = 0;
        while (cntremark < 200)
        {
            if (*p)
            {
                *p0 = *p;
                cntremark++;
                cntbuf++;
                p++;
                p0++;
            }
            else
            {
                *p0 = 0;
                cntbuf++;
                p += (200 - cntremark);
                p0++;
                break;
            }
        }
        cnts++;
    }
    return cntbuf;//返回压缩后的字节数
}
int  pack_student_whole(student* s, int sno, char* buf)
{
    int cnts = 0;
    char* p0 = buf;
    char* p = NULL;
    while (cnts < sno)
    {
        p = s[cnts].name;
        strcpy(p0, p);
        p0 += (strlen(p) + 1);//读入name数组

        p = (char*)&s[cnts].age;
        *((short*)p0) = *((short*)p);
        p0 += 2;//读入age

        p = (char*)&s[cnts].score;
        *((float*)p0) = *((float*)p);
        p0 += 4;//读入score

        p = s[cnts].remark;
        strcpy(p0, p);
        p0 += (strlen(p) + 1);//读入remark数组

        cnts++;
    }
    return p0 - buf;

}
int  restore_student(char* buf, int len, student* s)
{
    int cnts = 0;
    char* p = buf;//遍历message数组
    while (p - buf < len)//当从message数组中读入的数据不够len
    {
        strcpy(s[cnts].name, p);//读入name
        p += strlen(s[cnts].name) + 1;//p指针移动到age处
        s[cnts].age = *((short*)p);//读入age
        p += 2;//p指针移动到score处
        s[cnts].score = *((float*)p);//读入score
        p += 4;//p指针移动到remark处
        strcpy(s[cnts].remark, p);//读入remark
        p += strlen(s[cnts].remark) + 1;//p指针移动到下一name处
        cnts++;//增加学生数
    }
    return cnts;//返回学生数
}

int  coutmessage(char* buf, int len)
{
    int cnts = 0;
    char* p = buf;//遍历message数组
    while (p - buf < len)//当从message数组中读入的数据不够len
    {
        printf("%s ", p);
        p += strlen(p) + 1;//p指针移动到age处
        printf("%hd ", *((short*)p));
        p += 2;//p指针移动到score处
        printf("%f ", *((float*)p));
        p += 4;//p指针移动到remark处
        printf("%s\n", p);
        p += strlen(p) + 1;
        cnts++;//增加学生数
    }
    return cnts;//返回学生数
}
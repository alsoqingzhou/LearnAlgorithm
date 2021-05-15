#include <iostream>
#include <malloc.h>
using namespace std;

typedef struct {
    char* ch; //指向动态分配区域的首地址
    //分配成功返回一个连续存储空间，用str.ch[i]读取第i个字符
    int length; //存储字符串的长度
} Str;

void strAssign(Str &str, char *ch) {
    cout <<str.ch<<endl;
    //其中str为将被赋值的字符串，ch指向赋值字符串
    if(str.ch) {
        free(str.ch); //如果str原来有值，则先清空
    }

    int len = 0; //用于记录赋值字符串的长度
    char *c = ch; //c用于跟踪字符串中每个字符

    //读取赋值字符串的长度
    while(*c) {//只要c没有指向字符串末尾，继续前进
        ++len;
        ++c;
    }

    if(len == 0) { //赋值字符串为空串
        str.ch = NULL;
        str.length = 0;
        // return 1;
    } else {
        //为str重新分配需要的存储空间
        str.ch = (char *)malloc(sizeof(char) * (len+1));
        //取len+1是给结束标记\0分配空间
        c = ch;
        for(int i = 0; i <= len; ++i) {
            str.ch[i] = *c;//取出指针c当前指向的字符
            ++c; //c指向下一个字符
        }
        str.length = len;

        cout<<str.ch<<endl;

        return ;
    }
}

int main() {
    Str str;
    str.ch = (char*)"also";

    strAssign(str, (char*)"qingzhou");
    return 0;
}
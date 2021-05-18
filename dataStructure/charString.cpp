#include <iostream>
#include <malloc.h>
using namespace std;

typedef struct {
    char* ch; //指向动态分配区域的首地址
    //分配成功返回一个连续存储空间，用str.ch[i]读取第i个字符
    int length; //存储字符串的长度
} Str;

//将一个字符串赋值给另一个
int strAssign(Str &str, char *ch) {
    // cout <<str.ch<<endl;
    // cout <<ch<<endl;

    // 其中str为将被赋值的字符串，ch指向赋值字符串
    // if(str.ch) {
    //     free(str.ch); //如果str原来有值，则先清空
    //     //free运行后整个函数strAssign会立即返回，不执行下面所有代码
    // }


    int len = 0; //用于记录赋值字符串的长度
    char* c = ch; //c用于跟踪字符串中每个字符


    //读取赋值字符串的长度
    while(*c) {//只要c没有指向字符串末尾，继续前进
        ++len;
        ++c;
    }

    if(len == 0) { //赋值字符串为空串
        str.ch = NULL;
        str.length = 0;
        return 1;
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
        return 1;
    }
}

//比较两个字符串大小
int strCompare(Str s1, Str s2) {
    for(int i = 0; i < s1.length && i < s2.length; ++i) {
        //依次遍历比较两个字符串每一位，直到其中一个字符串末尾
        if(s1.ch[i] != s2.ch[i]) { //两个字符串第一次不相同的位置
            return s1.ch[i] - s2.ch[i];
            //返回结果负则s1小
        }
    }
    //跳出循环，前面字符都相同，其中一个字符串更短
    return s1.length - s2.length;
    //返回结果为负则s1小
}

//返回字符串长度
int countLength(Str st) {
    int length = 0; //累计长度
    char* c = st.ch; //追踪指针
    while(*c) {
        ++length;
        ++c;
    }
    return length;
}

//将两个字符串合并得到一个新的字符串
int merge(Str &st, Str s1, Str s2) {
    int len; //累计将合并的两个字符串总长

    len = countLength(s1) + countLength(s2);

    st.ch = (char*)malloc(sizeof(char) * (len + 1));

    for(int i = 0; i < countLength(s1); ++i) {
        st.ch[i] = s1.ch[i];
    }
    for(int i = 0; i <= countLength(s2); ++i) {
        st.ch[i + countLength(s1)]  = s2.ch[i];
    }
    st.length = len;

    cout << st.ch<<endl;
    return 1;
}

//求字串操作
int subString(Str &substr, Str str, int pos, int len) {
    //分别传入输出的子串，母串，开始找子串位置，子串长度
    if(pos<0 || pos>=str.length || len<0 || len>str.length) {
        //几种不合法的输入
        //位置超前或过后，子串过短或过长
        return 0;
    }
    if(substr.ch) {
        free(substr.ch); //原子串有值，清空，字符指针指空
        substr.ch = NULL;
    }

    //开始求子串
    if(len == 0) { //特殊情况单独处理，子串为空串
        substr.ch = NULL;
        substr.length = 0;
        return 1;
    } else {
        substr.ch = (char*)malloc(sizeof(char) * (len+1));
        int i = pos; //跟踪母串位置
        int j = 0; //跟踪子串位置

        while(i < pos+len) { //母串没走到结束位置，继续
            substr.ch[j] = str.ch[i];
            ++i;
            ++j;
        }
        //子串求出，此时j指向子串最后字符后一个位置
        substr[j] = '/0';
        substr.length = len;
        return 1;
    }
}

//串清空
int clearString(Str &str) {
    if(str.ch) {
        free(str.ch);
        str.ch = NULL;
    }
    str.length = 0;
    return 1;
}


int main() {
    Str s1, s2;
    Str ss;
    strAssign(s1, (char*)"qingzhou");
    strAssign(s2, (char*)"also");
    // printf("%d", strCompare(s1, s2));
    merge(ss, s1, s2);
    return 0;
}
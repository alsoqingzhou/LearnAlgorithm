#include <iostream>
#include <stdio.h>
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
        substr.ch[j] = '\0';
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

//简单模式匹配
int match(Str str, Str substr) {
    int i = 1, j = 1, k = i;
    //i跟踪母串，j跟踪匹配串，k记录母串开始匹配位置
    while(i <= str.length && j <= substr.length) {
            // cout <<"aaa"<<endl;
        //母串和匹配串未确认完成，继续确认
        if(str.ch[i] == substr.ch[j]) {
            //该位相同，比较下一位
            ++i;
            ++j;
        } else {
            i = ++k;//母串从之前的下一位开始匹配
            j = 1; //匹配串从头开始
        }
    }
    if(j > substr.length) { //匹配串到最后一个字符都符合
        return k; //匹配成功，返回母串匹配部分的开始位置
    } else {
        return 0; //否则匹配失败
    }
}

//KMP算法——生成next数组
void getNext(Str subString, int next[]) {
    //算法思路：假设next[j]已知，求next[j+1]

    int j = 1; //j跟踪模式串每一位，确定其next值
    int t = 0; //初始t值为next[1]的值，形成统一
    
    //作为数值看，t存储next[j]的值，即j位置前面串的最长前后缀长度加1
    //把主串考虑进来的话，t指向的是如果j位置和主串不匹配，跳转之后将和主串那个位置去比较的字符

    //当把t看作指针时，刚好指向j位置前面串的最长前缀的后一个位置
    //而t指向的这个位置的数值如果和j位置相等，
    //效果相当于比较两个新的位置，确定next[j]时的最长前缀向后拓展一个位置（即t指的位置），要确定最长前后缀的串后拓展一个位置（即j这个位置）
    //如果这两个位置相等，则next[j+1]的最长前后缀长度为上一次长度加一，即t+1
    
    //如果这两个位置不相等，则无法直接利用上一个得到的next[j]的值
    //此时，需要重新确定t的数值。这种状态可以描述为t位置和j位置的字符不等，而t前面和j前面都匹配
    //而这正是模式匹配中的要用next数组跳转的状态，即此时next数组的求值要调用自己已经求出的值
    //根据KMP算法的思想，当该位置不匹配是，t指针要跳转，跳转的目的是使得最终的t指针指向的字符和j指针指向的相等，即上一段描述的状态，也就是可以使用之前成果next[j]的状态
    //而如何跳转，就是看next[t]的数值，它将告诉t跳到哪个位置和j指针的字符去比较
    //如果最糟糕的情况，next[t]为0这种特殊情况，那么next[j+1]前面的最长前后缀长度就是0，next[j+1] = 1
    next[1] = 0;
    while(j < subString.length) {

        //如果此时t已经跳指向第一个位置，即t=1,而此时和j位置的字符不等，则进入else，t = next[1] = 0
        // 此时满足if判断中的t==0条件，此时意味着j+1之前的字符串最长前后缀长度为0，则next[j+1] = t+1 = 1,刚好满足此特殊条件
        if(t == 0 || subString.ch[j] == subString.ch[t]) {
            next[j + 1] = t + 1;
            ++t; //最长前后缀长度可以+1
            ++j; //要确定最长前后缀的串可以后延一位
        } else {
            t = next[t];
        }
    }
}

// KMP算法实现
int KMP(Str str, Str subString, int next[]) {
    int i = 1; //跟踪主串位置
    int j = 1; //跟踪模式串位置
    while(i <= str.length && j <= subString.length) {
        if(j == 0 || str.ch[i] == subString.ch[j]) {
            //j=0的情况意味着j指向第一位，仍不匹配，则进入else，j被赋值next[1] = 0
            //此时刚好该if也能处理这种特殊情况。
            
            ++i; //特殊情况下这句话表示主串比较当前字符下一个
            ++j; //特殊情况下++j刚好让j=1,即模式串从第一个位置开始比较
        } else {
            j = next[j]; //i和j所指字符不匹配，next数值告诉j如何跳转
        }
    }
    if(j > subString.length) {//进入该条件说明模式串比较完最后一个字符都匹配，++之后刚好大于长度
        return i - subString.length; //此时i指向主串最后一个匹配位置后一位
    } else { //匹配失败
        return 0;
    }
}

int main() {
    Str s1, s2;
    strAssign(s1, (char*)"qingzhou");
    strAssign(s2, (char*)"zhou");
    // printf("%d", strCompare(s1, s2));
    // merge(ss, s1, s2);
    printf("%d", match(s1, s2));
    return 0;
}
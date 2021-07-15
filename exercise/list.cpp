#include <stdio.h>
#include <iostream>
using namespace std;

const int maxsize = 50;
const int initsize = 100;

/*线性表（静态分配）结构体定义*/
typedef struct {
    int data[maxsize]; //默认整型数组
    int length;
} SSqList;

/*线性表（动态分配）结构体定义*/
typedef struct {
    int *data;
    int maxsize, length;
} DSqList;

//Q2.2.3-1
bool deleteMin(SSqList &L, int &value) {
    
    if(L.length == 0) {return false;} //线性表为空返回

    value = maxsize; //记录最小值
    int k; //记录最小值的位置

    for(int i = 0; i < L.length; ++i) {
        if(L.data[i] < value) {
            value = L.data[i];
            k = i;
        }
    }
    // 跳出循环，找到最小值及其位置
    L.data[k] = L.data[L.length - 1];
    --L.length;
    return true;
}

// Q2.2.3-2
void reverse(SSqList &l) {
    int pole = (l.length - 1) / 2; //翻转轴
    for(int i = 0; i <= pole; ++i) {
        int temp = l.data[i];
        l.data[i] = l.data[l.length-i-1];
        l.data[l.length-i-1] = temp;
    }
}

// Q2.2.3-3
void deleteAllX(SSqList &l, int x) {
    int k = 0; //用k记录表中非x,即需要保留的数字个数
    for(int i = 0; i < l.length; ++i) {
        if(l.data[i] != x) {
            l.data[k] = l.data[i]; //前k个元素是保留元素，则数组中下标k位置可以安放当前不为x的元素
            ++k; //保留元素加一
        }
    }
    // 跳出循环，删减完毕
    l.length = k; //更新顺序表长度
}

// Q2.2.3-4 从有序顺序表中删除s到t之间元素
bool del_s_t(SSqList &l, int s, int t) {
    if(s > t || l.length == 0) {
        return false;
    }

    int i, j;
    for(i = 0; i < l.length&&l.data[i] < s; ++i); //i标记第一个大于s的位置，从此开始删除
    if(i == l.length) {
        return true; //没有位于s,t之间的元素
    }
    for(j = i; j < l.length&&l.data[j] <= t; ++j) //j标记第一个大于t的位置，从此开始保留

    for(; j < l.length; ++i, ++j) {
        l.data[i] = l.data[j];
    }
    l.length = i;
    return true;
}

// Q2.2.3-5 从顺序表中删除s到t之间的元素
bool delete_s_t(SSqList &l, int s, int t) {
    int k = 0; //k记录要删除的元素个数
    if(s > t || l.length == 0) {
        return false;
    }
    for(int i = 0; i < l.length; ++i) {
        if(s <= l.data[i] <= t) {
            ++k;
        } else {
            l.data[i-k] = l.data[i];
        }
    }
    l.length = l.length - k;
    return true;
}

// Q2.2.3-6 从有序表中删除相同元素
bool deleteSame(SSqList &l) {
    int k = l.data[0]; //k跟踪表中元素是否变化
    int i, j = 0; //i是循环指针，j记录重复元素总个数
    if(l.length == 0) {
        return false;
    }
    for(i = 1; i < l.length; ++i) {
        if(l.data[i] == k) {
            ++j;
        } else {
            k = l.data[i];
            l.data[i-j] = l.data[i];
        }
    }
    l.length -= j;
    return true;
}
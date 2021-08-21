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

// Q2.2.3-7 合并两个有序表得到一个新的有序表
    // 算法思想：划出一块两个表长之和的空间给新表，两个指针遍历两个表，选取小的纳入新表
void mergeTwo(SSqList a, SSqList b, SSqList &c) { //c为新表，传入引用类型
    int i = 0, j = 0, k = 0;
    while(i < a.length && j < b.length) {
        while(a.data[i] <= b.data[j]) {
            c.data[k] = a.data[i];
            ++i;
            ++k;
        }
        while(b.data[j] < a.data[i]) {
            c.data[k] = b.data[j];
            ++j;
            ++k;
        }
    } //其中某个表传完，跳出循环，剩下的表接上
    while(i < a.length) {
        c.data[k] = a.data[i];
        ++i; ++k;
    }
    while(j < b.length) {
        c.data[k] = b.data[j];
        ++j; ++k;
    }
}

// Q2.2.3-8 长数组中交换两个子线性表的位置，从a1-am,b1-bn变为b1-bn,a1-am
// 算法思想，整个数组反转，前n个元素表反转，后m个元素表反转
void reverseRange(SSqList &l, int a, int b) {
    while(a < b) {
        swap(l.data[a++], l.data[b--]);
    }
}
void reverseAB(SSqList a, int m, int n) {
    reverseRange(a, 0, a.length-1);
    reverseRange(a, 0, n-1);
    reverseRange(a, n, m-1);
}

// Q2.2.3-9 查找，交换或插入
int search_exchangeORinsert(SSqList a, int key) {
    int low = 0, high = a.length-1, mid;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(a.data[mid] == key) { 
            break;
        }  else if(a.data[mid] < key) {
            low = mid + 1;
        } else if(a.data[mid] > key) {
            high = mid - 1;
        }
    }
    if(a.data[mid] == key && mid != a.length-1) { //找到且有后继元素，则交换
        int temp = a.data[mid+1];
        a.data[mid+1] = a.data[mid];
        a.data[mid] = temp;
        return;
    } else if(a.data[mid] == key && mid == a.length-1) { //找到但没有后继
        return 1; //直接返回   
    } else if(low > high) { //查找失败，交换
        int i;
        for(i = a.length-1; i >= low; --i) {
            a.data[i+1] = a.data[i];
        }
        a.data[i+1] = key;
        return;
    }
}

// Q2.2.3-11 寻找两个升序序列的中位数
// 算法思想：根据两个序列中长度确定中位数位置数值。两个指针分别从两个序列开始比较移动，同时设置一个计数器，有指针移动就加一
// 注：下面代码适用于两个任意长度的序列，若两个序列等长，则不用考虑指针越界的情况
int find_mid(int s1[], int s2[], int n1, int n2) {
    int mid; //求中位数位置
    if((n1 + n2) % 2 == 0) {
        mid = (n1 + n2) / 2;
    } else {
        mid = (n1 + n2) / 2 + 1;
    }

    int i = 0, j = 0; //两个序列的指针
    int k = 0; //计数器
    int flag_i = 0, flag_j = 0; //指针移动标记

    while(k != mid) {
        flag_i = flag_j = 0;
        if(s1[i] < s2[j] && i < n1 && j < n2) {
            ++i;
            ++k;
            flag_i = 1;
        } else if (s1[i] >= s2[j] && i < n1 && j < n2) {
            ++j;
            ++k;
            flag_j = 1;
        } else if (i >= n1 || j >= n2) {
            break;
        }
    }

    if(i >= n1) {
        flag_j = 1;
        while(k != mid) {
            ++j;
            ++k;
        }
    }
    if(j >= n2) {
        flag_j = 1;
        while(k != mid) {
            ++i;
            ++k;
        }
    }

    if(flag_i == 1) {
        return i-1;
    }
    if(flag_j == 1) {
        return j-1;
    }

}

// Q2.2.3-12 寻找数组中的主元素
int find_main(int a[], int n) {
    int c; //记录可能的主元素数值
    int num = 0; //计数器

    for(int i = 0; i < n; ++i) {
        if(num == 0) { //目前没有相同的数
            c = a[i];
            ++num;
        } else {
            if(c == a[i]) {
                ++num;
            } else {
                --num;
                c = a[i];
            }
        }
    }

    if(num > 0) {
        num == 0;
        for(int i = 0; i < n; ++i) {
            if(a[i] == c) {
                ++num;
            }
        }
    }
    if(num > n/2) {
        return c;
    } else {
        return -1;
    }
}

// Q2.2.3-13 找出一个数组中未出现的最小整数
// 算法思想：遍历数组，对每一个正整数，在辅助数组中该正整数对应位置标记
int find_maxN(int a[], int n) {
    int b[maxsize];
    for(int i = 0; i < n; ++i) {
        if(a[i] > 0) {
            b[a[i]] = 1;
        }
    }
    int i = 1;
    while(b[i] != 0){
        ++i;
    }
    return i;
}
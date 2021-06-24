#include <stdio.h>
#include <iostream>
using namespace std;

int R[10] = {2, 5, 3, 7, 1, 8, 4, 6, 9, 6};

// 直接插入排序
void InsertSort(int R[], int n) {
    for(int i = 1; i < n; ++i) { //数组下标0位置默认已排好序，从1位置开始向前面排好序的数组中选择合适位置插入
        int temp = R[i]; //每个外层循环排序一个数，用temp暂存待排序数字
        int j = i - 1; //i-1向前的位置已排序完毕，用j确定temp的插入位置

        while(j >= 0 && temp < R[j]) { //没有比较到第一位，且待定数字小于j位置数字，该层后移循环继续
            R[j + 1] = R[j]; //后移一位
            --j; //向前移动比较
        }//跳出循环，可能是temp大于j位数字可插入，或已经到达数组0位置

        R[j + 1] = temp;
    }
}

// 冒泡排序
void BubbleSort(int R[], int n) {
    for(int i = n-1; i >= 1; --i) { //排序趟数，i标记每趟冒泡排序停止位置，一趟排定一个位置
        int flag = 0; //每趟排序前重置flag为0，检测该趟排序是否发生交换，若没有则整个数组有序，直接返回
        // 开始该趟冒泡排序
        for(int j = 0; j < i; ++j) {
            if(R[j] > R[j+1]) { //前比后大，满足交换条件
                int temp = R[j+1];
                R[j+1] = R[j];
                R[j] = temp;
                flag = 1; //发生交换，flag置为1
            }
        }
        if(flag = 0) {
            return;
        }
    }
}

int main() {
    BubbleSort(R, 10);
    for(int i = 0; i < 10; ++i) {
        cout<< R[i] <<endl;
    }
    return 1;
}
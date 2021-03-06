#include <stdio.h>
#include <iostream>
using namespace std;

int R[10] = {2, 5, 9, 7, 1, 8, 4, 6, 6, 3};

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

// 快速排序
void QuickSort(int R[], int low, int high) { //low及其左侧都是小于等于枢轴的数，high及其右侧都是大于等于枢轴的数
    int temp; //保存每趟循环的枢轴值
    int left = low, right = high; //用left和right记录初始的low和high的位置，方便后期递归

    if(low < high) { //如果刚进入函数是low = high, 则说明本次递归的序列枢轴一边只剩一个数字，则无需排序，跳出这一侧的递归
        //满足本次递归函数的条件，准备开始本轮排序
        temp = R[low]; //temp暂存枢轴值

        while(low < high) {//该层循环完成一趟选择排序，使得枢轴左边都是小于等于的数，右边都是大于等于的数
            //该循环寻找比枢轴小的数值
            while(low < high && R[high] >= temp) {--high;} //跳出循环，找到比枢轴小的数值
            R[low] = R[high]; //安放到low位置

            //该循环寻找比枢轴大的数值
            while(low < high && R[low] <= temp) {++low;} //跳出循环，找到比枢轴大的数值
            R[high] = R[low];
        }
        // 跳出循环，low和high相遇，此位置是枢轴位置
        R[low] = temp;
        QuickSort(R, left, low-1); //对枢轴左侧数字快排
        QuickSort(R, high+1, right); //对枢轴右侧数字快排
    }   
}

// 简单选择排序
void SelectSort(int R[], int n) {
    int i, j, k; //i进行n趟选择，j遍历寻找剩余无序数组中最小值，k指向最小值
    int temp; //交换的辅助变量

    for(i = 0; i < n; ++i) {
        k = i; //先默认剩余无序数组第一个数最小，接下来更新
        for(j = i+1; j < n; ++j) {
            if(R[j] < R[k]) {
                k = j;//k更新始终指向剩余无序数组中最小值
            }
        } //跳出循环，此时k指向剩余无序数组中最小值
        // 将最小值交换至无序数组开始位置，实现递增排序
        temp = R[i];
        R[i] = R[k];
        R[k] = temp;
    }
}

//堆排序
// 将k对应的根结点的子树调整为小根堆
void HeapAdjust(int R[], int k, int len) {
    R[0] = R[k]; //数组空闲的0位置暂存k根结点的数值
    // 下面整个循环的目的是为k位置的数值寻找合适的落脚点，而k位置不断改变过程的原则是让它的孩子们中最小的上浮
    for(int i = 2*k; i <= len; i*=2) { //i指向k的左孩子，i<=len为了确保对应位置有结点
        
        if(i<len && R[i+1]<R[i]) { //该条件判断确保i指向k如果左右孩子都有的话，指向最小的孩子
            i++;
        }

        if(R[0] < R[i]) {break;} //该条件判断若根结点大于左右孩子，则不需要调整，直接跳出
        else { //否则将最大的孩子放到k位置
            R[k] = R[i];
            k = i; //k下沉到被转移走数值的i位置，进入下一个循环寻找合适的停止位置
        }
        // 如果还会再进入下一次循环的话，说明k可能待的位置还不符合它小元素的身份，下一次循环i会*2，而k此时已经指向i的位置，则2i为新的k的左孩子。
    } //跳出循环，找到k对应结点的合适安放位置
    R[k] = R[0]; //安放寄存在0位置的原来k指向的数值
}
void HeapSort(int R[], int len) { //len为结点总数，即数组内元素个数
    // 创建小根堆
    for(int i = len/2; i > 0; --i) { //len/2位置为非叶子结点在数组中最后位置，i>0因为数组从下标1位置开始存储
        HeapAdjust(R, i, len);//将每个根结点的子树调整为小根堆
    }
    //利用初始化的小根堆进行递减排序，不断将数组首位即最小元素与未排序部分末尾交换，实现降序排序
    for(int i = len; i >= 2; --i) {
        //将目前无序的数组末尾和首位(即数组中最小的元素)交换
        int temp = R[i];
        R[i] = R[1];
        R[1] = temp;
        HeapAdjust(R, 1, i-1);
    }
}

// 二路归并排序
int A[]; int n = 10; //n为将要归并排序的A数组的长度
void merge(int A[], int low, int mid, int high) {
    int *B = (int *)malloc(n * sizeof(int)); //辅助数组B

    for(int i = low; i <= high; ++i) {
        B[i] = A[i]; //该循环将A从low到high这需要归并的连续两部分的全部复制一份到辅助数组
    }

    // 下面的循环从i开始以及j开始的两路中选择较小的排入A中
    int i, j, k;
    for(i = low, j = mid+1, k = i; i <= mid && j <= high; ++k) {
        if(B[i] <= B[j]) {
            A[k] = B[i++]; //排进较小的，被排走数组的指针加一
        } else {
            A[k] = B[j++];
        }
    }

    while(i <= mid) {
        A[k++] = B[i++];
    }
    while(j <= high) {
        A[k++] = B[j++];
    }
}
void mergeSort(int A[], int low, int high) {
    if(low < high) {
        int mid = (low + high) / 2;
        mergeSort(A, low, mid); //对左边进行二路归并排序
        mergeSort(A, mid+1, high); //对右边进行二路归并排序
        merge(A, low, mid, high); //将上面排序好的两路归并
    }
}

int main() {
    HeapSort(R, 10);
    for(int i = 0; i < 10; ++i) {
        cout<< R[i] <<endl;
    }
    return 1;
}
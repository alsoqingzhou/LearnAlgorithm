#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

// Q8.3.3-2 双向冒泡排序算法
// 实现思想：奇数趟，从前向后冒泡，将大数向后冒。偶数趟从后向前冒，将小数向前冒
void doubleBubbleSort(int a[], int n) {
    int low = 0, high = n - 1; //两个方向冒泡的边界，一段冒出一个数后边界相应缩小
    bool flag = true; //标记本趟是否有冒出，没有则说明已经有序，跳出循环
    while(low < high && flag) {
        flag = false; //标记初始化
        // 本趟从前向后冒出大数
        for(int i = low; i < high; ++i) { //每趟冒泡都在边界内进行
            if(a[i] > a[i+1]) {
                swap(a[i], a[i+1]); //有逆序，交换
                flag = true;
            }
        }
        //本趟冒泡完毕，边界收缩一
        --high;
        // 本趟从后向前冒出小数
        for(int i = high; i > low; --i) {
            if(a[i] < a[i-1]) {
                swap(a[i], a[i-1]);
                flag = true;
            }
        }
        ++low;
    }
}

// Q8.3.3-3 顺序表奇偶数分离
// 实现思想：顺序存储，表头表尾两个指针，表头指针及其左边都是奇数，表尾指针及其右边都是偶数
// 参考快速排序的枢轴划分，利用两个指针划分
typedef struct {
    int *a;
    int length;
} SSTable;

void paritySep(SSTable st) {
    int temp = st.a[0]; //空出第一个位置
    int i = 0, j = st.length-1;
    while(i != j) {
        while(st.a[j] % 2 == 0) {
            --j; //是偶数，j指针前移
        }//遇到奇数，跳出循环，处理奇数
        st.a[i] = st.a[j];
        ++i;

        while(st.a[i] % 2 == 1) {
            ++i; //是奇数，i指针后移
        }//遇到偶数，跳出循环处理
        st.a[j] = st.a[i];
        --j;
    }//i和j相遇，跳出循环
    st.a[i] = temp;
}

// Q8.3.3-4 快速排序枢轴随机产生
int partition2(int a[], int low, int high) {
    int rand_index = low + rand()%(high-low+1); //获得随机位置为枢轴
    swap(a[rand_index], a[low]); //交换随机位置和数组开始位置

    int pivot = a[low]; //获取枢轴值
    int i = low; //i及其左边都是小于等于枢轴值的

    for(int j = low+1; j <= high; ++j) { //遍历剩余所有位置，寻找小于枢轴的值
        if(a[j] < pivot) { //找到小于枢轴的位置，交换到前面
            swap(a[++i], a[j]); //++i得到的位置一定大于枢轴，将其与前方找到的小于枢轴值的位置交换
        }
    } //跳出循环，此时i停止的位置处的值也是小于枢轴的，加下来将这个位置与枢轴交换即可定下枢轴位置
    swap(a[i], a[low]);
    return i; //返回枢轴位置
}

// Q8.3.3-5 找出数组中第k小的元素
// 算法思想；对数组进行一趟快速排序，确定枢轴位置，判断该位置与k位置大小，不断缩短范围进行枢轴确定
int partition(int a[], int low, int high) { //普通快速排序，确定一个枢轴
    int temp = a[low];
    while(low < high) {
        while(a[high] > temp) --high;
        a[low] = a[high]; ++low;

        while(a[low] < temp) ++low;
        a[high] = a[low]; --high;
    } //跳出循环，low与high相遇，该位置即枢轴位置
    a[low] = temp;
    return low; //返回枢轴位置
}
int searchK(int a[], int n, int k) {
    int low = 0, high = n-1; //两个指针分别指向数组首尾位置
    while(low < high) {
        int pole = partition(a, low, high);
        if(pole == k) {
            return a[pole];
        } else if(pole < k) {
            low = pole + 1;
        } else {
            high = pole - 1;
        }
    }
    
}
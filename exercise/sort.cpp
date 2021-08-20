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

// Q8.3.3-6 划分一个数组为两部分，两部分个数之差最小，两部分和最大
// 算法思想：即寻找中位数（的前一位），即找出数组中第n/2向下取整个最小位置，利用上面的算法，将其中的k赋值
int partition2(int a[], int low, int high) {
    int temp = a[low];
    while(low < high) {
        while(a[high] > temp) --high;
        a[low] = a[high]; ++low;

        while(a[low] < temp) ++low;
        a[high] = a[low]; --high;
    } //跳出循环，low = high
    a[low] = temp;
    return low;
}
int divide(int a[], int low, int high, int n) {
    int k = n / 2;
    int i; //划分位置
    int s1, s2; //两部分和
    while(low < high) {
        int pole = partition2(a, low, high);
        if(pole == k) {
            i = pole;
            break;
        } else if(pole < k) {
            low = pole + 1;
        } else {
            high = pole - 1;
        }
    }
    for(int j = 0; j < i; ++j) s1 += a[j];
    for(int j = i; j < n; ++j) s2 += a[j];
    return s2 - s1;
}

// Q8.3.3-7 荷兰国旗问题
void sort_3_Color(char a[], int n) {
    int i, j, k;
    i = 0; //i之前都为红色
    k = n-1; //k之后都为蓝色
    j = 0; //遍历数组指针
    while(j < n) {
        switch(a[j]) { //根据遍历颜色判断
            case 'red': swap(a[j], a[i]); ++i; ++j; //两者都可前移，不必担心，交换过来的必定不是红色，移动不会错过
            // 因为j和i从同一位置出发，如果第一个就是红色，则两者交换不变，一同前移
            // 因此在整个移动过程中，红色都只会在i左边，i处不会出现红色

            // i和j只有一种情况
            // 即：i白色，j红色，正常交换
            // 其他：i红色，j其他颜色，不会出现，因为j必定经过过i的红色，在那次经过时已经完成交换了
            
            case 'white': ++j; //白色不操作

            case 'blue': swap(a[j], a[k]); --k; //遍历指针j不移动，防止交换过来的颜色仍为蓝色，若移动后必会错过
        }
    }
}


#include <stdio.h>

int a[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};

void sort(int a[], int m, int n) {
    int i,j;//要在for循环之外调用i，j的数值，故定义在外面
    int temp;//保存当前要排序的元素数值
    
    for(i = m; i < m + n; i++) {//对后n个元素依次向前面m个元素中插入排序
        temp = a[i];
        for(j = i - 1; j >= 0 && a[j] > temp; j--) {
            a[j + 1] = a[j];//对a[i]直到a[0]的每一个元素,只要大于temp就后移一个
        }
        a[j + 1] = temp;//a[j]<temp,比较结束,留出空位在a[j+1]
    }
}

int main() {
    sort(a, 5, 5);
    for(int i = 0; i < 10; i++){
        printf("%d", a[i]);
    }

    return 0;
}
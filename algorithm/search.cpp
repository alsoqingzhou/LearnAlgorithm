#include <stdio.h>

typedef struct {
    int *elem; //动态分配的顺序表的开始指针
    int TableLen; //保存顺序表的长度
} SeqList;

// 利用哨兵提高查找效率，找到及时停止
int Search(SeqList L, int key) {
    L.elem[0] = key; //顺序表0位置不保存信息，留给安放待查找的哨兵
    //重点在于下面的for循环，用于移动指针，
    for(int i = L.TableLen-1; L.elem[i] != key; --i);
    //若找到key,则跳出循环，i即key的位置
    //若没有找到key, 则循环到0位置遇到哨兵退出循环，返回0，表示查找失败
    return i;
}
#include <stdio.h>
#include <iostream>
using namespace std;

int const maxsize = 10010;

// 矩阵转置
void matrixTrans(int A[][maxsize], int B[][maxsize], int row, int col) {
    for(int i = 0; i < row; ++i) { // 该循环对A而言遍历每一行，对B而言遍历每一列
        for(int j = 0; j < col; ++j) { // 该循环对A而言遍历一行内每一列，对B而言遍历一列内每一行
            B[j][i] = A[i][j];
        }
    }
}

// 矩阵相乘
void matrixMulti(int C[][maxsize], int A[][maxsize], int B[][maxsize], int row, int col, int n) {
    for(int i = 0; i < row; ++i) { // 该层遍历A矩阵每一行
        for(int j = 0; j < col; ++j) { // 该层遍历B矩阵每一列
            // 对于A的i行的元素与B的j列的元素，个数相等，都为n
            // 接下来的循环将它们对应相乘再加和，得到乘积矩阵C的[i][j]位置元素值
            C[i][j] = 0; // 初始化为0
            for(int k = 0; k < n; ++k) { // n的值表示i行有n列或者j列有n行个元素
                C[i][j] += A[i][k]*B[k][j]; // 对于A而言，是i行各列元素，于B而言，是j列各行元素
            }
        }
    }
}

// 三元组建立稀疏矩阵
void createTriMat(float A[][maxsize], float B[][3], int row, int col) {
    int k = 1;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(A[i][j] != 0) {
                B[k][0] = A[i][j];
                B[k][1] = i;
                B[k][2] = j;
                ++k;
            }
        }
    }
    B[0][0] = k; //记录矩阵非零元素个数
    B[0][1] = row; //记录矩阵行数
    B[0][2] = col; //记录矩阵列数
}

void print(float B[][3]) {
    int k = 1;
    for(int i = 0; i < B[0][1]; ++i) {
        for(int j = 0; j < B[0][2]; ++j) {
            if(i == B[k][1] && j == B[k][2]) {// 依次遍历的行列为非零元素位置，输出对应元素
                cout << B[k][0] << " ";
            } else { // 不符合，则该位置没有存于三元组，说明矩阵此位置为0
                cout << "0 ";
            }
        }
    }
}
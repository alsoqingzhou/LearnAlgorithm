//循环队列的定义
int const maxsize = 10010;
typedef struct {
    int data[maxsize];
    int front;
    int rear;
}cirQueue;

//判断循环队列是否为空
int isEmpty(cirQueue qu) {
    if(qu.front == qu.rear) {
        return 1;
    } else {
        return 0;
    }
}

//入队
int enQueue(cirQueue qu, int x) {
    if((qu.rear + 1) % maxsize == qu.front) {//判断是否队满
        return 0;
    }
    //准备入队
    qu.rear = (qu.rear + 1) % maxsize;//将rear指向下一个位置
    qu.data[qu.rear] = x;
    return 1;
}

//出队
int deQueue(cirQueue qu, int x) {
    if(qu.front == qu.rear) {//队空
        return 0;
    }
    //start delete
    qu.front = (qu.front + 1) % maxsize;//front指向下一个位置，即要删除的元素
    x = qu.data[qu.front];
    return 1;
}
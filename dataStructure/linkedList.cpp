// 查找元素X并删除
int findAndDelete(LNode *C, int x) {
    LNode *p, *q;
    p = C;
    // start find
    while(p->next != null) { //p指向最后一个节点，查找结束
        if(p->next->data == x) {
            break;//p的下一个结点是要查找元素，查找结束
        }
        p = p->next;//不是，跳转下一个结点
    }
    if(p->next == null) {
        return 0;//跳出循环，查找结束，p到达最后一个结点，未找到元素
    } else { //找到，是p的下一个结点
        //开始删除
        q = p->next;// q接收目标元素所在结点
        p->next = p->next->next;// 删除结点
        free(q);// 释放内存
        return 1;
    }
}

//归并两个递增链表，得到一个递增链表，采用尾插法
void merge01(LNode *A, LNode *B, LNode *&C) {// C结点本身要改变，采用引用型
    LNode *p = A->next;
    LNode *q = B->next;
    LNode *r;

    C = A;// 用A的头结点作为C的头结点
    C->next = null;// 断出C结点
    free(B); //释放B结点
    r = C; //r指向新链表的最后结点

    //开始归并
    while(p != null && q != null){// 只要原来两个链表还有元素，就要比较两者当前表头元素大小，选取小元素所在结点接上新链表
        if(p->data <= q->data) {
            r->next = p;// 此结点将成为新链表的尾结点，即当前尾结点的下一个结点
            p = p->next;// p指向链表的下一个结点
            r = r->next;// r指向新的尾结点，即当前指向的下一个结点
        } else {
            r->next = q;
            q = q->next;
            r = r->next;
        }
    }

    //某条链表已经接完，跳出循环
    if(p != null) {//q空，把p的剩余部分直接接上新链表
        r->next = p;
    }
    if(q != null) {
        r->next = q;
    }
}

// 新链表采用头插法，可实现归并后元素递减排列
void merge02(LNode *A, LNode *B, LNode *&C) {
    LNode *p = A->next;
    LNode *q = B->next;
    LNode *s;

    C = A;
    C->next = null;
    free(B);

    //start merge
    while(p != null && q != null) {
        if(p->data <= q->data) { //依然选择两者中较小的元素作为新链表的新节点
            s = p;//s永远指向新比较产生的结点
            p = p->next;//p 可以指向下一个结点了
            s->next = C->next;//新产生结点将成为新链表头结点之后，它的后面要先接当前的头结点之后
            C->next = s;//最后把新的结点接到链表头结点之后
        } else {
            s = q;
            q = q->next;
            s->next = C->next;
            C->next = s;
        }
    }

    //某个链表接完，循环结束
    if(p != null) {
        s = p;
        p = p->next;
        s->next = C->next;
        C->next = s;
    }
    if(q != null) {
        s = q;
        q = q->next;
        s->next = C->next;
        C->next = s;
    }
}
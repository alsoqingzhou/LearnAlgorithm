#include <stdio.h>
#include <malloc.h>

int a[10] = {1, 3, 7, 8, 9, 11, 14, 15, 16, 27};
int b[10] = {2, 3, 6, 7, 8, 10, 14, 18, 20, 27};

typedef struct LNode {
    int data;
    struct LNode *next;
}LNode;

LNode *A, *B;

LNode* create(int list[], int n, LNode *&L){
    LNode *r;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    r = L;

    for(int i = 0; i < n; i++){
        LNode *s;
        s = (LNode*)malloc(sizeof(LNode));
        r->next = s;
        s->data = list[i];
        s->next = NULL;
        r = s;
    }
    return L;
}

void different(LNode *A, LNode *B) {
    LNode *p = A;
    LNode *q = B;
    LNode *r;
    
    //start diff
    while(p->next != NULL && q->next != NULL) {
        if(p->next->data < q->next->data) {
            p = p->next;
        } else if(p->next->data > q->next->data) {
            q = q->next;
        } else {//两者下一个结点出现相同元素，删除p的下一个结点
            r = p->next;
            p->next = r->next;
            r->next = NULL;
            free(r);
        }
    }
}

int main() {
    LNode *f = create(a, 10, A);
    create(b, 10, B);

    different(A, B);
    while(f->next != NULL) {
        printf("%d ", f->next->data);
        f = f->next;
    }

    return 0;
}
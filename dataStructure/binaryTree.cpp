#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;

// 二叉树结点定义
typedef struct BTNode {
    char data;

    struct BTNode* lchild;
    struct BTNode* rchild;
} BTNode;

void Order(BTNode *p){   
    if(p != NULL) {
        Visit(p); // 先序遍历

        Order(p->lchild);

        Visit(p); // 中序遍历

        Order(p->rchild);

        Visit(p); // 后序遍历
    }
}
void Visit(BTNode* p) {
    printf("%d", p->data);
}

// 利用二叉树计算存储在其中的表达式
int op(int A, int B, char op) {
    if(op = '+') {return A + B;}
    if(op = '-') {return A - B;}
    if(op = '*') {return A * B;}
    if(op = '/') {return A / B;}
}

int compute(BTNode *p) {
    int A, B; //保存左右子树的值
    if(p != NULL) {
        if(p->lchild != NULL && p->rchild != NULL) { 
            //左右子树都存在的结点才访问
            //用A获取左子树数据，B获取右子树数据
            //遍历的每一层A，B都只保存该层结点的孩子数值
            A = compute(p->lchild);
            B = compute(p->rchild);
            return op(A, B, p->data);//集齐A，B返回compute函数运算结果
        } else {
            // 处理叶子结点
            return p->data - '0'; //叶子结点必为数值，返回字符转换后数值
        }
    } else { //二叉树为空树 
        return 0;
    }
}

// 求二叉树深度
// 基本思想：获取左子树和右子树深度，则该树深度为两者中较大的加一
// 递归结束条件：到达叶子结点，则叶子结点的左右子树为空，返回得到叶子结点（作为一个独立的树时）深度为一
int getDepth(BTNode *p) {
    int left, right;
    if(p == NULL) {
        return 0; //叶子结点的左右子树为空，空树深度为一
    } else {
        left = getDepth(p->lchild);
        right = getDepth(p->rchild);
        return max(left, right) + 1;
    }
}

// 二叉树查找值为key的结点是否存在
void search(BTNode *p, BTNode *&q, int key) {
    if(p != NULL) {
        if(p->data == key) { // 到达结点后先对该结点数据进行访问判断，故采用的先序遍历
            q = p;
        } else {
            search(p->lchild, q, key);
            search(p->rchild, q, key);
        }
    }
}

// 剪枝操作优化上述搜索代码
void search2(BTNode *p, BTNode *&q, int key) {
    if(p != NULL) {
        if(p->data == key) {
            q = p;
        } else {
            search2(p->lchild, q, key);
            if(q == NULL) { //左子树如果没有找到，才会搜索右子树
                search2(p->rchild, q, key);
            }
        }
    }
}

// 输出先序遍历第k个结点的值
// 计数i应放在函数体外作为全局变量
int i = 1; //用于计数访问到第几个结点

void printK(BTNode *p, int k) {
    // 初始p指向根结点，即访问到序列第一个结点
    if(p != NULL) {
        if(i == k) {
            cout << p->data<<endl;
            return;
        } else {
            ++i; // 将访问下一个结点，计数加一
            printK(p->lchild, k);
            printK(p->rchild, k);
        }
    }
}

// 为构造不同顺序遍历的模板，换种写法
int n = 0; //注意是访问计数器，不是遍历结点计数器，没有访问结点之前为0
// 这样对所有顺序访问都是公平的
// 上面写法计数器初始值为1，有默认遍历到第一个结点即访问，默认了先序遍历
void printFun(BTNode *p, int k) {
    if(p != NULL) {
        //下面这部分即访问代码
        ++n;//准备访问当前p遍历指向的结点，计数器加一
        if(k == n) {
            //如果是访问的第k个，满足条件打印
            cout <<p->data<<endl;
            return; //跳出递归
        }
        // 访问代码到此结束

        // 如果是中序，后序，将上面几行代码放到下面两行中间，末尾
        printFun(p->lchild, k);
        // 放这里中序遍历
        printFun(p->rchild, k);
        // 放这里后序遍历
    }
}

// 层次遍历
int const maxsize = 10010;
void level(BTNode *p) {
    // 先创建一个队列用于从左向右保存每一层的结点值
    int front, rear;
    BTNode *que[maxsize]; //该数组构建循环队列，其中保存的是结点的指针
    front = rear = 0;
    BTNode *q; // 该二叉树指针指向将要出队的元素

    // 开始层次遍历
    if(p != NULL) { //只要不是空结点，就要入队出队遍历
        rear = (rear+1) % maxsize;
        que[rear] = p; //p为根节点，此时根节点入队
        while(front != rear) {// 只要队列不空，循环继续
            front = (front + 1) % maxsize;//队首出队
            q = que[front];
            Visit(q);

            if(q->lchild != NULL) { //有左孩子，左孩子入队
                rear = (rear + 1) % maxsize;
                que[rear] = q->lchild;
            }
            if(q->rchild != NULL) { //有右孩子，右孩子入队
                rear = (rear + 1) % maxsize;
                que[rear] = q->rchild;
            }

        }
    }
}

// 层次遍历求二叉树最大宽度
typedef struct {
    BTNode *p; //指向二叉树的结点的指针
    int level; //保存结点的层数
} queue;

int maxWidth(BTNode *r) { //传入二叉树根节点
    // 利用新定义的结构体初始化用于保存遍历结果的队列,采用结构体数组
    queue que[maxsize];
    int front, rear;
    front = rear = 0;

    int levNum = 0;
    BTNode *s; //指向当前出队的结点的指针
    if(r != NULL) {
        // 根节点入队
        ++rear; //假设队列长度足够，不采用循环队列
        que[rear].p = r;
        que[rear].level = 1; //根结点层数为1
        
        while(front != rear) {//队列未出队完成，循环继续
            ++front; //根节点出队，注意只是访问，没有删除
            s = que[front].p; //访问目的一，获取当前结点指针
            levNum = que[front].level; //访问目的二，获取当前结点层数，以便给孩子层数赋值
            
            if(s->lchild != NULL) {
                ++rear;
                que[rear].p = s->lchild;
                que[rear].level = levNum + 1;
            }
            if(s->rchild != NULL) {
                ++rear;
                que[rear].p = s->rchild;
                que[rear].level = levNum + 1;
            }
        } // 循环结束，所有结点都保存在que数组中
        // 开始找最大层数
        int max = 0;
        for(int i = 1; i <= levNum; ++i) { //循环每一层
            int n = 0; //临时保存当前层的节点数
            for(int j = 1; j <= rear; ++j) {
                //该层循环从队首开始，一直走到队尾、
                // 由于不知道每一层有多少个结点，因此只能遍历整个队列，确定是不是当前层的结点
                if(que[j].level == i) { // 如果是当前层的
                    ++n; //当前层结点数加一
                }
                if(n > max) {//如果当前层结点数超过目前确认的最大值，更新最大值
                    max = n;
                }
            }
        }
        return max;
    } else { //二叉树为空，返回宽度0
        return 0;
    }
}

// 二叉树先序非递归遍历
void preOrderNonrecursion(BTNode *bt) {
    BTNode *stack[maxsize];
    int top = -1;
    
    BTNode *p; //指向出栈将要访问的元素
    if(bt != NULL) {
        stack[++top] = bt; //根结点入栈

        while(top != -1) {
            p = stack[top--];
            Visit(p);
            if(p->rchild != NULL) {
                stack[++top] = p->rchild;
            }
            if(p->lchild != NULL) {
                stack[++top] = p->lchild;
            }
        }
    }
}

// 二叉树中序非递归遍历
//访问顺序是结点的左子树，结点，结点的右子树
//栈的实现思路是结点入栈，接着左子树入栈，一直走到没有左子树的时候
void midOrderNonrecursion(BTNode *bt) {
    // 初始化保存结点的栈
    BTNode *stack[maxsize];
    int top = -1;
    
    BTNode *p; //用于指向将要入栈的结点
    p = bt;
    if(bt != NULL) {
        //开始循环遍历
        //只要栈非空，循环继续
        //只要p还指向结点，循环继续
        while(top != -1 || p != NULL) {
            //下面的循环用于入栈左子树及其祖先结点
            while(p != NULL) { //只要左子树还存在，循环继续
                stack[++top] = p;
                p = p->lchild;
            }
            //到达左下角叶子结点，左子树不存在，跳出上面的循环
            p = stack[top]; //获取当前栈顶结点
            top--; //栈顶出栈
            Visit(p); //访问刚出栈结点
            //刚出栈结点可能只是某结点的左孩子，自己没有孩子，则算访问左子树，则下面语句将指向空，下一个循环会继续出栈访问它的根节点
            //还有一种情况，刚出栈结点还有右孩子，则此次算访问它的右孩子的根节点，下面语句将把右孩子入栈待访问
            p = p->rchild;
        }
    }
}

// 二叉树后序非递归遍历
//基本思路：在先序遍历中，交换左右结点入栈顺序，得到的序列为逆后序
//出栈后即入新栈，再出栈则将逆后序转为后序
void postOrderNonrecursion(BTNode *bt) {
    BTNode *stack1[maxsize]; int top1 = -1; //用于遍历二叉树
    BTNode *stack2[maxsize]; int top2 = -1; //用于保存stack1的出栈元素，实现求逆
    BTNode *p;

    if(bt != NULL) {
        stack1[++top1] = bt;

        while(top1 != -1) {
            p = stack1[top1--]; //p指向栈顶，出栈
            stack2[++top2] = p; //stack2顺势入栈stack1的出栈元素

            //先入左，则出栈可先出右孩子
            if(p->lchild != NULL) {
                stack1[++top1] = p->lchild;
            }
            if(p->rchild != NULL) {
                stack2[++top2] = p->rchild;
            }
        } //二叉树遍历完毕，跳出循环

        while(top2 != -1) { //stack2依次出栈方法，实现后序访问
            p = stack2[top2--];
            Visit(p);
        }
    }
}

// 二叉树线索化结构体定义
typedef struct TBTNode{
    char data;
    int lTag, rTag; //为0则有左或右孩子，为1则左右指针指向该序列遍历方式的前驱，后继
    TBTNode *lchild, *rchild;
} TBTNode;

// 二叉树中序遍历线索化
void inThread(TBTNode *p, TBTNode *&pre) { // pre指针指向当前p结点的上一个访问结点，访问的第一个结点没有前驱，故初始值为null
    if(p != NULL) {
        inThread(p->lchild, pre);

        //p的左指针指向可线索化的前驱
        if(p->lchild == NULL) {
            p->lchild = pre;
            p->lTag = 1;
        }
        //可线索化的前驱的右指针指向当前p
        if(pre != NULL && pre->rchild == NULL) { //其中pre!=null处理初始情况，即第一个结点没有前驱，pre此时为空，不需要建立右孩子线索化
            pre->rchild = p;
            pre->rTag = 1;
        }
        pre = p;
        inThread(p->rchild, pre);
    }
}

// 利用中序遍历线索化建立中序线索二叉树
void createInThread(TBTNode *root) {
    TBTNode *pre = NULL; //初始pre指向空
    inThread(root, pre);
    //在inThread函数中，初次访问的结点左孩子为空时，处理方法是左指针指空，左tag标出，为实现对二叉树中所有空指针的统一处理，现对序列最后一个结点处理
    //线索化完最后一个结点后，pre便指向了它
    pre->rchild = NULL;
    pre->rTag = 1;
}

// 找出中序线索二叉树序列第一个访问的结点
TBTNode* First(TBTNode *p) { //传入的p为根结点
    //要找的结点应在左下角，第一个左孩子为空的结点,该结点的的标志是第一个被线索化的
    while(p->lTag == 0) { //或者写p->lChild != null, 第一个被线索化的结点，因为没有前驱，其左孩子为空
        p = p->lchild;
    }
    //此时p的左孩子为空，满足条件，跳出循环
    return p;
}

// 找出中序线索二叉树序列某结点的下一个结点
TBTNode *Next(TBTNode *p) {
    if(p->rTag == 0) {
        return First(p->rchild);//访问完p之后接下来访问它的右子树，右子树第一个访问的就是p的后继
    } else {
        return p->rchild;
    }
}

// 找出中序二叉树序列最后一个访问的结点
TBTNode *Last(TBTNode *p) {
    //要找的结点在右下角，第一个右孩子为空的结点
    while(p->rchild != NULL) {
        p = p->rchild;
    }
    return p;
}

// 找出中序二叉树序列某节点的前驱
TBTNode *Prior(TBTNode *p) {
    if(p->lTag == 0) {
        return Last(p->lchild); //中序访问完p的左子树才来访问p,所以前驱是左子树最后一个访问的结点
    }
}

// 对中序线索二叉树进行遍历并访问
void InOrder(TBTNode *root) {
    for(TBTNode *p = First(root); p != NULL; p = Next(p)) {
        // 此处填写访问代码
    }
}

// 二叉树前序线索化
void preThread(TBTNode *p, TBTNode *&pre) {
    if(p != NULL) {
        //前序先访问根结点，故先对根结点进行线索化
        if(p->lchild == NULL) { 
            p->lchild = pre;
            p->lTag = 1;
        }
        if(pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rTag = 1;
        }
        //此时p和其前驱线索化完成，当前的p将成为满足条件要访问的结点的前驱，故改变pre,让其指向当前的p;
        pre = p;
        if(p->lTag == 0){ //考虑到如果当前结点的左孩子已经被线索化，再递归其左孩子便回到当前结点的前驱，陷入死循环，故应该对其是否左线索化判断
            preThread(p->lchild, pre);
        }
        if(p->rTag == 0) { //若当前p的右孩子已经被线索化，那直接递归也会进入死循环
            preThread(p->rchild, pre);
        }   
    }
}

// 线索二叉树访问函数
void VisitTBT(TBTNode *p) {
    cout <<p->data<<endl;
}

// 前序线索化二叉树的遍历
void preOrder(TBTNode *root) {
    if(root != NULL) {
        TBTNode *p = root;
        if(p != NULL) {
            while(p->lTag == 0) { //如果当前结点未被线索化
                VisitTBT(p); //先序先访问当前结点，然后跳转左孩子
                p = p->lchild;
            }
            VisitTBT(p);//当前结点以被线索化，先访问之
            p = p->rchild; //然后直接跳转右孩子
            // 此时的右孩子，要么被线索化了，则跳转到当前结点的后继结点
            // 要么没有被线索化，则当前结点没有左孩子（线索化后的左孩子指向前驱），那访问完当前结点后只能访问右孩子
        }
    }
}

// 二叉树后序线索化
void postThread(TBTNode *p, TBTNode *&pre) {
    if(p != NULL) {
        postThread(p->lchild, pre);
        postThread(p->rchild, pre);
        if(p->lchild == NULL) {
            p->lchild = pre;
            p->lTag = 1;
        }
        if(pre->rchild == NULL && pre != NULL) {
            pre->rchild = p;
            pre->rTag = 1;
        }
        pre = p;
    }   
}
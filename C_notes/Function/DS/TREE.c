#include<stdio.h>
#include<stdlib.h>
#define MAX 10000
typedef struct T{
    int d;
    struct T *le,*ri;
}tn;

//层次遍历
void layer(tn *root){
    tn *queue[MAX];
    int front,rear;
    front=rear=0;
    queue[rear++]=root;
    while(front!=rear){
        tn *tmp=queue[front++];
        /*这里对tmp进行操作*/
        if(tmp->le!=NULL){
            queue[rear++]=tmp->le;
        }
        if(tmp->ri!=NULL){
            queue[rear++]=tmp->ri;
        }
    }
}

//深度遍历
// 前序遍历（根左右）
void preorder(tn *root) {
    if (root == NULL) return;
    /*这里对root进行操作*/
    preorder(root->le);
    preorder(root->ri);
}

// 中序遍历（左根右）
void inorder(tn *root) {
    if (root == NULL) return;
    inorder(root->le);
    /*这里对root进行操作*/
    inorder(root->ri);
}

// 后序遍历（左右根）
void postorder(tn *root) {
    if (root == NULL) return;
    postorder(root->le);
    postorder(root->ri);
    /*这里对root进行操作*/
}

//深度遍历非递归
//前序
void preorder_iterative(tn *root){
    tn *stack[MAX];
    int top=-1;
    tn *cur=root;
    while(cur!=NULL||top!=-1){
        //1.将当前节点及所有左孩子压栈
        while(cur!=NULL){
            stack[++top]=cur;
            /*这里对cur进行操作*/
            cur=cur->le;
        }
        //2.弹出栈顶节点
        cur=stack[top--];
        //3.转向右子树
        cur=cur->ri;
    }
}
//中序
void inorder_iterative(tn *root){
    tn *stack[MAX];
    int top=-1;
    tn *cur=root;
    while(cur!=NULL||top!=-1){
        //1.将当前节点及所有左孩子压栈
        while(cur!=NULL){
            stack[++top]=cur;
            cur=cur->le;
        }
        //2.弹出栈顶节点并访问
        cur=stack[top--];
        /*这里对cur进行操作*/

        //3.转向右子树
        cur=cur->ri;
    }
}
//后序（相对复杂一点）
//法一：双栈法，对“根右左”压栈取反
void postorder_iterative(tn *root) {
    if (!root) return;
    tn *stack1[MAX], *stack2[MAX];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1) {
        tn *node = stack1[top1--];
        stack2[++top2] = node;   // 将节点压入第二个栈
        // 注意顺序：先左后右，因为第一个栈是后进先出，我们要先处理右子树，所以这里先压左再压右
        if (node->le) stack1[++top1] = node->le;
        if (node->ri) stack1[++top1] = node->ri;
    }
    // 输出第二个栈中的结果（后序顺序）
    while (top2 != -1) {
        tn *node = stack2[top2--];
        printf("%d ", node->d);
    }
}
//法二：单栈标记，相对节省空间
void postorder_iterative(tn *root) {
    if (!root) return;
    tn *stack[MAX];
    int top = -1;
    tn *cur = root;
    tn *prev = NULL;
    while (cur != NULL || top != -1) {
        // 走到最左
        while (cur != NULL) {
            stack[++top] = cur;
            cur = cur->le;
        }
        cur = stack[top];  // 取栈顶节点但不弹出
        // 如果右子树为空或已被访问，则访问当前节点并弹出
        if (cur->ri == NULL || cur->ri == prev) {
            printf("%d ", cur->d);
            prev = cur;
            top--;
            cur = NULL;     // 当前节点已处理，下次循环直接弹出栈中下一个
        } else {
            // 否则先处理右子树
            cur = cur->ri;
        }
    }
}

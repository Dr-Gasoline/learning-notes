#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100   // 栈和队列的最大容量

typedef int ElemType;  // 元素类型，可根据需要修改

/* ==================== 顺序栈 ==================== */
typedef struct {
    ElemType data[MAX_SIZE];
    int top;           // 栈顶元素位置，-1 表示空栈
} SeqStack;

// 初始化栈
void initStack(SeqStack *s) {
    s->top = -1;
}

// 判断栈空
bool isStackEmpty(const SeqStack *s) {
    return s->top == -1;
}

// 判断栈满
bool isStackFull(const SeqStack *s) {
    return s->top == MAX_SIZE - 1;
}

// 入栈（压栈）
void push(SeqStack *s, ElemType e) {
    // 调用前请确保栈未满，否则溢出
    s->data[++(s->top)] = e;
}

// 出栈（弹栈），返回栈顶元素
ElemType pop(SeqStack *s) {
    // 调用前请确保栈非空
    return s->data[(s->top)--];
}

// 获取栈顶元素（不出栈）
ElemType getTop(const SeqStack *s) {
    // 调用前请确保栈非空
    return s->data[s->top];
}


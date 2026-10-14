#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100   // 栈和队列的最大容量

typedef int ElemType;  // 元素类型，可根据需要修改

/* ==================== 循环队列 ==================== */
typedef struct {
    ElemType data[MAX_SIZE];
    int front;         // 队头元素位置
    int rear;          // 队尾元素位置
    int count;         // 队列中元素个数
} SeqQueue;

// 初始化队列（front=0, rear=MAX_SIZE-1, count=0）
void initQueue(SeqQueue *q) {
    q->front = 0;
    q->rear = MAX_SIZE - 1;
    q->count = 0;
}

// 判断队空
bool isQueueEmpty(const SeqQueue *q) {
    return q->count == 0;
}

// 判断队满
bool isQueueFull(const SeqQueue *q) {
    return q->count == MAX_SIZE;
}

// 入队（在队尾插入）
void enQueue(SeqQueue *q, ElemType e) {
    // 调用前请确保队列未满
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = e;
    q->count++;
}

// 出队（删除队头元素并返回）
ElemType deQueue(SeqQueue *q) {
    // 调用前请确保队列非空
    ElemType e = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return e;
}

// 获取队头元素（不出队）
ElemType getFront(const SeqQueue *q) {
    // 调用前请确保队列非空
    return q->data[q->front];
}
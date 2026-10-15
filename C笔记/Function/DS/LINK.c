/*链表的增删改查一定要注意 空链表/链表头/链表尾 的特殊情况，做好特判*/

#include<stdio.h>
#include<stdlib.h>

typedef struct N{
    long long num;
    struct N *prev;
    struct N *next;
}sorted_node;

typedef struct M{
    long long data;
    struct M *next;
    struct M *prev;
}un_node;

//双向有序链表，按num值从小到大进行插入
void sorted_insert(sorted_node *p,sorted_node **list,sorted_node **tail){
    /*特殊情况剪枝*/
    if(p==NULL) return;
    p->next=p->prev=NULL;
    //空链表
    if(*list==NULL){
        *list=*tail=p;
        return;
    }
    //链表尾
    if (*tail!=NULL&&p->num>=(*tail)->num){
        p->prev=*tail;
        (*tail)->next=p;
        *tail=p;
        return;
    }
    /*一般处理*/
    sorted_node *ptr;
    for(ptr=*list;ptr!=NULL&&ptr->num<=p->num;ptr=ptr->next);
    //链表头
    if(ptr==*list){
        p->next=*list;
        (*list)->prev=p;
        *list=p;
    }
    //链表中
    else{
        p->next=ptr;
        p->prev=ptr->prev;
        ptr->prev->next=p;
        ptr->prev=p;
    }
}

//找到单项无序链表中第一个存储值为k的节点
un_node * find_node(long long k,un_node *list){
    un_node *ptr=list;
    while(ptr!=NULL&&ptr->data!=k){
        ptr=ptr->next;
    }
    return ptr;
}
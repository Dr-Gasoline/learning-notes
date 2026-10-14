#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct W{
    char word[50];
    int cnt;
    struct W *pr,*ne;
}rec;
rec *head=NULL,*tail=NULL;
char str[10000];

void free_list(rec *a){
    rec *ptr=a;
    while(ptr!=NULL){
        rec *tmp=ptr;
        ptr=ptr->ne;
        free(tmp);
    }
}

int main(){
    char tmp[1000];
    str[0]='\0';
    while((fgets(tmp,1000,stdin))!=NULL){
        strcat(str,tmp);
    }

    size_t len=strlen(str);
    for(int i=0;i<len;i++){
        if(!(isalpha(str[i]))){
            str[i]=' ';
        }
        else{
            str[i]=tolower(str[i]);
        }
    }

    int bias=0,num;
    while((sscanf(str+bias,"%s%n",tmp,&num))!=EOF){
        bias+=num;
        rec *p=malloc(sizeof(rec));
        p->pr=p->ne=NULL;
        p->cnt=1;
        strcpy(p->word,tmp);
        if(head==NULL){
            head=tail=p;
        }
        else{
            rec *ptr=head;
            while(ptr!=NULL&&strcmp(ptr->word,tmp)<0){//在每次试图调用结构内容时，都要确保指针非空！！！
                ptr=ptr->ne;
            }
            if(ptr==NULL){
                tail->ne=p;
                p->pr=tail;
                tail=p;
            }
            else if(strcmp(ptr->word,tmp)==0){
                free(p);
                ptr->cnt++;
            }
            else if(ptr==head){
                head->pr=p;
                p->ne=head;
                head=p;
            }
            else{
                p->ne=ptr;
                p->pr=ptr->pr;
                ptr->pr->ne=p;
                ptr->pr=p;
            }
        }
    }

    rec *ptr=head;
    while(ptr!=NULL){
        printf("%s %d\n",ptr->word,ptr->cnt);
        ptr=ptr->ne;
    }

    free_list(head);
}


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 101

typedef struct{
    char name[30];
    char num[15];
    char ori[25];
}indi;

unsigned int hash(char *str){
    unsigned long hash=5381;
    int c;
    while((c=*str++))
        hash=((hash<<5)+hash)+c;  //hash*33+c
    return hash%SIZE;
}

int cmp(const void *a,const void *b){
    indi *aa=(indi*)a,*bb=(indi*)b;
    return strcmp(aa->name,bb->name);
}

int n;
indi List[105];
int rec[SIZE][100];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf(" %s %s",List[i].name,List[i].num);
        strcpy(List[i].ori,List[i].name);
    }
    
    for(int i=1;i<=n;i++){
        int h=hash(List[i].name);
        if(rec[h][0]){
            int flag=1;
            int cnt=0,j;
            //判断.ori是否相同，用cnt计数，形式上避免了哈希冲突（实际上hash相同仍然在同一个桶中）
            for(j=0;rec[h][j];j++){
                if(strcmp(List[i].ori,List[rec[h][j]].ori)==0){
                    if(strcmp(List[i].num,List[rec[h][j]].num)==0){
                        List[i].name[0]='\0';
                        flag=0;
                        break;
                    }
                    cnt++;
                }
            }
            if(flag){
                rec[h][j]=i;
                if(cnt){
                    char tmp[10];
                    sprintf(tmp,"_%d",cnt);
                    strcat(List[i].name,tmp);
                }
            }
        }
        else
            rec[h][0]=i;
    }

    qsort(List+1,n,sizeof(indi),cmp);
    for(int i=1;i<=n;i++)
        if(List[i].name[0])
            printf("%s %s\n",List[i].name,List[i].num);
}
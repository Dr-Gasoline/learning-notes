#include<string.h>
#include<stdlib.h>

//在str原内存位置做字符串反转
void reverse(char *str){
    if (str==NULL) return;
    size_t len=strlen(str);
    if (len < 2) return;
    char *left=str,*right=str+len-1;
    while(left<right){
        char tmp=*left;
        *left=*right;
        *right=tmp;
        left++,right--;
    }
}

//分配新的内存，函数返回反转字符串首的指针，原字符串顺序不变
char *reverse_new_one(const char *str){
    if(str==NULL) return NULL;
    size_t len=strlen(str);
    char *re=malloc(len+1);
    for(int i=0;i<len;i++){
        re[i]=str[len-i-1];
    }
    re[len]='\0';
    return re;
}
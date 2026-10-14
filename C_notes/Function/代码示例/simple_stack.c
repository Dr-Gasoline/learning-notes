#include<stdio.h>
#include<string.h>
#include<ctype.h>
int c(int a,char sig,int b){
    switch(sig){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        default: return 0;
    }
}
char str[10000];
int nums[1000],ops[1000];
int main(){
    fgets(str,10000,stdin);
    size_t str_len = strlen(str);
    if(str_len > 0 && str[str_len-1] == '\n') {
        str[str_len-1] = '\0';
        str_len--;
    }
    int j=0;
    for(int i=0;str[i]!='=';i++){
        if(str[i]!=' '){
            str[j++]=str[i];
        }
    }
    str[j]='=',str_len=j+1;
    int n=0,o=0;
    int temp;
    int i=0;
    ops[o++]=str[i]=='-'?'-':'+';
    while(str[i]!='='){
        if(isdigit(str[i])){
            temp=str[i]-'0';
            while(isdigit(str[++i])){
                temp*=10;
                temp+=str[i]-'0';
            }
            nums[n++]=temp;
            if(str[i]=='=') break;
            ops[o++]=str[i];
        }
        i++;
    }
    int ind=0;
    while(ind<o){
        if(ops[ind]!='+'&&ops[ind]!='-'){
            temp=c(nums[ind-1],ops[ind],nums[ind]);
            nums[ind-1]=temp;
            for(int x=ind;x<n;x++){
                nums[x]=nums[x+1];
            }
            n--;
            for(int x=ind;x<o-1;x++){
                ops[x]=ops[x+1];
            }
            o--;
        }
        else{
            ind++;
        }
    }
    int ans=0;
    for(int i=0;i<o;i++){
        temp=c(ans,ops[i],nums[i]);
        ans=temp;
    }
    printf("%d",ans);
}
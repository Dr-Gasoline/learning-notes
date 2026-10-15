int next_permutation(int j[],int n){
    int l,r;
    for(l=n-1;l>0&&j[l]>j[l+1];l--);
    if(l==0) return 0;
    for(r=n;j[r]<j[l];r--);
    int tmp=j[l];
    j[l]=j[r];
    j[r]=tmp;
    for(l++,r=n;l<r;l++,r--){
        tmp=j[l];
        j[l]=j[r];
        j[r]=tmp;
    }
    return 1;
}

int main(){
    int n;
    int J[10];
    for (int i=1;i<=n;i++)
        J[i]=i;
    do {
        // 此时 J[1] 到 J[n] 是 1 到 n 的一个排列。你可以先在这里打印数组，观察它是怎么运行的。
    }while(next_permutation(J, n));
}

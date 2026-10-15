#define SIZE 1009
//DJB2 算法：简单快速，适用于中小规模数据
unsigned int hash(char *str){
    unsigned long hash=5381;
    int c;
    while((c=*str++))
        hash=((hash<<5)+hash)+c;  //hash*33+c
    return hash%SIZE;
}
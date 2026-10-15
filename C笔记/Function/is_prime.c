int is_prime(int a){
    if(a==2||a==3) return 1;
    if(a<=1||a%2==0||a%3==0) return 0;
    int step=4;
    for(int i=5;i*i<=a;step=6-step,i+=step)
      if(a%i==0) return 0;
    return 1;
}
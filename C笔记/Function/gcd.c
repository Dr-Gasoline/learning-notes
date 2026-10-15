int gcd(int a, int b) {
    while(b){
      int t=a%b;
      a=b;
      b=t;
    }
    return a;
}
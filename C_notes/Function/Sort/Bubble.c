void upsort(int a[], int n) // 升序
{
    int temp, aa = 0;
    for (int i = 0; i < n - 1; ++i){
        aa = 0;
        for (int j = 0; j < n - 1 - i; ++j){
            if (a[j] > a[j + 1]){
                temp = a[j + 1];
                aa = 1;
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
        if (aa == 0)
            break;
    }
}
void downsort(int a[], int n) // 降序
{
    int temp, aa = 0;
    for (int i = 0; i < n - 1; ++i){
        aa = 0;
        for (int j = 0; j < n - 1 - i; ++j){
            if (a[j] < a[j + 1]){
                temp = a[j + 1];
                aa = 1;
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
        if (aa == 0)
            break;
    }
}
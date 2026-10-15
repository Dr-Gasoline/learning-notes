#include <stdio.h>
typedef long long ll;
int a[1000010], b[1000010];
int n, i;
int sum;
ll result;
void merge(int lo, int hi)
{
    if (hi > lo)
    {
        int mi = (hi + lo) >> 1;
        merge(lo, mi), merge(mi + 1, hi);
        int bmark = lo, lomark = lo, himark = mi + 1;
        while (lomark <= mi || himark <= hi)
        {
            if ((himark > hi || a[lomark] <= a[himark]) && lomark <= mi)
                b[bmark++] = a[lomark++];
            else
                b[bmark++] = a[himark++], result += mi - lomark + 1;
        }
        for (int i = lo; i <= hi; ++i)
            a[i] = b[i];
    }
}
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        merge(0, n - 1);
        for (i = 0; i < n; ++i)
            printf("%d ", a[i]);
        putchar('\n');
    }
}
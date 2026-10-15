int qpow(int a, long long b, int p)
{
    int ans = 1;
    int base = a;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = ans * (long long)base % p;
        }
        base = (long long)base * base % p;
        b >>= 1;
    }
    return ans;
}
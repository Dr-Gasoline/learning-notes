#include<string.h>
#include<stdio.h>
int main()
{
    char str[2001];
    fgets(str,2001,stdin);
    size_t str_len = strlen(str);
    if(str_len > 0 && str[str_len-1] == '\n')
        str[--str_len] = '\0';
}
#include<cstdio>
int nums[64]={-60, -16, -15, -8, -7, -4, -1, 0, 1, 2, 4, 7, 8, 9, 15, 16, 17, 24, 32, 60, 68, 256};
char ops[64][8]={"-**", "-*-", "/-*", "-*+", "/--", "//-", "-/-", "///", "/*/", "/+/", "//+", "-/+", "/*+", "/++", "*-/", "/**", "/+*", "*++", "*+*", "**-", "**+", "***"};
int main()
{
    int n;
    int i;
    int tc;
    for(scanf("%d", &tc);tc--;)
    {
        scanf("%d", &n);
        for(i=0;i<=21 && nums[i]!=n;i++);
        if(i>21) printf("no solution\n");
        else printf("4 %c 4 %c 4 %c 4 = %d\n", ops[i][0], ops[i][1], ops[i][2], n);
    }
    return 0;
}


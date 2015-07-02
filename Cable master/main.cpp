#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
#define N 10010
#define MAX 10000000

int a[N];

int main()
{
    int n,m;
    double len;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        int Max = 0;
        for(int i=0; i<n; i++)
        {
            scanf("%lf",&len);
            a[i] = len * 100;
            Max = max(Max , a[i]);
        }
        int low = 1 , high = Max;
        int res = 0;
        while(low <= high)
        {
            int mid = (low + high) >> 1;
            int count = 0;
            for(int i=0; i<n; i++)
                count += a[i] / mid;

            if(count >= m)
                res = max(res , mid) , low = mid + 1;
            else
                high = mid - 1;
        }
        printf("%.2f\n",(double)res / 100.0);
    }
    return 0;
}

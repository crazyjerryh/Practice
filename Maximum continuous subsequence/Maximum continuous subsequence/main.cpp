#include <stdio.h>
#define maxn 10019

#define inf 0xffffff
int n;
int a[maxn];
int first,second;
int maxsum;
int main(void)
{
	while(scanf("%d",&n)!=EOF)
	{
        if(n==0)  break;
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);

		maxsum=-inf;
		int cur=0;
		int l,r;
		l=r=0;
        for(int i=0;i<n;i++){
		    cur+=a[i];
			r++;
			if(maxsum<cur)
			{
				maxsum=cur;
				first=l,second=r;
			}
			
			if(cur<0){
				cur=0;
				l=r;
			}
		}

		printf("%d %d %d\n",maxsum,a[first],a[second-1]);
	}
	return 0;
}
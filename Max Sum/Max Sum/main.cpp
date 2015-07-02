#include <stdio.h>
#define maxn 100010

#define inf 0xffffff
int maxsum;
int tcase,n;
int a[maxn];
int first,second;

int main(void)
{
	scanf("%d",&tcase);
	for(int t=1;t<=tcase;t++){
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		
		int cur=0;
		maxsum=-inf;
		first=second=-1;
		int l,r;
		l=r=0;
		for(int i=0;i<n;i++){
			cur+=a[i];
			r++;
			if(cur>maxsum)
			{
				maxsum=cur;
				first=l,second=r;
			}
			if(cur<0)
			{
				cur=0;
				l=r;
			}
		}
		printf("Case %d:\n%d %d %d\n",t,maxsum,first+1,second);
		if(t<tcase)
		 printf("\n");
	}
	return 0;
}
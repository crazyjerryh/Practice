#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 1010

struct _node{
	int a,b;
}a[maxn];

typedef struct _node node;
int n,k;

bool cmp(node a1,node b1)
{
	 double rate=(double)a1.a/a1.b;
	 double rate1=(double)b1.a/b1.b;
	 return rate>rate1;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&k)!=EOF){
		if(n==-1&&k==-1)  break;
		for(int i=0;i<k;i++){
			scanf("%d%d",&a[i].a,&a[i].b);
		}
		sort(a,a+k,cmp);
		int sum=n;
		double ans=0;
		for(int i=0;i<k;i++){
			 if(sum>a[i].b){
				 ans+=a[i].a;
				 sum-=a[i].b;
			}
			 else{
				 ans+=((double)a[i].a/a[i].b)*sum;
				 sum=0;
				 break;
			 }

		}
		printf("%.3f\n",ans);
	}
	return 0;
}

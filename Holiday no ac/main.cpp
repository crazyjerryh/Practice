#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;

#define maxn 110
struct _node
{
	int l,r;
}a[maxn];
typedef struct _node node;

bool cmp(node a,node b)
{
	return a.r<b.r;
}

int n;

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		if(n==0)  break;
		for(int i=0;i<n;i++){
			  scanf("%d%d",&a[i].l,&a[i].r);
		}
		sort(a,a+n,cmp);
		int prev=0;
		int ans=0;
		for(int i=0;i<n;i++){
			 if(a[i].l>=prev){
				 ans++;
				 prev=a[i].r;
			 }
		}
		printf("%d\n",ans);
	}
	return 0;
}

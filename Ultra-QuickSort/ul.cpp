#include <stdio.h>
#include <algorithm>
#include <memory.h>
using namespace std;
#define LL long long
#define maxn 500010

struct _node
{
	LL val;
	int pos;
}a[maxn];
typedef struct _node node;
int n;
LL tree[maxn];
int num[maxn];   //num 离散化
 
bool cmp(node a1,node a2){
	return a1.val<a2.val;    
}

LL sum(int x)
{
	LL res=0;
	while(x){
		res+=tree[x];
		x=x-(x&-x);
	}
	return res;
}
void update(int x,int num)
{
	while(x<=n){
		tree[x]+=(LL)num;
		x=x+(x&-x);
	}
}

LL solve()
{
	 LL ans=0;
	 memset(tree,0,sizeof(tree));  //设置树状数组的初始化值 
     for(int i=1;i<=n;i++){
     	  update(num[i],1);
     	  ans+=((LL)i)-sum(num[i]);  //累计前面比他大的数的个数 
	 }	
	 return ans;
}

int main(void)
{
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		if(n==0)  break;
		for(int i=1;i<=n;i++){
			LL tmp;
			scanf("%lld",&tmp);
			a[i].val=tmp,a[i].pos=i;
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++){
			num[a[i].pos]=i;  // 离散化 
		}
		
		LL ans=solve();
		printf("%lld\n",ans);
	}
	return 0;
}

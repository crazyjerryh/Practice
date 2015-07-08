#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn  200010
int tree[maxn*4],ans[maxn<<2],a[maxn],b[maxn];
int n,tot;

void build(int root,int l,int r){
	tree[root]=r-l+1;
	if(l==r)  {
		tree[root]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(2*root,l,mid);
	build(2*root+1,mid+1,r);
}

void insert(int root,int l,int r,int data,int pos){
	 if(l==r){
		   tree[root]--,ans[root]=data;
		   return;
	 }
	 int mid=(l+r)>>1;
	 if(tree[2*root]>=pos)
		 insert(2*root,l,mid,data,pos);
	 else
		 insert(2*root+1,mid+1,r,data,pos-tree[2*root]);
	 tree[root]=tree[root*2]+tree[2*root+1];
}

void query(int root,int l,int r){
	if(l==r){
		 if(tot==0)   printf("%d",ans[root]);
		 else  printf(" %d",ans[root]);
		 tot++;
		 return;
	}
	int mid=(l+r)>>1;
	query(2*root,l,mid);
	query(2*root+1,mid+1,r);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		memset(tree,0,sizeof(tree));
		memset(ans,0,sizeof(ans));
		build(1,1,n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i],&b[i]);
		}

		for(int i=n;i>=1;i--)
			insert(1,1,n,b[i],a[i]+1);
		tot=0;
		query(1,1,n);
		printf("\n");
	}
	return 0;
}

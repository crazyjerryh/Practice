#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;
#define MAXN 100010
#define MAXM 30

int n,m,kk;
int tree[MAXM][MAXN];
int toleft[MAXM][MAXN];
int sorted[MAXN];

int cmp(const void *a,const void *b)
{
   	  return *(int *)a-*(int *)b;
}

void build(int l,int r,int dep)
{
	if(l==r) return;
	 int mid=(l+r)>>1;
	 
	 int same=mid+1-l;
	 for(int i=l;i<=r;i++) 
		 if(tree[dep][i]<sorted[mid]) same--;

	 int lpos=l,rpos=mid+1;
	 for(int i=l;i<=r;i++){
		 if(tree[dep][i]<sorted[mid])
			   tree[dep+1][lpos++]=tree[dep][i];
		 else if(tree[dep][i]==sorted[mid]&&same>0){
			   tree[dep+1][lpos++]=tree[dep][i];
		       same--;
		 }
		 else
			   tree[dep+1][rpos++]=tree[dep][i];
		 
		 toleft[dep][i]=toleft[dep][l-1]+lpos-l;
	 }

	 build(l,mid,dep+1);
	 build(mid+1,r,dep+1);
}

int query(int L,int R,int l,int r,int k,int dep)
{
	 if(l==r)   return tree[dep][l];
	 
	 int mid=(L+R)>>1;
	 int cnt=toleft[dep][r]-toleft[dep][l-1];
	 if(cnt>=k){
		  int newl=toleft[dep][l-1]-toleft[dep][L-1]+L;
		  int newr=newl+cnt-1;
		  return query(L,mid,newl,newr,k,dep+1);
	 }
	 else
	 {
		 int newr=r+toleft[dep][R]-toleft[dep][r];  
		 int newl=newr-(r-l-cnt);
		 return query(mid+1,R,newl,newr,k-cnt,dep+1);
	 }
}

int main(void)
{
    cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>tree[0][i];
		sorted[i]=tree[0][i];
	}

	memset(toleft,0,sizeof(toleft));
	qsort(sorted+1,n,sizeof(int),cmp);
	

	build(1,n,0);
	for(int i=0;i<m;i++){
		int l,r;
		cin>>l>>r>>kk;
		int res=query(1,n,l,r,kk,0);
		cout<<res<<endl;
	}
	return 0;
}
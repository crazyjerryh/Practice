#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

//ifstream fin("debug.txt");
#define maxn 800010
//#define cin fin
#define max(a,b) a>b?a:b
int n,m;
int tree[maxn<<1];
int a[maxn];


int getid(int l,int r)
{
     return l+r|l!=r;	
}

int build(int l,int r)
{
	int id=getid(l,r);
	if(l==r)
	{
		tree[id]=a[l];
		return tree[id];
	}
	int mid=(l+r)>>1;
	int lmax=build(l,mid);
	int rmax=build(mid+1,r);

	tree[id]=max(lmax,rmax);
	return tree[id];
}

int insert(int l,int r,int data,int pos)
{
    int id=getid(l,r);
	if(l==r){
		a[l]=data;
		tree[id]=data;
		return data;
	}
	int mid=(l+r)>>1;
	int mmax;
	if(pos<=mid){
		mmax=insert(l,mid,data,pos);
		int tmp=getid(mid+1,r);
		if(tree[tmp]<mmax)
			tree[id]=mmax;
		else
			tree[id]=tree[tmp];
	}
	else
	{
		mmax=insert(mid+1,r,data,pos);
		int tmp=getid(l,mid);
		if(tree[tmp]<mmax)
			tree[id]=mmax;
		else
			tree[id]=tree[tmp];
	}
	return tree[id];
}

int query(int l,int r,int L,int R)
{
	int id=getid(L,R);
	int mid=(L+R)>>1;
	if(l<=L&&r>=R)
		return tree[id];
	
	if(l>mid)
		return query(l,r,mid+1,R);
	else if(r<=mid)
		return query(l,r,L,mid);
	else
	{
		int lmax=query(l,mid,L,mid);
	    int rmax=query(mid+1,r,mid+1,R);
		return max(lmax,rmax);
	}
    return 0;
}

int main(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	
	memset(tree,0,sizeof(tree));
	build(1,n);
	for(int i=0;i<m;i++)
	{
		char c;
		int l,r;
		cin>>c>>l>>r;
		if(c=='Q'){
			int ans=query(l,r,1,n);
			cout<<ans<<endl;
		}
		else
		{
			insert(1,n,r,l);
		}
	}
	return 0;
}
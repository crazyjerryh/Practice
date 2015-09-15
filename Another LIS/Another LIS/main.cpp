/*
* author Rotile_H
* file E:\POJ\Practice\Another LIS\Another LIS\main.cpp
* 2015 9 15
*/
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100
int tree[maxn<<2],ans[maxn],s[maxn],dp[maxn];
int tcase,t,n,len;

void pushup(int rt){
	tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}

void build(int rt,int l,int r){
	if(l==r)  {
		tree[rt]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
}

void insert(int rt,int l,int r,int x,int pos){
	if(l==r){
		ans[x]=l; 
		tree[rt]=0;
		return;
	}
	tree[rt]--;
	int mid=(l+r)>>1;
	if(pos<=tree[rt<<1])  insert(rt<<1,l,mid,x,pos);
	else insert(rt<<1|1,mid+1,r,x,pos-tree[rt<<1]);
}

int search(int k){
	int l=1,r=len;
	int res;
	if(k>dp[r]) return r+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(k<=dp[mid]){
			r=mid-1;
			res=mid;
		}
		else l=mid+1;
	}
	return res;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	int t=0;
	while(tcase--){
		printf("Case #%d:\n",++t);
		scanf("%d",&n);
		build(1,1,n);
		for(int i=1;i<=n;i++) scanf("%d",&s[i]);
		for(int i=n;i>=1;i--) insert(1,1,n,i,s[i]+1);
		
		len=1;
		dp[1]=ans[1];
		printf("%d\n",len);
		for(int i=2;i<=n;i++){
			int k=search(ans[i]);
			len=max(k,len);
			dp[k]=ans[i];
			printf("%d\n",len);
		}
		printf("\n");
	}
}
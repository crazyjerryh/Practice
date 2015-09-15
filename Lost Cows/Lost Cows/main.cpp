/*
* author Rotile_H
* file E:\POJ\Practice\Lost Cows\Lost Cows\main.cpp
* 2015 9 15
*/
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn  8100

int tree[maxn<<2],n,s[maxn];
int ans[maxn];

void push_up(int rt){
	tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}

void build(int rt,int l,int r){
     if(l==r){
		 tree[rt]=1;
		 return;
	 }
	 int mid=(l+r)>>1;
	 build(rt<<1,l,mid);
	 build(rt<<1|1,mid+1,r);
	 push_up(rt);
}

int insert(int rt,int l,int r,int x){
	if(l==r) {
		tree[rt]=0;
		return l;
	}
	int mid=(l+r)>>1;
	tree[rt]--;
	if(tree[rt<<1]>=x) return insert(rt<<1,l,mid,x);
	else return insert(rt<<1|1,mid+1,r,x-tree[rt<<1]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		s[1]=0;
		for(int i=2;i<=n;i++) scanf("%d",&s[i]);
		for(int i=1;i<=n;i++) s[i]++;
		
		build(1,1,n);
		for(int i=n;i>=1;i--){
			ans[i]=insert(1,1,n,s[i]);
		}
		
		for(int i=1;i<=n;i++) 
			printf("%d\n",ans[i]);
	}
}
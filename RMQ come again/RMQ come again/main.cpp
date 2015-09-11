/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/10
 * 
 */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1000100
int tree[maxn<<2];
int a[maxn];
int n,q;
#define lson rt<<1
#define rson rt<<1|1
void push_up(int rt){
	tree[rt]=min(tree[lson],tree[rson]);
}

void build(int rt,int l,int r){
	if(l==r) {
		tree[rt]=a[l];
		return;
	}
    int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	push_up(rt);
}

void update(int rt,int l,int r,int u,int w){
	if(l==r){
		tree[rt]=w;
		return;
	}
	int mid=(l+r)>>1;
	if(u<=mid) update(rt<<1,l,mid,u,w);
	else if(u>mid) update(rt<<1|1,mid+1,r,u,w);
	push_up(rt);
}

int query(int rt,int L,int R,int l,int r){
	if(L==l&&R==r)
		return tree[rt];
	int mid=(L+R)>>1;
	if(r<=mid) return query(lson,L,mid,l,r);
	else if(l>mid) return query(rson,mid+1,R,l,r);
	else return min(query(lson,L,mid,l,mid),query(rson,mid+1,R,mid+1,r));
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		build(1,1,n);
		scanf("%d",&q);
		for(int i=0;i<q;i++){
			int t,l,r;
			scanf("%d%d%d",&t,&l,&r);
			if(t==0){
				int ans=query(1,1,n,l,r);
				printf("%d\n",ans);
			}
			else update(1,1,n,l,r);
		}
	}
}
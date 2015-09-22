/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/22
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
#define maxn 100100

int n,m,k;
int T[maxn];
int sum[maxn*30],ls[maxn*30],rs[maxn*30];
int s[maxn],h[maxn];
int tot;

// void build(int &rt,int l,int r){
// 	rt=++tot;
// 	tree[rt]=0;
// 	if(l==r) return;
// 	int mid=(l+r)>>1;
// 	build(ls[rt],l,mid);
// 	build(rs[rt],mid+1,r);
// }
// 
// void update(int &rt,int l,int r,int p,int last){
// 	rt=++tot;
// 	ls[rt]=ls[last];
// 	rs[rt]=rs[last];
// 	tree[rt]=tree[last]+1;
// 	if(l==r) return;
// 	int mid=(l+r)>>1;
// 	if(p<=mid) update(ls[rt],l,mid,p,ls[last]);
// 	else update(rs[rt],mid+1,r,p,rs[last]);
// }
// 
// int query(int ss,int tt,int l,int r,int k){
// 	if(l==r)  return l;
// 	int t=tree[ls[tt]]-tree[ls[ss]];
// 	int mid=(l+r)>>1;
// 	if(t<=k)
// 		return query(ls[ss],ls[tt],l,mid,k);
// 	else
// 		return query(rs[ss],rs[ss],mid+1,r,k-t);
// }


void Build(int l,int r,int &rt)  
{  
	 	rt=++tot;
	 	sum[rt]=0;
	 	if(l==r) return;
	 	int mid=(l+r)>>1;
	 	Build(l,mid,ls[rt]);
	 	Build(mid+1,r,rs[rt]);
}  

void Update(int last,int p,int l,int r,int &rt)  
{  
	 	rt=++tot;
	 	ls[rt]=ls[last];
	 	rs[rt]=rs[last];
	 	sum[rt]=sum[last]+1;
	 	if(l==r) return;
	 	int mid=(l+r)>>1;
	 	if(p<=mid) Update(ls[last],p,l,mid,ls[rt]);
	 	else Update(rs[last],p,mid+1,r,rs[rt]);
}  

int Query(int ss,int tt,int l,int r,int k)  
{  
	if(l==r)  return l;
    int mid=(l+r)>>1;
	int cnt=sum[ls[tt]]-sum[ls[ss]];
	if(k<=cnt)
	 		return Query(ls[ss],ls[tt],l,mid,k);
	 else
	 		return Query(rs[ss],rs[tt],mid+1,r,k-cnt);
}  

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++){
			scanf("%d",&s[i]); 
			h[i]=s[i];
		}
		tot=0;
		sort(h+1,h+1+n);
		int cnt=unique(h+1,h+1+n)-h-1;
		for(int i=1;i<=n;i++)
			s[i]=std::lower_bound(h+1,h+1+cnt,s[i])-h; // lisan
		
		Build(1,cnt,T[0]);
		for(int i=1;i<=n;i++) Update(T[i-1],s[i],1,cnt,T[i]);
		while(m--){
			int l,r;
			scanf("%d%d%d",&l,&r,&k);
			int ans=Query(T[l-1],T[r],1,cnt,k);
			printf("%d\n",h[ans]);
		}
	}
	return 0;
}

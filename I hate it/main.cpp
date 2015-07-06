#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 200020

int tree[maxn*10];
int n,m;

void update(int root,int l,int r,int inx,int num){
	 if(l==r){
		 tree[root]=num;
		 return;
	 }
	 int mid=(l+r)>>1;
	 if(inx<=mid)
		 update(2*root,l,mid,inx,num);
	 else
		 update(2*root+1,mid+1,r,inx,num);
	 tree[root]=max(tree[2*root],tree[2*root+1]);
}

int query(int root,int l,int r,int L,int R){
	if(l==L&&r==R)  return tree[root];
	int mid=(L+R)>>1;
	if(r<=mid)
		return query(2*root,l,r,L,mid);
	else if(l>mid)
		return query(2*root+1,l,r,mid+1,R);
	else{
		int ans=query(2*root,l,mid,L,mid);
		ans=max(ans,query(2*root+1,mid+1,r,mid+1,R));
		return ans;
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=n;i++){
			int tmp;
			scanf("%d",&tmp);
			update(1,1,n,i,tmp);
		}
		getchar();
		
		for(int i=0;i<m;i++){
			 char cmd;
			 int l,r;
			 scanf("%c",&cmd);
			 if(cmd=='Q'){
				scanf("%d%d",&l,&r);
				int ans=query(1,l,r,1,n);
				printf("%d\n",ans);
			 }
			 else{
				scanf("%d%d",&l,&r);
				update(1,1,n,l,r);  //l reperesent the update location
			 }
			 getchar();
		}
	}
	return 0;
}

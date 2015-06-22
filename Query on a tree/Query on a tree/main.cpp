#include <stdio.h>
#include <algorithm>
#include <memory.h>
using namespace std;

#define maxn 100010
int tcase,n;
struct _edge
{
	int u,v;
	int w;
	int next;
}edges[maxn<<1];
typedef struct _edge edge;
int cnt,loc;
int head[maxn],top[maxn],parent[maxn],dep[maxn];
int size[maxn],son[maxn],w[maxn];
int dp[maxn][3];
int tree[maxn*4];

void init()
{
	cnt=0,loc=0;
	for(int i=0;i<maxn;i++){
		head[i]=-1;
		size[i]=1;
		tree[i]=0;
	}
}

void addedge(int u,int v,int w)
{
	 edges[cnt].u=u,edges[cnt].v=v,edges[cnt].w=w;
	 edges[cnt].next=head[u],head[u]=cnt++;
	 edges[cnt].v=u,edges[cnt].u=v,edges[cnt].w=w;
	 edges[cnt].next=head[v],head[v]=cnt++;
}

void dfs(int u,int p)
{
	int maxson=-1;
	size[u]=1;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=p){
			dep[v]=dep[u]+1;
			parent[v]=u;
			dfs(v,u);
			size[u]+=size[v];
			if(maxson<size[v]){
				 maxson=size[v];
				 son[u]=v;
			}
		}
	}
}

void maketree(int u,int tp)
{
	top[u]=tp,w[u]=++loc;
	if(son[u]!=0)  maketree(son[u],tp);
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=parent[u]&&v!=son[u])
			 maketree(v,v);
	}
}

void updateTree(int root,int l,int r,int lo,int data)
{
	 if(l==r){
		  tree[root]=data;
		  return;
	 }
	 int mid=(l+r)/2;
	 if(lo>mid)
		 updateTree(root*2+1,mid+1,r,lo,data);
	 else
		 updateTree(root*2,l,mid,lo,data);
	 tree[root]=max(tree[root*2],tree[root*2+1]);
}


int query(int root,int l,int r,int low,int high)
{
	 if(low==l&&high==r) return tree[root];
	 int mid=(low+high)>>1;
	 if(r<=mid)
		  return query(2*root,l,r,low,mid);
	 else if(l>mid)
		 return query(2*root+1,l,r,mid+1,high);
	 else
		 return std::max(query(2*root,l,mid,low,mid),query(2*root+1,mid+1,r,mid+1,high));
}

int find(int a,int b)
{
	int maxnum=0;
	//找到区间[a,b]中的最大的权重
	int f1=top[a],f2=top[b];
	int va=a,vb=b;
	while(f1!=f2){
		//逼近到一个重链上去
		if(dep[f1]>dep[f2]){
			std::swap(f1,f2),std::swap(va,vb);
		}
		maxnum=std::max(maxnum,query(1,w[f2],w[vb],1,loc));
		vb=parent[f2];
		f2=top[vb];
	}
	
	if(va==vb)  return maxnum;
	if(dep[va]>dep[vb])  std::swap(va,vb);  //设va为父节点
	maxnum=max(maxnum,query(1,w[son[va]],w[vb],1,loc));
	return maxnum;
}

int main(void)
{
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		init();
		for(int i=0;i<n-1;i++){
			int a,b,w;
			scanf("%d%d%d",&a,&b,&w);
			addedge(a,b,w);
			dp[i][0]=a,dp[i][1]=b,dp[i][2]=w;
		}

		int root=(n+1)/2;
		parent[root]=dep[root]=0;
		dfs(root,0);
		maketree(root,root);
		
		for(int i=0;i<n-1;i++){
			 if(dep[dp[i][0]>dep[dp[i][1]]])  std::swap(dp[i][0],dp[i][1]);
			 updateTree(1,1,loc,w[dp[i][1]],dp[i][2]);
		}
		
		char tmp[20];
		while(scanf("%s",&tmp)!=EOF)
		{
			if(tmp[0]=='D')  break;
			if(tmp[0]=='Q'){
				 int a,b; 
				 scanf("%d%d",&a,&b);
				 int res=find(a,b);
				 printf("%d\n",res);
			}
			if(tmp[0]=='C'){
				int a,b;
				scanf("%d%d",&a,&b);
				updateTree(1,1,loc,w[dp[a-1][1]],b);
			}
		}
	}
	return 0;
}
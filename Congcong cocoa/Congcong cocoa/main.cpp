/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/07
 * Ê÷·ÖÖÎ
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 20010
struct edge{
	int v,w;
	int next;
}edges[maxn<<1];
int head[maxn],size[maxn],vis[maxn],fx[maxn],dep[maxn];
int flag[3];
int n,cnt;
int sum,root;

int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}

void addedge(int u,int v,int w){
	edges[cnt].v=v,edges[cnt].w=w,edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].v=u,edges[cnt].w=w,edges[cnt].next=head[v],head[v]=cnt++;
}

//get the senior point
void getroot(int u,int fa){
	size[u]=1,fx[u]=0;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(vis[v]==0&&v!=fa){
			getroot(v,u);
			size[u]+=size[v];
			fx[u]=max(fx[u],size[v]);
		}
	}
	fx[u]=max(fx[u],sum-size[u]);
	if(fx[u]<fx[root]) root=u;
}

void getdep(int u,int fa){
	flag[dep[u]%3]++;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(!vis[v]&&v!=fa){
			dep[v]=dep[u]+edges[i].w;
			getdep(v,u);
		}
	}
}

int cal(int rt,int now){
	flag[0]=flag[1]=flag[2]=0;
	dep[rt]=now;
	getdep(rt,0);
	return flag[0]*flag[0]+2*flag[1]*flag[2];
}

int solve(int rt){
	vis[rt]=1;
	int ans=0;
	ans+=cal(rt,0);
	for(int i=head[rt];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(!vis[v]){
			ans-=cal(v,edges[i].w);
			root=0;
			sum=size[v];
			getroot(v,0); 
			ans+=solve(root);
		}
	}
	return ans;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		cnt=0;
		for(int i=1;i<n;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addedge(u,v,w);
		}
		sum=n;
		root=0,fx[root]=n;
		getroot(1,0);
		int ans=solve(root);
		int t=gcd(ans,n*n);
		printf("%d/%d\n",ans/t,n*n/t);
	}
	return 0;
}

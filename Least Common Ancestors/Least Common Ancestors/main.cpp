/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/11
 * lca
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100
int n,q;
map<string,int> Map;
int cnt,tot,ccnt;
int root;

struct edge {
	int v,next;
}edges[maxn<<1];

struct ques{
	int v,next,num;
}quess[maxn<<1];
int head[maxn],dep[maxn],vis[maxn];
int qhead[maxn],res[maxn],pa[maxn],sz[maxn];
string rMap[maxn];
int curdep;

void addedge(int a,int b){
	edges[cnt].v=b,edges[cnt].next=head[a],head[a]=cnt++;
}

void addqedge(int a,int b,int num){
	quess[ccnt].v=b,quess[ccnt].next=qhead[a],quess[ccnt].num=num,qhead[a]=ccnt++;
	quess[ccnt].v=a,quess[ccnt].next=qhead[b],quess[ccnt].num=num,qhead[b]=ccnt++;
}

void getdep(int u,int fa){
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=fa){
			dep[v]=dep[u]+1;
		    getdep(v,u);
		}
	}
}

int find(int u){
	while(pa[u]!=-1) u=pa[u];
	return u;
}

void _union(int u,int v){
	int f1,f2;
	f1=find(u);
	f2=find(v);
	if(f1!=f2){
		if(dep[f1]<dep[f2]) pa[f2]=f1;
		else pa[f1]=f2;
	}
}

void lca(int u,int fa){
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		lca(v,u);
		_union(u,v);
	}
	vis[u]=1;
	for(int i=qhead[u];i!=-1;i=quess[i].next){
		int v=quess[i].v;
		if(vis[v]){
			int num=quess[i].num;
			res[num]=find(v);
		}
	}
}


int main(void){
	freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		cnt=tot=ccnt=0;
		root=1;
		dep[root]=1;
		dep[0]=inf;
		memset(head,-1,sizeof(head));
		memset(qhead,-1,sizeof(qhead));
		memset(vis,0,sizeof(vis));
		memset(pa,-1,sizeof(pa));
		memset(sz,1,sizeof(sz));
		curdep=0;
		for(int i=0;i<n;i++){
			string a,b;
		    cin>>a>>b;
		    if(Map.find(a)==Map.end()){
				Map.insert(make_pair(a,++tot));
				rMap[tot]=a;
			}
			if(Map.find(b)==Map.end()){
				Map.insert(make_pair(b,++tot));
				rMap[tot]=b;
			}
			int u=Map[a];
			int v=Map[b];
			addedge(u,v);
		}
		scanf("%d",&q);
		for(int i=0;i<q;i++){
			string a,b;
			cin>>a>>b;
			int u=Map[a];
			int v=Map[b];
			addqedge(u,v,i); 
		}
		getdep(root,0);
		lca(root,0);
		for(int i=0;i<q;i++){
			int ans=res[i];
			cout<<rMap[ans]<<endl;
		}
	}
	return 0;
}

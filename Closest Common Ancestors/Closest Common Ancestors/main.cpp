#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

const int N=1100;

vector<int> edge[N];
int query[N][N],father[N],count[N],indeg[N];
int vis[N],n,m;

int findSet(int x){
	if(x!=father[x]){
		father[x]=findSet(father[x]);
	}
	return father[x];
}

void Tarjan(int u){
	father[u]=u;
	for(int i=0;i<edge[u].size();i++){
		Tarjan(edge[u][i]);
		father[edge[u][i]]=u;
	}
	vis[u]=1;
	for(int i=1;i<=n;i++)
		if(vis[i] && query[u][i])
			count[findSet(i)]+=query[u][i];
}

int main(){

	//freopen("debug.txt","r",stdin);

	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++)
			edge[i].clear();
		memset(query,0,sizeof(query));
		memset(vis,0,sizeof(vis));
		memset(count,0,sizeof(count));
		memset(indeg,0,sizeof(indeg));
		int u,v;
		for(int i=0;i<n;i++){
			scanf("%d:(%d)",&u,&m);
			while(m--){
				scanf(" %d",&v);
				edge[u].push_back(v);
				indeg[v]++;
			}
		}
		scanf(" %d",&m);
		for(int i=0;i<m;i++){
			scanf(" (%d %d)",&u,&v);
			query[u][v]++;
			query[v][u]++;
		}
		for(int i=1;i<=n;i++)
			if(indeg[i]==0){
				Tarjan(i);
				break;
			}
			for(int i=1;i<=n;i++)
				if(count[i])
					printf("%d:%d\n",i,count[i]);
	}
	return 0;
}
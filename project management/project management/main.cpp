#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 100100

vector<int> g[maxn];
int val[maxn];
int tcase,n,m;

int getval(int u){
     int size=g[u].size();
	 int sum=0;
	 for(int i=0;i<size;i++)
		 sum+=val[g[u][i]];
	 return sum;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		memset(g,0,sizeof(g));
		memset(val,0,sizeof(val));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		int cmd,u,v;
		int q;
		scanf("%d",&q);
		for(int i=0;i<q;i++){
			scanf("%d",&cmd);
			if(cmd==0){
				scanf("%d%d",&u,&v);
				val[u]+=v;
			}
			else  scanf("%d",&u),printf("%d\n",getval(u));
		}
	}
	return 0;
}
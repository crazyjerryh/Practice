#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 5010
#define maxm 510
#define inf 0x3f3f3f3f
struct edge{
	int u,v,val;
}edges[maxn<<1];
int fa[maxm],size[maxm];
int n,m;
int s,t;
bool cmp(edge a,edge b){
	return a.val<b.val;
}

int find(int a){
	while(fa[a]!=-1)  a=fa[a];
	return a;
}

bool judge(int a,int b){
	int faa=find(a);
	int fbb=find(b);
	if(faa==fbb)
		return true;
	else
		return false;
}

void _union(int a,int b){
    int faa,fbb;
	faa=find(a);
	fbb=find(b);
	if(faa!=fbb){
	   //fa[fbb]=faa;
	   if(size[faa]>=size[fbb]){
		   fa[fbb]=faa;
		   size[faa]+=size[fbb];
	   }
	   else
	   {
		   fa[faa]=fbb;
		   size[fbb]+=size[faa];
	   }
	}
}

int gcd(int a,int b){
	if(b==0)
		return a;
	return gcd(b,a%b);
}

void solve(){
	int i,j;
	double ans=inf;
	int resx,resn;
	for(i=1;i<=m;i++){
		memset(fa,-1,sizeof(fa));
		memset(size,1,sizeof(size));
		bool flag=false;
		j=i;
		while(j<=m){
			_union(edges[j].u,edges[j].v);
	    	if(judge(s,t)) {
			double tmp=(double)edges[j].val/edges[i].val;
				if(tmp<ans)
					resn=i,resx=j,ans=tmp;
				flag=true;
				break;
			}
			j++;
		}
		if(!flag)  break;
	}
	if(ans>=inf)
		printf("IMPOSSIBLE\n");
	else
	{
		int tmp=gcd(edges[resx].val,edges[resn].val);  //最大公约数
		if(edges[resn].val/tmp!=1)
		   printf("%d/%d\n",edges[resx].val/tmp,edges[resn].val/tmp);
		else
		   printf("%d\n",edges[resx].val/tmp);
	}
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(edges,0,sizeof(edges));
		for(int i=1;i<=m;i++){
			 int a,b,val;
			 scanf("%d%d%d",&a,&b,&val);
			 edges[i].u=a,edges[i].v=b,edges[i].val=val;
		}
	   scanf("%d%d",&s,&t);
	   sort(edges+1,edges+1+m,cmp);
	   solve();
	}
	return 0;
}

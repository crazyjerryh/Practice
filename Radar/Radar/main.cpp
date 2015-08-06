/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/08/06
 * dancing links 重复覆盖
 */
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100
#define maxm 10000
#define epos 1e-8

struct point{
	int x,y;
}station[maxn],city[maxn];

int tcase,n,m,k;
int L[maxm],R[maxm],U[maxm],D[maxm],Col[maxm],Row[maxm];
int S[maxn],H[maxn];
int used[maxn];
int cnt;

void init(){
	for(int i=0;i<=n;i++){
		S[i]=0;
		U[i]=D[i]=i;
		L[i]=i-1;
		R[i]=i+1;
	}
	R[n]=0;L[0]=n;
    cnt=n;
	for(int i=1;i<=m;i++)  H[i]=-1;
}

void link(int r,int c){
	++S[Col[++cnt]=c];
	Row[cnt]=r;
	D[U[c]]=cnt;
	U[cnt]=U[c];
	U[c]=cnt;
	D[cnt]=c;
	if(H[r]<0)  H[r]=L[cnt]=R[cnt]=cnt;
	else{
		R[L[H[r]]]=cnt;
		L[cnt]=L[H[r]];
		R[cnt]=H[r];
		L[H[r]]=cnt;
	}
}

void remove(int c){
	for(int i=D[c];i!=c;i=D[i]){
		L[R[i]]=L[i];
		R[L[i]]=R[i];
	}
}

void resume(int c){
	for(int i=U[c];i!=c;i=U[i]){
		L[R[i]]=R[L[i]]=i;
	}
}

int h(){ //启发式函数
	int ret=0;
	memset(used,0,sizeof(used));
	for(int i=R[0];i!=0;i=R[i]){
		if(!used[i]){
			used[i]=1;
			ret++;
			for(int j=D[i];j!=i;j=D[j]){
				for(int k=R[j];k!=j;k=R[k])
					used[Col[k]]=1;
			}
		}
	}
	return ret;
}

bool dfs(int d){
	if(d+h()>k)  return false;
	if(R[0]==0) return d<=k;
	int c=R[0];
	for(int i=R[0];i!=0;i=R[i])
		if(S[c]>S[i])  c=i;
	
	for(int i=D[c];i!=c;i=D[i]){
		remove(i);
		for(int j=R[i];j!=i;j=R[j]) remove(j);
		if(dfs(d+1)) return true;
		for(int j=L[i];j!=i;j=L[j]) resume(j);
		resume(i);
	}
	return false;
}

double dis(point a,point b){
	return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++) scanf("%d%d",&city[i].x,&city[i].y);
		for(int i=1;i<=m;i++) scanf("%d%d",&station[i].x,&station[i].y);
		double l=0;
		double r=1e8;
		while(r-l>=epos){
			double mid=(l+r)/2;
			init();
			for(int i=1;i<=m;i++)
				for(int j=1;j<=n;j++){
					if(dis(city[j],station[i])<(mid-epos)){
						link(i,j);
					}
				}
			if(dfs(0)) r=mid-epos;
			else l=mid+epos;
		}
		printf("%.6lf\n",l);
	}
	return 0;
}
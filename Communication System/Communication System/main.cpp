#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <string.h>
using namespace std;

#define maxn 110
#define inf 0x3f3f3f3f
int bb[maxn][maxn],pp[maxn][maxn];
int b[maxn*maxn];
int n,m,tcase;
int cnt;

void solve(){
	sort(b+1,b+cnt+1);
	double ratio=-1;
	for(int t=1;t<=cnt;t++){
		if(t!=1&&b[t]==b[t-1]) continue;
		int sump=0;
		for(int i=1;i<=n;i++){
			m=bb[i][0];
			int minp=inf;
			for(int j=1;j<=m;j++)  if(bb[i][j]>=b[t]&&pp[i][j]<minp) minp=pp[i][j];
			sump+=minp;
		}
		double tmp=(double)(b[t]*1.0)/sump;
		if(tmp>ratio)  ratio=tmp;
	}
	printf("%.3f\n",ratio);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&m);
			bb[i][0]=pp[i][0]=m;
			for(int j=1;j<=m;j++) scanf("%d%d",&bb[i][j],&pp[i][j]),b[++cnt]=bb[i][j];
		}
		solve();
	}
	return 0;
}
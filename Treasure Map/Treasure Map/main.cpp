/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/08/05
 * dancing links
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxm 1024*505
#define maxn 1010

int tcase;
int n,m,p;
int L[maxm],R[maxm],U[maxm],D[maxm],Row[maxm],Col[maxm];
int H[maxn],S[maxn],ans[maxn];
int cnt,ansd,curd;

void init(){
	for(int i=0;i<=n*m;i++)  {
		S[i]=0;
		U[i]=D[i]=i;
		L[i]=i-1;
		R[i]=i+1;
	}
	R[m*n]=0;
	L[0]=m*n;
	cnt=m*n;
	for(int i=1;i<=p;i++)  H[i]=-1;
}

void link(int r,int c){
	++S[Col[++cnt]=c];
	Row[cnt]=r;
	U[cnt]=U[c];
	D[U[c]]=cnt;
	U[c]=cnt;
	D[cnt]=c;
	if(H[r]<0)  H[r]=L[cnt]=R[cnt]=cnt;
	else{
		R[L[H[r]]]=cnt;
		L[cnt]=L[H[r]];
		L[H[r]]=cnt;
		R[cnt]=H[r];
	}
}

void remove(int c){
	L[R[c]]=L[c];
	R[L[c]]=R[c];

	for(int i=D[c];i!=c;i=D[i]){
		for(int j=R[i];j!=i;j=R[j]){
			U[D[j]]=U[j];
			D[U[j]]=D[j];
			S[Col[j]]--;
		}
	}
}

void resume(int c){
	for(int i=U[c];i!=c;i=U[i]){
		for(int j=L[i];j!=i;j=L[j]){
			D[U[j]]=U[D[j]]=j;
			S[Col[j]]++;
		}
	}
	L[R[c]]=R[L[c]]=c;
}

void dfs(int d){
	if(d>=ansd&&ansd!=-1)  return;
	if(R[0]==0){
		if(ansd==-1)  ansd=d;
		else if(d<ansd)  ansd=d;
		return;
	}

	int p=R[0];
	for(int i=R[0];i!=0;i=R[i]){
		if(S[i]<S[p])
			p=i;
	}

	remove(p);
	for(int i=D[p];i!=p;i=D[i]){
		ans[d]=Row[i];
		for(int j=R[i];j!=i;j=R[j]) remove(Col[j]);
		dfs(d+1);
		for(int j=L[i];j!=i;j=L[j]) resume(Col[j]);
	}
	resume(p);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&n,&m,&p);
		init();
		for(int i=1;i<=p;i++){
			int x1,x2,y1,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			for(int ii=x1+1;ii<=x2;ii++){
				for(int jj=y1+1;jj<=y2;jj++){
					link(i,(ii-1)*m+jj);
				}
			}
		}
		
		ansd=-1;
		dfs(0);
		printf("%d\n",ansd);
	}
}
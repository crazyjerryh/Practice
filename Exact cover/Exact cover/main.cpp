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
#define maxm 10001111
#define maxn 1010

int n,m,c;
int L[maxm],R[maxm],U[maxm],D[maxm],Row[maxm],Col[maxm];
int S[maxn],H[maxn],ans[maxn];
int cnt,ansd;

void init(){
	for(int i=0;i<=m;i++)  {
		S[i]=0;
		U[i]=D[i]=i;
		L[i]=i-1;
		R[i]=i+1;
	}
	R[m]=0;L[0]=m;
	cnt=m;
	for(int i=1;i<=n;i++)  H[i]=-1;
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

bool dfs(int d){
	if(R[0]==0){
		ansd=d;
		return true;
	}
	
	int p=R[0];
	for(int i=R[0];i!=0;i=R[i])
		if(S[i]<S[p])
			p=i;

	remove(p);
	for(int i=D[p];i!=p;i=D[i]){
		ans[d]=Row[i];
		for(int j=R[i];j!=i;j=R[j]) remove(Col[j]);
		if(dfs(d+1))  return true;
		for(int j=L[i];j!=i;j=L[j]) resume(Col[j]);
	}
	resume(p);
	return false;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		init();
		for(int i=1;i<=n;i++){
			scanf("%d",&c);
			while(c--){
				int tmp;
				scanf("%d",&tmp);
				link(i,tmp);
			}
		}
		
		if(!dfs(0))  printf("NO\n");
		else{
			printf("%d",ansd);
			for(int i=0;i<ansd;i++)  printf(" %d",ans[i]);
			printf("\n");
		}
	}
	return 0;
}
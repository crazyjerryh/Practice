/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/14
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100010
#define tmod 1000000

int T,A,S,B;
int mat[1002];
int c1[maxn],c2[maxn];
int ans;
void solve(){
	memset(c1,0,sizeof(c1));
	c1[0]=1;
	for(int i=1;i<=T;i++){
		memset(c2,0,sizeof(c2));
		for(int j=0;j<=mat[i];j++){
			for(int k=0;k+j<=B;k++){
				c2[k+j]=(c2[k+j]+c1[k])%tmod;
			}
		}
		for(int j=0;j<=B;j++) c1[j]=c2[j];
	}
	
	ans=0;
	for(int i=S;i<=B;i++) ans=(ans+c1[i])%tmod;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&T)){
		scanf("%d%d%d",&A,&S,&B);
		memset(mat,0,sizeof(mat));
		for(int i=0;i<A;i++){
			int a;
			scanf("%d",&a);
		    mat[a]++;
		}
		solve();
		printf("%d\n",ans);
	}
	return 0;
}

/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/08
 * dp
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1010
#define tmod 1000000007
#define LL long long

int n,m;
LL ans;
int base[6]={0,1,3,7,15,31};
LL dp[50][maxn];
int bit[10];

bool check(int v){
	for(int i=0;i<m;i++){
		bit[i]=v%2;
		v=v/2;
	}
	int sum=0;
	for(int i=0;i<m;i++){
		if(bit[i]){
			if(sum%2) return false;
			else sum=0;
		}
		else sum++;
	}
	if(sum%2) return false;
	
	return true;
}

bool iscorr(int a,int b){
	for(int i=0;i<m;i++){
		if(a%2==1&&b%2==0) return false;
		a=a/2,b=b/2;
	}
	return true;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&m)){
		 memset(dp,0,sizeof(dp));
		 for(int i=0;i<=base[m];i++){
			 if(check(i)) dp[i][0]=1;
		 }

		 for(int i=1;i<n;i++){
			 for(int j=0;j<=base[m];j++){ 
			      if(!check(j)) continue;
				  for(int k=0;k<=base[m];k++){
				      if(!iscorr(k,j)) continue;
					  dp[j^k][i]=(dp[j^k][i]+dp[k][i-1])%tmod;
				  }
			 }
		 }
		 printf("%d\n",dp[0][n-1]);
	}
	return 0;
}
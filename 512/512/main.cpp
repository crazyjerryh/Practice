/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/25
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

#define maxn 300
int w[maxn<<2],vv[maxn<<2],v[maxn],num[maxn];
int c[maxn];
int dp[maxn];
int ww,n;

int tcase;
int main(void){
	//freopen("main.txt","r",stdin);
    scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&ww,&n);
		for(int i=1;i<=n;i++) scanf("%d%d%d",&c[i],&v[i],&num[i]);
		int cnt=0;
		for(int i=1;i<=n;i++){
			int t=1;
			while(num[i]-t>0){
				w[cnt]=c[i]*t;
				vv[cnt++]=v[i]*t;
				num[i]-=t;
				t=t*2;
			}
			w[cnt]=c[i]*num[i];
			vv[cnt++]=v[i]*num[i];
		}

		memset(dp,0,sizeof(dp));
		for(int i=0;i<cnt;i++){
			for(int j=ww;j>=w[i];j--)
				 dp[j]=max(dp[j],dp[j-w[i]]+vv[i]);
		}
		printf("%d\n",dp[ww]);
	}
	return 0;
}
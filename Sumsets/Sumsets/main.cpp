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
#define ll long long
#define maxn 1000100
#define tmod 1000000000
int bit[100];
int dp[maxn];

int n;
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		dp[1]=1;
		dp[2]=2;
		for(int i=3;i<=n;i++){
		    if(i%2) dp[i]=dp[i-1];
			else dp[i]=(dp[i-1]+dp[i/2])%tmod;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
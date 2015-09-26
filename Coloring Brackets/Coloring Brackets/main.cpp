/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/26
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stack>
#include <string>
#include <map>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define tmod 1000000007
#define ll long long
#define maxn 710

char str[maxn];
ll dp[maxn][maxn][3][3];
int match[maxn];
map<char,char> Map;
stack<int> stk;

void dfs(int l,int r){
	if(l+1==r){
		dp[l][r][0][1]=1;
		dp[l][r][0][2]=1;
		dp[l][r][1][0]=1;
		dp[l][r][2][0]=1;
		return;
	}
	
	if(match[l]==r){
		dfs(l+1,r-1);
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(j!=1)
					dp[l][r][0][1]=(dp[l][r][0][1]+dp[l+1][r-1][i][j])%tmod;
				if(i!=1)  
					dp[l][r][1][0]=(dp[l][r][1][0]+dp[l+1][r-1][i][j])%tmod;  
				if(j!=2)  
					dp[l][r][0][2]=(dp[l][r][0][2]+dp[l+1][r-1][i][j])%tmod;  
				if(i!=2)  
					dp[l][r][2][0]=(dp[l][r][2][0]+dp[l+1][r-1][i][j])%tmod;  
			}
		}
		return;
	}
	else{
		int p=match[l];
		dfs(l,p);
		dfs(p+1,r);
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					for(int q=0;q<3;q++){
						if(!((k==1 && q==1) || (k==2 && q==2)))  
							dp[l][r][i][j]=(dp[l][r][i][j]+(dp[l][p][i][k]*dp[p+1][r][q][j])%tmod)%tmod;  
					}
				}
			}
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%s",&str)){
	    while(!stk.empty()) stk.pop();
		int len=strlen(str);
		memset(dp,0,sizeof(dp));
		for(int i=0;i<len;i++){
			if(str[i]=='(') stk.push(i);
			else{
				match[i]=stk.top();
				match[stk.top()]=i;
				stk.pop();
			}
		}
		

		dfs(0,len-1);
		ll ans=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				 ans=(ans+dp[0][len-1][i][j])%tmod;  
			}
		}

		printf("%I64d\n",ans);
	}

	return 0;
}

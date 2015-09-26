/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/26
 * 
 */
#include <stdio.h>
#include <map>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 300

char str[maxn];
int dp[maxn][maxn];
map<char,char> Map;

void init(){
	Map.insert(make_pair('(',')'));
	Map.insert(make_pair('[',']'));
}

int main(void){
	//freopen("debug.txt","r",stdin);
	init();
	while(~scanf("%s",str)){
		if(str[0]=='e') break;
		int n=strlen(str);
		memset(dp,0,sizeof(dp));

		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(str[i]=='['||str[i]=='(') dp[j][i]=max(dp[j][i-1],dp[j][i]);
				else{
					dp[j][i]=max(dp[j][i-1],dp[j][i]);
					for(int k=j;k<i;k++){
						if(Map[str[k]]==str[i])
							dp[j][i]=max(dp[j][i],dp[j][k-1]+1+dp[k+1][i-1]);
					}
				}
			}
		}

		printf("%d\n",dp[0][n-1]*2);
	}
	return 0;
}

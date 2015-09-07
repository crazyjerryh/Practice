/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/07
 * 
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 110
int f[maxn][maxn];
char s[maxn];

// int dfs(int m,int n){
// 	if(m>n) return 0;
// 	if(m==n&&(str[n]=='0'||str[n]=='1'))	return dp[m][n]=1;
// 	if(m==n&&(str[n]!='0'&&str[n]!='1'))  return dp[m][n]=0;
// 	if(dp[m][n]!=-1) return dp[m][n];
// 	if(str[n]=='*')
// 		return dp[m][n]=dfs(m,n-1);
// 	if(str[m]=='('&&str[n]==')')
// 		if(dfs(m+1,n-1)) return dp[m][n]=1;
// 	for(int i=m;i<n;i++){
// 		if(str[i]=='|')
// 			if(dfs(m,i-1)&&dfs(i+1,n))  return dp[m][n]=1;
// 		else
// 			if(dfs(m,i)&&dfs(i+1,n)) return dp[m][n]=1;
// 	}
// 	return dp[m][n]=0;
// }

int dfs(int i,int j)  
{  
	//cout<<"i="<<i<<" j="<<j<<endl;  
	if(i>j) return 0;  
	if(i==j&&(s[i]=='0'||s[i]=='1')) return f[i][j]=1;  
	if(i==j&&(s[i]!='0'&&s[i]!='1')) return f[i][j]=0;  
	if(f[i][j]!=-1) return f[i][j];  
	if(s[j]=='*') return f[i][j]=dfs(i,j-1);  
	if(s[i]=='('&&s[j]==')')  
		if(dfs(i+1,j-1)) return f[i][j]=1;  
	for(int k=i;k<j;k++)  
		if(s[k]=='|')  
		{  
			if(dfs(i,k-1)&&dfs(k+1,j)) return f[i][j]=1;  
		}  
		else  
		{  
			if(dfs(i,k)&&dfs(k+1,j)) return f[i][j]=1;  
		}  
		return f[i][j]=0;  
}  

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%s",s)){
		memset(f,-1,sizeof(f));
		int n=strlen(s);
		if(dfs(0,n-1))  printf("yes\n");
		else printf("no\n");
	}
	return 0;
}

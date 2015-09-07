#include <cstdio>  
#include <cstring>  
using namespace std;  
const int maxn = 105;  
int f[maxn][maxn];  
char s[maxn];  
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
int main()  
{  
	freopen("in.txt","r",stdin);  
	while(~scanf("%s",s))  
	{  
		memset(f,-1,sizeof(f));  
		int len=strlen(s);  
		if(dfs(0,len-1))  
			printf("yes\n");  
		else printf("no\n");  
	}  
	return 0;  
}  
#include <stdio.h>
#include <string.h>
#include <memory.h>
#define maxn 50
char str[maxn];
int len,num;
char order[150];
int graph[maxn][maxn];
int degree[maxn];
int sum[maxn];
char buf[maxn];

void dfs(int dep)
{
	if(dep>=len){
		for(int i=0;i<len;i++)
			printf("%c",buf[i]);
		printf("\n");
	}	

	for(int i=0;i<26;i++){
		if(degree[i]==0&&sum[i]){
			sum[i]--;
			for(int j=0;j<26;j++)
				if(graph[i][j])
					degree[j]--;
			buf[dep]=char(i+'a');
			dfs(dep+1);
			for(int j=0;j<26;j++)
				if(graph[i][j])
					degree[j]++;
			sum[i]++;
		}
	}
}

int main(void)
{
	while(gets(str))
	{
		memset(sum,0,sizeof(sum));
		len=strlen(str);
		int i,j;
		for(i=0,j=0;i<len;i++){
			if(str[i]!=' '){
				sum[str[i]-'a']++;
				j++;
			}
		}
		len=j;

		memset(graph,0,sizeof(graph));
		memset(degree,0,sizeof(degree));
		gets(order);
		num=strlen(order);
		for(i=0,j=0;i<num;i+=2){
			int a=order[i]-'a';
			i+=2;
			int b=order[i]-'a';
			graph[a][b]=1;
			degree[b]++;
			j++;
		}

		num=j;
		dfs(0);
		printf("\n");
	}
	return 0;
}
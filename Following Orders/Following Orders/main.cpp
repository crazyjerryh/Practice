#include <iostream>
#include <vector>
#include <string.h>
#include <memory.h>
using namespace std;
#define maxn 60
int sum[40];
char str[maxn];
char buf[maxn];
char constrains[120];
std::vector<int> nodes[30];
int len;
int num;


void dfs(int dep)
{
	if(dep>=len){
		for(int i=0;i<len;i++)
			cout<<buf[i];
		cout<<endl;
		return;
	}
	
	for(int i=0;i<26;i++){
		if(sum[i]){
			sum[i]--;
			buf[dep]=i+'a';
			bool flag=true;
			for(int k=0;k<dep;k++)
			{
				int size=nodes[i].size();
				for(int j=0;j<size;j++){
					if(nodes[i][j]==(buf[k]-'a'))
					{
					     flag=false;
						 break;
					}
				}
			}
			if(flag)
			   dfs(dep+1);
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

		for(int i=0;i<len;i+=2){
		     sum[str[i]-'a']++;
		}
		len=len/2+1;
		gets(constrains);
		int len1=strlen(constrains);
		
		num=0;
		for(int i=0;i<len1;i+=2){
			int first=constrains[i]-'a';
			i+=2;
			int second=constrains[i]-'a';
			nodes[first].push_back(second);
		}

		dfs(0);
		cout<<endl;
		for(int i=0;i<26;i++)
			nodes[i].clear();
	}
	return 0;
}
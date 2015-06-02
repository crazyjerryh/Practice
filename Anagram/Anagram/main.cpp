#include <iostream>
#include <string.h>
#include <memory.h>
#define maxn 60
#define maxm 15
using namespace std;

int tcase;
int sum[maxn];
char str[maxm];
char buf[maxm];
char hashtable[maxn];
int len;

void dfs(int dep)
{
     if(dep>=len){
		 for(int i=0;i<len;i++)
			 cout<<buf[i];
		 cout<<endl;
	 }

	 for(int i=0;i<52;i++){
		 if(sum[i]>0){
		     sum[i]--;
			 if(i%2)
				 buf[dep]='a'+i/2;
			 else
				 buf[dep]='A'+i/2;
			 dfs(dep+1);
			 sum[i]++;
		 }
	 }
}

int main(void)
{
	cin>>tcase;
	for(int i=0;i<tcase;i++){
		cin>>str;
		len=strlen(str);
		memset(sum,0,sizeof(sum));
		for(int i=0;i<len;i++){
			if(str[i]>='a')
				sum[2*(str[i]-'a')+1]++;
			else
				sum[2*(str[i]-'A')]++;
		}
		dfs(0);
	}
	return 0;
}
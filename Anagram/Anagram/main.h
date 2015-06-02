#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <set>
using namespace std;
#define maxn 20

char str[maxn];
char buf[maxn];
int vis[maxn];
std::set<std::string> res;
int tcase;
int len;

void dfs(int dep)
{
	if(dep>=len)
	{
		std::string str="";
		for(int i=0;i<len;i++){
			str+=buf[i];
		}
		res.insert(str);
	}

	for(int i=0;i<len;i++){
		if(!vis[i]){
			vis[i]=1;
			buf[dep]=str[i];
			dfs(dep+1);
			vis[i]=0;
		}
	}
}

int main(void)
{
	cin>>tcase;
	for(int i=0;i<tcase;i++){
		cin>>str;
		len=strlen(str);
		dfs(0);

		for(std::set<std::string>::iterator iter=res.begin();iter!=res.end();++iter)
			cout<<*iter<<endl;
		res.clear();
	}
	return 0;
}
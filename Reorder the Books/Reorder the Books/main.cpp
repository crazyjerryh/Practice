/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/12
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

int tcase,n;
string src;
int best;

bool isend(string tmp){
	int len=tmp.size();
	for(int i=0;i<len;i++){
		char a=i+1+'a';
		if(tmp[i]!=a) return false;
	}
	return true;
}

void dfs(char val,string cur,int dep){
	if(isend(cur)){
		best=min(best,dep);
		return;
	}
	
	if(val<='a') return;
	string tmp="";
	tmp+=val;
	for(int i=0;i<cur.size();i++){
		if(cur[i]==val) continue;
		tmp+=cur[i];
	}
	dfs(val-1,tmp,dep+1);
}

int solve(){
	best=inf;
	if(isend(src)) return 0;
	for(int i=1;i<=n;i++){
		char val=i+'a';
		string cur="";
		cur+=val;
		for(int j=0;j<src.size();j++){
			if(src[j]==val) continue;
			cur+=src[j];
		}
		dfs(val-1,cur,1);
	}
	return best;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		src="";
		for(int i=0;i<n;i++) {
			int tmp;
			scanf("%d",&tmp);
			char a=tmp+'a';
			src+=a;
		}
		
		int ans=solve();
		printf("%d\n",ans);
	}
	return 0;
}

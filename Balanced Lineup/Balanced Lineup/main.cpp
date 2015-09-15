/*
* author Rotile_H
* file E:\POJ\Practice\Balanced Lineup\Balanced Lineup\main.cpp
* 2015 9 15
*/
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 50100

int a[maxn][30],b[maxn][30];
int s[maxn];
int n,q;

void rmqinit(){
	for(int i=1;i<=n;i++)  a[i][0]=b[i][0]=s[i];

	for(int j=1;j<20;j++){
		for(int i=1;i<=n;i++){
			if(i+(1<<j)-1<=n){
				a[i][j]=max(a[i][j-1],a[i+(1<<(j-1))][j-1]);
				b[i][j]=min(b[i][j-1],b[i+(1<<(j-1))][j-1]);
			}
		}
	}
}


int query(int l,int r){
	int len=(int)(log(1.0*(r-l+1))/log(2.0));
	int mmax=max(a[l][len],a[r-(1<<len)+1][len]);
	int mmin=min(b[l][len],b[r-(1<<len)+1][len]);
	return mmax-mmin;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&q)){
		for(int i=1;i<=n;i++){
			scanf("%d",&s[i]);
		}
		rmqinit();
		int l,r;
		for(int i=0;i<q;i++){
		  scanf("%d%d",&l,&r);
		  int ans=query(l,r);
		  printf("%d\n",ans);
		}
	}
	return 0;
}
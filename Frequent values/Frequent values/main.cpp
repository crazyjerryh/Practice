/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/19
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn  100100

int n,q;
int a[maxn],cnt[maxn],l[maxn],r[maxn];
int total[maxn];
int dp[maxn][30];
int m;

void rmqinit(){
	for(int i=0;i<=m;i++) dp[i][0]=cnt[i];

	for(int j=1;j<30;j++){
	     for(int i=0;i<=m;i++){
			 if(i+(1<<j)-1<=m){
			      dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
			 }
		 }
	}
}

int query(int l,int r){
	 int len=(int)(log(1.0*(r-l+1))/log(2.0));
	 return max(dp[l][len],dp[r-(1<<len)+1][len]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		if(n==0) break;
		scanf("%d",&q);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		int cur=-1;
		for(int i=1;i<=n;i++){
			if(i==1||a[i]!=a[i-1])  cnt[++cur]=1;
			else if(a[i]==a[i-1])  cnt[cur]++;
		}

		total[0]=0;
		for(int i=1;i<=cur;i++){
			total[i]=total[i-1]+cnt[i-1];
		}

		int k=0,sum=cnt[k];
		for(int i=1;i<=n;i++){
			if(i<=sum) l[i]=k;
			else{
				k++;
				sum+=cnt[k];
				l[i]=k;
			}
		}
		
		m=cur;
		rmqinit();

		for(int i=0;i<q;i++){
			int l1,r1;
			scanf("%d%d",&l1,&r1);
			int L=l[l1]+1,R=l[r1]-1;
			if(l[l1]==l[r1]){
				printf("%d\n",r1-l1+1);
				continue;
			}
			int res=0;
			if(R>=L)
			   res=query(L,R);
			
			res=max(res,cnt[l[l1]]-l1+total[l[l1]]+1);
			res=max(res,r1-total[l[r1]]);
			printf("%d\n",res);
		}
	}
}

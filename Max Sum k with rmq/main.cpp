#include <stdio.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 200010
#define inf 0x3f3f3f3f

int tcase;
int n,k; 
int a[maxn],sum[maxn];
int dp[22][maxn];
void init_RMQ(){
     for(int i=1;i<=2*n;i++){
     	 dp[0][i]=i; 
	 }	
	 
	 for(int i=1;i<22;i++){
	 	 for(int j=1;j<=2*n;j++){
	 	 	 if(j+(1<<i)-1<=2*n){
	 	 	 	 if(sum[dp[i-1][j]]<sum[dp[i-1][j+(1<<(i-1))]])   
	 	 	          dp[i][j]=dp[i-1][j];	
	 	 	     else 
	 	 	          dp[i][j]=dp[i-1][j+(1<<(i-1))];
			 }
		  }
	 }
}

int get_min(int l,int r){
	int len=log(1.0*(r-l+1))/log(2.0);
	 if(sum[dp[len][l]]<sum[dp[len][r-(1<<len)+1]])
	 	 	return dp[len][l];	
	 else 
	 	 	return dp[len][r-(1<<len)+1];
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=n+1;i<n+k;i++){
			a[i]=a[i-n];
		}
		sum[1]=0;
		for(int i=2;i<n+k;i++){
			sum[i]=sum[i-1]+a[i-1];
		}
		init_RMQ();
		int ans=-inf;
		int first,second;
		first=second=1;
		for(int i=1;i<n+k;i++){
		    int l=(i-k+1)<1?1:i-k+1;
		    int tmp=sum[i]+a[i]-sum[get_min(l,i)]; //get_min是得到当前的 
		    if(tmp>ans){
		    	ans=tmp;
		    	first=get_min(l,i),second=i;
			} 
		}
		if(second>n) second=second%n;
		printf("%d %d %d\n",ans,first,second);
	}
	return 0;
} 

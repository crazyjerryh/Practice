#include <stdio.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 100005
int qmax[maxn][20],qmin[maxn][20];
int n,m,k;
int a[maxn];

void init_RMQ(){
	for(int i=1;i<=n;i++){
		qmax[i][0]=a[i],qmin[i][0]=a[i];
	} 
	
    for(int i=1;i<20;i++){
    	for(int j=1;j<=n;j++){
    		if(j+(1<<i)-1<=n){
    		    qmax[j][i]=max(qmax[j][i-1],qmax[j+(1<<(i-1))][i-1]);
    	    	qmin[j][i]=min(qmin[j][i-1],qmin[j+(1<<(i-1))][i-1]);
    	   }
		} 
	} 

}

int get_max(int l,int r){
	int len=log((r-l+1)*1.0)/log(2.0);
	return max(qmax[l][len],qmax[r-(1<<len)+1][len]); 
}

int get_min(int l,int r){ 
	int len=log((r-l+1)*1.0)/log(2.0);
	return min(qmin[l][len],qmin[r-(1<<len)+1][len]);
}

void solve(){
	int l,r;
	int ans=0;
	for(int i=1,r=1,l=1;i<=n;i++){
		r=i;
	    int t=get_max(l,r)-get_min(l,r); 
	    if(t<=k&&t>=m){
	    	ans=max(r-l+1,ans); //最大值和最小值的差 
		} 
	    else if(t<m)  continue;
	    else 
		    while(l<=r&&(get_max(l,r)-get_min(l,r))>k)  l++;  //get_max and get_min to be the  
	}
	printf("%d\n",ans);
}

int main(void){
	//freopen("debug.txt","r",stdin); 
   	while(scanf("%d%d%d",&n,&m,&k)!=EOF){
   		for(int i=1;i<=n;i++){
   		    scanf("%d",&a[i]);	
		} 
		init_RMQ();
		solve();
	}
} 

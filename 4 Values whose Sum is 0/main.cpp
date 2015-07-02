#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 4010
#define maxm 16001000
int A[maxn],B[maxn],C[maxn],D[maxn];
int E[maxm],F[maxm];
int n;
int cnt;

int search(int num){
	int l=1,r=cnt;
	int mid;
	bool flag=false;
	while(l<=r){
		mid=(l+r)>>1;
		if(F[mid]==num) {
		      flag=true;
			  break;	
		} 
		if(F[mid]>num)  r=mid-1;
		else if(F[mid]<num) l=mid+1;
	}
	
	if(!flag)  return 0;
	int ans=1;
	for(int i=mid-1;i>=1&&F[i]==F[mid];--i)  ans++;
	for(int i=mid+1;i<=cnt&&F[i]==F[mid];++i)  ans++;
	return ans;
}

int solve()
{
	  int res=0,ans=0;
      for(int i=1;i<=cnt;i++)
      {
      	       ans=search(-E[i]);
      	       res+=ans;
	  } 
	  return res;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
		}
		cnt=0;
		for(int i=1;i<=n;i++){
		    for(int j=1;j<=n;j++){
		    	 E[++cnt]=A[i]+B[j];
			}
		}
		cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				F[++cnt]=C[i]+D[j];
			}
		}
		sort(F+1,F+cnt+1);
		int ans=solve();
		printf("%d\n",ans);
	}
	return 0;
} 

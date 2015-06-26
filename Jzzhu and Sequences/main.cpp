#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define tmod 1000000007

#define LL long long

struct Matrix{
	LL x[2][2];
	Matrix(){
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				x[i][j]=0;
			}
		}
	}
}mat;

LL f[2],n;
Matrix mul(Matrix a,Matrix b)
{
	 Matrix c;
	 for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				  c.x[i][j]=(c.x[i][j]+a.x[i][k]*b.x[k][j])%tmod;
			}
		}
	 }
	 return c;
}

LL solve(){
	Matrix ans;
	ans.x[0][0]=1,ans.x[0][1]=0,ans.x[1][0]=0,ans.x[1][1]=1;
	Matrix c;
	c.x[0][0]=0,c.x[0][1]=1,c.x[1][0]=-1,c.x[1][1]=1;
	LL cur=n-2;
	while(cur){
		if(cur&1) ans=mul(ans,c);
		c=mul(c,c);
		cur=cur>>1;
	}

	LL res=((f[1]*ans.x[1][1]+f[0]*ans.x[1][0])%tmod+tmod)%tmod;
	return res;
}

int main(void){
    //freopen("debug.txt","r",stdin);
	while(scanf("%lld%lld",&f[0],&f[1])!=EOF){
		scanf("%lld",&n);
		if(n==1){
			printf("%lld\n",(f[0]%tmod+tmod)%tmod);
		}
		else if(n==2){
			printf("%lld\n",(f[1]%tmod+tmod)%tmod);
		}
		else{
			LL ans=solve();
			printf("%lld\n",ans);
		}
	}
}

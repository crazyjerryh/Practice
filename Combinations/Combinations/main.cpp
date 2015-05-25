#include <iostream>
using namespace std;
#define tmod 1000003
#define maxn 1000010

typedef long long LL;
LL dp[maxn];
LL tcase;
LL n,k;
void init()
{
	dp[0]=1;
	for(int i=1;i<maxn;i++)
		dp[i]=dp[i-1]*i%tmod;
}

LL extendgcd(LL &x,LL &y,LL a,LL b)
{
	 if(b==0){
		 x=1;
		 y=0;
		 return a;
	 }
	 LL d=extendgcd(x,y,b,a%b);
	 LL t=x;
	 x=y;
	 y=t-(a/b)*y;
	 return d;
}

LL calc()
{
   LL r=dp[k]*dp[n-k]%tmod;
   LL x,y;
   LL d=extendgcd(x,y,r,tmod);
   x=(x%tmod+tmod)%tmod;
   return (x*dp[n])%tmod; 
}

int main(void)
{
	cin>>tcase;
	init();
	for(int i=1;i<=tcase;i++){
		cin>>n>>k;
		LL result=calc();
        cout<<"Case "<<i<<": "<<result<<endl;
	}
	return 0;
}
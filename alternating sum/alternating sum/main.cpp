#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;
//ofstream fout("debug.txt");

typedef unsigned long long ULL;
typedef long long LL;
#define tmod 1000000007
#define maxn 220
#define LEN 20
#define WEI 11

#define ADJUST 101

LL first,second,k;
LL dp[LEN][WEI][maxn];
LL sum[LEN][WEI][maxn];
int bit[LEN];
int cnt;

ULL pow(LL num,int n)
{
	if(num==0)
		return 0;

     LL basenum=1;
	 for(int i=1;i<n;i++){
		 basenum*=10;
	 }

	 ULL res=1;
	 while(num)
	 {
		 if(num&1)
			 res=(res*basenum)%tmod;
		 basenum=(basenum*basenum)%tmod;
		 num=num>>1;
	 }
	 return res;
}

void init(void)
{
	memset(dp,0,sizeof(dp));
	memset(sum,0,sizeof(sum));
	for(int i=0;i<=9;i++)
	{
		dp[1][i][i+ADJUST]=1;
		sum[1][i][i+ADJUST]=i;  //相加的和
	}

	for(int len=2;len<LEN;len++){
		for(int i=0;i<=9;i++){
			
			for(int j=0;j<=9;j++){
				for(int l=0;l<maxn;l++){
					dp[len][i][i-(l-ADJUST)+ADJUST]+=dp[len-1][j][l];
					dp[len][i][i-(l-ADJUST)+ADJUST]=dp[len][i][i-(l-ADJUST)+ADJUST]%tmod;
					//相加的和,满足条件的和
					sum[len][i][i-(l-ADJUST)+ADJUST]=(sum[len][i][i-(l-ADJUST)+ADJUST]+sum[len-1][j][l])%tmod+((pow(dp[len-1][j][l],len))%tmod*i)%tmod;
				}
			}
		}
	}
}

LL calc(LL n)
{
	LL temp=n;
    cnt=0;
	LL result=0;
	while(n){
		bit[++cnt]=n%10;
		n=n/10;
	}
	
	for(int i=1;i<cnt;i++){
		for(int j=(i==1)?0:1;j<=9;j++){
			result=(result+sum[i][j][k+ADJUST])%tmod;
		}
	}
	LL num=0;
	for(int i=cnt;i>=1;i--){
		int sgn=1;
		
		int prev=0;
		for(int j=cnt;j>i;j--){
			prev+=sgn*(bit[j]);
			sgn=-sgn;
		}
		
	    for(int j=((i==cnt)?1:0);j<bit[i];j++){
			LL cur=sgn*(k-prev);
			cur+=ADJUST;
			if(dp[i][j][cur])
			{
	        		result=(result+((num*pow((LL)i,2))%tmod+sum[i][j][cur])%tmod)%tmod;
			}
		}
		num=num*10+bit[i];
	}

    int sgn=1;
	int prev=0;
	for(int i=cnt;i>=1;i--){
		prev+=sgn*bit[i];
		sgn=-sgn;
	}

	if(prev==k)
		result=(result+temp)%tmod;

	return result;
}

int main(void)
{
	while(cin>>first>>second)
	{
		cin>>k;
		init();

		cout<<(calc(second)-calc(first-1)+tmod)%tmod<<endl;
	}
	return 0;
}
#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define LL long long 
LL n;

LL solve(){
    LL ans=n,cur=n;
    LL res=1;
	while(cur>0){
		if(cur&1)  res=res*ans%10; 
		ans=ans*ans%10;
		cur=cur>>1;
	}	
    return res%10;
}

int main(void){
	//reopen("debug.txt","r",stdin);
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld",&n);
		LL ans=solve();
		printf("%lld\n",ans);
	}
	return 0;
} 

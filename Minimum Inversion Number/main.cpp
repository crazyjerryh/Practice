#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 5010
int sum[maxn],a[maxn];
int n;
int lowbit(int x){
	return x&-x;
}

int get_sum(int x){
	int ans=0;
	while(x>0){
		ans+=sum[x];
		x-=lowbit(x);
	}
	return ans;
}

void update(int x,int num){
	while(x<=n){
		sum[x]+=num;
		x+=lowbit(x);
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		 memset(sum,0,sizeof(sum));
		 int ans=0;
		 for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			update(a[i]+1,1);
			ans+=i-get_sum(a[i]+1);
		 }

		int res=ans;
		//printf("%d\n",ans);
		for(int i=1;i<n;i++){
			ans=ans-a[i]+n-1-a[i];
			//printf("%d\n",ans);
			if(ans<res)
				res=ans;
		}
		printf("%d\n",res);
	}
	return 0;
}

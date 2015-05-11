#include <stdio.h>
#include <memory.h>
#include <vector>
using namespace std;
#define maxn 100002

int n,tcase;
int root;
std::vector<int> map[maxn];
int dp[maxn];

void dfs(int deep)
{
	int size=map[deep].size();
	for(int i=0;i<size;i++){
	     int child=map[deep][i];
		 dfs(child);
		 dp[deep]+=dp[child];
	}
}

int main(void)
{
	scanf("%d",&tcase);
	while(tcase--){
 		scanf("%d%d",&n,&root);
 		for(int i=0;i<maxn;i++)
			dp[i]=0;

		for(int i=0;i<n-1;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			map[a].push_back(b);
			map[b].push_back(a);
		}

		for(int i=1;i<=n;i++)
			scanf("%d",&dp[i]);
		
 		dp[root]=0;
        dfs(root);
		dp[root]=0;
		int size=map[root].size();
		for(int i=0;i<size;i++)
			dp[root]=max(dp[root],dp[map[root][i]]);

 		printf("Case #%d: %d\n",tcase+1,dp[root]);
 		for(int i=1;i<=n;i++)
 			map[i].clear();
	}
	return 0;
}
#include <stdio.h>
using namespace std;

#define maxn 40
int n;
int map[maxn][maxn];

int solve()
{
	 int ans=0;
     for(int i=0;i<n;i++){
		 for(int j=i+1;j<n;j++)
			 ans+=map[i][j];
	 }	
	 return ans;
}

int main(void)
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				scanf("%d",&map[i][j]);
			}

        int ans=2*n;
		int res=solve();
		printf("%d\n",ans+2*res);
	}
	return 0;
}
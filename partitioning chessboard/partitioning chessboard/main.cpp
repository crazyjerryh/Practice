#include <stdio.h>
#include <vector>
#include <memory.h>
using namespace std;
#define maxn 10
std::vector<int> map[maxn];

int n,m;
int vis[maxn];
int ans;
int cur;

void dfs(int dep)
{
	if(cur>=m){
		ans++;
		return;
	}

	if(dep>=n)
		return;

	if(cur+n-dep<m)
		return;
	
	
	int size=map[dep].size();
	int cnt=0;
	for(int i=0;i<size;i++){
		int j=map[dep][i];
		if(!vis[j]){
			cnt++;
			vis[j]=1;
			cur++;
			dfs(dep+1);
			cur--;
			vis[j]=0;
		}
	}
    dfs(dep+1);
}

int main(void)
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n==-1&&m==-1)  break;
		int cnt=0;
		getchar();
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				char c;
				scanf("%c",&c);
				if(c=='#')
				{
				   map[i].push_back(j);
				   cnt++;
				}
			}
			getchar();
	    }

	  if(cnt<m)
	  {
		  printf("0\n");
		  continue;
	  }
	  
	  ans=0;
	  cur=0;
	  memset(vis,0,sizeof(vis));
	  dfs(0);
	  printf("%d\n",ans);

	  for(int i=0;i<n;i++)
		  map[i].clear();
	}
	return 0;
}
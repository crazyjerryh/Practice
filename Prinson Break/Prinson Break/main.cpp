//TLE
#include <iostream>
using namespace std;
#define maxm 1010
#define maxn 110

#define INF 0xfffff

struct _edge
{
	int u,v,w;
}edges[maxm<<1];

typedef struct _edge edge;
int price[maxn];
int n,m,tcase,q;
int s,t;
int cap;
int map[maxn][maxn];
int dp[maxn][maxn];

int main(void)
{
	cin>>tcase;
	while(tcase--){
          cin>>n>>m;

		  for(int i=0;i<n;i++){
			  cin>>price[i];
		  }

		  for(int i=0;i<m;i++){
			  int a,b,w;
			  cin>>a>>b>>w;
			  edges[2*i].u=a;
			  edges[2*i].v=b;
			  edges[2*i].w=w;

			  edges[2*i+1].u=b;
			  edges[2*i+1].v=a;
			  edges[2*i+1].w=w;
		  }

		  cin>>q;
		  cout<<"Case "<<tcase+1<<":"<<endl;
		  for(int p=0;p<q;p++){
			  cin>>cap>>s>>t;
			  
			  for(int i=0;i<maxn;i++)
				  for(int j=0;j<maxn;j++)
					  dp[i][j]=INF;

			  for(int i=0;i<=cap;i++)
				  dp[s][i]=i*price[s];
			  
			  for(int i=0;i<n-1;i++){
			      for(int j=0;j<2*m;j++){
					  int u,v,w;
					  u=edges[j].u;
					  v=edges[j].v;
					  w=edges[j].w;

					  for(int k=w;k<=cap;k++){
			              if(dp[u][k]!=INF){
							  for(int l=0;l<=(cap-k+w);l++){
							       if(dp[v][l+k-w]>dp[u][k]+price[v]*l){
									   dp[v][l+k-w]=dp[u][k]+price[v]*l;
								   }
							  }
						  }
					  }
				  }
			  }
			if(dp[t][0]==INF)
				cout<<"impossible"<<endl;
			else
			{
				cout<<dp[t][0]<<endl;
			}
		  }
	}
	return 0;
}
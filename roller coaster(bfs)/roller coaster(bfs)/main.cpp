#include <stdio.h>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 510

int n,m,k;
int match[maxn],vis[maxn];
int match2[maxn];
int pre[maxn];
int _next[maxn];
int graph[maxn][maxn];
int main(void)
{
	while(scanf("%d",&k)!=EOF){
		 if(k==0)  break;
	     scanf("%d%d",&m,&n);
		 memset(graph,0,sizeof(graph));
		 for(int i=0;i<k;i++){
		     int a,b;
			 scanf("%d%d",&a,&b);
			 graph[a][b]=1;
		 }
		 
		 memset(match,0,sizeof(match));
		 memset(match2,0,sizeof(match2));
		 int ans=0;
		 for(int i=1;i<=m;i++){
			 int p;
			 std::queue<int> Q; 
			 while(!Q.empty())  Q.pop();
			 memset(vis,0,sizeof(vis));
			 memset(pre,0,sizeof(pre));
			 bool flag=false;
			 int des;
			 for(int j=1;j<=n;j++){
				 if(graph[i][j]&&!vis[j]){
					 if(match[j]==0){
						 match[j]=i;
			             des=i;
						 p=j;
						 flag=true;
						 break;
					 }  
					 else
					 {
						 vis[j]=1;
						 pre[match[j]]=i;
						 _next[i]=match[j];
						 Q.push(match[j]);
					 }
				 }
			 }
			if(flag)
			   while(!Q.empty()) Q.pop();

			 while(!Q.empty()){
				 int top=Q.front();
				 Q.pop();
				 for(int j=1;j<=n;j++){
					 if(graph[top][j]&&!vis[j]){
						 if(match[j]==0){     //match rep the boy
							  match[j]=top; 
							  des=top;
							  p=j;
							  flag=true;
							  break;
						 }
						 else
						 {
							 vis[j]=1;
							 pre[match[j]]=top; //top link to the j
							 _next[top]=match[j];
							 Q.push(match[j]);
						 }
					 }
				 }

			 }
	
			 int cur=des;
			 while(cur!=i){    //des is the find unmatching girl 
			      int tmp=pre[cur];
				  match[match2[cur]]=tmp;
				  cur=tmp;
			 }
			 cur=i;
			 while(cur!=des){
			      int tmp=_next[cur];
				  match2[cur]=match2[tmp];
				  cur=tmp;
			 }
			 match2[des]=p;

			 //check the path from i to the 
			if(match2[i]!=0) ans++;
		 }
		 printf("%d\n",ans);
	}
	return 0;
}
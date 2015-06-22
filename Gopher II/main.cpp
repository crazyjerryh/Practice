 #include <stdio.h>
 #include <memory.h>
 #include <algorithm>
 using namespace std;
 
 #define maxn 110
 #define inf 0xfffff
 
 struct _point{
 	float x,y;
 };
 typedef struct _point point;

 int n,m,s,v;
 int mat[maxn][maxn];
 int vis[maxn],match[maxn];
 point a[maxn],b[maxn];
 
 int isLine(point a1,point b1)
 {
      float ans;
      ans=(a1.x-b1.x)*(a1.x-b1.x)+(a1.y-b1.y)*(a1.y-b1.y);
      int res=(int)ans;
      if(res<(s*v*s*v))
          return 1;
      return 0;
 } 
 
 bool dfs(int a)
 {
 	for(int i=0;i<m;i++){
 		 if(vis[i]==0&&mat[a][i]){
 		 	  vis[i]=1;
 		 	  if(match[i]==-1||dfs(match[i])){
 		 	       match[i]=a;
				   return true;	
			  }
		 }
	 }
	 return false;
 }
 
 int solve()
 {
 	int ans=0;
 	memset(match,-1,sizeof(match));
 	for(int i=0;i<n;i++){
 		 memset(vis,0,sizeof(vis));
 		 if(dfs(i)) ans++;
	 }
	 return ans;
 }
 
int main(void)
{
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d%d%d",&n,&m,&s,&v)!=EOF){
		for(int i=0;i<n;i++)
			scanf("%f%f",&a[i].x,&a[i].y);
			
		for(int i=0;i<m;i++)
		    scanf("%f%f",&b[i].x,&b[i].y);
		
		memset(mat,0,sizeof(mat));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				 if(isLine(a[i],b[j]))
				     mat[i][j]=1;
			}
		}
		
		int ans=solve();
		printf("%d\n",n-ans);
	}
 	return 0;
} 

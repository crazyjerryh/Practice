#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 510
using namespace std;
const int inf=1<<30;
int s[N][N],lx[N],ly[N],mat[N],slack[N],n;
bool vx[N],vy[N];
bool dfs(int u){
    vx[u]=1;
    for(int i=1;i<=n;i++){
    	    if(vy[i])  continue; 
            int t=lx[u]+ly[i]-s[u][i];
            if(t==0){
                vy[i]=1;
                if(mat[i]==-1||dfs(mat[i])){
                    mat[i]=u;
                    return 1;
                }
            }else slack[i]=min(slack[i],t);
    }
    return 0;
}
void KM(){
    memset(mat,-1,sizeof(mat));
    memset(ly,0,sizeof(ly));
    memset(lx,0,sizeof(lx));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],s[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)slack[j]=inf;
        while(1){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if(dfs(i))break;
            int d=inf;
            for(int j=1;j<=n;j++)
                if(!vy[j])d=min(d,slack[j]);
            for(int j=1;j<=n;j++)
                if(vx[j])lx[j]-=d;
            for(int j=1;j<=n;j++)
                if(vy[j])ly[j]+=d;
        }
    }
    int ans=0;
    for(int i=1;i<n;i++){
        printf("%d ",lx[i]);
        ans+=lx[i];
    }
    printf("%d\n",lx[n]);
    ans+=lx[n];
    for(int  i=1;i<n;i++){
        printf("%d ",ly[i]);
        ans+=ly[i];
    }
    printf("%d\n",ly[n]);
    ans+=ly[n];
    printf("%d\n",ans);
}
int main(){
	freopen("debug.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&s[i][j]);
        KM();
    }
    return 0;
}

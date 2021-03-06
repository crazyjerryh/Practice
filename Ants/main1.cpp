#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#define N 110
using namespace std;
typedef long long ll;
const double inf=1e40;
const double eps=1e-6;
double s[N][N],slack[N];
double lx[N],ly[N];
int mat[N],n;
bool vx[N],vy[N];
bool dfs(int u){
    vx[u]=1;
    for(int i=1;i<=n;i++){
        if(!vy[i]){
            double t=lx[u]+ly[i]-s[u][i];
            if(fabs(t)<eps){
                vy[i]=1;
                if(mat[i]==-1||dfs(mat[i])){
                    mat[i]=u;
                    return 1;
                }
            }
			else 
			    slack[i]=min(slack[i],t);
        }
    }
    return 0;
}
void KM(){
    memset(mat,-1,sizeof(mat));
    memset(ly,0,sizeof(ly));
    for(int i=1;i<=n;i++){
        lx[i]=-inf;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],s[i][j]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)slack[j]=inf;
        while(1){
            memset(vx,0,sizeof(vx));
            memset(vy,0,sizeof(vy));
            if(dfs(i))break;
            double d=inf;
            for(int j=1;j<=n;j++)
                if(!vy[j])d=min(d,slack[j]);
            for(int j=1;j<=n;j++)
                if(vx[j])lx[j]-=d;
            for(int j=1;j<=n;j++)
                if(vy[j])ly[j]+=d;
        }
    }
    for(int i=1;i<=n;i++)
        printf("%d\n",mat[i]);
}
double bx[N],by[N],wx[N],wy[N];
double dis(int i,int j){
    return sqrt((wx[i]-bx[j])*(wx[i]-bx[j])+(wy[i]-by[j])*(wy[i]-by[j]));
}
int main(){
    int flag=0;
    //freopen("debug.txt","r",stdin);
    while(cin>>n){
        for(int i=1;i<=n;i++)cin>>bx[i]>>by[i];  
        for(int i=1;i<=n;i++)cin>>wx[i]>>wy[i];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                s[i][j]=-dis(i,j);  
        if(flag)printf("\n");
        KM();
        flag=1;
    }
    return 0;
}

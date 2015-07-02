#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <cmath>
using namespace std;
#define maxn 110
const double delta=1e-6;
const double inf=0x3f3f3f3f;
struct _node{
	double x,y;
}ants[maxn],apples[maxn];

typedef struct _node node;
double mat[maxn][maxn];
int vx[maxn],vy[maxn];
double lx[maxn],ly[maxn],slack[maxn];
int match[maxn];
int n;

bool dfs(int u){
    vx[u]=1;
    for(int i=1;i<=n;i++){
        if(!vy[i]){
            double t=lx[u]+ly[i]-mat[u][i];
            if(fabs(t)<delta){
                vy[i]=1;
                if(match[i]==-1||dfs(match[i])){
                    match[i]=u;
                    return 1;
                }
            }
			else 
			    slack[i]=min(slack[i],t);
        }
    }
    return 0;
}
void solve(){
	memset(match,-1,sizeof(match));
	memset(ly,0,sizeof(ly));
	for(int i=1;i<=n;i++){
		lx[i]=-inf;
        for(int j=1;j<=n;j++){
        	  lx[i]=max(lx[i],mat[i][j]);
		}
	}
	
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++)  slack[j]=inf;
	    while(1){
	    	memset(vx,0,sizeof(vx));
	    	memset(vy,0,sizeof(vy));
	    	if(dfs(i)) break;
	    	double d=inf;
	    	for(int j=1;j<=n;j++)
	    	    if(!vy[j]) 
				      d=min(d,slack[j]);
		
			for(int j=1;j<=n;j++){
				if(vx[j]) lx[j]-=d;
				if(vy[j]) ly[j]+=d;
			} 
		
		}
	}
	
	for(int i=1;i<=n;i++){
		printf("%d\n",match[i]);
	}
}

double dis(int i,int j){
	return sqrt((-ants[j].x+apples[i].x)*(-ants[j].x+apples[i].x)+(-ants[j].y+apples[i].y)*(-ants[j].y+apples[i].y));
}

int main(void){
	bool flag=0;
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&ants[i].x,&ants[i].y);  //ant
		}
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&apples[i].x,&apples[i].y);  //apple
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				mat[i][j]=-dis(i,j);
			}
		}
		
		if(flag)  printf("\n");
		solve();
		flag=1;
	}
} 

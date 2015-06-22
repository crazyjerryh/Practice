#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 32010

struct _point{
	int x,y;
}a[maxn];

typedef struct _point point;
int n;
int tree[maxn],sum[maxn];
int m;

void update(int x,int num){
	while(x<=m){
		 tree[x]+=num;
		 x=x+(x&-x);
	}
}

int getsum(int x){
	int ans=0;
	while(x){
		ans+=tree[x];
		x=x-(x&-x);
	}
	return ans;
}

void solve(){
    memset(sum,0,sizeof(sum));
    memset(tree,0,sizeof(tree));
    for(int i=0;i<n;i++){
    	update(a[i].x,1);
        int ans=getsum(a[i].x);  //get the result of the sequence
        sum[ans-1]++;
	}
	for(int i=0;i<n;i++)
	    printf("%d\n",sum[i]);
}

int main(void)
{
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		m=-1;
		for(int i=0;i<n;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			a[i].x=x+1,a[i].y=y+1;
			if(a[i].x>m)
			     m=a[i].x;
		}
		solve();
	}
	return 0;
}

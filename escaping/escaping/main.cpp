#include <stdio.h>
#include <string.h>
#include <queue>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;

#define maxn 33000
#define maxm 110010
struct edge{
	int a,b;
	int next;
}edges[maxm];
int tcase,n,m;
int cnt;
int head[maxn],degree[maxn],ans[maxn];
struct cmp{
public:
	bool operator()(const int a,const int b){
		return a<b;
	}
};
priority_queue<int> Q;

void init(){
	cnt=0;
	memset(head,-1,sizeof(head));
	memset(degree,0,sizeof(degree));
}

void addedge(int a,int b){
	edges[cnt].a=a,edges[cnt].b=b;
    edges[cnt].next=head[a],head[a]=cnt++;
}

void solve(){
	//while(!Q.empty()) Q.pop();
    for(int i=1;i<=n;i++) if(degree[i]==0)  Q.push(i);
	int j=0;
	while(!Q.empty()){
		int front=Q.top();
		Q.pop();
	    for(int i=head[front];i!=-1;i=edges[i].next){
			int v=edges[i].b;
			degree[v]--;
			if(degree[v]==0) Q.push(v);
		}
	    ans[j++]=front;
	}
	for(int i=n-1;i>=0;i--) if(i==n-1) printf("%d",ans[i]);
	else printf(" %d",ans[i]);
	printf("\n");
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		init();
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			addedge(b,a);
			degree[a]++;
		}
		solve();
	}
	return 0;
}
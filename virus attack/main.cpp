#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <queue>
#include <algorithm>
using namespace std;
#define maxn  10010
#define maxm 210
#define maxl 510
#define inf 0x3f3f3f3f

// use array to realize
struct _node{
	int next[128];
	int fail;
	int type;
	void init(){
		for(int i=0;i<128;i++)  next[i]=-1;
		fail=-1;
		type=0;
	}
	//初始化数据
}tree[100010];

typedef struct _node node;
int vis[maxl];
int m,n;
int cnt, root;
int res;
char src[maxn];

void insert(char tmp[],int type){
	int len=strlen(tmp);
	int cur=root;
	for(int i=0;i<len;i++){
		int inx=tmp[i];
		if(tree[cur].next[inx]==-1){
		   tree[++cnt].init();
		   tree[cur].next[inx]=cnt;
		}
		cur=tree[cur].next[inx];
	}
	tree[cur].type=type;
}

void build(){
	queue<int> Q;
	tree[root].fail=root;
	for(int i=0;i<128;i++){
		if(tree[root].next[i]==-1) tree[root].next[i]=root;  //指针指向root
		else{
			int tmp=tree[root].next[i];  //tree[root]
			tree[tmp].fail=root;
			Q.push(tmp);
		}
	}

	while(!Q.empty()){
		int front=Q.front();
		Q.pop();

		for(int i=0;i<128;i++){
			if(tree[front].next[i]==-1){
				int tmp=tree[front].fail;
				tree[front].next[i]=tree[tmp].next[i];
			}
			else{
				int p=tree[front].next[i];
				int tmp=tree[front].fail;
				tree[p].fail=tree[tmp].next[i];
				Q.push(p);
			}
		}
	}
}

int query(){
	int len=strlen(src);
	int flag=0;
	int cur=root;
	for(int i=0;i<len;i++){
		int inx=src[i];
		cur=tree[cur].next[inx];
		int tmp=cur;
		while(tmp!=root){
			 if(tree[tmp].type){
				 vis[tree[tmp].type]=1;
				 flag++;
			 }
			 tmp=tree[tmp].fail;
		}
	}
	return flag;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&m)!=EOF){
		root=0;
		tree[root].init();
		cnt=0;
		for(int i=0;i<m;i++){
			char tmp[maxm];
			scanf("%s",tmp);
			insert(tmp,i+1);
		}
		build();
		scanf("%d",&n);
		int count=0;
		for(int i=0;i<n;i++){
			memset(vis,0,sizeof(vis));
			scanf("%s",src);
			int ans=query();  //一共有多少个病毒特征码
			if(ans){
			    printf("web %d:",i+1);
				for(int i=1;i<=m;i++){
					if(vis[i])
						printf(" %d",i);
				}
				printf("\n");
				count++;
			}
		}
		printf("total: %d\n",count);
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <queue>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 2000010
#define maxl 100010

int n,root,cnt;
char src[maxn];
char str[1010][60];
int result[1010];
struct _node{
	int next[128],fail,type;
	void init(){
		memset(next,-1,sizeof(next));
		fail=-1;
		type=0;
	}
}tree[maxl];
typedef struct _node node;
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
		 if(tree[root].next[i]==-1)  tree[root].next[i]=root;
		 else
		 {
			 int p=tree[root].next[i];
			 tree[p].fail=root;
			 Q.push(p);
		 }
	}
	
	while(!Q.empty()){
		int front=Q.front();
		Q.pop();

		for(int i=0;i<128;i++){
			if(tree[front].next[i]==-1)  tree[front].next[i]=tree[tree[front].fail].next[i];
			else{
				 int p=tree[front].next[i];
				 tree[p].fail=tree[tree[front].fail].next[i];
				 Q.push(p);
			}
		}
	}
}

int query(){
	int len=strlen(src);
	int cur=root;
	for(int i=0;i<len;i++){
		int inx=src[i];
		cur=tree[cur].next[inx];
		int tmp=cur;
		while(tmp!=root){
			 int type=tree[tmp].type;
			 if(type){
				result[type]++;
			 }
			 tmp=tree[tmp].fail;
		}
	}
	return 1;
}


int main(void){
	 //freopen("debug.txt","r",stdin);
	 while(scanf("%d",&n)!=EOF){
	 	memset(result,0,sizeof(result));
		root=cnt=0;
		tree[root].init();

		for(int i=1;i<=n;i++){
			scanf("%s",&str[i]);
			insert(str[i],i);
		}
		
		build();
		scanf("%s",src);
		query();
		for(int i=1;i<=n;i++){
			if(result[i])
			   printf("%s: %d\n",str[i],result[i]);
		}
	 }
}

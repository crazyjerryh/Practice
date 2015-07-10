#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 200010
int n;
int child[maxn][2],fa[maxn],size[maxn],val[maxn];
int a[maxn],b[maxn];
int root,cnt;
int num;

void init(){
	memset(child,0,sizeof(child));
	memset(fa,0,sizeof(fa));
	memset(size,0,sizeof(size));
	root=0,cnt=0;
	num=0;
}

void push_up(int x){
	size[x]=size[child[x][0]]+size[child[x][1]]+1;
}

void newnode(int &x,int k,int data,int father){
	x=++cnt;
	size[x]++;
	val[x]=data;
	child[x][0]=child[x][1]=0;
	fa[x]=father;
}

//旋转操作
void rotate(int x,int kind){
	//更新size值
	int y=fa[x];
	child[y][!kind]=child[x][kind];
	fa[child[x][kind]]=y;
	child[fa[y]][child[fa[y]][1]==y]=x;
	fa[x]=fa[y];
	child[x][kind]=y;
	fa[y]=x;
	push_up(y);
}

void splay(int x,int goal){
	while(fa[x]!=goal){
		if(fa[fa[x]]==goal)  rotate(x,child[fa[x]][0]==x);
		else{
			int y=fa[x],kind=(child[fa[y]][0]==y);
			if(child[y][kind]==x){
				rotate(x,!kind);
				rotate(x,kind);
			}
			else{
				rotate(x,kind);
				rotate(x,kind);
			}
		}
	}
	push_up(x);
	if(goal==0)  root=x;
}

void insert(int k,int data){
	if(!root){
		newnode(child[0][0],k,data,0);
		root=cnt;
		return;
	}
	else{
		//找到第k个子节点，然后将数字插入到第k大的节点的右子树的最左节点
		int cur=root;
		while(1){
			int t=size[cur]-size[child[cur][1]];
			size[cur]++;
			if(t==k)  break;
			if(t>k)  cur=child[cur][0];
			else{
				cur=child[cur][1];
				k-=t;
			}
		}
		//找到右子树的最左子节点
		int x,y;
	    if(child[cur][1]==0){
			newnode(child[cur][1],k,data,cur);
			splay(child[cur][1],0);
			child[0][1]=child[0][0]=0;
		}
		else
		{
		    y=child[cur][1];
			while(y!=0){
				x=y;
				size[y]++;
				y=child[y][0];
			}
			newnode(child[x][0],k,data,x);
			splay(child[x][0],0);
			child[0][1]=child[0][0]=0;
		}
	}
	
}

void travel(int rt){
	if(child[rt][0])  travel(child[rt][0]);
	if(num==1)  printf("%d",val[rt]);
	else if(num>1)  printf(" %d",val[rt]);
	num++;
	if(child[rt][1])  travel(child[rt][1]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		init();
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i],&b[i]);
		}
		insert(0,0);
		for(int i=1;i<=n;i++){
			insert(a[i]+1,b[i]);  //插入右子树的
		}
		travel(root);
		printf("\n");
	}
	return 0;
}
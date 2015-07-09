#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 1000100
int child[maxn][2],fa[maxn],key[maxn],val[maxn];
int root,cnt;

void init(){
	memset(child,0,sizeof(child));
	memset(fa,0,sizeof(fa));
	memset(key,0,sizeof(key));
	memset(val,0,sizeof(val));
	root=cnt=0;
}

void newnode(int &x,int k,int data,int father){
	x=++cnt;
	child[x][0]=child[x][1]=0;
	key[x]=k,val[x]=data;
	fa[x]=father;
}

void rotate(int x,int kind){
	int y=fa[x];
	child[y][!kind]=child[x][kind];
	fa[child[x][kind]]=y;
	if(fa[y]) child[fa[y]][child[fa[y]][1]==y]=x;
	fa[x]=fa[y];
	child[x][kind]=y;
	fa[y]=x;
}

void splay(int x,int goal){
	while(fa[x]!=goal){
		if(fa[fa[x]]==goal) rotate(x,child[fa[x]][0]==x);  //1表示的是右旋，0表示的是左旋
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
	if(goal==0)  root=x;
}

void insert(int k,int data){
	if(!root){
		newnode(child[0][0],k,data,0);
		child[0][0]=child[0][1]=0;
		root=cnt;
		return;
	}
	int cur=root,y;
	while(cur!=0){
		y=cur;
		if(k>key[cur]) cur=child[cur][1];
		else cur=child[cur][0];
	}
	newnode(child[y][k>key[y]],k,data,y);
	splay(child[y][k>key[y]],0);
	child[0][0]=child[0][1]=0;
}

int get_min(){
	if(!root)  return 0;
	int cur=root;
	while(child[cur][0])  cur=child[cur][0];
	if(cur==root){root=child[cur][1];}
	fa[child[cur][1]]=fa[cur];
	child[fa[cur]][0]=child[cur][1];
	return val[cur];
}

int get_max(){
	if(!root)  return 0;
	int cur=root;
	while(child[cur][1]) cur=child[cur][1];
	if(cur==root){root=child[cur][0];}
	fa[child[cur][0]]=fa[cur];
	child[fa[cur]][1]=child[cur][0];
	return val[cur];
}

int main(void){
	//freopen("debug.txt","r",stdin);
	int type;
	init();
	while(true){
		scanf("%d",&type);
		if(type==0)  break;
		else if(type==1){
			int a,b;
			scanf("%d%d",&a,&b);
		    insert(b,a);  
		}
		else if(type==2){
			int ans=get_max();
			printf("%d\n",ans);
		}
		else if(type==3){
			int ans=get_min();
			printf("%d\n",ans);
		}
	}
	return 0;
}
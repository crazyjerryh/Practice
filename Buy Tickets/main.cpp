#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 200010

int fa[maxn],child[maxn][2],k[maxn],val[maxn];
int n,root,cnt;
int tot;

void init(){
	memset(fa,0,sizeof(fa));
	memset(child,0,sizeof(child));
	memset(k,0,sizeof(k));
	memset(val,0,sizeof(val));
	root=1,cnt=0;
	tot=1;
}

//旋转操作,左旋and右旋
void rotate(int x,int kind){  //kind 为0 或者1
	 int y=fa[x];
	 child[y][kind^1]=child[x][kind];
	 if(child[x][kind])  fa[child[x][kind]]=y;
	 child[x][kind]=y;
	 if(fa[y]) child[fa[y]][child[fa[y]][1]==y]=x;
	 fa[x]=fa[y];
	 fa[y]=x;
}

void splay(int x){
	while(fa[x]!=0){
		if(fa[fa[x]]==0)  rotate(x,child[fa[x]][0]==x);
		else{
		   //旋转操作
		   int y=fa[x];
		   int kind=child[fa[y]][0]==y;
		   if(child[y][kind]==x){
			  rotate(x,kind^1);
			  rotate(x,kind);
		   }
		   else
		   {
			  rotate(x,kind);
			  rotate(x,kind);
		   }
		}
	}
	root=x;
}

void insert(int key,int data){
	 if(cnt==0){
			k[++cnt]=key,val[cnt]=data;
			return;
	}
	int x=root;
	int y;
	while(true){
		y=child[x][k[x]<key];
		if(y==0){
			y=++cnt;
			child[y][0]=child[y][1]=0;
			fa[y]=x;
			child[x][k[x]<key]=y;
			k[y]=key;
			val[y]=data;
			break;
		}
		x=y;
	}
	splay(y);
}

void travel(int num){
	if(child[num][0])  travel(child[num][0]);
	if(tot==1){
	   printf("%d",val[num]);
	   tot++;
	}
	else{
	   printf(" %d",val[num]);
	   tot++;
	}
	if(child[num][1])  travel(child[num][1]);
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		init();
		for(int i=1;i<=n;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			insert(a,b);
		}
		travel(root);
		printf("\n");
	}
	return 0;
}

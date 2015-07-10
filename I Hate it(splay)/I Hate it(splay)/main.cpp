#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 200100
int child[maxn][2],fa[maxn],val[maxn],size[maxn],m[maxn];
int num[maxn];
int root,cnt,n,p;

void push_up(int x){
	size[x]=size[child[x][0]]+size[child[x][1]]+1;
	m[x]=max(val[x],max(m[child[x][0]],m[child[x][1]]));
}

void newnode(int &x,int data,int father){
	x=++cnt;
	child[x][0]=child[x][1]=0;
	fa[x]=father;
	val[x]=data;
}

void rotate(int x,int kind){
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
		if(fa[fa[x]]==goal){rotate(x,child[fa[x]][0]==x);}
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
	if(goal==0) root=x;
}

void select(int k,int goal){
	int cur=root;
	while(k!=(size[child[cur][0]]+1)){
		int tmp=size[child[cur][0]]+1;
		if(k<tmp)  cur=child[cur][0];
		else   k-=tmp,cur=child[cur][1];
	}
    splay(cur,goal);
}

int query(int a,int b){
	select(a-1,0);
	select(b+1,root);
	return m[child[child[root][1]][0]]; 
}

void change(int k,int b){
	select(k,0);
	m[root]=max(max(m[child[root][0]],m[child[root][1]]),b);
	val[root]=b;
}

void build(int &x,int l,int r,int father){
    if(r<l)  return;
	int mid=(l+r)>>1;
	newnode(x,num[mid],father);
	build(child[x][0],l,mid-1,x);
	build(child[x][1],mid+1,r,x);
	push_up(x);
}

void init(){
	memset(child,0,sizeof(child));
	memset(fa,0,sizeof(fa));
	memset(size,0,sizeof(size));
	memset(m,0,sizeof(m));
	cnt=root=0;
	newnode(root,-1,0);
	newnode(child[root][1],-1,root); 
	int cur=child[root][1];
	build(child[cur][0],1,n,cur);
	push_up(cur);
	push_up(root);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&p)!=EOF){
		for(int i=1;i<=n;i++)
			scanf("%d",&num[i]);
	    init();
		getchar();
		for(int i=1;i<=p;i++){
			char c;
			c=getchar();
			int a,b;
			if(c=='Q'){
				scanf("%d%d",&a,&b);
				int ans=query(a+1,b+1);
				printf("%d\n",ans);
			}
			else{
				scanf("%d%d",&a,&b);
				change(a+1,b);
			}
			getchar();
		}
	}
	return 0;
}
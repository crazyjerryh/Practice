#include <stdio.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn  100005 
#define inf 1<<29
int child[maxn][2],fa[maxn],val[maxn];
int root,cnt,n;
void init(){
	memset(child,0,sizeof(child));
	memset(fa,0,sizeof(fa));
	root=cnt=0;
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
    if(goal==0)  root=x;
}

void insert(int data){
	if(!root){
		newnode(root,data,0);
		child[0][0]=child[0][1]=0;
		return;
	}
	int y,rt=root;
	while(rt!=0){
		y=rt;
		if(data>val[rt])  rt=child[rt][1];
		else rt=child[rt][0];
	}
	newnode(child[y][data>val[y]],data,y);
	splay(child[y][data>val[y]],0);
	child[0][0]=child[0][1]=0;
}

int query(int data){
	if(!root)  return data;
	int cur=root,rt=root;
	int ans=inf;
	while(rt!=0){
		if(val[rt]==data) return 0;
		ans=min(ans,abs(val[rt]-data));
		if(val[rt]>data) rt=child[rt][0];
		else rt=child[rt][1];
	}
	return ans;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		int sum=0,tmp;
		init();
		for(int i=0;i<n;i++){
			if(scanf("%d",&tmp)==EOF) tmp=0;
			int ans=query(tmp);
			sum+=ans;
			insert(tmp);
		}
		printf("%d\n",sum);
	}
	return 0;
}
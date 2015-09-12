/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/11
 * avl tree
 */

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1000100
struct node{
	int data;
	int ls,rs,fa;
	int height;
}tree[maxn];
int sz[maxn];

int n,k;
int tot,root;

void newnode(int v,int fa){
	tree[++tot].data=v;
	tree[tot].ls=tree[tot].rs=0;
	tree[tot].height=1;
	tree[tot].fa=fa;
	sz[tot]=1;
}

void rrotate(int rt){
     int x=rt,y=tree[rt].fa;
	 tree[y].ls=tree[x].rs;
	 if(tree[y].fa!=0){
		 int z=tree[y].fa;
		 if(tree[z].ls==y) tree[z].ls=x;
		 else tree[z].rs=x;
		 tree[x].fa=z;
	 }
	 tree[tree[x].rs].fa=y;
	 tree[x].rs=y;
	 tree[y].fa=x;
	 tree[y].height=max(tree[tree[y].ls].height,tree[tree[y].rs].height);
	 tree[x].height=max(tree[tree[x].ls].height,tree[tree[x].rs].height);
}

void lrotate(int rt){
	int x=rt,y=tree[rt].fa;
	tree[y].rs=tree[x].ls;
	tree[tree[x].ls].fa=y;
	if(tree[y].fa!=0){
		int z=tree[y].fa;
		if(tree[z].ls==y) tree[z].ls=x;
		else tree[z].rs=x;
		tree[x].fa=z;
	}
	tree[x].ls=y;
	tree[y].fa=x;
	tree[y].height=max(tree[tree[y].ls].height,tree[tree[y].rs].height);
	tree[x].height=max(tree[tree[x].ls].height,tree[tree[x].rs].height);
}

int insert(int rt,int v,int fa){
	if(rt==0){
		newnode(v,fa);
		return tot;
	}
	
	int data=tree[rt].data;
	if(data>=v){
		tree[rt].ls=insert(tree[rt].ls,v,rt);
		int h1=tree[tree[rt].ls].height;
		int h2=tree[tree[rt].rs].height;
		if(h1-h2>=2){
			int ls=tree[rt].ls;
			if(v<=tree[ls].data){
				rrotate(tree[ls].ls);
				rrotate(ls);
			}
			else{
				lrotate(tree[ls].rs);
				rrotate(ls);
			}
            sz[rt]=sz[tree[rt].ls]+sz[tree[rt].rs]+1;
		}
 		else{
			tree[rt].height=max(h1,h2);
		    sz[rt]=sz[tree[rt].ls]+sz[tree[rt].rs]+1;
 		}
	}
	else
	{
        tree[rt].rs=insert(tree[rt].rs,v,rt);
		int h1=tree[tree[rt].rs].height;
		int h2=tree[tree[rt].ls].height;
		if(h1-h2>=2){
			int rs=tree[rt].rs;
			if(v>tree[rs].data){
			    lrotate(tree[rs].rs);
				lrotate(rs);
			}
			else{
				rrotate(tree[rs].ls);
				rrotate(rs);
			}
			sz[rt]=sz[tree[rt].ls]+sz[tree[rt].rs]+1;
		}
		else{
			tree[rt].height=max(h1,h2);
		    sz[rt]=sz[tree[rt].ls]+sz[tree[rt].rs]+1;
 		}
	}
	return rt;
}

int search(int rt,int k){
    int ls=tree[rt].ls;
	int rs=tree[rt].rs;
	if(sz[ls]>=k) return search(ls,k);
	else if(sz[ls]==k-1) return tree[rt].data;
	else return search(rs,k-sz[ls]-1);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&k)){
		tot=root=0;
		sz[0]=0;
		int num=0;
		for(int i=0;i<n;i++){
			char c[10];
			int data;
			scanf("%s",c);
			if(c[0]=='I'){
				scanf("%d",&data);
				root=insert(root,data,0);
				num++;
			}
			else
			{
		        int ans=search(root,num-k+1);
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
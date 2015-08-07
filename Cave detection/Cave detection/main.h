#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cstdio>

using namespace std;

#define MAXN 20000

int sz,ch[MAXN][2],f[MAXN],rev[MAXN];

void newnode()
{
	int p=++sz;
	rev[p]=ch[p][0]=ch[p][1]=f[p]=0;
}

bool isroot(int x)
{
	return (!f[x]||ch[f[x]][0]!=x&&ch[f[x]][1]!=x);
}


void push_down(int rt)
{
	if(!rt) return;
	if(rev[rt])
	{
		swap(ch[rt][0],ch[rt][1]);
		rev[ch[rt][0]]^=1;
		rev[ch[rt][1]]^=1;
		rev[rt]=0;
	}
}

void rotate(int x,int c)
{
	if(isroot(x)) return;
	int y=f[x],z=f[y];
	ch[y][!c]=ch[x][c];
	if(ch[x][c]) f[ch[x][c]]=y;
	ch[x][c]=y;
	if(f[y])
	{
		if(ch[f[y]][0]==y)
			ch[f[y]][0]=x;
		if(ch[f[y]][1]==y)
			ch[f[y]][1]=x;
	}
	f[y]=x;f[x]=z;
}

void splay(int x)
{
	int y,z;
	push_down(x);
	while(!isroot(x))
	{
		y=f[x],z=f[y];
		if(isroot(y))
		{
			push_down(y);push_down(x);
			if(ch[y][0]==x)
				rotate(x,1);
			else
				rotate(x,0);
		}
		else
		{
			push_down(z);push_down(y);push_down(x);
			if(ch[z][0]==y)
			{
				if(ch[y][0]==x)
					rotate(y,1),rotate(x,1);
				else
					rotate(x,0),rotate(x,1);
			}
			else
			{
				if(ch[y][1]==x)
					rotate(y,0),rotate(x,0);
				else
					rotate(x,1),rotate(x,0);
			}
		}
	}
}

int Access(int u)
{
	int v=0;
	for(;u;u=f[u])
	{
		splay(u);
		ch[u][1]=v;
		v=u;
	}
	return v;
}

void makeRoot(int u)
{
	int p=Access(u);
	rev[p]^=1;
	splay(u);
}

int findRoot(int x) {
	for (x = Access(x); push_down(x),ch[x][0]!=0 ; x = ch[x][0]);
	splay(x);
	return x;
}

bool link(int u,int v)
{
	if(findRoot(u)==findRoot(v)) return false;
	makeRoot(u);
	f[u]=v;
	Access(u);
	return true;
}

bool cut(int u,int v)
{
	if(u==v||findRoot(u)!=findRoot(v)) return false;
	makeRoot(u);
	Access(v);
	splay(v);
	f[ch[v][0]]=0;
	ch[v][0]=0;
	return true;
}

int n,m;

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		sz=0;
		for(int i=1;i<=n;i++)
			newnode();
		char str[300];
		int u,v;
		for(int i=1;i<=m;i++)
		{
			scanf("%s%d%d",str,&u,&v);
			//  cout<<str<<" "<<u<<" "<<v<<endl;
			if(str[0]=='Q')
			{
				if(findRoot(u)==findRoot(v))
					printf("Yes\n");
				else
					printf("No\n");
			}
			else if(str[0]=='D')
				cut(u,v);
			else if(str[0]=='C')
				link(u,v);
		}

	}
	return 0;
}

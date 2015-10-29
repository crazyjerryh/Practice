#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
//普通的线段树操作，区间增加一个值，查询区间的和
#define Key_value ch[ch[root][1]][0]
const int MAXN = 100010;
int pre[MAXN],ch[MAXN][2],root,tot1;
int size[MAXN];//子树的结点数
int add[MAXN];//增量的延迟标记
int key[MAXN];
long long sum[MAXN];//子树的和
int s[MAXN],tot2;//内存池和容量
int a[MAXN];//初始的数组，建树的时候用，下标从1开始

//debug部分**********************************
void Treavel(int x)
{
	if(x)
	{
		Treavel(ch[x][0]);
		printf("结点：%2d: 左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d add = %2d sum = %I64d\n",x,ch[x][0],ch[x][1],pre[x],size[x],add[x],sum[x]);
		Treavel(ch[x][1]);
	}
}
void debug()
{
	printf("root:%d\n",root);
	Treavel(root);
}
//以上是debug部分**************************************

void NewNode(int &r,int father,int k)
{
	r = ++tot1;
	pre[r] = father;
	size[r] = 1;
	add[r] = 0;
	key[r] = k;
	sum[r] = k;
	ch[r][0] = ch[r][1] = 0;
}
//给r为根的子树增加值，把当前结点更新掉，加延迟标记
void Update_Add(int r,int ADD)
{
	if(r == 0)return;
	add[r] += ADD;
	key[r] += ADD;
	sum[r] += (long long)ADD*size[r];
}
void push_up(int r)
{
	size[r] = size[ch[r][0]] + size[ch[r][1]] + 1;
	sum[r] = sum[ch[r][0]] + sum[ch[r][1]] + key[r];
}
void push_down(int r)
{
	if(add[r])
	{
		Update_Add(ch[r][0],add[r]);
		Update_Add(ch[r][1],add[r]);
		add[r] = 0;
	}
}
//建树
void Build(int &x,int l,int r,int father)
{
	if(l > r)return;
	int mid = (l+r)/2;
	NewNode(x,father,a[mid]);
	Build(ch[x][0],l,mid-1,x);
	Build(ch[x][1],mid+1,r,x);
	push_up(x);
}
int n,q;
//初始化
void Init()
{
	root = tot1=0;
	ch[root][0] = ch[root][1] = pre[root] = size[root] = add[root] = sum[root] = key[root] = 0;
	//加两个虚结点
	NewNode(root,0,-1);
	NewNode(ch[root][1],root,-1);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	Build(Key_value,1,n,ch[root][1]);
	push_up(ch[root][1]);
	push_up(root);
}
//旋转，0为左旋，1为右旋
void Rotate(int x,int kind)
{
	int y = pre[x];
	push_down(y);
	push_down(x);//先把y的标记下传，在把x的标记下传
	ch[y][!kind] = ch[x][kind];
	pre[ch[x][kind]] = y;
	if(pre[y])
		ch[pre[y]][ch[pre[y]][1]==y] = x;
	pre[x] = pre[y];
	ch[x][kind] = y;
	pre[y] = x;
	push_up(y);
}
//Splay调整，将r结点调整到goal下面
void Splay(int r,int goal)
{
	push_down(r);
	while(pre[r] != goal)
	{
		if(pre[pre[r]] == goal)
			Rotate(r,ch[pre[r]][0]==r);
		else
		{
			int y = pre[r];
			int kind = ch[pre[y]][0]==y;
			if(ch[y][kind] == r)
			{
				Rotate(r,!kind);
				Rotate(r,kind);
			}
			else
			{
				Rotate(y,kind);
				Rotate(r,kind);
			}
		}
	}
	push_up(r);
	if(goal == 0) root = r;
}
//得到第k个结点
int Get_kth(int r,int k)
{
	push_down(r);
	int t = size[ch[r][0]] + 1;
	if(t == k)return r;
	if(t > k)return Get_kth(ch[r][0],k);
	else return Get_kth(ch[r][1],k-t);
}

//区间增加一个值
//因为加了个空结点，所以将第l个点旋转到根结点，第r+2个点旋转到根结点的右孩子
//那么Key_value就是需要修改的区间[l,r]
void ADD(int l,int r,int D)
{
	Splay(Get_kth(root,l),0);
	Splay(Get_kth(root,r+2),root);
	Update_Add(Key_value,D);
	push_up(ch[root][1]);
	push_up(root);
}
//查询区间的和
long long Query_sum(int l,int r)
{
	Splay(Get_kth(root,l),0);
	Splay(Get_kth(root,r+2),root);
	return sum[Key_value];
}

int main()
{
	freopen("debug.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(scanf("%d%d",&n,&q) == 2)
	{
		Init();
		//debug();
		int x,y,z;
		char op[20];
		while(q--)
		{
			scanf("%s",op);
			if(op[0] == 'Q')
			{
				scanf("%d%d",&x,&y);
				printf("%I64d\n",Query_sum(x,y));
			}
			else
			{
				scanf("%d%d%d",&x,&y,&z);
				ADD(x,y,z);
			}
		}
	}
	return 0;
}
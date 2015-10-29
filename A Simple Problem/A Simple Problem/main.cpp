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
//��ͨ���߶�����������������һ��ֵ����ѯ����ĺ�
#define Key_value ch[ch[root][1]][0]
const int MAXN = 100010;
int pre[MAXN],ch[MAXN][2],root,tot1;
int size[MAXN];//�����Ľ����
int add[MAXN];//�������ӳٱ��
int key[MAXN];
long long sum[MAXN];//�����ĺ�
int s[MAXN],tot2;//�ڴ�غ�����
int a[MAXN];//��ʼ�����飬������ʱ���ã��±��1��ʼ

//debug����**********************************
void Treavel(int x)
{
	if(x)
	{
		Treavel(ch[x][0]);
		printf("��㣺%2d: ����� %2d �Ҷ��� %2d ����� %2d size = %2d add = %2d sum = %I64d\n",x,ch[x][0],ch[x][1],pre[x],size[x],add[x],sum[x]);
		Treavel(ch[x][1]);
	}
}
void debug()
{
	printf("root:%d\n",root);
	Treavel(root);
}
//������debug����**************************************

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
//��rΪ������������ֵ���ѵ�ǰ�����µ������ӳٱ��
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
//����
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
//��ʼ��
void Init()
{
	root = tot1=0;
	ch[root][0] = ch[root][1] = pre[root] = size[root] = add[root] = sum[root] = key[root] = 0;
	//����������
	NewNode(root,0,-1);
	NewNode(ch[root][1],root,-1);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	Build(Key_value,1,n,ch[root][1]);
	push_up(ch[root][1]);
	push_up(root);
}
//��ת��0Ϊ������1Ϊ����
void Rotate(int x,int kind)
{
	int y = pre[x];
	push_down(y);
	push_down(x);//�Ȱ�y�ı���´����ڰ�x�ı���´�
	ch[y][!kind] = ch[x][kind];
	pre[ch[x][kind]] = y;
	if(pre[y])
		ch[pre[y]][ch[pre[y]][1]==y] = x;
	pre[x] = pre[y];
	ch[x][kind] = y;
	pre[y] = x;
	push_up(y);
}
//Splay��������r��������goal����
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
//�õ���k�����
int Get_kth(int r,int k)
{
	push_down(r);
	int t = size[ch[r][0]] + 1;
	if(t == k)return r;
	if(t > k)return Get_kth(ch[r][0],k);
	else return Get_kth(ch[r][1],k-t);
}

//��������һ��ֵ
//��Ϊ���˸��ս�㣬���Խ���l������ת������㣬��r+2������ת���������Һ���
//��ôKey_value������Ҫ�޸ĵ�����[l,r]
void ADD(int l,int r,int D)
{
	Splay(Get_kth(root,l),0);
	Splay(Get_kth(root,r+2),root);
	Update_Add(Key_value,D);
	push_up(ch[root][1]);
	push_up(root);
}
//��ѯ����ĺ�
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
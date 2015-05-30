#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>
using namespace std;
//ofstream fout("debug.txt");
#define maxn 300000
//#define cout fout
int flag[maxn];

int a[9][9]={{1,1,0,1,1,0,0,0,0},
{1,1,1,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0},
{1,0,0,1,0,0,1,0,0},
{0,1,0,1,1,1,0,1,0},
{0,0,1,0,0,1,0,0,1},
{0,0,0,1,1,0,1,1,0},
{0,0,0,0,0,0,1,1,1},
{0,0,0,0,1,1,0,1,1}
           };
int dir[10];
std::vector<int> res;
struct _node
{
	int depth;
	int status;
	int fa,id;
	_node(){}
	_node(int _depth,int _status,int father,int _id):depth(_depth),status(_status),fa(father),id(_id){}
};

typedef struct _node node;
node queue[maxn];
int front,back;
int start,finish;

void init()
{
	int cur=1;
	for(int i=0;i<9;i++){
		int ans=0;
		for(int j=0;j<9;j++){
			ans=ans*4+a[i][j];
		}
		dir[cur++]=ans;
	}
}

int add(int a,int b)
{
	int p[10]={0};
	for(int i=0;i<9;i++){
		int a1,b1;
		a1=a%4,b1=b%4;
	    a=a/4,b=b/4;
		p[i]=(a1+b1)%4;	
	}

	int ans=0;
	for(int i=8;i>=0;i--)
		ans=ans*4+p[i];
	
	return ans;
}

void bfs()
{
	front=back=0;
	flag[start]=1;
	queue[back++]=node(1,start,-1,0);
    while(front<back)
	{
		node top=queue[front];
		front++;

		int status=top.status;
		for(int i=1;i<=9;i++){
			int curstatus=add(status,dir[i]);
			if(curstatus==finish){
				res.push_back(i);
				for(int j=front-1;j!=0;j=queue[j].fa)
					res.push_back(queue[j].id);

				int size=res.size();
				cout<<res[size-1];
				for(int j=size-2;j>=0;j--)
					cout<<" "<<res[j];
				cout<<endl;
				return;
			}
			if(!flag[curstatus]){
				flag[curstatus]=1;
				queue[back++]=node(top.depth+1,curstatus,front-1,i);
			}
		}
	}
}

int main(void)
{
	init();
	start=finish=0;
	memset(flag,0,sizeof(flag));
	for(int i=0;i<9;i++)
	{
		int tmp;
		cin>>tmp;
		start=start*4+tmp;
	}
    bfs();
}
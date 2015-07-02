/*poj 47ms  hdu TLE*/
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <stack>
#include <memory.h>
#include <string.h>
#include <queue>
#define maxn 400000
#define maxm 100
using namespace std;

struct _node
{
	int map[3][3];
	int status;
	int loc;
	int step;
	void func(int _map[][3])
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				map[i][j]=_map[i][j];
	}
};
typedef struct _node node;

char str[maxm];
int vis1[maxn],vis2[maxn];
int pre[maxn];
int path[maxn];
int len;
int map[10],start[10]={1,2,3,4,5,6,7,8,0,0};
std::queue<node> q1,q2;
int fac[]={40320,5040,720,120,24,6,2,1,1};
int dir[2][4][2]={{{-1,0},{1,0},{0,-1},{0,1}},
                {{-1,0},{1,0},{0,-1},{0,1}}};

char cdir1[4]={'u','d','l','r'};
char cdir2[4]={'d','u','r','l'};
int key;

void show(int p)
{
	if(pre[p]==-1)  return;
	show(pre[p]);
	printf("%c",path[p]);
}

int cator(int _map[][3])
{
	int ans=0;
    for(int i=0;i<9;i++){
		int cnt=0;
		for(int j=i+1;j<9;j++){
			int x,y,x1,y1;
			x=i/3,y=i%3;
		    x1=j/3,y1=j%3;
			if(_map[x][y]>_map[x1][y1])
				cnt++;
		}
		ans+=cnt*fac[i];
	}
	return ans;
}

bool isbound(int a,int b)
{
	if(a<0||b<0||a>=3||b>=3)
		return false;
	
	return true;
}

void bfs()
{
	while(!q1.empty()) q1.pop();
	while(!q2.empty()) q2.pop();
	memset(vis1,0,sizeof(vis1));
	memset(vis2,0,sizeof(vis2));
	int tmp1[3][3],tmp2[3][3];
	for(int i=0;i<9;i++)
	{
		int x,y;
		x=i/3,y=i%3;
		tmp1[x][y]=map[i];
	}

	for(int i=0;i<9;i++){
		int x,y;
		x=i/3,y=i%3;
		tmp2[x][y]=start[i];
	}
	
	int s1,s2;
	node nnode;
	nnode.loc=key;
	nnode.status=cator(tmp1);
	nnode.step=1;
	nnode.func(tmp1);
	q1.push(nnode);
	vis1[nnode.status]=1;
	pre[nnode.status]=-1;
	s1=nnode.status;
	
	nnode.loc=8;
	nnode.status=cator(tmp2);
	nnode.step=1;
	nnode.func(tmp2);
	q2.push(nnode);
	vis2[nnode.status]=1;
	pre[nnode.status]=-1;
	s2=nnode.status;
    if(s1==s2){
	    printf("\n");
		return;
	}
	
	
	int step=1;
	while(!q1.empty()&&!q2.empty())
	{
		while(!q1.empty()&&q1.front().step==step){
			node front1=q1.front();
			q1.pop();
			for(int i=0;i<4;i++){
				int x,y;
				int loc=front1.loc;
				int a,b;
				a=loc/3,b=loc%3;
				x=dir[0][i][0]+a;
				y=dir[0][i][1]+b;
				if(isbound(x,y)){
					std::swap(front1.map[a][b],front1.map[x][y]);
					int tstatus=cator(front1.map);
					if(vis1[tstatus]==0){
					if(vis2[tstatus]){
						int tmp=front1.status;
						show(tmp);
						tmp=tstatus;
						printf("%c",cdir1[i]);
						while(pre[tmp]!=-1){
							printf("%c",path[tmp]);
							tmp=pre[tmp];
						}
						printf("\n");
						return;
					}
				   pre[tstatus]=front1.status;
				   path[tstatus]=cdir1[i];
				   node nnode1;
				   nnode1.status=tstatus;
				   nnode1.func(front1.map);
				   nnode1.loc=x*3+y;
				   nnode1.step=front1.step+1;
				   q1.push(nnode1);
				   vis1[tstatus]=1;
				   }
				   std::swap(front1.map[a][b],front1.map[x][y]);
				}
			}
		}
		
		while(!q2.empty()&&q2.front().step==step){
			node front1=q2.front();
			q2.pop();
			for(int i=0;i<4;i++){
				int x,y;
				int loc=front1.loc;
				int a,b;
				a=loc/3,b=loc%3;
				x=dir[1][i][0]+a;
				y=dir[1][i][1]+b;
				if(isbound(x,y)){	
					std::swap(front1.map[a][b],front1.map[x][y]);
					int tstatus=cator(front1.map);
					if(vis2[tstatus]==0){
					if(vis1[tstatus]){
						int tmp=tstatus;
						show(tmp);
						tmp=front1.status;
						printf("%c",cdir2[i]);
						while(pre[tmp]!=-1){
							printf("%c",path[tmp]);
							tmp=pre[tmp];
						}
						return;
					}
					pre[tstatus]=front1.status;
					path[tstatus]=cdir2[i];
					node nnode1;
					nnode1.status=tstatus;
					nnode1.func(front1.map);
					nnode1.loc=x*3+y;
					nnode1.step=step+1;
					q2.push(nnode1);
					vis2[tstatus]=1;
					}
					std::swap(front1.map[a][b],front1.map[x][y]);
				}
			}
		}
		step++;
	}
	printf("unsolvable\n");
}

int main(void)
{
	while(gets(str))
	{
		len=strlen(str);
		for(int i=0,j=0;i<len;i++){
			if(str[i]!=' '){
				if(str[i]=='x'){
					key=j;
					map[j++]=0;
				}
				else
					map[j++]=str[i]-'0';
			}
		}
		bfs();
	}
	return 0;
}
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <string.h>
using namespace std;
#define maxn 100
#define maxm 400000

int vis[maxm];
int pre[maxm];
int path[maxm];
char str[maxn];
int map[10];
int len;
struct _node
{
	int map[9];
	int status;
	int loc;
	void func(int _map[]){
		for(int i=0;i<9;i++)
			map[i]=_map[i];
	}
};

typedef struct _node node;
std::queue<node> Q;
int start[9]={1,2,3,4,5,6,7,8,0};
int fac[]={40320,5040,720,120,24,6,2,1,1};
int dir[4]={1,-1,3,-3};
int ddir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
char cdir[5]={'l','r','u','d'};

int cator(int a[])
{
	int ans=0;
	for(int i=0;i<9;i++){
		int cnt=0;
		for(int j=i+1;j<9;j++){
			if(a[i]>a[j])
				cnt++;
		}
		ans+=cnt*fac[i];
	}
	return ans;
}

bool isbound(int loc,int d)
{
      int x,y;
	  x=loc/3;
	  y=loc%3;
	  
	  x=x+ddir[d][0];
	  y=y+ddir[d][1];
	  
	  if(x<0||y<0||x>=3||y>=3)
		  return false;
	  
	  return true;
}

void bfs()
{
	memset(vis,0,sizeof(vis));
	memset(pre,0,sizeof(pre));
    node nnode;
	nnode.func(start);
	int status=cator(start);
	nnode.status=status;
	nnode.loc=8;  
	Q.push(nnode);
	pre[status]=-1;
	vis[status]=1;

	while(!Q.empty())
	{
	     node front=Q.front();
		 Q.pop();
		 for(int i=0;i<4;i++){
			 int loc=front.loc;
			 int pos=loc+dir[i];
			 if(isbound(loc,i))
			 {
		          std::swap(front.map[loc],front.map[pos]);
				  nnode.func(front.map);
				  nnode.loc=pos;
				  nnode.status=cator(front.map);
				  if(vis[nnode.status]==0){
					  pre[nnode.status]=front.status;
					  path[nnode.status]=cdir[i];
					  Q.push(nnode);
					  vis[nnode.status]=1;
				  }
				  std::swap(front.map[loc],front.map[pos]);
			 }
		 }
	}
	
}

int main(void)
{
	bfs();
	while(gets(str))
	{
		len=strlen(str);
		for(int i=0,j=0;i<len;i++){
			if(str[i]!=' '){
				if(str[i]=='x')
					map[j++]=0;
				else
					map[j++]=str[i]-'0';
			}
		}
		
		int status=cator(map);
		if(vis[status]==0)
		{
			printf("unsolvable\n");
			continue;
		}
		
		int first=cator(start);
		if(status==first){
			printf("\n");
			continue;
		}
		
		int cur=status;
		while(cur!=-1)
		{
			printf("%c",path[cur]);
			cur=pre[cur];
		}
		printf("\n");
		
	}
	return 0;
}
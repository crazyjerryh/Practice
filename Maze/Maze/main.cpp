/*1103 maze ,main idea is how to construct map*/
//author huanghao,2015/4/30
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
// ofstream fout("debug.txt");
// #define cout fout

typedef struct _point{
	int x,y;
	int child;
	struct _point(int _x,int _y,int _child):x(_x),y(_y),child(_child){}
}point;

#define maxn 100
int map[maxn][maxn][4];
int type[maxn][maxn];
int res;
int w,h;
int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
queue<point> Q;

bool update(int x,int y,int child)
{
    bool flag=true;
	int dirinx[2];
	dirinx[0]=child;
	dirinx[1]=(child+1)%4;

	int curx,cury;
	for(int i=0;i<2;i++){
		curx=x+dir[dirinx[i]][0];
		cury=y+dir[dirinx[i]][1];
		
		if(curx<0||cury<0||curx>=h||cury>=w)
			flag=false;
	}

	//修改周围的节点的值
	for(int i=0;i<4;i++){
		if(i!=dirinx[0]&&i!=dirinx[1])
			continue;
		
		curx=x+dir[i][0];
		cury=y+dir[i][1];
		switch(i){
		case 0:
			if(curx>=0&&cury>=0&&curx<h&&cury<w){
				if(type[curx][cury]==0&&!map[curx][cury][2]){
					map[curx][cury][2]=1;
					Q.push(point(curx,cury,2));
				}
				else if(type[curx][cury]==1&&!map[curx][cury][1]){
					map[curx][cury][1]=1;
					Q.push(point(curx,cury,1));
				}
			}
			break;
		case 1:
			if(curx>=0&&cury>=0&&curx<h&&cury<w){
				if(type[curx][cury]==0&&!map[curx][cury][2]){
					map[curx][cury][2]=1;
					Q.push(point(curx,cury,2));
				}
				else if(type[curx][cury]==1&&!map[curx][cury][3]){
					map[curx][cury][3]=1;
					Q.push(point(curx,cury,3));
				}
			}
			break;
		case 2:
			if(curx>=0&&cury>=0&&curx<h&&cury<w){
				if(type[curx][cury]==0&&!map[curx][cury][0]){
					map[curx][cury][0]=1;
					Q.push(point(curx,cury,0));
				}
				else if(type[curx][cury]==1&&!map[curx][cury][3]){
					map[curx][cury][3]=1;
					Q.push(point(curx,cury,3));
				}
			}
			break;
		case 3:
			if(curx>=0&&cury>=0&&curx<h&&cury<w){
				if(type[curx][cury]==0&&!map[curx][cury][0]){
					map[curx][cury][0]=1;
					Q.push(point(curx,cury,0));
				}
				else if(type[curx][cury]==1&&!map[curx][cury][1]){
					map[curx][cury][1]=1;
					Q.push(point(curx,cury,1));
				}
			}
			break;
		}
	}

	return flag;
}

int bfs()
{
	int count=0;
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
		      //对当前的节点的两个的子节点的状态进行判断
			   if(type[i][j]==0){
				  for(int k=0;k<2;k++){
				   if(!map[i][j][2*k+0])
				   {
						    Q.push(point(i,j,2*k+0));
							map[i][j][2*k+0]=1;
				   }
					   int cnt=0;
					   bool flag=1;   //代表该区域是不是一个封闭的区域
					   bool qc=0;
					   while(!Q.empty()){
						   //加入相邻的节点，计算出一个封闭区域的三角形的个数
						   qc=1;
						   point front=Q.front();
						   /*cout<<"front"<<front.x<<front.y<<front.child<<endl;*/
						   Q.pop();
						   cnt++;
						   int curx,cury;
						   curx=front.x;
						   cury=front.y;

						   int child=front.child; 

						   //根据当前节点,来判断周围的节点是不是跟其相邻，并且更新其状态
						   flag=flag&update(curx,cury,child);
					   }	   

					   if(flag&&qc)
						   ++count;
					   if(flag&&cnt>res)
						   res=cnt;
				   }
			   }
			   else
			   {
				   for(int k=0;k<2;k++){
				      if(!map[i][j][2*k+1])
					  {
						  Q.push(point(i,j,2*k+1));
						  map[i][j][2*k+1]=1;
					  }
					  int cnt=0;
					  bool flag=1;   //代表该区域是不是一个封闭的区域
					  bool qc=0;
					  while(!Q.empty()){
						  qc=1;
						  //加入相邻的节点，计算出一个封闭区域的三角形的个数
						  point front=Q.front();
						  /*cout<<"front"<<front.x<<front.y<<front.child<<endl;*/
						  Q.pop();
						  cnt++;
						  int curx,cury;
						  curx=front.x;
						  cury=front.y;

						  int child=front.child; 

						  //根据当前节点,来判断周围的节点是不是跟其相邻，并且更新其状态
						  flag=flag&update(curx,cury,child);		  
					  }	   
					

					  if(flag&&qc)
						  ++count;
					  if(flag&&cnt>res)
						  res=cnt;
					  /*cout<<"count"<<count<<endl;*/
				   }

			   }

			  
			   
		}   
		return count;
}

int main(void)
{
	int tcase=1;
	while(scanf("%d%d",&w,&h))
	{
	    if(h==0&&w==0)  break;
		res=0;
		memset(map,0,sizeof(map));
		getchar();
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++)
			{
			   char c;
			   c=getchar();
			   if(c=='/')
				   type[i][j]=0;
			   else
				   type[i][j]=1;
			}
			getchar();
		}

		int cycle=bfs();
		cout<<"Maze #"<<tcase++<<":"<<endl;
		if(cycle)
		   cout<<cycle<<" Cycles; the longest has length "<<res<<"."<<endl;
		else
		   cout<<"There are no cycles."<<endl;
		cout<<endl;
	}
	return 0;
}
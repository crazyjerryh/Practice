#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("debug.txt");
#define cin fin
#define maxn 110

typedef struct _rect
{
	int tt;
	int l,t,r,b;
}rect;

typedef struct _point
{
	int x,y;
	struct _point(int _x,int _y):x(_x),y(_y){}
}point;

int w,h,t;
int n;
std::vector<rect> rects;
std::vector<point> points;
std::vector<std::vector<point> > paths;
std::vector<point> path;
int map[maxn][maxn];  //用来记录这个点是不是被判断过
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int cmp(rect &a,rect &b){ 
	return a.tt<b.tt; 
}

int tcase=0;
int main(void)
{
	while(cin>>w>>h>>t)
	{
		if(w==0&&h==0&&t==0)  break;
		cin>>n;

		rects.clear();
		path.clear();
		paths.clear();
		points.clear();

		for(int i=0;i<n;i++){
			rect rectangle;
			cin>>rectangle.tt>>rectangle.l>>rectangle.t>>rectangle.r>>rectangle.b;
			rects.push_back(rectangle);  
		}
		std::sort(rects.begin(),rects.end(),cmp);

		int num=0;
		for(int i=0;i<n;i++){
			if(rects[i].tt!=1)
				break;
			++num;
		}
		
		int maxnum=rects[n-1].tt;

		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++){
			   bool flag=true;
               for(int k=0;k<num;k++){
			       if(i>=rects[k].t&&i<=rects[k].b&&j>=rects[k].l&&j<=rects[k].r){
					    flag=false;
						break;
				   }
			   }
			   if(flag)
				   points.push_back(point(i,j));   //i 代表的长度，j代表的是宽度
			}


			cout<<"Robbery #"<<++tcase<<":"<<endl;

			paths.push_back(points);
			if(points.size()==0){
			    cout<<"The robber has escaped."<<endl;
				continue;
			}
	
	    //从第二时间判断人所在的位置
			for(int tt=2;tt<=maxnum;++tt){
				memset(map,0,sizeof(map));
			    int size=points.size();
				int first=num;
				int second=num;

				for(int i=first;i<n;i++){
					if(rects[i].tt!=tt)
						break;
					second++;
				}
				
				num=second;  //设置num为second

				std::vector<point> tpoints;
				for(int j=0;j<size;j++){
					for(int k=0;k<4;++k){
						//判断四个方向的节点是不是可用的
						int curx=points[j].x+dir[k][0];
						int cury=points[j].y+dir[k][1];

						if(curx>0&&cury>0&&curx<=h&&cury<=w)
						{
							if(!map[curx][cury]){
								//未被探测
								bool flag=true;
								for(int d=first;d<second;++d){
									//判断当前的节点在矩形区域内
									if(rects[d].t<=curx&&rects[d].b>=curx&&rects[d].l<=cury&&rects[d].r>=cury)
									{
										//节点在矩形区域内
										flag=false;
										break;
									}
								}
								map[curx][cury]=1;
								if(flag)
								{
									tpoints.push_back(point(curx,cury));
								}
							}
						}
					}
				}

				//交换
				points.swap(tpoints);
				paths.push_back(points);
                //得到每一个时间点，劫匪所有可能的情况
			}

            if(points.size()==0)
				cout<<"The robber has escaped."<<endl;
			else if(points.size()!=1)
				cout<<"Nothing known."<<endl;
			else
			{
				int curx,cury;
				bool f=true;
				curx=points[0].x,cury=points[0].y;
				path.push_back(point(curx,cury));
				int size=paths.size();

				int savex,savey;
				for(int k=size-2;k>=0;k--){
				  std::vector<point> tpoints=paths[k];
				  int cnt=0;
				  for(int i=0;i<4;i++){
					 int x=curx+dir[i][0];
					 int y=cury+dir[i][1];
					 int tsize=tpoints.size();
					 if(x>0&&y>0&&x<=h&&y<=w){
					     for(int j=0;j<tsize;j++)
							 if(x==tpoints[j].x&&y==tpoints[j].y)
							 {
								 cnt++;
								 savex=x;
								 savey=y;
								 break;
							 }
					 }
				 }
				 
				 if(cnt>1)
				 {
					 cout<<"Nothing known"<<endl;
					 f=true;
					 break;
				 }
				 else
				 {
					 path.push_back(point(savex,savey));
					 curx=savex,cury=savey;
				 }
			 }

			 if(f){
				 int s=path.size();
				 int i,j;
				 for(i=s-1,j=1;i>=0;i--,j++)
					 cout<<"Time step "<<j<<": The robber has been at "<<path[i].y<<","<<path[i].x<<endl;
			 }
		  }

		cout<<endl;
	}
	return 0;
}
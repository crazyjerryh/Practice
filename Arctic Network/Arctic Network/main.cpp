#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <memory.h>
#include <vector>
using namespace std;

#define maxn 510
struct point__
{
	double x,y;
	point__(double _x,double _y):x(_x),y(_y){}
	struct point__(){}
}pt[maxn];

typedef struct _edge{
	int a,b;
	double len;
	bool visit;
	_edge(int _a,int _b,double _len):a(_a),b(_b),len(_len),visit(false){}
}edge;

typedef struct point__ point;
int tcase;
int m,n;
double map[maxn][maxn];
int ancestor[maxn];
std::vector<edge> edges;

bool cmp(edge a,edge b)
{
	return a.len<b.len;
}
 
double disce(point a,point b)
{
	double dis=(b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
	return sqrt(dis);
}

int findSet(int a)
{
	while(ancestor[a]!=-1)  a=ancestor[a];
	return a;
}

void unionSet(int a,int b)
{
	int fa=findSet(a);
	int fb=findSet(b);

	if(fa!=fb){
		ancestor[fa]=fb;   
	}
}

double kruskal()
{
	double ans=0;

	int size=edges.size();
	int i,j;
	for(i=0,j=1;i<size;i++){
		if(j>=n)  break;
		int a=edges[i].a;
		int b=edges[i].b;
		
		int fa=findSet(a);
		int fb=findSet(b);
		if((fa==-1&&fb==-1)||fa!=fb){
			unionSet(a,b);
			j++;
			edges[i].visit=true;
		}
	}

	int s=m;
	for(int i=size-1;i>=0;i--){
		if(edges[i].visit){
			s--;
			if(s==0) {
				ans=edges[i].len;
				break;
			}
		}
	}
	return ans;
}

int main(void)
{
	cin>>tcase;
	while(tcase--)
	{
	     cin>>m>>n;
		 for(int i=1;i<=n;i++){
			 cin>>pt[i].x>>pt[i].y;
		 }
		 memset(map,0,sizeof(map));
		 memset(ancestor,-1,sizeof(ancestor));
		 for(int i=1;i<=n;i++){
			 for(int j=i+1;j<=n;j++){
 			      double dis=disce(pt[i],pt[j]);
				  edges.push_back(edge(i,j,dis));
				  map[i][j]=dis;
				  map[j][i]=dis;
			 }
		 }
		 sort(edges.begin(),edges.end(),cmp); 
		 int size=edges.size();
		 double res=kruskal();
		 cout<<fixed<<setprecision(2)<<res<<endl;
		 edges.clear();
	}
	return 0;
}
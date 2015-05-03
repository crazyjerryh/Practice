#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

//ifstream fin("debug.txt");
//#define cin fin

typedef struct _point
{
	double x,y;
}point;

double cross(point a,point b,point c)
{
	//≤Ê≥À,a «‘≠µ„
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

double centerx,centery;
double radius;
int n;
std::vector<point> points;
int main(void)
{
    while(cin>>centerx>>centery>>radius)
	{
		if(radius<0)  break;
	    cin>>n;
		for(int i=0;i<n;i++){
			point pt;
			cin>>pt.x>>pt.y;

			double dis=pow((pt.x-centerx),2)+pow((pt.y-centery),2);
			if(dis<radius*radius||fabs(dis-radius*radius)<1e-9)
			   points.push_back(pt);
		}

		int size=points.size();
		point center;
		center.x=centerx,center.y=centery;
		int cnt=0;
		for(int i=0;i<size;i++)
		{
			int curcnt=0;
			for(int j=0;j<size;j++)
			{
			    double flag=cross(center,points[i],points[j]);
				if(flag>=0)
					curcnt++;
			}
			if(curcnt>cnt)
				cnt=curcnt;
		}
		cout<<cnt<<endl;
		
		points.clear();
	}
	return 0;
}
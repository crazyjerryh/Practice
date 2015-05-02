#include <iostream>
#include <memory.h>
#include <fstream>
using namespace std;

//ifstream fin("debug.txt");
#define maxn 105
//#define cin fin

int flag[maxn][maxn][maxn];
int res[maxn][2];

int w,h,t;
int n;
int maxT;
int dir[5][2]={{0,0},{-1,0},{0,1},{1,0},{0,-1}};
int tcase=0;

bool in(int curx,int cury)
{
	if(curx<1||cury<1||curx>h||cury>w)
		return false;
	return true;
}

void check(int x,int y,int tt,int pt)
{
    for(int i=0;i<5;i++)
	{
		int curx=x+dir[i][0];
		int cury=y+dir[i][1];
		
		if(in(curx,cury)){
			if(!flag[pt][curx][cury])
				return;
		}
	}

	flag[tt][x][y]=1;
}

int main(void)
{
	while(cin>>w>>h>>t)
	{
		if(w==0&&h==0&&t==0)  break;
		
		maxT=0;  //当前的最长的时间
		memset(flag,0,sizeof(flag));
		cin>>n;

		for(int i=0;i<n;i++){
			int tt,l,t,r,b;
			cin>>tt>>l>>t>>r>>b;
			
			for(int j=t;j<=b;j++)
				for(int k=l;k<=r;k++)
				{
					if(!flag[tt][j][k]&&j<=b&&j>=t&&k>=l&&k<=r)
						flag[tt][j][k]=1;   //1 表示点是没有被探测到的， 0表示点被探测到了
					if(maxT<tt)
						maxT=tt;
				}
		}

	 for(int d=0;d<2;d++){
		for(int i=1;i<=maxT;i++){
			for(int j=1;j<=h;j++){
				for(int k=1;k<=w;k++){
					//判断每一个位置是不是存在
					if(d==0&&i!=1)
						check(j,k,i,i-1);
					else if(d==1)
						check(j,k,maxT-i+1,maxT-i+2);
				}
			}
		}
   	}

	memset(res,-1,sizeof(res));
	//计算出结果
	bool mescaped=false;
	bool mmulited=false;
	 for(int i=1;i<=maxT;i++){
		bool escaped=true;
		bool multied=true;  
		for(int j=1;j<=h&&multied;j++)
			for(int k=1;k<=w&&multied;k++){
				if(!flag[i][j][k])
				{
					escaped=false;
					if(res[i][0]>=1)
					{
						multied=false;
						res[i][j]=-2;
					}
					else if(res[i][0]==-1)
					{
						res[i][0]=j;
						res[i][1]=k;
					}
				}
			}
		if(escaped)
			mescaped=true;
		
		if(!multied)
			mmulited=true;
     }

	cout<<"Robbery #"<<++tcase<<":"<<endl;
	if(mescaped)
	    cout<<"The robber has escaped."<<endl;
	else if(mmulited)
		cout<<"Nothing known."<<endl;
	else
	{
		for(int i=1;i<=maxT;i++)
		{
			cout<<"Time step "<<i<<": ";
		    cout<<"The robber has been at "<<res[i][1]<<","<<res[i][0]<<"."<<endl;
		}
	}
    cout<<endl;	
}
	return 0;
}
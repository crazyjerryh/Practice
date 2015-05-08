#include <iostream>
using namespace std;

int mmonth[2][13]={  {0,31,28,31,30,31,30,31,31,30,31,30,31},
	               {0,31,29,31,30,31,30,31,31,30,31,30,31}};

int tcase,n;
typedef struct _date
{
	int year,mouth,day;
}Date;

int getyears(int year)
{
	if((year%4==0&&year%100!=0)||(year%400==0))
		return 366;
	else
		return 365;
}

Date solve(int a,int type)
{
	if(a<0)
	{
		type=(type+1)%2;
		a=-a;
	}

	Date res;
	res.year=2013;
	res.mouth=1;
	res.day=1;


	switch(type)
	{
		int cur,t,curmouth;
	case 0:
		cur=2012;
		
		if(a==0)
			break;
		
		res.year=2012;
		res.mouth=12;
		res.day=31;

		while(a>getyears(cur))
		{
			res.year--;
			a-=getyears(cur);
			cur--;
		}
		
		//月份
		t=getyears(cur)==365?0:1;  
		curmouth=12;
		while(a>mmonth[t][curmouth])
		{
			res.mouth-=1;
			a-=mmonth[t][curmouth];
			curmouth--;
		}

		//日子
		res.day=mmonth[t][curmouth]-a; //当前的a的的值
		break;
	case 1:
		cur=2013;
		
		while(a>getyears(cur)){
			res.year++;
			a-=getyears(cur);
			cur--;
		}
		
		//月份
		t=getyears(cur)==365?0:1;
		curmouth=1;
		while(a>mmonth[t][curmouth])
		{
			res.mouth++;
			a-=mmonth[t][curmouth];
			curmouth++;
		}

		res.day+=a;;
		break;
	}

	return res;
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n;
 
		int ajust=31+28+24-1; //调整的时间
		
		//向前调整
		int a,b;
		a=n-ajust,b=n+ajust; 

		Date res1=solve(a,0);
		Date res2=solve(b,1);
		
		//输出结果
		printf("%4d/%.2d/%.2d ",res2.year,res2.mouth,res2.day);
		printf("%4d/%.2d/%.2d\n",res1.year,res1.mouth,res1.day);
	}
	return 0;
}
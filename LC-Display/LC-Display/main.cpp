#include <iostream>
#include <vector>
using namespace std;

int s,n;
int map[10][5][3]={
	{
		{0,1,0}, //0
		{1,0,1},
		{0,0,0},
		{1,0,1},
		{0,1,0}
	},
    {
	 {0,0,0},   //1
	 {0,0,1},
	 {0,0,0},
	 {0,0,1},   
	 {0,0,0}
	},
	{
	 {0,1,0},   //2
	 {0,0,1},
	 {0,1,0},
	 {1,0,0},
	 {0,1,0}
	},
	{
	 {0,1,0},  //3
	 {0,0,1},
	 {0,1,0},
	 {0,0,1},
	 {0,1,0}
	},
	{
     {0,0,0},  //4
	 {1,0,1},
	 {0,1,0},
	 {0,0,1},
	 {0,0,0}
	},
	{
	  {0,1,0},  //5
	  {1,0,0},
	  {0,1,0},
	  {0,0,1},
	  {0,1,0}
	},
	{
	  {0,1,0},   //6
      {1,0,0},
	  {0,1,0},
	  {1,0,1},   
	  {0,1,0}
	},
	{
	  {0,1,0},   //7
	  {0,0,1},
	  {0,0,0},
	  {0,0,1},
	  {0,0,0}
	},
	{
	  {0,1,0},  //8
	  {1,0,1},
	  {0,1,0},
	  {1,0,1},
	  {0,1,0}
	},
	{
	  {0,1,0},  //9
	  {1,0,1},
	  {0,1,0},
	  {0,0,1},
	  {0,1,0}
	}
};

void printrow(int row,int num)
{
	//打印一行数据
	cout<<' ';
	for(int i=0;i<s;i++)
	  if(map[num][row][1])
		  cout<<'-';
	  else
		  cout<<' ';
	cout<<' ';
	cout<<' ';
}

void printcol(int row,int num)
{
		//打印s行数据
		if(map[num][row][0])
			cout<<'|';
		else
			cout<<' ';
		for(int j=0;j<s;j++)
			cout<<' ';
		
		if(map[num][row][2])
			cout<<'|';
		else
			cout<<' ';
		cout<<' ';
}

int main(void)
{
	while(cin>>s>>n)
	{
		if(s==0&&n==0)  break;
		//打印行数据
		std::vector<int> vec;
		if(n==0)
			vec.push_back(0);
		else
		{
			while(n)
			{
				vec.push_back(n%10);
				n=n/10;
			}
		}

		int size=vec.size();
		for(int i=size-1;i>=0;i--){
			int num=vec[i];
			printrow(0,num);
		}
		cout<<endl;
		for(int j=0;j<s;j++){
		for(int i=size-1;i>=0;i--){
			int num=vec[i];
			printcol(1,num);
		}
		cout<<endl;
		}

		for(int i=size-1;i>=0;i--){
			int num=vec[i];
			printrow(2,num);
		}
		cout<<endl;

		for(int j=0;j<s;j++){
		for(int i=size-1;i>=0;i--){
			int num=vec[i];
			printcol(3,num);
		}
		cout<<endl;
		}

		for(int i=size-1;i>=0;i--){
			int num=vec[i];
			printrow(4,num);
		}
		cout<<endl;
		cout<<endl;
	}
	return 0;
}
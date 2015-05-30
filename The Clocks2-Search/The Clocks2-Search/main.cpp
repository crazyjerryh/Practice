#include <iostream>
#include <memory.h>
using namespace std;

int dir[9][9]={{1,1,0,1,1,0,0,0,0},
{1,1,1,0,0,0,0,0,0},
{0,1,1,0,1,1,0,0,0},
{1,0,0,1,0,0,1,0,0},
{0,1,0,1,1,1,0,1,0},
{0,0,1,0,0,1,0,0,1},
{0,0,0,1,1,0,1,1,0},
{0,0,0,0,0,0,1,1,1},
{0,0,0,0,1,1,0,1,1}
};

int start[9],tmp[9];
int num[9];
bool judge(){
	for(int i=0;i<9;i++)
		tmp[i]=start[i];

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			tmp[j]=(tmp[j]+dir[i][j]*num[i])%4;

	for(int i=0;i<9;i++)
        if(tmp[i])
			return 0;
	return 1;
}

void print()
{
	for(int i=0;i<9;i++)
		for(int j=0;j<num[i];j++)
			if(num[i]) cout<<i+1<<" ";
	cout<<endl;
}

bool dfs(int dep)
{
     if(judge()){
		 print();
		 return true;
	 }
	 
	 if(dep>=9)
		 return false;
	 
	 for(int i=0;i<4;i++){
		 num[dep]=i;
		 if(dfs(dep+1))
			 return true;
		 num[dep]=0;
	 }
	 return false;
}

int main(void)
{
	for(int i=0;i<9;i++)
		cin>>start[i];
	memset(num,0,sizeof(num));
	dfs(0);
	return 0;
}
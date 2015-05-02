#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
#include <cmath>
using namespace std;
#define maxn 10
#define mmax 400

int n,m;  //m代表的是查询个数
int a[maxn];
int b[maxn];
int tree[mmax]; //树节点的个数
int tcase=0;
int main(void)
{
	while(cin>>n)
	{
		if(n==0)   break;
		memset(tree,0,sizeof(tree));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));

		for(int i=0;i<n;i++){
			char c;
			c=getchar();
			//消去x
			getchar();
			c=getchar();
			a[i]=c-'0';
		}
		getchar();
		//初始化树节点
		for(int i=((1<<n)-1);i<((1<<(n+1))-1);++i){
			char c;
			c=getchar();
			tree[i]=c-'0';  
		}

		cin>>m;

		std::vector<int> res;
		for(int i=0;i<m;i++)
		{
			getchar();
			char c;
			for(int j=0;j<n;j++){
				c=getchar();
				b[j]=c-'0';
			}
	  
			//对当前的查询进行判断
			int cur=0;
			for(int j=0;j<n;j++){
				int branch=b[a[j]-1];
				if(branch==0)
					cur=2*(cur+1)-1;
				else
					cur=2*(cur+1);
			}
		   res.push_back(tree[cur]);
	   }

	   int size=res.size();
	   cout<<"S-Tree #"<<++tcase<<":"<<endl;
	   for(int i=0;i<size;i++)
		   cout<<res[i];
	   cout<<endl;

	   //each case output a blank line
	   cout<<endl;
	}
	return 0;
}
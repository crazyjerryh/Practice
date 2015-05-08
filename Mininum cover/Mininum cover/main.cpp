#include <stdio.h>
#include <algorithm>

#define maxn 2004
char result[maxn][maxn];
char str[maxn][maxn];

int n,m,x,y;
#define max(a,b) a>b?a:b

int solveA(int w,int h,int len)
{
	int cnt=0;
    for(int i=0;i<h;i++){
		int k=0;
		for(int j=0;j<w;j++){
			if(str[i][j]=='*')
				k++;
			else
			    k=0;
			
			if(k==len)
			{
				result[i][j]='*';
				cnt++;
				k--;
			}
			else
				result[i][j]='.';
		}
	}	
	
	return cnt;
}

int solveB(int w,int h,int len)
{
	int cnt=0;
	for(int i=0;i<h;i++){
		int k=0;
		for(int j=0;j<w;j++){
			if(result[i][j]=='*')
				k++;
			else
				k=0;

			if(k==len)
			{
				result[i][j]='*';
				cnt++;
				k--;
			}
			else
				result[i][j]='.';
		}
	}	

	return cnt;
}


void reserveA(int &w,int &h)
{
	int mm=max(w,h);
	for(int i=0;i<mm;i++)
	   for(int j=0;j<i;j++){
		   std::swap(str[i][j],str[j][i]); //交换数据
	   }
}

void reserveB(int &w,int &h)
{
	int mm=max(w,h);
	for(int i=0;i<mm;i++)
		for(int j=0;j<i;j++){
			std::swap(result[i][j],result[j][i]); //交换数据
		}
}

int main(void)
{
	while(scanf("%d%d",&n,&m)){
		if(n==0&&m==0) break;
		
		scanf("%d%d",&x,&y);
		for(int i=0;i<n;i++){
			scanf("%s",&str[i]);
		}

		solveA(m,n,y);  //y代表宽度
		reserveB(m,n);
		int total=solveB(n,m,x); //x代表高度

		if(x!=y){
			reserveA(m,n);
			solveA(n,m,y);
			reserveB(n,m);  
			total+=solveB(m,n,x);
		}
		printf("%d\n",total);
		//free memory
	}
	return 0;
}
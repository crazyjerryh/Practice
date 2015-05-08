 /*#include <stdio.h>
#include <memory.h>

#define maxn 2004
char str[maxn][maxn]; 
int sum[maxn][maxn];

int n,m,x,y;
int main(void)
{
	while(scanf("%d%d",&n,&m)!=EOF){
		if(n==0&&m==0)  break;
		scanf("%d%d",&x,&y);  //x height,y width
		memset(sum,0,sizeof(sum));
		getchar();
		for(int i=1;i<=n;i++){
			scanf("%s",1+str[i]);
		    int  count=0;
			 for(int j=1;j<=m;j++){
			 if(str[i][j]=='*')count++;
			    sum[i][j]=count+sum[i-1][j];
			  }
		}

		//判断是不是大于零
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(i+x-1<=n&&j+y-1<=m){
					int ans=sum[i+x-1][j+y-1]-sum[i-1][j+y-1]-sum[i+x-1][j-1]+sum[i-1][j-1];
					if(ans==x*y)
						cnt++;
				}

				if(i+y-1<=n&&j+x-1<=m&&x!=y){
					int ans=sum[i+y-1][j+x-1]-sum[i-1][j+x-1]-sum[i+y-1][j-1]+sum[i-1][j-1];
					if(ans==x*y)
						cnt++;
				}
			}
	   printf("%d\n",cnt);
	}
	return 0;
}*/
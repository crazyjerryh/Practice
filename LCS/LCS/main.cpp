#include <stdio.h>
#include <memory.h>
#include <string.h>
#define maxn 1001
#define max(a,b) a>b?a:b

char first[maxn],second[maxn];
int a[maxn][maxn];
int main(void)
{
	while(scanf("%s%s",first+1,second+1)!=EOF){
		first[0]=second[0]='#';
		int len1,len2;
		len1=strlen(first),len2=strlen(second);
		
		memset(a,0,sizeof(a));

		int result=0;
		for(int i=1;i<len1;i++){
			for(int j=1;j<len2;j++){
				if(first[i]==second[j])
					a[i][j]=max(a[i-1][j-1]+1,a[i][j]);
				else
					a[i][j]=max(a[i-1][j],a[i][j-1]);
				if(a[i][j]>result)
					result=a[i][j];
			}
	}

		printf("%d\n",result);
	}
	return 0;
}
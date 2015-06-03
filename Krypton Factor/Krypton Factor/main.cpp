#include <stdio.h>
#define maxn 100

int n,L;
int cnt;
char str[maxn];

bool judge(int len)
{
	for(int i=1;2*i<=len+1;i++){
		bool flag=true;
		for(int j=0;j<i;j++){
			if(str[len-i-j]!=str[len-j]){
				flag=false;
				break;
			}
		}
		if(flag) return false;
	}
	return true;
}

bool dfs(int len)
{
     if(cnt==n){
		 for(int i=0;i<len;i++){
		       if(i%64==0&&i>0)
				   printf("\n");
			   else if(i%4==0&&i>0)
				   printf(" ");
			   printf("%c",str[i]);
		 }
		 printf("\n%d\n",len);
		 return true;
	 }

	 for(int i=0;i<L;i++)
	 {
		 str[len]=i+'A';
		 if(judge(len)){
		     cnt++;
		     if(dfs(len+1))
				 return true;
		 }
	 }
	 return false;
}

int main(void)
{
	while(scanf("%d%d",&n,&L)!=EOF)
	{
		if(n==0&&L==0)  break;
		cnt=0;
		dfs(0);
	}
	return 0;
}
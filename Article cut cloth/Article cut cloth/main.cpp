#include <stdio.h>
#include <string.h>
using namespace std;
#define maxn 1010

char src[maxn],des[maxn];
int _next[maxn];

void getNext()
{
	_next[0]=-1;
	_next[1]=0;

	int len=strlen(des+1);
	for(int i=2;i<=len;i++)
	{
		int prefix=_next[i-1];
		while(prefix>=0&&des[prefix+1]!=des[i])
			 prefix=_next[prefix]; 
		
		if(prefix<0)
		    _next[i]=0;
		else
			_next[i]=prefix+1;
	}
}

int main(void)
{
	while(scanf("%s",src+1)!=EOF)
	{
		if(src[1]=='#')  break;
		scanf("%s",des+1);
		getNext();
		
		int ans=0;
		int len=strlen(src+1);
		int Len=strlen(des+1);

		int i,j;
		for(i=1,j=0;i<=len;i++){
			while(j>=0&&des[j+1]!=src[i])
				j=_next[j];
			
			if(j<0)
				j=0;
			else
				j++;

			if(j>=Len)
			{
				++ans;
				j=0;
			}
		}
		
		printf("%d\n",ans);
	}
	return 0;
}
#include <stdio.h>
#include <string.h>
#define maxn 110010

char str1[maxn];
#define max(a,b)  a>b?a:b
#define min(a,b)  a<b?a:b
int px[maxn<<1];
char str[maxn<<1];
int main(void)
{
	while(scanf("%s",&str1)!=EOF)
	{
		int len=strlen(str1);
		str[0]='#';
		for(int i=0;i<len;i++){
			str[2*i+1]=str1[i];
			str[2*i+2]='#';
		}

		int id=0;
		px[0]=1;
		int maxid=0;
		for(int i=1;i<2*len+1;i++){
		    if(i<id+px[id])  px[i]=min(px[2*id-i],px[id]+id-i);
			else
				px[i]=1;
			
			while(i>=px[i]&&str[px[i]+i]==str[i-px[i]])   px[i]++;
			if(px[i]+i>id+px[id])
				id=i;
			if(px[i]>px[maxid])
				maxid=id;
		}
	    
		printf("%d\n",px[maxid]-1);
		
	}
}
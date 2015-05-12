#include <stdio.h>
#include <string.h>

#define maxn 2000004
#define maxm 1000004
#define min(a,b) a<b?a:b

char temp[maxm],str[maxn];
int px[maxn];
int n;
int main(void)
{
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%s",&temp);

		int len=strlen(temp);
		str[0]='*';

		for(int i=0;i<len;i++){
			str[2*i+1]='#';
			str[2*i+2]=temp[i];
		}
		str[2*len+1]='#';

		int id=0;
		px[id]=0;
		int maxlen=0;
		for(int i=1;i<=2*len+1;i++){
			if(id+px[id]>i)
				px[i]=min(px[id]+id-i,px[2*id-i]);
			else
				px[i]=1;
			
			while(str[i+px[i]]==str[i-px[i]]) px[i]++;
			
			if(i+px[i]>px[id]+id)
		          id=i;

			if(px[i]>maxlen)  maxlen=px[i];
		}

		printf("%d\n",maxlen-1);
		}
	}
	return 0;
}

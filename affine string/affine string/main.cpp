#include <stdio.h>
#include <memory.h>
#include <string.h>
// #include <iostream>
// using namespace std;
#define maxn 200010
#define maxm 100010

char src[maxn],des[maxm];
int _next[maxm];
int maxlen;
int len;
void getNext()
{
	_next[1]=0;
	_next[0]=-1;
	for(int i=2;i<=len;i++){
		int inx=_next[i-1];
		
		while(inx>=0&&des[inx+1]!=des[i])
	        inx=_next[inx];

		if(inx<0)
			_next[i]=0;
		else
		{
			if(des[inx+1]==des[i])
				_next[i]=inx+1;
		}
	}
}

bool kmp()
{
	int i,j=0;
	for(i=1;i<=maxlen;i++){
		while(j>=0&&src[i]!=des[j+1])
			j=_next[j];

		if(j<0)
			j=0;
		else
		{
			if(src[i]==des[j+1])
				j++;
			if(j==len)
				return true;
		}
	}

   return false;
}

int main(void)
{
	while(scanf("%s%s",src+1,des+1)!=EOF){
		maxlen=strlen(src+1);
		int i,j;
	    for(i=1,j=maxlen+1;i<=maxlen;i++,j++){
		    src[j]=src[i];
		}
		src[j]='\0';
		maxlen=j-1;

		//cout<<src+1<<endl;
		len=strlen(des+1);
		getNext();

// 		for(int i=1;i<=len;i++)
// 			cout<<_next[i]<<" ";
// 		cout<<endl;

		bool flag=kmp();
		if(flag)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}
#include <iostream>
#include <string.h>
#define maxm 104
#define maxn 104
#define inf 0x3ffff

using namespace std;
char str[maxm][maxn];
int len[maxn];
int tcase;
int n;
int mink;
int maxlen,minlen;

bool match(int start,int end)
{
   bool flag=false;
   for(int i=0;i<n;i++){
	   if(i==mink)
		    continue;
	   
	   bool pflag=false;
	   for(int j=0;j<len[i]-end+start;j++){
		     bool fflag=true;
	         for(int k=0;k<end-start+1;k++){
				  //cout<<str[mink][start+k]<<" "<<str[i][j+k]<<endl;
				  if(str[mink][start+k]!=str[i][j+k])
				  {
					  fflag=false;
					  break;
				  }
			 }   

			 if(fflag)
			 {
				 pflag=true;
				 break;
			 }

			 fflag=true;
			 for(int k=0;k<end-start+1;k++){
				 if(str[mink][end-k]!=str[i][j+k])
				 {
					 fflag=false;
					 break;
				 }
			 }

			 if(fflag)
			 {
			    pflag=true;
				break;
			 }
	   }

	   if(!pflag)
		   return false;
   }	

   return true;
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n;
		int minlen=inf;
		int maxlen=0;
		for(int i=0;i<n;i++){
			cin>>str[i];
			len[i]=strlen(str[i]);
			if(len[i]<minlen)
			{
				minlen=len[i];
				mink=i;
			}
		}

		bool flag=0;
		for(int i=minlen;i>=1;i--){
			for(int j=0;j+i<=minlen;j++){
				int start=j,end=j+i-1;

				if(match(start,end))
				{
					flag=1;
					maxlen=i;
					break;
				}
			}
			if(flag)
				break;
		}

		cout<<maxlen<<endl;
	}
	return 0;
}
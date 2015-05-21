/*2-dimension
#include <iostream>
#include <fstream>
using namespace std;

#define maxn 100010
int a[maxn];
int n;
ifstream fin("debug.txt");

int main(void)
{
     while(fin>>n){
	     if(n==0 )  break;
		 for(int i=1;i<=n;i++)
			 fin>>a[i];

		 int first,second;
		 first=second=0;
		 int mmax=-0xffffff;

		 int i;
		 int prefix=0;
		 first=second=1;
		 int pre=1;
		 for(i=1;i<=n;i++){
		      if(prefix+a[i]>mmax)
			  {
			        mmax=prefix+a[i];
					first=pre;
					second=i;
			  }

			  prefix+=a[i];
			  //prefix is negative
			  while(pre<=i&&prefix<0){
				   prefix-=a[pre];
				   pre++;
			  }

		 }

		 cout<<"["<<first<<","<<second<<"]:"<<mmax<<endl;
		
	 }
	return 0;
}*/
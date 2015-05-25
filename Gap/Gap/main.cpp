#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <memory.h>
#include <map>
using namespace std;

typedef unsigned long long ULL;
int tcase;
int A[33]={11,12,13,14,15,16,17,0,21,22,23,24,25,26,27,0,31,32,33,34,35,36,37,0,41,42,43,44,45,46,47,0};
int a[33];
map<ULL,int> hashtable;


typedef struct _node
{
     int a[33];
	 int x[4];
	 ULL hashval;
	 int step;
}node;

queue<node> Q;

ULL getkey(int *a)
{
	ULL res=1;
	for(int i=0;i<32;i++)
		res=(res<<1)+a[i];

	return res;
}
int main(void)
{
	//cin>>tcase;
	scanf("%d",&tcase);
	ULL end=getkey(A);
	while(tcase--){
		while(!Q.empty()) Q.pop();
		hashtable.clear();
		int now=0;
		memset(a,0,sizeof(a));
		node start;
		int h=0;
		for(int i=0;i<4;i++){
			now++;
			for(int j=0;j<7;j++){
				//cin>>a[now];
				scanf("%d",&a[now]);
				if(a[now]%10==1){
					 swap(a[now],a[(a[now]/10-1)*8]);
					 start.x[h++]=now;
				}
				now++;
			}
		}
		
		for(int i=0;i<32;i++)
			start.a[i]=a[i];

		start.hashval=getkey(start.a);
		hashtable[start.hashval]=1;
		start.step=0;
		std::queue<node> Q;
		Q.push(start);
		int flag=0;
		while(!Q.empty())
		{
			 node top=Q.front();
			 Q.pop();
			 if(top.hashval==end)
			 {
				 printf("%d\n",top.step);
				 flag=1;
				 break;
			 }
			 for(int i=0;i<4;i++){
				 int cur=top.a[top.x[i]-1];
				 if(cur%10==7||cur==0)  continue;
				 node tmp=top;
				 for(int j=0;j<32;j++){
				      if(tmp.a[j]==cur+1)
					  {
						  swap(tmp.a[j],tmp.a[tmp.x[i]]);
						  tmp.x[i]=j;
						  break;
					  }
				 }


				 ULL hs=getkey(tmp.a);
				 if(hashtable.find(hs)!=hashtable.end())   continue;
				 hashtable[hs]=1;
				 tmp.hashval=hs;
				 tmp.step++;
				 Q.push(tmp);
					 
			 }
		}
		if(!flag)
			cout<<"-1"<<endl;
	}
	return 0;
}
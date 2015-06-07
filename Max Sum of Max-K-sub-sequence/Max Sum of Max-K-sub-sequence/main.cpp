#include <stdio.h>
#define maxn 201111

struct _node
{
	int data;
	int pos;
	_node(int _data,int _pos):data(_data),pos(_pos){}
	_node(){}
};

typedef struct _node node;
int a[maxn];
node queue[maxn];
int tcase,n,k;
int main(void)
{
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		
		for(int i=1;i<=k;i++)
			a[i+n]=a[i];

		int first,second;
		first=second=0;
		int maxsum=-0xfffff;
		int front,tail;
		front=tail=0;
		queue[tail++]=node(0,0);
		int sum=0;
		for(int i=1;i<=n+k;i++){
			 sum+=a[i];
			 while(front<tail&&queue[tail-1].data>sum)
				  tail--;
			 queue[tail++]=node(sum,i);
			 while(front<tail&&queue[front].pos<i-k)
				  front++;

			 if(tail-1==front)
			 {
				 int pos=queue[front].pos;
				 if(maxsum<a[pos]){
				      maxsum=a[pos];
					  first=pos;
					  second=pos;
				 }
				 continue;
			 }

			 if(maxsum<queue[tail-1].data-queue[front].data)
			 {
				 maxsum=queue[tail-1].data-queue[front].data;
				 first=queue[front].pos+1;
				 second=queue[tail-1].pos;
			 }
		}

		if(first>n)  first=first%n;
		if(second>n)  second=second%n;
		printf("%d %d %d\n",maxsum,first,second);
		
	}
	
	return 0;
}
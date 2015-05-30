#include <stdio.h>
#include <memory.h>
#define maxn (1<<20)+3
int prime[maxn];
int composite[maxn];
int n;
int *a;

FILE *file;

void isprime()
{
    memset(prime,1,sizeof(prime));
	prime[1]=prime[0]=0;
	for(int i=2;i<maxn;i++){
		if(!prime[i])  continue;
		for(int j=2;i*j<maxn;j++){
			prime[i*j]=0;
		}
	}

	for(int i=0;i<maxn;i++)
		if(prime[i])
          		fprintf(file,"%d ",i);
	fprintf(file,"\n");
}

void  init()
{
	isprime();
    memset(composite,1,sizeof(composite));
	composite[0]=composite[1]=composite[2]=composite[3]=0;
    for(int i=4;i<maxn;i++){
		if(prime[i])  {composite[i]=0; continue;}
		for(int j=2;i*j<maxn;j++){
		     composite[i*j]=0;
		}
	}

	for(int i=0;i<maxn;i++)
		if(composite[i])
			fprintf(file,"%d ",i);
	fprintf(file,"\n");
}

int main(void)
{
	file=fopen("debug.txt","w");
	init();
	while(scanf("%d",&n)!=EOF){
	      a=new int[n];
		  for(int i=0;i<n;i++){
			  scanf("%d",&a[i]);
		  }

		  int ans=0;
		  for(int i=0;i<n;i++){
			  int inx=a[i];
			  if(composite[inx])  ans++;
		  }
		  printf("%d\n",ans);
	}
	return 0;
}
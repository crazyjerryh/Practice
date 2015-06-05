#include <stdio.h>

#define inf 0xffff
#define STATUS (1<<18)-1
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

int mat[11][11]=
{{0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,2,3,4,0,0,0,0,0},
{0,1,2,0,0,5,6,0,0,0,0},
{0,0,3,0,0,7,0,9,10,0,0},
{0,0,4,5,7,0,8,0,11,12,0},
{0,0,0,6,0,8,0,0,0,13,14},
{0,0,0,0,9,0,0,0,15,0,0},
{0,0,0,0,10,11,0,15,0,16,0},
{0,0,0,0,0,12,13,0,16,0,17},
{0,0,0,0,0,0,0,14,0,17,0}
};
int tri[9]={7,152,52,352,34304,3200,71680,12544,155648};
int tcase;
int n;
int status;

int minsearch(int,int,int,int);
int maxsearch(int,int,int,int);

int getstatus(int old,int seg,int &cnt)
{

	int now=old|seg;
	for(int i=0;i<9;i++){
		if(((old&tri[i])!=tri[i])&&((now&tri[i])==tri[i]))
			cnt++;
	}
	return now;
}

int minsearch(int state,int alpha,int ca,int cb)
{
	 int beta=inf;
	 if(ca>=5)  return inf;
	 else if(cb>=5)  return -inf;
	 if(state==STATUS)  return ca>cb?inf:-inf;
	 
	 int remain=(~state)&STATUS;
	 while(remain){
		 int seg=remain&(-remain);
		 int ta,tb;
		 ta=ca,tb=cb;
		 int now=getstatus(state,seg,tb);
		 int tmp;
	     if(tb>cb)
			 tmp=minsearch(now,alpha,ta,tb);
		 else
			 tmp=maxsearch(now,beta,ta,tb);
		 if(tmp<beta)  beta=tmp;
		 if(tmp<=alpha)  return beta;
		 remain-=seg;
	 }
	 return beta;
}

int maxsearch(int state,int beta,int ca,int cb)
{
	int alpha=-inf;
	if(ca>=5)  return inf;
	else if(cb>=5)  return -inf;
	if(state==STATUS)  return ca>cb?inf:-inf;

	int remain=(~state)&STATUS;
	while(remain){
		int seg=remain&(-remain);
		int ta=ca,tb=cb;
		int now=getstatus(state,seg,ta);
		int tmp;
		if(ta>ca)
			tmp=maxsearch(now,beta,ta,tb);
		else
		    tmp=minsearch(now,alpha,ta,tb);
		if(tmp>alpha)  alpha=tmp; 
		if(tmp>=beta) return alpha;
		remain-=seg;
	}
	return alpha;
}


int main(void)
{
	scanf("%d",&tcase);
	int tt=1;
	while(tcase--){
	    scanf("%d",&n);
		int ca=0,cb=0;
		status=0;
		int cnt=0;
		for(int i=0;i<n;i++){
		    int u,v;
			scanf("%d%d",&u,&v);
			int ta=ca,tb=cb;
		    status=getstatus(status,1<<mat[u][v],(cnt&1)?cb:ca);
			if(ca==ta&&cb==tb)
				cnt++;
		}
		int ans;
		if(cnt&1)  ans=minsearch(status,-inf,ca,cb);  
		else
			ans=maxsearch(status,inf,ca,cb);
		printf("Game %d: %c wins.\n",tt++,ans==inf?'A':'B');
		 
	}
	return 0;
} 
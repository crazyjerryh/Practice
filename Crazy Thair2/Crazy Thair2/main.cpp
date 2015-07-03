#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 50010
#define base 10000

struct node{
	int x,y;
}nodes[maxn];

struct BigInt{
	int num[7],len;
	BigInt():len(0){
		memset(num,0,sizeof(num));
	}

	BigInt operator=(int n){
		int size=0;
		while(n){
			num[size++]=n%base;
			n=n/base;
		}
		len=size;
		return *this;
	}

	BigInt operator+(BigInt b){
		BigInt c;
		int size=0,carry=0;
		for(int i=0;i<b.len||i<len||carry;i++){
			if(i<b.len) carry+=b.num[i];
			if(i<len)  carry+=num[i];
			c.num[i]=carry%base;
			carry=carry/base;
			size++;
		}
		c.len=size;
		return c;
	}

	void output(){
		if(len==0)  {printf("0\n"); return;}
		printf("%d",num[len-1]);
		for(int i=len-2;i>=0;i--){
			printf("%04d",num[i]);
		}
		printf("\n");
	}
};

int n,maxnum;
BigInt dp[6][maxn];
int b[maxn];

bool cmp(node a,node b){
	if(a.x==b.x)
		return a.y<b.y;
	return a.x<b.x;
}

int lowbit(int x){
	return x&-x;
}

void update(int inx,int x,BigInt num){
	while(x<=maxnum){
		dp[inx][x]=dp[inx][x]+num;
		x=x+lowbit(x);
	}
}

BigInt sum(int inx,int x){
	BigInt ans;
	ans=0;
	while(x){
		ans=ans+dp[inx][x];
		x=x-lowbit(x);
	}
	return ans;
}

void solve(){
	for(int i=0;i<6;i++){
		for(int j=0;j<maxn;j++)
			dp[i][j]=0;
	}

	for(int i=1;i<=n;i++){
		BigInt tmp;
		tmp=1;
		update(1,b[i],tmp);
		for(int j=2;j<=5;j++)
			update(j,b[i],sum(j-1,b[i]-1));
	}
	BigInt ans;
	ans=0;
	ans=sum(5,maxnum);
	ans.output();
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%d",&nodes[i].x);
			nodes[i].y=i;
		}
		sort(nodes+1,nodes+1+n,cmp);

		maxnum=0;
		b[nodes[1].y]=++maxnum;
		for(int i=2;i<=n;i++){
			if(nodes[i].x==nodes[i-1].x)   b[nodes[i].y]=maxnum;
			else
				b[nodes[i].y]=++maxnum;
		}
		solve();
	}
}
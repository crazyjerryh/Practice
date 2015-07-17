#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <cmath>
#include <algorithm>
using namespace std;
#define maxn 1000010
#define inf   0x3f3f3f3f
char str[maxn];
int s[maxn],rk[maxn],sa[maxn],height[maxn];
int wa[maxn],wb[maxn],c[maxn],r[maxn];
int dp[20][maxn];

void init(){
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
}

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void buildsa(int n){
	int *x=wa,*y=wb,m=maxn;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(int j=1,p=1;p<n;j*=2,m=p){
		p=0;
		for(int i=n-j;i<n;i++)  y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=j)  y[p++]=sa[i]-j;
		for(int i=0;i<n;i++) r[i]=x[y[i]];
		for(int i=0;i<m;i++)  c[i]=0;
		for(int i=0;i<n;i++)  c[r[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)  sa[--c[r[i]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)  x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
	}
}

void calheight(int n){
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
	for(int i=0,k=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

void InitRMQ(int n){
	for(int i=0;i<20;i++)
		for(int j=0;j<maxn;j++)
			dp[i][j]=inf;
	for(int i=2;i<=n;i++)  dp[0][i]=height[i];
	for(int i=1;i<21;i++){
		for(int j=2;j<=n;j++){
			if(j+(1<<i)-1<=n)
				dp[i][j]=min(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
		}
	}
}

int check(int patch,int n){
	int l=rk[0],r=rk[patch];
	if(l>r)  swap(l,r);
	l++;
	int len=(int)(log(1.0*(r-l+1))/log(2.0));
	return min(dp[len][l],dp[len][r-(1<<len)+1]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%s",str)){
		if(str[0]=='.')  break;
		init();
		int n=strlen(str);
		for(int i=0;i<n;i++)  s[i]=(int)str[i];
		s[n]=0;
		buildsa(n+1);
		calheight(n);
		InitRMQ(n);

		int left=1,right=n;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(i==n){
				ans=n;
				break;
			}
			if(n%i==0){
				int tmp=check(i,n);
				if(tmp==n-i){
					ans=i;
					break;
				}
			}
		}
		printf("%d\n",n/ans);
	}
	return 0;
}#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <cmath>
#include <algorithm>
	using namespace std;
#define maxn 1000010
#define inf   0x3f3f3f3f
char str[maxn];
int s[maxn],rk[maxn],sa[maxn],height[maxn];
int wa[maxn],wb[maxn],c[maxn],r[maxn];
int dp[20][maxn];

void init(){
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
}

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void buildsa(int n){
	int *x=wa,*y=wb,m=maxn;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(int j=1,p=1;p<n;j*=2,m=p){
		p=0;
		for(int i=n-j;i<n;i++)  y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=j)  y[p++]=sa[i]-j;
		for(int i=0;i<n;i++) r[i]=x[y[i]];
		for(int i=0;i<m;i++)  c[i]=0;
		for(int i=0;i<n;i++)  c[r[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)  sa[--c[r[i]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)  x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
	}
}

void calheight(int n){
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
	for(int i=0,k=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

void InitRMQ(int n){
	for(int i=0;i<20;i++)
		for(int j=0;j<maxn;j++)
			dp[i][j]=inf;
	for(int i=2;i<=n;i++)  dp[0][i]=height[i];
	for(int i=1;i<21;i++){
		for(int j=2;j<=n;j++){
			if(j+(1<<i)-1<=n)
				dp[i][j]=min(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
		}
	}
}

int check(int patch,int n){
	int l=rk[0],r=rk[patch];
	if(l>r)  swap(l,r);
	l++;
	int len=(int)(log(1.0*(r-l+1))/log(2.0));
	return min(dp[len][l],dp[len][r-(1<<len)+1]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%s",str)){
		if(str[0]=='.')  break;
		init();
		int n=strlen(str);
		for(int i=0;i<n;i++)  s[i]=(int)str[i];
		s[n]=0;
		buildsa(n+1);
		calheight(n);
		InitRMQ(n);

		int left=1,right=n;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(i==n){
				ans=n;
				break;
			}
			if(n%i==0){
				int tmp=check(i,n);
				if(tmp==n-i){
					ans=i;
					break;
				}
			}
		}
		printf("%d\n",n/ans);
	}
	return 0;
}
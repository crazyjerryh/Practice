#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn  20010
#define maxm 1000010

int num[maxn],sa[maxn],rk[maxn],height[maxn];
int wa[maxn],wb[maxn],c[maxm],r[maxn];
int cnt;

void init(){
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
}

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void buildsa(int n){
	int *x=wa,*y=wb,m=maxm;
	for(int i=0;i<m;i++)  c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=num[i]]++;
	for(int i=1;i<m;i++)  c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)  sa[--c[x[i]]]=i;
	for(int j=1,p=1;p<n;j*=2,m=p){
		p=0;
		for(int i=n-j;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(int i=0;i<n;i++)  r[i]=x[y[i]];
		for(int i=0;i<m;i++)  c[i]=0;
		for(int i=0;i<n;i++)  c[r[i]]++;
		for(int i=1;i<m;i++)  c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)  sa[--c[r[i]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)  x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
	}
}

void calheight(int n){
	for(int i=1;i<=n;i++)  rk[sa[i]]=i;
	for(int i=0,k=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rk[i]-1];
		while(num[i+k]==num[j+k]) k++;
		height[rk[i]]=k;
	}
}

bool check(int mid,int n){
	int ans=1;
	for(int i=2;i<=n;i++){
		if(height[i]<mid) {ans=1;}
		else{
			ans++;
			if(ans>=cnt)  return 1;
		}
	}
	return 0;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	int n;
	while(scanf("%d%d",&n,&cnt)!=EOF){
		init();
		for(int i=0;i<n;i++)  scanf("%d",&num[i]),num[i]++;
		num[n]=0;
		buildsa(n+1);
		calheight(n);
		int ans=0;
		int first=1,second=n;
		while(first<=second){
			int mid=(first+second)>>1;
			if(check(mid,n)){
			    ans=mid;
				first=mid+1;
			}
			else
			    second=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
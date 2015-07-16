#include <stdio.h>
#include <memory.h>
#include <cmath>
#include <algorithm>
using namespace std;
#define maxn 200001

int sa[maxn],rk[maxn],height[maxn],s[maxn];
int wa[maxn],wb[maxn],c[maxn],r[maxn];

void init(){
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
}

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void build_sa(int n){
	int *x=wa,*y=wb,m=200;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=s[i]]++;
	for(int i=1;i<m;i++)  c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(int k=1,p=1;p<n;k*=2,m=p){ 
		p=0;
		for(int i=n-k;i<n;i++)  y[p++]=i;
		for(int i=0;i<n;i++)  if(sa[i]>=k)  y[p++]=sa[i]-k;
		for(int i=0;i<n;i++)   r[i]=x[y[i]];
		for(int i=0;i<m;i++)   c[i]=0;
		for(int i=0;i<n;i++)   c[r[i]]++;
		for(int i=1;i<m;i++)   c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)   sa[--c[r[i]]]=y[i];
		swap(x,y);
		int i;
		for(p=1,x[sa[0]]=0,i=1;i<n;i++){
			x[sa[i]]=cmp(y,sa[i-1],sa[i],k)?p-1:p++;
		}
	}
}

void calheight(int n){
	for(int i=1;i<=n;i++)  rk[sa[i]]=i; 
	for(int k=0,i=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k])  k++;
		height[rk[i]]=k;
	}
}

bool check(int mid,int n){
	for(int i=2;i<=n;i++){
		if(height[i]<mid)  continue;
		for(int j=i-1;j>=1;j--){
			if(abs(sa[i]-sa[j])>=mid)
				return 1;
			if(height[j]<mid) break;
		}
	}
	return 0;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	int n;
	while(scanf("%d",&n)!=EOF){
		if(n==0)  break;
		n--;
		for(int i=0;i<=n;i++)  scanf("%d",&s[i]);
		if(n<10) {
			printf("0\n");
			continue;
		}
		for(int i=0;i<n;i++)  s[i]=s[i+1]-s[i]+90;
		s[n]=0;
		init();
		build_sa(n+1);
		calheight(n);
		int first=3,second=n;
		int ans=0;
		while(first<=second){
			int mid=(first+second)/2;
			if(check(mid,n)){
				ans=mid;
				first=mid+1;
			}
			else second=mid-1;
		}
		if(ans<4)
			printf("0\n");
		else
			printf("%d\n",ans+1);
	}
	return 0;
}
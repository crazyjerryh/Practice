/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/08
 * suffix array
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxm 1000010
#define maxn 20100

int s[maxn],sa[maxn],c[maxm],wa[maxn],wb[maxn],r[maxn],rk[maxn],height[maxn];
int n,K;
bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void getsa(int n){
	int *x=wa,*y=wb,m=maxm;
	for(int i=0;i<m;i++)  c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=s[i]]++;
	for(int i=1;i<m;i++)  c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)  sa[--c[x[i]]]=i;
	for(int j=1,p=1;p<n;j=j*2,m=p){
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
	int b=0;
	for(int i=0;i<n;i++){
		if(b>0) b--;
		while(s[i+b]==s[sa[rk[i]-1]+b]) b++;
		height[rk[i]]=b;
	}
}

bool solve(int mid,int n){
	int k=1;
	for(int i=2;i<=n;i++){
		if(height[i]>=mid) {k++; if(k>=K) return true;}
		else  k=1;
	}
	return false;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&K)){
		for(int i=0;i<n;i++)
			scanf("%d",&s[i]);
		s[n]=0;
		getsa(n+1);
 		calheight(n);
 		int l=0,r=maxn;
 		int ans;
 		while(l<=r){
 			int mid=(l+r)>>1;
 			if(solve(mid,n)){
 				ans=mid;
 				l=mid+1;
 			}
 			else
 				r=mid-1;
		}
		printf("%d\n",ans);
	}
}

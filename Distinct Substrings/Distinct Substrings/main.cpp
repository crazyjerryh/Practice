#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn  50010
char str[maxn];
int sa[maxn],rk[maxn],height[maxn],s[maxn];
int wa[maxn],wb[maxn],c[maxn],r[maxn];
int tcase;

void init(){
	memset(wa,0,sizeof(wa));
	memset(wb,0,sizeof(wb));
}

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void buildsa(int n){
	int *x=wa,*y=wb,m=maxn;
	for(int i=0;i<m;i++)  c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=s[i]]++;
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
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	getchar();
	while(tcase--){
		init();
		scanf("%s",&str);
	    int n=strlen(str);
		for(int i=0;i<n;i++)  s[i]=(int)str[i];
		s[n]=0;
		buildsa(n+1);
		calheight(n);
		int ans=0;
		for(int i=1;i<=n;i++)
			 ans+=n-sa[i]-height[i];
		printf("%d\n",ans);
	}
}

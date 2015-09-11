/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/11
 * suffix array
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100
#define maxm 300

char str[maxn];
int wa[maxn],wb[maxn],c[maxm],sa[maxn],rk[maxn],height[maxn],r[maxn];
int dp[maxn][30];
int ans[maxn],start[maxn];

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void buildsa(int n){
	int *x=wa,*y=wb,m=maxm;
	for(int i=0;i<m;i++)  c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=str[i]]++;
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
		while(str[i+k]==str[j+k]) k++;
		height[rk[i]]=k;
	}
}

void rmqinit(int n){
	for(int i=0;i<n;i++) dp[i][0]=height[i];
	for(int i=1;i<20;i++){
		for(int j=0;j<n;j++){
			if(j+(1<<i)-1<=n)
				dp[j][i]=min(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
		}
	}
}

int lcp(int a,int b){
	int l=rk[a],r=rk[b];
	if(r<l)  swap(l,r);
	l++;
	int len=(int)(log((r-l+1)*1.0)/log(2.0));
	return min(dp[l][len],dp[r-(1<<len)+1][len]);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	int tcase=0;
	while(~scanf("%s",str)){
		if(str[0]=='#') break;
		int len=strlen(str);
		str[len]=0;
		buildsa(len+1);
		calheight(len);
		rmqinit(len);
		int n=len;

		int mmax=-1;
		int m;
		int cnt=0;
		for(int l=1;l<=n-1;l++){
			for(int i=0;i+l<n;i+=l){
				int k=lcp(i,i+l);
				m=k/l+1;
				int t=l-k%l;
				t=i-t;
				if(t>=0&&k%l){
					if(lcp(t,t+l)>=k) m++;
				}
				if(mmax<m){
					cnt=0;
					mmax=m;
					ans[cnt++]=l;
				}
				if(mmax==m){
					ans[cnt++]=l;
				}
			}
		}
		bool flag=true;
		int start,l;
		for(int i=1;i<=n;i++){
			for(int j=0;j<cnt;j++){
				int tem=ans[j];
				if(lcp(sa[i],sa[i]+tem)>=(mmax-1)*tem){
					start=sa[i];
					l=mmax*tem;
					flag=false;
					break;
				}
			}
			if(!flag)
				break;
		}
		printf("Case %d: ",++tcase);
		for(int i=0,j=start;i<l;i++,j++)
			printf("%c",str[j]);
		printf("\n");
	}
}

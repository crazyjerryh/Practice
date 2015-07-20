#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>
using namespace std;

#define maxn 250010
char str[maxn];
int sa[maxn*2],rk[maxn*2],height[maxn*2],s[maxn*2];
int wa[maxn*2],wb[maxn*2],r[maxn*2],c[maxn];
int l1,l2;

bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void build_sa(int n){
	int *x=wa,*y=wb,m=300;
	for(int i=0;i<m;i++)  c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=s[i]]++;
	for(int i=1;i<m;i++)  c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)  sa[--c[x[i]]]=i;
	for(int j=1,p=1;p<n;j*=2,m=p){
		p=0;
		for(int i=n-j;i<n;i++) y[p++]=i;
		for(int i=0;i<n;i++)  if(sa[i]>=j) y[p++]=sa[i]-j;
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
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
	for(int i=0,k=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rk[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}
}

bool check(int mid,int n){
	int rans=0,lans=0;
	for(int i=2;i<=n;i++){
		if(height[i]<mid){
			if(sa[i-1]>l1) rans++;
			if(sa[i-1]<l1) lans++;
			if(lans>0&&rans>0) return true;
			lans=rans=0;
			continue;
		}
		//group contain the l1 and l2
		if(sa[i-1]>l1) rans++;
		if(sa[i-1]<l1) lans++;
	}
	return false;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	int n;
	while(scanf("%s",str)!=EOF){
		int len=strlen(str);
		int mmin=len;
		l1=len;
		int i,j;
		for(i=0;i<len;i++)  s[i]=(int)str[i];
		s[i]='$';
		scanf("%s",str);
		len=strlen(str);
		l2=len;
		if(len<mmin)  mmin=len;
		for(j=0;j<len;j++) s[++i]=(int)str[j];
		s[++i]=0;
		n=i;
		build_sa(n+1);
		calheight(n);
		int first=1,second=mmin;
		int ans=0;
		bool flag=false;
		while(first<=second){
			int mid=(first+second)>>1;
			if(check(mid,n)){
				ans=mid;
			    flag=true;
			    first=mid+1;
			}
			else
				second=mid-1;
		}
		if(flag)
		   printf("%d\n",ans);
		else 
		   printf("%d\n",0);
	}
	return 0;
}
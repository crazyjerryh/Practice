#include<iostream>
#include<cstdio>
#include<cstring>
#include <cmath>
using namespace std;
const int nMax = 200001;

int  num[nMax];
int sa[nMax], rank[nMax], height[nMax];
int wa[nMax], wb[nMax], r[nMax], c[nMax];

int cmp(int *r, int a, int b, int l){
	return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int n){
	int *x=wa,*y=wb,m=200;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++)  c[x[i]=num[i]]++;
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
	for(int i=1;i<=n;i++)  rank[sa[i]]=i; 
	for(int k=0,i=0;i<n;i++){
		if(k>0) k--;
		int j=sa[rank[i]-1];
		while(num[i+k]==num[j+k])  k++;
		height[rank[i]]=k;
	}
}

bool check(int mid,int len){
	int i,j;
	// cout<<"mid"<<mid<<endl;
	for(i=2;i<=len;i++){
		if(height[i]<mid)continue;
		for(j=i-1;j>=1;j--){
			//       cout<<i<<' '<<j<<endl;
			if(abs(sa[i]-sa[j])>=mid){
				return 1;
			}
			if(height[j]<mid)break;
		}
	}
	return 0;
}

int main(){
	int n,k,i,j,a,b,sp,ans;
	while(scanf("%d",&n)&&n){
		n--;
		ans=0;
		for(i=0;i<=n;i++){
			scanf("%d",&num[i]);
		}
		if(n<10){
			printf("0\n");
			continue;
		}
		for(i=0;i<n;i++){
			num[i]=num[i+1]-num[i]+90;
		}
		num[n]=0;
		da(n+1);
		calheight(n);
		//        for(i=0;i<=n;i++){
		//            cout<<"h"<<height[i]<<" s"<<sa[i]<<endl;
		//        }
		int left=3,right=n,mid;//开始二分
		while(right>=left){
			mid=(right+left)/2;
			//         cout<<"fuck"<<mid<<endl;
			if(check(mid,n)){         //判断长度为mid的串是否是所有字符串的公共子串
				left=mid+1;
				ans=mid;
			}
			else{
				right=mid-1;
			}
		}
		if(ans<4){
			printf("0\n");
		}
		else{
			printf("%d\n",ans+1);
		}
	}
	return 0;
}
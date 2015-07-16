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

void da(int n){          //  �����㷨 rΪ��ƥ������  nΪ�ܳ��� mΪ�ַ���Χ
	int i, j, p, *x = wa, *y = wb, *t,m=200;
	for(i = 0; i < m; i ++) c[i] = 0;
	for(i = 0; i < n; i ++) c[x[i]=num[i]] ++;
	for(i = 1; i < m; i ++) c[i] += c[i-1];
	for(i = n-1; i >= 0; i --) sa[-- c[x[i]]] = i;
	for(j = 1, p = 1; p < n; j *= 2, m = p){
		for(p = 0, i = n-j; i < n; i ++) y[p ++] = i;
		for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
		for(i=0;i<n;i++)  r[i]=x[y[i]];
		for(i = 0; i < m; i ++) wd[i] = 0;
		for(i = 0; i < n; i ++) wd[r[i]] ++;
		for(i = 1; i < m; i ++) wd[i] += wd[i-1];
		for(i = n-1; i >= 0; i --) sa[-- wd[r[i]]] = y[i];
		for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i ++){
			x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p - 1: p ++;
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
		int left=3,right=n,mid;//��ʼ����
		while(right>=left){
			mid=(right+left)/2;
			//         cout<<"fuck"<<mid<<endl;
			if(check(mid,n)){         //�жϳ���Ϊmid�Ĵ��Ƿ��������ַ����Ĺ����Ӵ�
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
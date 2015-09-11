/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/11
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 200
#define ll long long
vector<ll > ans;

int tcase,n;
ll a[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		ans.clear();
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%ld",&a[i]);
		for(int k=0;k<n;k++){
			ll t=a[k];
			for(ll i=2;i*i<=t;i++){
				while(t%i==0) t=t/i,ans.push_back(i);
			}
			if(t>1) ans.push_back(t);
		}
		if(ans.size()<2) printf("-1\n");
		else{
			sort(ans.begin(),ans.end());
			printf("%I64d\n",1LL*ans[0]*ans[1]);
		}
	}
}

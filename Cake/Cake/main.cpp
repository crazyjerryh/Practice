/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/16
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 400

struct point{
	double x,y;
	point(){}
	point(int _x,int _y):x(_x),y(_y){}
	friend bool operator<(const point &a,const point &b){
		if(a.x!=b.x) return a.x<b.x;
		else return a.y<b.y;
	}
}points[maxn];
point res[maxn];
int n,p;
int c[maxn][maxn],dp[maxn][maxn];

double mult(point a,point b,point o){
	return (a.x-o.x)*(b.y-o.y)>=(a.y-o.y)*(b.x-o.x); 
}

int graham_scan(){
	sort(points,points+n);
	int top = 1;  
	if (n == 0) return 0;  
	res[0] = points[0];  
	if (n == 1) return 0;  
	res[1] = points[1];  
	for (int i = 2; i < n; i++) {  
		while (top && (mult(points[i], res[top], res[top - 1])))  
			top--;  
		res[++top] = points[i];  
	}  
	int len = top;  
	res[++top] = points[n - 2];  
	for (int i = n - 3; i >= 0; i--) {  
		while (top != len && (mult(points[i], res[top], res[top - 1])))  
			top--;  
		res[++top] = points[i];  
	}  
	return top; 
}

int calc(int i, int j) {  
	return (abs((int)res[i].x + (int)res[j].x) * abs((int)res[i].y + (int)res[j].y)) % p;  
}  

int dfs(int l,int r){
	if(dp[l][r]) return dp[l][r];
	if(r-l<=2) return 0;
	int ans=inf;
	for(int i=l+1;i<r;i++){
		ans=min(ans,dfs(l,i)+dfs(i,r)+c[l][i]+c[i][r]);
	}
	return dp[l][r]=ans;
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&p)){
		for(int i=0;i<n;i++) scanf("%lf%lf",&points[i].x,&points[i].y);
		if(n<=3) {
			printf("0\n");
			continue;
		}
		if(graham_scan()<n){
			printf("I can't cut.\n");
			continue;
		}
		memset(dp,0,sizeof(dp));
		//最优三角形剖分
		for(int i=0;i<n;i++) 
			for(int j=i+2;j<n;j++)  
				c[i][j]=c[j][i]=calc(i,j);
		printf("%d\n",dfs(0,n-1));
	}
	return 0;
}

/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/21
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 5

struct line{
	int x1,y1,x2,y2;
}lines[maxn];

int dot(line a,line b){
	int cx,cy;
	cx=a.x1-a.x2;
	cy=a.y1-a.y2;

	int dx,dy;
	dx=b.x1-b.x2;
	dy=b.y1-b.y2;
	
	return cx*dx+cy*dy;
}

int same(line a,line b){
	if(a.x1==b.x1&&a.y1==b.y1) return true;
	if(a.x1==b.x2&&a.y1==b.y2) return true;
	if(a.x2==b.x1&&a.y2==b.y1) return true;
	if(a.x2==b.x2&&a.y2==b.y2) return true;
	
	return false;
}

int tcase;
int solve(){
	std::vector<line> res;
	int vis[4];
	memset(vis,0,sizeof(vis));
	vis[0]=1;
   	for(int i=1;i<4;i++){
		if(!dot(lines[i],lines[0]))
			res.push_back(lines[i]),vis[i]=1;
	}

	if(res.size()==0||res.size()==1||res.size()==3) return 0;
	if(same(lines[0],res[0])&&same(lines[0],res[1])&&!same(res[0],res[1])){
		 int left;
		 for(int i=0;i<4;i++) if(!vis[i]){
			 left=i; 
			 break;
		 }
		 
		 if(!dot(res[0],lines[left])&&!dot(res[1],lines[left])){
			  if(same(lines[left],res[0])&&same(lines[left],res[1])){
				  return 1;
			  }
			  return 0;
		 }
	}
	return 0;
}

int main(void){
	freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		for(int i=0;i<4;i++){
			scanf("%d%d%d%d",&lines[i].x1,&lines[i].y1,&lines[i].x2,&lines[i].y2);
		}
		
		int ans=solve();
		if(ans==1)
			printf("YES\n");
		else printf("NO\n");
	}
}
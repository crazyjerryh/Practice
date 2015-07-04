#include <stdio.h>
#include <algorithm>
#include <memory.h>
using namespace std;
#define maxn 100010

int n,m,k;
int a[maxn],qmax[maxn],qmin[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d%d",&n,&m,&k)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		int l,r;
		int lm,rm,lx,rx;
		lm=rm=lx=rx=0;
		int ans=0;
		for(int i=1,l=1;i<=n;i++){
			r=i;
			while(lm<rm&&a[qmin[rm-1]]<a[i])  rm--;  //qmin:  递减 
			while(lx<rx&&a[qmax[rx-1]]>a[i])  rx--;  //qmax： 递增 
			qmin[rm++]=i;
			qmax[rx++]=i;
			
			int t=a[qmin[lm]]-a[qmax[lx]];
			if((t>=m)&&(t<=k)){
				 ans=max(ans,r-l+1);
			}
			else if(t<m) continue;
			else{
				while(t>k){ //t到最后必定为0，所以不需要加关于队列的限定   
					l=qmin[lm]<qmax[lx]?qmin[lm++]:qmax[lx++];
					l++; 
					t=a[qmin[lm]]-a[qmax[lx]];
				}
			} 
		}
		printf("%d\n",ans);
	}
} 

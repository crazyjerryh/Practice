#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 1050
#define inf 0x3f3f3f3f 

int tree[maxn][maxn]; 
int type;
int n;

void update(int x,int y,int num){
     for(int i=x;i<=n;i=i+(i&-i))
	     for(int j=y;j<=n;j=j+(j&-j))
		       tree[i][j]+=num;	
}

int getsum(int x1,int y1)
{
	 int ans=0;
	 for(int i=x1;i>0;i=i-(i&-i))
	     for(int j=y1;j>0;j=j-(j&-j))
	          ans+=tree[i][j];
	 return ans;
}

int main(){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&type)!=EOF){
		if(type>2)  break;
		if(type==0){
	        scanf("%d",&n);
		    memset(tree,0,sizeof(tree));		
		}
		
		if(type==1){
			int x,y,num;
			scanf("%d%d%d",&x,&y,&num);
			update(x+1,y+1,num);
		}
		
		if(type==2){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int ans=getsum(x1,y1)+getsum(x2+1,y2+1)-getsum(x1,y2+1)-getsum(x2+1,y1);
			printf("%d\n",ans);
		}
	}
	return 0;
}

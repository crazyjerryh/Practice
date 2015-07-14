#include <stdio.h>
#include <string.h>
//#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 110

char str[maxn],ss[maxn];
int vis[maxn];
int n;

int solve(int len){
	memset(vis,0,sizeof(vis));
	while(1){
		int cnt=0,pre,i=1,num=0;
		while(vis[i]&&i<=len) i++;
		if(i>len)  return 0;
		pre=i;
		for(i++;i<=len;i++){
			if(vis[i])  continue;
			if(ss[i]==ss[pre]) {cnt=1,vis[pre]=1,pre=i,num++;}
			else{
				if(num)  vis[pre]=1;
				pre=i,num=0;
			}
		}
		if(num) vis[pre]=1,num=0;
		if(!cnt){
			int ans=0;
			for(int i=1;i<=len;i++)
				if(!vis[i])  ans++;
			return ans;
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&n);
	for(int tt=0;tt<n;tt++){
		scanf("%s",str+1);
		str[0]='#';
		int res=0x3f3f3f;
		int len=strlen(str+1);
		for(int pos=1;pos<=len;pos++){
			for(char tp='A';tp<='C';tp++){
				//if(str[pos-1]==str[pos]&&str[pos]!=tp)  continue;
				for(int i=1,inx=1;i<=len;i++){
					if(pos==inx) 
						ss[inx++]=tp;
					ss[inx++]=str[i];
				}
				int ans=solve(len+1);
				if(ans<res) res=ans;  //找的最小值
				if(res==0)  break;
			}
			
		}
		printf("%d\n",len+1-res);
	}
}

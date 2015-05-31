#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

#define maxn 100010
struct _node
{
	int data;
	int pos;
	_node(int _data,int _pos):data(_data),pos(_pos){}
	_node(){}
}a[maxn],b[maxn];

int res[maxn];
typedef struct _node node; 
int n,m;

int cmp(node a2,node b2)
{
	if(a2.data==b2.data){
		return a2.pos<b2.pos;
	}
	return a2.data<b2.data;
}
int main(void)
{
	while(scanf("%d%d",&n,&m)!=EOF){
		int cnt=0;
		for(int i=0;i<n;i++){
			int tmp;
			scanf("%d",&tmp);
			a[cnt]=_node(tmp,cnt);
			cnt++;
		}

		int ans=0;
		for(int i=0;i<m;i++){
			int tmp;
			scanf("%d",&tmp);
			b[ans]=_node(tmp,ans);
			ans++;
		}

		sort(a,a+cnt,cmp);
		sort(b,b+ans,cmp);

		int i=0,j=0;
		for(;i<n&&j<m;){
			if(a[i].data==b[j].data){
				res[b[j].pos]=a[i].pos;
				i++,j++;
			}
			else
			{
				if(a[i].data<b[j].data){
					while(a[i].data<b[j].data&&i<n)  i++;
				}
				else
				{
					while(a[i].data>b[j].data&&j<m)
					{
						res[b[j].pos]=-2;
						j++;
					}
				}
			}
		}

		while(j<m){
			res[b[j].pos]=-2;
			j++;
		}


		for(int i=0;i<m;i++)
			printf("%d\n",res[i]+1);
	}
	return 0;
}
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 110000

int n,m;
struct _node
{
	int id,data;
	int flag;
	_node(int _id,int _data,int _flag):data(_data),id(_id),flag(_flag){}
	_node(){}
}nodes[maxn];

typedef struct _node node;
int cmp(node a,node b)
{
	if(a.data==b.data)  return a.id<b.id;
	return a.data<b.data;
}

int bSearch(int data)
{
	int pos=-1;
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
	    if(nodes[mid].data<data)  l=mid+1;
		else if(nodes[mid].data>data) r=mid-1;
		else
		{
             if(!nodes[mid].flag) l=mid+1;
			 else
			 {
				 pos=mid;
				 r=mid-1;
			 }
		}
	}
	return pos;
}

int main(void)
{
	while(scanf("%d%d",&n,&m)!=EOF){
	
	for(int i=1;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		nodes[i]=node(i,tmp,1);
	}
	sort(nodes+1,nodes+n+1,cmp);
	for(int i=0;i<m;i++){
		int tmp;
		scanf("%d",&tmp);
		int res=bSearch(tmp);
		if(res!=-1)
			nodes[res].flag=0;
		if(res!=-1)
		  cout<<nodes[res].id<<endl;
		else
		  cout<<-1<<endl;
	}
	}
	return 0;
}
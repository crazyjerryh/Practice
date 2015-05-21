//0代表的是最小堆，1代表的是最大堆
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 30010
int hTree[2][maxn];

int n,m;
int a[maxn],b[maxn];
int cursize[2];
void insert(int data,int size,int _type)
{
	hTree[_type][++size]=data;
    if(_type==0){
		int pa=size/2;
		int tmp=size;
		while(pa>0&&hTree[_type][pa]>hTree[_type][tmp]){  
			swap(hTree[_type][pa],hTree[_type][tmp]);
			tmp=pa;
			pa=pa/2;
		}
	}	
	else
	{
		int pa=size/2;
		int tmp=size;
		while(pa>0&&hTree[_type][pa]<hTree[_type][tmp]){
			swap(hTree[_type][pa],hTree[_type][tmp]);
			tmp=pa;
			pa=pa/2;
		}
	}
}

int del(int _type,int size)
{
	swap(hTree[_type][1],hTree[_type][size]);
	int fa=1;
	int cur=2*fa;
	if(_type==0){
		while(cur<size){
			if(cur+1<size&&hTree[_type][cur+1]<hTree[_type][cur])   cur++;
			if(hTree[_type][cur]>=hTree[_type][fa])  break;
			swap(hTree[_type][cur],hTree[_type][fa]);
			fa=cur;
			cur=2*fa;
		}
	}
	else
	{
		while(cur<size){
			if(cur+1<size&&hTree[_type][cur+1]>hTree[_type][cur])  cur++;
			if(hTree[_type][cur]<=hTree[_type][fa])  break;
			swap(hTree[_type][cur],hTree[_type][fa]);
			fa=cur;
			cur=2*fa;
		}
	}
   return hTree[_type][size];
}


int main(void)
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];

	for(int i=1;i<=m;i++)
		cin>>b[i];
 
	cursize[0]=cursize[1]=0;
	for(int i=1,j=1;i<=n;i++){
		if(cursize[1]>0&&hTree[1][1]>a[i])
		{
		      int ans=del(1,cursize[1]);
			  cursize[1]--;
			  insert(a[i],cursize[1],1);
			  cursize[1]++;
			  insert(ans,cursize[0],0);
			  cursize[0]++;
		}
		else
		{
		      insert(a[i],cursize[0],0);
			  cursize[0]++;
		}
		

		while(i==b[j]){
			  j++;
		      int ans=del(0,cursize[0]);
			  cursize[0]--;
			  cout<<ans<<endl;
			  insert(ans,cursize[1],1);
			  cursize[1]++;
		}
	}
	return 0;
}
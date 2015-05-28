//force
#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 35

int a[maxn];
int tcase;
int n,w;
int cnt;

int cmp(const void *a,const void *b)
{
	int a1=*(int *)a;
	int b1=*(int *)b;

	return a1<b1;
}

void dfs(int dep,int leftweight)
{
	if(dep>n)
	{
		cnt++;
		return;
	}
	if(leftweight>=a[dep]){
		dfs(dep+1,leftweight-a[dep]);
	}
	dfs(dep+1,leftweight);
}

int main(void)
{
	cin>>tcase;
	for(int tt=1;tt<=tcase;tt++)
	{
		cnt=0;
		cin>>n>>w;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		qsort(a+1,n,sizeof(int),cmp);
		dfs(1,w);
		cout<<"Case "<<tt<<": ";
		cout<<cnt<<endl;
	}
	return 0;
}
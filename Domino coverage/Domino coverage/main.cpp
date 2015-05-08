#include <iostream>
#include <memory.h>
using namespace std;

#define LL long long
#define tmod 19999997
typedef struct _matrix{
	LL a[2][2];
}Matrix;

int n;

Matrix matmul(Matrix a,Matrix b)
{
	Matrix res;
	memset(res.a,0,sizeof(res.a));
	for(int i=0;i<2;i++)
		for(int j=0;j<2;j++){
			
			for(int k=0;k<2;k++){
				res.a[i][j]=(res.a[i][j]+(a.a[i][k]*b.a[k][j])%tmod)%tmod;
			}
		}
	return res;
}

Matrix matpow(Matrix a,int m)
{
	Matrix s;
	memset(s.a,0,sizeof(s.a));
	for(int i=0;i<2;i++)
			s.a[i][i]=1;

	while(m)
	{
		if(m&1)
			s=matmul(s,a);
		a=matmul(a,a);
		m=m>>1;  
	}
	
	return s;
}

LL solve()
{
	Matrix s;
	s.a[0][0]=0,s.a[0][1]=1;
	s.a[1][0]=1,s.a[1][1]=1;
	if(n==1)
		return 1;
	else if(n==2)
		return 2;
	
	Matrix res=matpow(s,n-2);
	LL result=(res.a[0][1]+(2*(res.a[1][1]))%tmod)%tmod;
	return result;
}

int main(void)
{
	cin>>n;
	LL result=solve();
	cout<<result<<endl;
	return 0;
}
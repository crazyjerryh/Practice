#include <iostream>
#include <fstream>
#include <cmath>
#include <memory.h>
using namespace std;
#define maxn 60
#define tmod 1000000007
#define size 51  //大写字母和小写字母

int tcase,n;
//ofstream fout("debug.txt");
long long f[maxn][maxn];  //f数组存储的结果为长度为i ，最后字符为j的所有的相邻字符不大于32的个数
long long g[maxn][maxn];  //g数组存储的结果为长度为i，最后字符为j的所有的相邻字符小于32的个数
                   //所以最后的结果为f[i][j]-g[i][j]

typedef struct _matrix{
	long long norm[maxn][maxn];
}Matrix;

Matrix e; //for f
Matrix ee; //for ff

Matrix mul(Matrix a,Matrix b)
{
	//两个矩阵相乘
	Matrix res;
	memset(res.norm,0,sizeof(res.norm));
	for(int i=0;i<=size;++i)
		for(int j=0;j<=size;++j){
		    //计算矩阵每一项的值
			for(int k=0;k<=size;++k){
				res.norm[i][j]=(res.norm[i][j]+(a.norm[i][k]*b.norm[k][j])%tmod)%tmod; //矩阵相加的结果
			}
		}
	return res;
}

Matrix pow(Matrix a,int m)
{
	//矩阵的幂
	Matrix s;
	memset(s.norm,0,sizeof(s.norm));
	for(int i=0;i<=size;i++)
		s.norm[i][i]=1; 

	while(m){
		 if(m&1) 
			s=mul(s,a);
		 a=mul(a,a);
		 m=m>>1;
    }
	
	return s;
}

int main(int argc,char **argv)
{
	cin>>tcase;
	//初始化初始条件

	while(tcase--){
		cin>>n;
		
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int i=0;i<=size;++i)
			f[1][i]=g[1][i]=1;  //设置初始化条件

		for(int i=0;i<=size;++i)
			for(int j=0;j<=size;++j){
				int a,b;
				if(i>=26)
					a=i+32-26;
				else
					a=i;

				if(j>=26)
					b=j+32-26;
				else
					b=j;

				if(abs(a-b)<=32)
					e.norm[i][j]=1;
				else
					e.norm[i][j]=0;

				if(abs(a-b)<32)
					ee.norm[i][j]=1;
				else
					ee.norm[i][j]=0;
			}
		//初始化dp,从长度为1开始初始化
		
		e=pow(e,n-1);
		ee=pow(ee,n-1);
		long long res=0;
		long long ans=0;
		for(int i=0;i<=size;i++)
		{
			for(int j=0;j<=size;j++){
				res=(res+e.norm[j][i])%tmod;
				ans=(ans+ee.norm[j][i])%tmod;
			}
		}				
		cout<<long long((res-ans+tmod)%tmod)<<endl; 		
	}
	return 0;
}
/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/08/06
 * dancing links
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f

#define MaxN 15*15+10
#define MaxM 15*15+10
#define maxnode 300*300
int n,m,ansd,tot;
int mat[20][20];
int idd[20][20];

struct DLX
{
	int n,m,size;
	int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
	int H[MaxN],S[MaxM];
	int ansd;
	void init(int _n,int _m)
	{
		n = _n;
		m = _m;
		for(int i = 0;i <= m;i++)
		{
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i-1;
			R[i] = i+1;
		}
		R[m] = 0; L[0] = m;
		size = m;
		for(int i = 1;i <= n;i++)H[i] = -1;
	}
	void Link(int r,int c)
	{
		++S[Col[++size]=c];
		Row[size] = r;
		D[size] = D[c];
		U[D[c]] = size;
		U[size] = c;
		D[c] = size;
		if(H[r] < 0)H[r] = L[size] = R[size] = size;
		else
		{
			R[size] = R[H[r]];
			L[R[H[r]]] = size;
			L[size] = H[r];
			R[H[r]] = size;
		}
	}
	void remove(int c)
	{
		for(int i = D[c];i != c;i = D[i])
			L[R[i]] = L[i], R[L[i]] = R[i];
	}
	void resume(int c)
	{
		for(int i = U[c];i != c;i = U[i])
			L[R[i]] = R[L[i]] = i;
	}
	bool v[MaxM];
	int f()
	{
		int ret = 0;
		for(int c = R[0]; c != 0;c = R[c])v[c] = true;
		for(int c = R[0]; c != 0;c = R[c])
			if(v[c])
			{
				ret++;
				v[c] = false;
				for(int i = D[c];i != c;i = D[i])
					for(int j = R[i];j != i;j = R[j])
						v[Col[j]] = false;
			}
			return ret;
	}
	void Dance(int d)
	{
		if(d + f() >= ansd)return;
		if(R[0] == 0)
		{
			if(d < ansd)ansd = d;
			return;
		}
		int c = R[0];
		for(int i = R[0];i != 0;i = R[i])
			if(S[i] < S[c])
				c = i;
		for(int i = D[c];i != c;i = D[i])
		{
			remove(i);
			for(int j = R[i];j != i;j = R[j])remove(j);
			Dance(d+1);
			for(int j = L[i];j != i;j = L[j])resume(j);
			resume(i);
		}
	}
};
DLX g;


int main(void){
	freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)==2){
		tot=0;
		memset(idd,0,sizeof(idd));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",&mat[i][j]);
				if(mat[i][j]==1) idd[i][j]=++tot;
			}
			
		}
		g.init(n*m,tot);
		int n1,m1;
		scanf("%d%d",&n1,&m1);
		int sz=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				++sz;
				for(int ii=0;ii<n1&&i+ii<=n;ii++)
					for(int jj=0;jj<m1&&j+jj<=m;jj++){
						if(idd[i+ii][j+jj]>0){
							g.Link(sz,idd[i+ii][j+jj]);
						}
					}
			}
		}
		g.ansd=inf;
		g.Dance(0);
		printf("%d\n",g.ansd);
	}
	return 0;
}
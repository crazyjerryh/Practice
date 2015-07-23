#include<stdio.h>
#include<string.h>
#define MAXD 50010
#define MAXM 100010
int N, M, Q, first[MAXD], e, next[MAXM], v[MAXM];
int fa[MAXD], dep[MAXD], size[MAXD], son[MAXD], top[MAXD], w[MAXD], cnt;
int a[MAXD], add[4 * MAXD], q[MAXD];
void Swap(int &x, int &y)
{
	int t;
	t = x, x = y, y = t;
}
void Add(int x, int y)
{
	v[e] = y;
	next[e] = first[x], first[x] = e ++;
}
void pushdown(int cur)
{
	if(add[cur])
	{
		add[cur << 1] += add[cur], add[cur << 1 | 1] += add[cur];
		add[cur] = 0;
	}
}
void prepare()
{
	int i, j, x, rear = 0;
	q[rear ++] = 1;
	fa[1] = 0, dep[1] = 1;
	for(i = 0; i < rear; i ++)
	{
		x = q[i];
		for(j = first[x]; j != -1; j = next[j])
			if(v[j] != fa[x])
			{
				fa[v[j]] = x, dep[v[j]] = dep[x] + 1;
				q[rear ++] = v[j];
			}
	}
	size[0] = 0;
	for(i = rear - 1; i >= 0; i --)
	{
		x = q[i];
		size[x] = 1, son[x] = 0;
		for(j = first[x]; j != -1; j = next[j])
			if(v[j] != fa[x])
			{
				size[x] += size[v[j]];
				if(size[v[j]] > size[son[x]])
					son[x] = v[j];
			}
	}
	cnt = 0;
	memset(top, 0, sizeof(top));
	for(i = 0; i < rear; i ++)
	{
		x = q[i];
		if(top[x] == 0)
		{
			for(j = x; j != 0; j = son[j])
				top[j] = x, w[j] = ++ cnt;
		}
	}
}
void refresh(int cur, int x, int y, int s, int t, int v)
{
	int mid = (x + y) >> 1, ls = cur << 1, rs = cur << 1 | 1;
	if(x >= s && y <= t)
	{
		add[cur] += v;
		return ;
	}
	pushdown(cur);
	if(mid >= s)
		refresh(ls, x, mid, s, t, v);
	if(mid + 1 <= t)
		refresh(rs, mid + 1, y, s, t, v);
}
void init()
{
	int i, x, y;
	for(i = 1; i <= N; i ++)
		scanf("%d", &a[i]);
	e = 0;
	memset(first, -1, sizeof(first));
	for(i = 0; i < M; i ++)
	{
		scanf("%d%d", &x, &y);
		Add(x, y), Add(y, x);
	}
	prepare();
	memset(add, 0, sizeof(add));
	for(i = 1; i <= N; i ++)
		refresh(1, 1, N, w[i], w[i], a[i]);
}
int Search(int cur, int x, int y, int k)
{
	int mid = (x + y) >> 1, ls = cur << 1, rs = cur << 1 | 1;
	if(x == y)
		return add[cur];
	pushdown(cur);
	if(k <= mid)
		return Search(ls, x, mid, k);
	else
		return Search(rs, mid + 1, y, k);
}
void deal(int x, int y, int z)
{
	int fx = top[x], fy = top[y];
	while(fx != fy)
	{
		if(dep[fx] > dep[fy])
			Swap(fx, fy), Swap(x, y);
		refresh(1, 1, N, w[fy], w[y], z);
		y = fa[fy], fy = top[y];
	}
	if(dep[x] > dep[y])
		Swap(x, y);
	refresh(1, 1, N, w[x], w[y], z);
}
void solve()
{
	int i, x, y, z;
	char op[5];
	for(i = 0; i < Q; i ++)
	{
		scanf("%s%d", op, &x);
		if(op[0] == 'Q')
			printf("%d\n", Search(1, 1, N, w[x]));
		else
		{
			scanf("%d%d", &y, &z);
			if(op[0] == 'I')
				deal(x, y, z);
			else
				deal(x, y, -z);
		}
	}
}
int main()
{
	while(scanf("%d%d%d", &N, &M, &Q) == 3)
	{
		init();
		solve();
	}
	return 0;
}
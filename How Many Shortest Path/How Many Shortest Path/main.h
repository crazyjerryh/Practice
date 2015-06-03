#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;

const int MAXN = 310;
const int MAXM = 100100;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int to, cap, next;
};

Edge edge[MAXM];
int level[MAXN];
int head[MAXN];
int dist[MAXN][MAXN];
int path[MAXN][MAXN];
int src, des, cnt;

void addedge(int from, int to, int cap)
{
	edge[cnt].to = to;
	edge[cnt].cap = cap;
	edge[cnt].next = head[from];
	head[from] = cnt++;

	swap(from, to);

	edge[cnt].to = to;
	edge[cnt].cap = 0;
	edge[cnt].next = head[from];
	head[from] = cnt++;
}

int bfs()
{
	queue<int> q;
	while (!q.empty())
		q.pop();
	memset(level, -1, sizeof level);
	level[src] = 0;
	q.push(src);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].to;

			if (edge[i].cap > 0 && level[v] == -1)
			{
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return level[des] != -1;
}


int dfs(int u, int f)
{
	if (u == des)	return f;

	for (int i = head[u]; i != -1; i = edge[i].next)
	{
		int v = edge[i].to;
		if (edge[i].cap > 0 && level[v] == level[u] + 1)
		{
			int tem = dfs(v, min(f, edge[i].cap));
			if (tem > 0)
			{
				edge[i].cap -= tem;
				edge[i ^ 1].cap += tem;
				return tem;
			}
		}
	}
	level[u] = -1;
	return 0;
}


int Dinic()
{
	int ans = 0, tem;

	while (bfs())
	{
		while (tem = dfs(src, INF))
		{
			ans += tem;
		}
	}
	return ans;
}


int main()
{
	int n, from, to;
	while (cin >> n)
	{

		memset(head, -1, sizeof head);
		cnt = 0;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				scanf( "%d", &path[i][j] );
				dist[i][j] = path[i][j];
				if(dist[i][j]==-1)
					dist[i][j]=INF;
			}
			dist[i][i] = path[i][i] = 0;
		}
		cin >> from >> to;
		from++;
		to++;
		src = from, des = to;
		if (from == to)
		{
			cout << "inf" << endl;
			continue; 
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if ((dist[i][j] > dist[i][k] + dist[k][j] ))
						 dist[i][j] = dist[i][k] + dist[k][j];

		if (dist[from][to] >=INF)
		{
			cout << 0 << endl;
			continue;
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (dist[from][to] == dist[from][i] + path[i][j] + dist[j][to] &&path[i][j]>0)
					addedge(i, j, 1);
			}
		}
		cout<<Dinic()<<endl;;
	}

	return 0;
}
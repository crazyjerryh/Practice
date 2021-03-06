#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 100010
#define MAXL 510
#define MAXM 128
using namespace std;
char str[MAXN];
int size;
bool vis[MAXL], flag;
struct node {
    int pos, fail, next[MAXM];
    void Init() {
        pos = fail = 0;
        memset(next, 0, sizeof(next));
    }
};
node tree[MAXN];
void Insert(char *s, int pos) {
    int now, t;
    for (now = 0; *s; s++) {
        t = *s;
        if (!tree[now].next[t]) {
            tree[++size].Init();
            tree[now].next[t] = size;
        }
        now = tree[now].next[t];
    }
    tree[now].pos = pos;
}
void BFS() {
    int now, i, p;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        now = q.front();
        q.pop();
        for (i = 0; i < MAXM; i++) {
            if (tree[now].next[i]) {
                p = tree[now].next[i];
                if (now)
                    tree[p].fail = tree[tree[now].fail].next[i];
                q.push(p);
            } else
                tree[now].next[i] = tree[tree[now].fail].next[i];
        }
    }
}
void Match(char *s) {
    int now, t, p;
    for (now = 0; *s; s++) {
        t = *s;
        now = tree[now].next[t];
        for (p = now; p; p = tree[p].fail) {
            if (tree[p].pos)
                flag = vis[tree[p].pos] = true;
        }
    }
}
int main() {
    int n, m, i, j, ans;
    while (~scanf("%d", &n)) {
        tree[0].Init();
        for (i = size = 0; i < n; i++) {
            scanf(" %s", str);
            Insert(str, i + 1);
        }
        BFS();
        scanf("%d", &m);
        for (i = ans = 0; i < m; i++) {
            flag = false;
            memset(vis, false, sizeof(vis));
            scanf(" %s", str);
	            Match(str);
	            if (flag) {
                ans++;
                printf("web %d:", i + 1);
                for (j = 1; j <= n; j++) {
                    if (vis[j])
                        printf(" %d", j);
                }
                putchar('\n');
            }
        }
        printf("total: %d\n", ans);
    }
    return 0;
}

#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 2000010
#define MAXM 50000
#define MAXL 128
using namespace std;
char str[MAXN], dic[MAXM][60];
int size, cnt[MAXM];
struct node {
    int pos, fail, next[MAXL];
    void Init() {
        pos = fail = 0;
        memset(next, 0, sizeof(next));
    }
};
node tree[MAXM];
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
        for (i = 'A'; i <= 'Z'; i++) {
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
        for (p = now; p; p = tree[p].fail)
            cnt[tree[p].pos]++;
    }
}
int main() {
    int n, i;
    while (~scanf("%d", &n)) {
        tree[size = 0].Init();
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; i++) {
            scanf(" %s", dic[i]);
            Insert(dic[i], i);
        }
        BFS();
        scanf(" %s", str);
        Match(str);
        for (i = 1; i <= n; i++) {
            if (cnt[i])
                printf("%s: %d\n", dic[i], cnt[i]);
        }
    }
    return 0;
}

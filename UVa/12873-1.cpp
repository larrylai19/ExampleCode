#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define CLR(c) memset(c, 0, sizeof(c))

static auto __ = []
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}();

template <typename T>
T QPOP(queue<T>& q)
{
    T tmp = q.front();
    q.pop();
    return tmp;
}

// reference: https://ppt.cc/fwPNIx

const int INF = (int)1e9;
const int MXN = 530;

int rn[MXN][MXN];
int p[MXN];
bool vis[MXN];

// source: 0, sink: P + S + 1
int P, S, C, m;
int source = 0, sink;

void init()
{
    CLR(rn);
}

void read()
{
    cin >> P >> S >> C >> m;
    sink = P + S + 1;

    int u, v;
    while (m--)
    {
        cin >> u >> v;
        rn[u][P + v] = 1;
    }

    // build edges
    FOR(i, 1, P + 1) rn[source][i] = 1;
    FOR(i, 1, S + 1) rn[i + P][sink] = C;
}

int augment(int u, int v, int bottleNeck)
{
    if (v == source) return bottleNeck;
    bottleNeck = augment(p[u], u, min(rn[u][v], bottleNeck));
    rn[u][v] -= bottleNeck;
    rn[v][u] += bottleNeck;
    return bottleNeck;
}

// Edmonds-Karp
int maxiumFlow()
{
    int mf = 0;

    while (true)
    {
        CLR(vis);

        queue<int> q;
        q.push(source);
        vis[source] = true;

        while (!q.empty() && !vis[sink])
        {
            int u = QPOP(q);

            FOR(v, 0, sink + 1)
            {
                if (vis[v] || !rn[u][v]) continue;

                q.push(v);
                vis[v] = true;
                p[v] = u;
            }
        }

        if (!vis[sink]) break;
        mf += augment(p[sink], sink, INF);
    }

    return mf;
}

void solve()
{
    cout << maxiumFlow() << '\n';
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        init();
        read();
        solve();
    }
}
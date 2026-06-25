/**
 *    author:  Meet
 *    created: 24.01.2026 13:00:20
**/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
// order_of_key(k) : no. of elements < k
// *find_by_order(i) : value at index i (0-based)

#define ll long long int
const ll INF = 4e18;
const ll MINF = -4e18;
const ll M = 1e9 + 7;
//const ll M = 998244353;
const ll M1 = 111053273;
const ll M2 = 4011052531;
#define PI acos(-1)

#define whole(x) (x).begin(), (x).end()

#define yes cout << "YES\n"
#define no cout << "NO\n"
#define minus cout << -1 << "\n"

vector<vector<ll>> adj;
vector<ll> cnt, par, dep;
vector<vector<ll>> dp;

void dfs(ll ver, ll p) {
    par[ver] = p;
    dp[ver][0] = p;
    for(ll i=1; i<22; ++i) {
        if(dp[ver][i-1] != -1) dp[ver][i] = dp[dp[ver][i-1]][i-1];
    }

    for(auto& child : adj[ver]) {
        if(child == p) continue;
        dep[child] = dep[ver] + 1;
        dfs(child, ver);
    }
}

ll jump(ll x, ll k) {
    for(ll i=0; i<22; ++i) {
        if((k >> i) & 1) x = dp[x][i];
    }
    return x;
}

ll lca(ll a, ll b) {
    if(dep[a] < dep[b]) swap(a,b);
    ll k = dep[a] - dep[b];

    a = jump(a, k);

    if(a == b) return a;

    for(ll i=21; i>=0; --i) {
        if(dp[a][i] == dp[b][i]) continue;
        a = dp[a][i];
        b = dp[b][i];
    }

    return dp[a][0];
}

void dfs2(ll ver, ll p) {
    for(auto& child : adj[ver]) {
        if(child == p) continue;
        dfs2(child, ver);
        cnt[ver] += cnt[child];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,m;
    cin >> n >> m;

    adj.assign(n+1, {});
    cnt.assign(n+1, 0);
    dep.assign(n+1, 0);
    par.assign(n+1, -1);
    dp.assign(n+1, vector<ll>(22, -1));

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, -1);

    for(ll i=0; i<m; ++i) {
        ll u,v;
        cin >> u >> v;

        ++cnt[u];
        ++cnt[v];
        
        ll LCA = lca(u, v);
        --cnt[LCA];
        if(par[LCA] != -1) --cnt[par[LCA]];
    }

    dfs2(1, -1);

    for(ll i=1; i<=n; ++i) cout << cnt[i] << " ";
    cout << "\n";
    return 0;
}
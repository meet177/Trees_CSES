/**
 *    author:  Meet
 *    created: 22.01.2026 15:26:23
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
vector<vector<ll>> dp;
vector<ll> dep;

void bfs(ll src) {
    queue<ll> q;
    q.push(src);
    dep[src] = 0;

    while(!q.empty()) {
        ll ver = q.front(); q.pop();
        for(auto& child : adj[ver]) {
            if(dep[child] == -1) {
                dep[child] = dep[ver] + 1;
                q.push(child);
            }
        }
    }
}

ll jump(ll x, ll k) {
    for(ll i=0; i<22; ++i) {
        if((k >> i) & 1) {
            x = dp[x][i];
        }
    }
    return x;
}

ll lca(ll a, ll b) {
    if(dep[a] < dep[b]) swap(a, b);

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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    adj.assign(n+1, {});
    dp.assign(n+1, vector<ll>(22, -1));
    dep.assign(n+1, -1);

    for(ll i=2; i<=n; ++i) {
        cin >> dp[i][0];
        adj[i].push_back(dp[i][0]);
        adj[dp[i][0]].push_back(i);
    }

    for(ll i=1; i<22; ++i) {
        for(ll j=2; j<=n; ++j) {
            if(dp[j][i-1] != -1) dp[j][i] = dp[dp[j][i-1]][i-1];
        }
    }

    bfs(1);

    while(q--) {
        ll a,b;
        cin >> a >> b;

        cout << lca(a, b) << "\n";
    }
    return 0;
}
/**
 *    author:  Meet
 *    created: 22.01.2026 15:48:09
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

void dfs(ll ver, ll par) {
    dp[ver][0] = par;
    for(ll i=1; i<22; ++i) {
        if(dp[ver][i-1] != -1) dp[ver][i] = dp[dp[ver][i-1]][i-1];
    }

    for(auto& child : adj[ver]) {
        if(child == par) continue;
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

ll mini(ll a, ll b) {
    ll ans = 0;

    if(dep[a] < dep[b]) swap(a, b);

    ll pda = dep[a], pdb = dep[b];
    ll k = dep[a] - dep[b];
    a = jump(a, k);
    ans += (pda - dep[a]);

    if(a == b) return ans;

    for(ll i=21; i>=0; --i) {
        if(dp[a][i] == dp[b][i]) continue;
        a = dp[a][i];
        b = dp[b][i];
        ans += (1LL << i);
    }

    ++ans;
    a = dp[a][0];
    ans += (pdb - dep[a]);

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    adj.assign(n+1, {});
    dep.assign(n+1, -1);
    dp.assign(n+1, vector<ll>(22, -1));

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs(1);

    ll mx = max_element(whole(dep)) - dep.begin();

    for(ll i=1; i<=n; ++i) dep[i] = -1;
    dep[mx] = 0;
    dfs(mx, -1);

    while(q--) {
        ll a,b;
        cin >> a >> b;

        cout << mini(a, b) << "\n";
    }
    return 0;
}
/**
 *    author:  Meet
 *    created: 21.01.2026 19:22:46
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n;
    cin >> n;

    adj.assign(n+1, {});

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs = [&] (ll ver) -> vector<ll> {
        vector<ll> dep(n+1, -1);

        queue<ll> q;
        q.push(ver);
        dep[ver] = 0;

        while(!q.empty()) {
            ll ver = q.front(); q.pop();

            for(auto& child : adj[ver]) {
                if(dep[child] == -1) {
                    dep[child] = dep[ver] + 1;
                    q.push(child);
                }
            }
        }

        return dep;
    };

    auto dp1 = bfs(1);

    ll ep1 = max_element(whole(dp1)) - dp1.begin();
    dp1 = bfs(ep1);

    ll ep2 = max_element(whole(dp1)) - dp1.begin();
    auto dp2 = bfs(ep2);

    for(ll i=1; i<=n; ++i) {
        cout << max(dp1[i], dp2[i]) << " ";
    }

    cout << "\n";

    return 0;
}
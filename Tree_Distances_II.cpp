/**
 *    author:  Meet
 *    created: 21.01.2026 19:31:56
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

ll n;
vector<vector<ll>> adj;
vector<ll> dp, childs;
vector<ll> ans;

void dfs1(ll ver, ll par) {
    for(auto& child : adj[ver]) {
        if(child == par) continue;
        dfs1(child, ver);
        dp[ver] += (dp[child] + childs[child]);
        childs[ver] += childs[child];
    }
}

void dfs2(ll ver, ll par) {
    for(auto& child : adj[ver]) {
        if(child == par) continue;
        //childs of child will be closer by 1 unit than parent so minus it from parent and all other childs will be farther by 1 unit than parent so plus it from parent
        ans[child] = ans[ver] - (childs[child]) + (n - childs[child]);
        dfs2(child, ver);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    cin >> n;

    adj.assign(n+1, {});
    dp.assign(n+1, 0);
    childs.assign(n+1, 1);
    ans.assign(n+1, 0);

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //we compute from 1 so after dfs 1's whole sum will be computed 
    dfs1(1, 0);

    ans[1] = dp[1];
    //now we will calculate for each children by using their parent
    dfs2(1, 0);

    for(ll i=1; i<=n; ++i) cout << ans[i] << " ";

    cout << "\n";

    return 0;
}
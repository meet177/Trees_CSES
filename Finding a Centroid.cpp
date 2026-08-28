/**
 *    author:  Meet
 *    created: 28.08.2026 00:23:50
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
const ll M = 1e9 + 7;
//const ll M = 998244353;
#define PI acos(-1)

#define whole(x) (x).begin(), (x).end()

#define yes cout << "YES\n"
#define no cout << "NO\n"

void dfs(ll ver, ll par, vector<vector<ll>>& adj, vector<ll>& sz) {
    sz[ver] = 1;
    for(ll child : adj[ver]) {
        if(child == par) continue;
        dfs(child, ver, adj, sz);
        sz[ver] += sz[child];
    }
}

ll findCentroid(ll ver, ll par, ll n, vector<vector<ll>>& adj, vector<ll>& sz) {
    for(ll child : adj[ver]) {
        if(child == par) continue;
        //if sz[child] > n/2 then it has centroid inside it
        //at most one child can have > n/2 
        if(2*sz[child] > n) return findCentroid(child, ver, n, adj, sz);
    }
    //no child is having more than n/2 and we came to the ver from the condition sz[ver] > n/2 so the component which is not part of subtrees will also have <= n/2 itself so this is the centroid itself
    return ver;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n;
    cin >> n;

    vector<vector<ll>> adj(n+1);
    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> sz(n+1, 0);
    dfs(1, 0, adj, sz);

    cout << findCentroid(1, 0, n, adj, sz) << "\n";
    return 0;
}
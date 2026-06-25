/**
 *    author:  Meet
 *    created: 21.01.2026 17:18:19
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
vector<array<ll,2>> dp;
//dp[ver][0] is the max we can get from subtree of ver if ver is not matched 
//dp[ver][1] is the max we can get from subtree of ver if ver is matched with exactly one of its child

void dfs(ll ver, ll par) {
    for(auto& child : adj[ver]) {
        if(child == par) continue;
        dfs(child, ver);
        //if ver is not matched then we can match every child of it or not match so we take max over all children
        dp[ver][0] += max(dp[child][0], dp[child][1]);
    }

    for(auto& child : adj[ver]) {
        if(child == par) continue;

        //if we want to make a pair with any one of the child then we need to select that child, all other will contribute the same as it doesn't impact them, so possibility is max over all of the children
        ll cand = dp[ver][0] - max(dp[child][0], dp[child][1]) + dp[child][0] + 1;

        dp[ver][1] = max(dp[ver][1], cand);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n;
    cin >> n;

    adj.assign(n+1, {});
    dp.assign(n+1, {0,0});

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    cout << max(dp[1][0], dp[1][1]) << "\n";
    return 0;
}
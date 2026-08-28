/**
 *    author:  Meet
 *    created: 22.08.2026 15:27:41
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

set<ll>* dfs(ll ver, ll par, vector<ll>& color, vector<vector<ll>>& adj, vector<ll>& dist) {
    set<ll>* dsver = new set<ll>();
    dsver->insert(color[ver]);

    for(ll child : adj[ver]) {
        if(child == par) continue;

        set<ll>* dschild = dfs(child, ver, color, adj, dist);

        if(dschild->size() > dsver->size()) {
            swap(dsver, dschild);
        }

        for(ll info : *dschild) {
            dsver->insert(info);
        }

        delete dschild;
    }

    dist[ver] = dsver->size();
    return dsver;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n;
    cin >> n;

    //so we can store information about every node and then merge information of node based on their children's info 
    //we can represent information using some data structures and then for merging we use small to large merging which guarantees that each individual element moves at most O(logn) times 
    //why O(logn) because whenever one element moves the set containing it becomes at least twice as before due to small to large rule
    //so after k movements size should be at least 2^k
    //now the total elements are n itself so 2^k <= n
    //which is k <= log2(n) 
    //k is the movements so this is the proof of why each individual moves at most logn times and we are not actually storing any set we are working with pointers and avoiding copying larger parts into smaller parts which can be more overhead
    //after merging the bigger one is basically the info we still need and smaller one we can throw away so it is memory efficient and time efficient both

    vector<ll> color(n+1);
    for(ll i=1; i<=n; ++i) cin >> color[i];

    vector<vector<ll>> adj(n+1);
    for(ll i=1; i<=n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> dist(n+1, 0);
    set<ll>* rootSet = dfs(1, -1, color, adj, dist);

    delete rootSet;

    for(ll i=1; i<=n; ++i) cout << dist[i] << " ";
    cout << "\n";
    return 0;
}
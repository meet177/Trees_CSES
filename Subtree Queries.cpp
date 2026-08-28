/**
 *    author:  Meet
 *    created: 22.08.2026 00:27:37
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

class Fenwick {
    vector<ll> bit;
    ll n;
    public :
    Fenwick(ll n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(ll i, ll val) {
        for(; i<=n; i += (i & (-i))) {
            bit[i] += val;
        }
    }

    ll query(ll i) {
        ll ans = 0;
        for(; i>0; i -= (i & (-i))) {
            ans += bit[i];
        }
        return ans;
    }
};  

ll timer;

void dfs(ll ver, ll par, vector<ll>& val, vector<vector<ll>>& adj, vector<ll>& st, vector<ll>& en) {
    st[ver] = ++timer;

    for(ll child : adj[ver]) {
        if(child == par) continue;
        dfs(child, ver, val, adj, st, en);
    }

    en[ver] = timer;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n, q;
    cin >> n >> q;

    vector<ll> val(n+1);
    for(ll i=1; i<=n; ++i) cin >> val[i];

    vector<vector<ll>> adj(n+1);

    for(ll i=1; i<=n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //for subtrees we basically go with euler time and create an array of st and en time of the vertex into dfs after that index [st[i],en[i]] will denote the subtree of vertex i

    timer = 0;
    vector<ll> st(n+1, -1), en(n+1, -1);

    dfs(1, -1, val, adj, st, en);

    Fenwick ft(n);

    for(ll i=1; i<=n; ++i) ft.update(st[i], val[i]);

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll s,x;
            cin >> s >> x;
            ft.update(st[s], x - val[s]);
            val[s] = x;
        }else {
            ll s;
            cin >> s;

            ll ans = ft.query(en[s]) - ft.query(st[s] - 1);
            cout << ans << "\n";
        }
    }
    return 0;
}
/**
 *    author:  Meet
 *    created: 22.08.2026 13:37:39
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
    vector<ll> bit; //bit[i] holds the info for [i - lowbit(i) + 1, i]
    ll n;

    public :
    Fenwick(ll _n) {
        n = _n;
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

void dfs(ll ver, ll par, vector<ll>& val, vector<vector<ll>>& adj, vector<ll>& st, vector<ll>& en, vector<ll>& pf) {
    st[ver] = ++timer;
    pf[st[ver]] = pf[st[par]] + val[ver];

    for(ll child : adj[ver]) {
        if(child == par) continue;
        dfs(child, ver, val, adj, st, en, pf);
    }

    en[ver] = timer;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> val(n + 1, 0);
    for(ll i=1; i<=n; ++i) cin >> val[i];

    vector<vector<ll>> adj(n+1);
    for(ll i=1; i<=n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    timer = 0;
    vector<ll> st(n+1), en(n+1), pf(n+1);

    dfs(1, 0, val, adj, st, en, pf);

    // for(ll i=1; i<=n; ++i) cout << st[i] << " " << en[i] << " " << pf[i] << "\n";


    //so we are keeping the pf[ver] at the position the vertex is starting its subtree in the traversal array
    //now the question essentially became that range update and then find the find the value at some index which can be done using difference array method which we have learnt in range queries that just change values of end points and for finding value we just need to do query(i) it will give sum of that
    Fenwick ft(n);
    for(ll i=1; i<=n; ++i) ft.update(i, pf[i] - pf[i-1]);

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll s,x;
            cin >> s >> x;

            ll delta = x - val[s];
            ft.update(st[s], delta);
            if(en[s] < n) ft.update(en[s] + 1, -delta);
            val[s] = x;
        }else {
            ll s;
            cin >> s;
            cout << ft.query(st[s]) << "\n";
        }
    }
    return 0;
}
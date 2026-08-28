/**
 *    author:  Meet
 *    created: 28.08.2026 16:42:42
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
    void init(ll _n) {
        n = _n;
        bit.assign(n+1, 0);
    }

    void update(ll i, ll val) {
        for(; i<=n; i += (i & (-i))) {
            bit[i] += val;
        }
    }

    ll query(ll l, ll r) {
        ll ans = 0;
        for(ll i=r; i>0; i -= (i & (-i))) 
            ans += bit[i];

        for(ll i=l-1; i>0; i -= (i & (-i))) 
            ans -= bit[i];
        
        return ans;
    }
};

ll n,k1,k2,ans;
vector<vector<ll>> adj;
vector<ll> sz, dists, used, cnt;
vector<bool> dead;

Fenwick ft; //global fenwick tree

void calcSizes(ll ver, ll par) {
    sz[ver] = 1;
    for(ll child : adj[ver]) {
        if(child == par || dead[child]) continue;
        calcSizes(child, ver);
        sz[ver] += sz[child]; 
    }
}

ll findCentroid(ll ver, ll par, ll total_sz) {
    for(ll child : adj[ver]) {
        if(child == par || dead[child]) continue;
        if(2*sz[child] > total_sz) return findCentroid(child, ver, total_sz);
    }

    return ver;
}

void calcDistances(ll ver, ll par, ll dist) {
    if(dist > k2) return; //at most k2 is needed
    dists.push_back(dist);

    for(ll child : adj[ver]) {
        if(child == par || dead[child]) continue;
        //allow same distance multiple times 
        calcDistances(child, ver, dist + 1);
    }
}

void processCentroid(ll c) {
    used.clear();

    cnt[0] = 1;
    used.push_back(0); //distance 0 is used
    ft.update(1, 1); //i need 1 based indexing (distance of centroid is 0)

    for(ll child : adj[c]) {
        if(dead[child]) continue;

        //for each subtree we need different dists (otherwise it will overlap)
        dists.clear();
        //calculate distances for this child and then first query and then include
        calcDistances(child, c, 1); //child is at distance 1 from centroid

        //now first query
        for(ll d : dists) {
            ll l = max(0LL, k1 - d);
            ll r = k2 - d;
            ans += ft.query(l + 1, r + 1);
        }

        //then include it
        for(ll d : dists) {
            if(cnt[d] == 0) used.push_back(d);
            ft.update(d + 1, 1); //1 based indexing
            ++cnt[d];
        }
    }

    for(ll d : used) {
        ft.update(d + 1, -cnt[d]); //undo the ops for this centroid
        cnt[d] = 0;
    }

}

void dfs(ll ver, ll par) {
    //find centroid of subtree rooted at ver
    //for centroid two things (calcSizes and findCentroid)
    calcSizes(ver, par);
    ll c = findCentroid(ver, par, sz[ver]);

    //process the centroid
    processCentroid(c);

    //now remove the centroid and process all the subtrees of centroid recursively 
    dead[c] = true;
    for(ll child : adj[c]) {
        if(dead[child]) continue;
        dfs(child, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n >> k1 >> k2;
    adj.assign(n+1, {});
    sz.assign(n+1, 0);
    dead.assign(n+1, false);
    
    cnt.assign(k2+1, 0);
    ft.init(k2+1); //initialization of fenwick tree (global)

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ans = 0;
    dfs(1, 0);

    cout << ans << "\n";
    return 0;
}
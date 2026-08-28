/**
 *    author:  Meet
 *    created: 28.08.2026 16:00:09
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

ll n,k,ans;
vector<vector<ll>> adj;
vector<ll> sz, distances, cnt, used;
vector<bool> dead;

void calcSizes(ll ver, ll par) {
    sz[ver] = 1; //make this assignment so that we don't have to reset it for each of the centroid pass (if we do ++ we have to reset each time)
    //assignment take care of resetting things now all the other values in sz will not be used just as simple as it is they are there but we will not use it and which we want we are calculating it now
    for(ll child : adj[ver]) {
        //we don't want to see the dead nodes they are already processed
        if(child == par || dead[child]) continue;
        calcSizes(child, ver);
        sz[ver] += sz[child];
    }
}

ll findCentroid(ll ver, ll par, ll total_size) {
    for(ll child : adj[ver]) {
        if(child == par || dead[child]) continue;
        if(2*sz[child] > total_size) return findCentroid(child, ver, total_size);
    }

    return ver;
}

void calcDistances(ll ver, ll par, ll dist) {
    if(dist > k) return; //more than k i don't need
    distances.push_back(dist);

    for(ll child : adj[ver]) {
        if(child == par || dead[child]) continue;
        //the same dist can be pushed multiple times
        calcDistances(child, ver, dist + 1);
    }
}

void processCentroid(ll c) {
    //this stores the cnt of nodes which are at dist d 
    cnt[0] = 1; //centroid is at distance 0
    used.push_back(0); //the distances are used in this decompositions are stored in this

    //go into each of the child of centroid and we first query and then increase the count this way we are ensuring that we don't count in the same subtree which will not pass through centroid
    for(ll child : adj[c]) {
        if(dead[child]) continue;

        //for each subtree we calculate different distances array and then first query and then include
        distances.clear();
        calcDistances(child, c, 1); //child is at distance 1 from c

        for(ll d : distances) {
            ans += cnt[k - d]; //d here and (k - d) in some other subtree of centroid total k that is what we wanted
        }

        for(ll d : distances) {
            if(cnt[d] == 0) used.push_back(d); //not already there then push it into used
            ++cnt[d]; //include the current distances into cnt
        }
    }

    //clear the distances which are used for this centroid
    for(ll d : used) cnt[d] = 0;
    used.clear();
}

void dfs(ll ver, ll par) {
    //i am processing the subtree of ver

    //first find centroid of the particular subtree
    //calculating centroid needs basically two things one dfs pass for calculating sizes of subtrees and another for finding centroid
    calcSizes(ver, par);
    //now we are just considering the subtree of ver not whole tree so total nodes in subtree is basically sz[ver] as calculated above 
    ll c = findCentroid(ver, par, sz[ver]);

    //now we have the centroid of subtree of ver
    //now we will process all the paths which go through the centroid and having dist as k which is dist(c, u) + dist(c, v) = k

    processCentroid(c);

    //now all the paths which pass through the centroid is processed now we want the paths which don't pass through centroid so they must lie on the same subtree of centroid
    //so we can process them recursively all the subtrees with making the centroid as dead so that we don't process it again

    dead[c] = true;

    for(ll child : adj[c]) {
        if(dead[child]) continue;
        dfs(child, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    cin >> n >> k;
    adj.assign(n+1, {});
    dead.assign(n+1, false);
    sz.assign(n+1, 0);
    cnt.assign(k+1, 0);

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
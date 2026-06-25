/**
 *    author:  Meet
 *    created: 22.01.2026 14:59:04
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

vector<vector<ll>> dp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    dp.assign(n+1, vector<ll>(22,INF));

    for(ll i=2; i<=n; ++i) {
        cin >> dp[i][0];
    }

    for(ll i=1; i<22; ++i) {
        for(ll j=2; j<=n; ++j) {
            if(dp[j][i-1] != INF) dp[j][i] = dp[dp[j][i-1]][i-1];
        }
    }

    for(ll i=1; i<=n; ++i) {
        for(ll j=0; j<22; ++j) {
            if(dp[i][j] == INF) dp[i][j] = -1;
        }
    }

    while(q--) {
        ll x,k;
        cin >> x >> k;

        for(ll i=0; i<22; ++i) {
            if(x == -1) break;
            if((k >> i) & 1) {
                x = dp[x][i];
            }
        }

        cout << x << "\n";
    }

    return 0;
}
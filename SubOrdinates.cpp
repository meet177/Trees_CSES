#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pb push_back
#define mp make_pair
#define vll vector<ll>
#define vb vector<bool>
#define vvll vector<vector<ll>>
#define vvb vector<vector<bool>>
#define vs vector<string>
#define vp vector<pair<ll,ll>>
#define pll pair<ll,ll>

#define f(i,a,b) for(ll i=a; i<b; ++i)
#define fr(i,a,b) for(ll i=a-1; i>=b; --i)
#define fa(v) for(auto& it : v)
#define ff first
#define ss second
#define whole(x) (x).begin(), (x).end()

#define yes cout << "Yes\n"
#define no cout << "No\n"
#define out1(x) cout << (x) << "\n"
#define out2(x,y) cout << (x) << " " << (y) << "\n"
#define out3(x,y,z) cout << (x) << " " << (y) << " " << (z) << "\n"

#define inarr(x) f(i,0,n) cin >> x[i];
#define outarr(x) f(i,0,n) cout << x[i] << " "; cout << "\n";

const ll M = 1e9 + 7;

void setupIO() {
    ios_base::sync_with_stdio(false); //disables the sync between ios and stdio
    cin.tie(0); //untie cin and cout
    cout.tie(0); //optional
}
const ll N = 2e5 + 1;
vll graph[N];
vll childs(N);

void dfs(ll vertex, ll par=-1) {
    for(auto& child : graph[vertex]) {
        if(child == par) continue;
        dfs(child,vertex);
        childs[vertex] += childs[child] + 1;
    }
}

int main() {
    setupIO();
    ll n;
    cin >> n;
    f(i,2,n+1) {
        ll v;
        cin >> v;
        graph[i].push_back(v);
        graph[v].push_back(i);
    }
    dfs(1);
    f(i,1,n+1) cout << childs[i] << " "; cout << "\n";
    return 0;
}
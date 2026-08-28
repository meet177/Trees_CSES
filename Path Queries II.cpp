/**
 *    author:  Meet
 *    created: 27.08.2026 19:19:02
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

class SegTree {
    vector<ll> seg;
    ll n;

    //when only point update and range query are needed then consider iterative sometimes here for cses we need iterative (recursive will give TLE)
public:
    void init(vector<ll>& arr) {
        this->n = arr.size();

        //for iterative we need only 2*n
        seg.assign(2*n, 0);

        //leaf nodes are from [n...2*n]
        for(ll i=n; i<2*n; ++i) seg[i] = arr[i - n];

        //all upper nodes are representing some segment 
        //just same relation as used in recursive segment tree
        for(ll i=n-1; i>=1; --i) seg[i] = max(seg[2*i], seg[2*i + 1]);
    }

    void update(ll pos, ll val) {
        pos += n; //now this is the position where leaf of pos is in seg
        seg[pos] = val; //the leaf is updated 
        //now update all the parents
        for(ll id=pos>>1; id>=1; id >>= 1) {
            seg[id] = max(seg[2*id], seg[2*id + 1]);
        }
    }

    ll query(ll l, ll r) {
        //go to leafs of both l and r
        l += n;
        r += n;

        ll ans = 0;

        //fix the unsafe boundaries first then move upward
        while(l <= r) {
            //now 2*id is left child so left child are always even and 2*id + 1 is right child so right child are always odd

            //if l is right child
            //now after every move we go to the upper level means parent level 
            //if l is a right child then it's immediate parent is containing info about left child also which is not part of my query range so i just take l and move 
            if(l & 1) {
                ans = max(ans, seg[l]);
                ++l;
            }

            //if r is left child
            //if r is a left child then it's immediate parent is containing info about right child also which is not part of my query range so i just take r and move
            if(!(r & 1)) {  
                ans = max(ans, seg[r]);
                --r;
            }

            //now we are at safe boundaries of l and r so just move one level up (parent)
            l >>= 1;
            r >>= 1;
        }

        //so the basic flow is take boundary nodes and go levelwise upward
        return ans;
    }
};

class HLD {
    ll timer, n;
    vector<ll> parent, depth, subsize, heavy; //from dfs
    vector<ll> head, pos; //from decompose
    vector<ll> baseArray; //from buildBaseArray (mapping nodes to its positions in chains)

    SegTree st;//HLD has a segment Tree (it is composition relationship)

    void dfs(ll ver, ll par, vector<vector<ll>>& adj) {
        parent[ver] = par;
        depth[ver] = depth[par] + 1;
        subsize[ver] = 1;

        ll mxSize = 0;
        //find the heaviest subtree size of the ver and mark it as heavy of ver
        ll heavyNode = 0;
        for(ll child : adj[ver]) {
            if(child == par) continue;
            
            dfs(child, ver, adj);

            if(subsize[child] > mxSize) {
                mxSize = subsize[child];
                heavyNode = child;
            }

            subsize[ver] += subsize[child];
        }

        heavy[ver] = heavyNode;
    }

    //breaking down whole tree into chains which can be represented by some contagious range and we can query on them
    void decompose(ll ver, ll h, vector<vector<ll>>& adj) {
        head[ver] = h;
        pos[ver] = timer++;

        //for heavy the chain is continuing so head would be same as ver
        if(heavy[ver] != 0) {
            decompose(heavy[ver], h, adj);
        }

        //for light there is a different chain as heavy is already filled so they will be making a different chain starting at themselves
        for(ll child : adj[ver]) {
            if(child == parent[ver] || child == heavy[ver]) continue;
            //all light's will make different chains
            decompose(child, child, adj);
        }
    }

    void buildBaseArray(vector<ll>& value) {
        //position of each node are [0...n-1] but nodes are 1...n
        //mapping of nodes to its pos based on chains
        for(ll node=1; node<=n; ++node) {
            baseArray[pos[node]] = value[node];
        }
    }

    public :
    HLD(ll n, vector<ll>& value, vector<vector<ll>>& adj) {
        this->n = n;
        timer = 0;
        parent.assign(n+1, 0);
        depth.assign(n+1, 0);
        subsize.assign(n+1, 0);
        heavy.assign(n+1, 0);
        head.assign(n+1, 0);
        pos.assign(n+1, 0);
        baseArray.assign(n, 0);

        dfs(1, 0, adj);
        decompose(1, 1, adj);
        buildBaseArray(value);

        st.init(baseArray); //build the segment Tree on baseArray as it is the one which is having the continuous ranges
    }

    void update(ll node, ll val) {
        st.update(pos[node], val); //in baseArray node is at pos[node] so update it
    }

    ll queryPath(ll u, ll v) {
        //they are in different chains
        ll ans = 0;
        while(head[u] != head[v]) {
            if(depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }
            //now u is in the deeper chain so move it upwards
            ll h = head[u];
            //we came from head to u so pos[h] <= pos[u] (here we need [l,r])
            ans = max(ans, st.query(pos[h], pos[u]));

            u = parent[h]; //this chain is processed now move to the next chain
        }

        //now head[u] == head[v] so they are in the same chain just process a single query 
        ll l = min(pos[u], pos[v]);
        ll r = max(pos[u], pos[v]);
        ans = max(ans, st.query(l, r));

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    ll n,q;
    cin >> n >> q;

    vector<ll> value(n+1, 0);
    for(ll i=1; i<=n; ++i) cin >> value[i];

    vector<vector<ll>> adj(n+1);

    for(ll i=0; i<n-1; ++i) {
        ll u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD hld(n, value, adj);

    while(q--) {
        ll tp;
        cin >> tp;
        if(tp == 1) {
            ll s,x;
            cin >> s >> x;
            hld.update(s, x);
        }else {
            ll u,v;
            cin >> u >> v;
            cout << hld.queryPath(u, v) << " ";
        }
    }

    cout << "\n";
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct centroid {
    vector<vector<ll>>adj;
    vector<bool>vis;
    vector<ll>par;
    vector<ll>sz;
    vector<ll>depth;
    ll l, timer;
    vector<ll> tin, tout;
    vector<vector<ll>> up;
    ll n;

    void init(ll s){
        n = s;
        adj = vector<vector<ll> >(n, vector<ll>());
        vis = vector<bool>(n,0);
        par = vector<ll>(n);
        sz = vector<ll>(n);
    }

    ll find_size(ll v, ll p = -1){
        if(vis[v]){return 0;}
        sz[v] = 1;

        for(ll x:adj[v]){
            if(x!=p){
                sz[v] += find_size(x,v);
            }
        }
        return sz[v];
    }
    
    ll find_centroid(ll v, ll p, ll n){
        for(ll x:adj[v]){
            if(x!=p){
                if(!vis[x] && sz[x] > n/2){
                    return find_centroid(x,v,n);
                }
            }
        }
        return v;
    }

    void init_centroid(ll v =0, ll p = -1){
        find_size(v);
        
        ll c = find_centroid(v,p,sz[v]);
        vis[c] = true;
        par[c] = p;

        for(ll x:adj[c]){
            if(!vis[x]){
                init_centroid(x,c);
            }
        }
    }
    void dfs(int v, int p)
    {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];

        for (int u : adj[v]) {
            if (u != p){
                depth[u] = depth[v]+1;
                dfs(u, v);
            }
        }

        tout[v] = ++timer;
    }

    bool is_ancestor(int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    void preprocess(int root) {
        tin.resize(n);
        tout.resize(n);
        depth.resize(n,0);
        timer = 0;
        l = ceil(log2(n));
        up.assign(n, vector<ll>(l + 1));
        dfs(root, root);
    }
    ll dist(ll u, ll v){
        ll x = lca(u,v);
        return depth[u]+depth[v]-2*depth[x];
    }
};
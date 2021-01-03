/* Kruskal Algorithm */

#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
#define N 998244353
#define ll long long
#define REP(i,a,b) for(ll i=a;i<b;i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vll vector<long long>
#define INF 1000000000
vector<tuple<ll, ll, ll> > edge;
vector<ll>parent(3001), siz(3001);
void make_set(ll i){
    parent[i] = i;
    siz[i] = 0;
}
ll find(ll v){
    if(v == parent[v]){return v;}
    return find(parent[v]);
}
void unite(ll a, ll b){
    a = find(a);
    b = find(b);
    if(a != b){
        if(siz[a] < siz[b]){
            swap(a, b);}
        parent[b] = a;
        if(siz[a] == siz[b]){
            siz[a]++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ll n, m;
    cin>>n>>m;
    REP(i, 0, m){
        ll x, y, z;
        cin>>x>>y>>z;
        edge.pb({z, x, y});
    }
    ll cost=0;
    REP(i, 0, n+1){
        make_set(i);
    }
    sort(edge.begin(), edge.end());
    for(auto x:edge){
        if(find(get<1>(x)) != find(get<2>(x))){
            cost += get<0>(x);
            unite(get<1>(x), get<2>(x));
        }
    }
    cout<<cost;
}

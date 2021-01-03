#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define M 1000000007
#define M2 998244353
#define ll long long
#define pll pair<long,long>
#define REP(i,a,b) for(ll i=a;i<b;i++)
#define REPI(i,a,b) for(ll i=b-1;i>=a;i--)
#define ff first
#define ss second
#define pb push_back
#define db pop_back
#define mp make_pair
#define mt make_tuple
#define g(a,b) get<a>(b)
#define INF (ll)1e18+5
#define ull unsigned long long
 
#define o_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define o_setll tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : iterator to k-th element in the set
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
 //for multiset purpose, same functions as above.
ll modI(ll a, ll m);
ll gcd(ll a, ll b);
ll powM(ll x, ll y, ll m);
void pairsort(int a[], int b[], int n);
void pairsortll(ll a[],ll b[],ll n);
ll logint(ll x,ll y);
 
 
ll gcd(ll x,ll y)
{
    if(x==0) return y;
    return gcd(y%x,x);
}
 
ll powM(ll x,ll y,ll m)
{
    if(y==0) return 1;
    ll p=powM(x,y/2,m)%m;
    p=(p*p)%m;
    return (y%2==0)?p:(x*p)%m;
}
 
ll modI(ll a, ll m)
{
   return powM(a, m-2, m);
}
 
void pairsort(int a[],int b[],int n)
{
    pair<int,int> v[n];
    REP(i,0,n)
    {
        v[i].ff=a[i];
        v[i].ss=b[i];
    }
    sort(v,v+n);
    REP(i,0,n)
    {
        a[i]=v[i].ff;
        b[i]=v[i].ss;
    }
}
 
void pairsortll(ll a[],ll b[],ll n)
{
    pair<ll,ll> v[n];
    REP(i,0,n)
    {
        v[i].ff=a[i];
        v[i].ss=b[i];
    }
    sort(v,v+n);
    REP(i,0,n)
    {
        a[i]=v[i].ff;
        b[i]=v[i].ss;
    }
}
 
ll logint(ll x,ll y)
{
    ll ans=0;
    ll a=1;
    for(ll i=0;i<=x;i++)
    {
        if(x<a)
        {
            return ans;
        }
        ans++;
        a*=y;
    }
    return -1;
}
//const int N = 1e5+5;
/*ll parent[N];
ll siz[N];
void make(){
    REP(i, 0, N){
        parent[i]=i;
        siz[i] = 1;
    }
}
ll find(ll x){
    while(parent[x] != x){
        x = parent[x];
    }
    return x;
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
} */
int n, m;
const int N = 2e5+5;
ll x[N];
struct node{
    ll sum=0;
    ll pref=0;
    ll suff=0;
    ll ans=0;
};
node seg[4*N+1];
node combine(node l, node r){
    node ret;
    ret.sum = l.sum+r.sum;
    ret.pref = max(l.pref, l.sum+r.pref);
    ret.suff=max(r.suff, r.sum+l.suff);
    ret.ans = max(max(l.ans,r.ans), l.suff+r.pref);
    return ret;
}
void build(ll l, ll r, ll v){
    if(l == r){
        seg[v].sum=x[l];
        seg[v].pref=seg[v].suff=seg[v].ans=max(0LL, x[l]);
        return;
    }
    ll mid = (l+r)/2;
    build(l, mid, 2*v);
    build(mid+1, r, 2*v+1);
    seg[v] = combine(seg[2*v], seg[2*v+1]);
}

void update(ll l, ll r, ll v, ll pos, ll val){
    if(l > r){
        return;
    }
    if(l == r){
         seg[v].sum=val;
        seg[v].pref=seg[v].suff=seg[v].ans=max(0LL, val);
        return;
        //cout<<seg[v].pref<<" "<<seg[v].ans<<" "<<seg[v].suff<<"\n";
        //return;
    }
    ll mid = (l+r)/2;
    if(pos <= mid){
        update(l, mid, 2*v, pos, val);
    }
    else{
        update(mid+1, r, 2*v+1, pos, val);
    }
    seg[v] = combine(seg[2*v], seg[2*v+1]);
    //cout<<seg[v].pref<<" "<<seg[v].ans<<" "<<seg[v].suff<<"\n";
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    /* 
    Hey, 
    You, 
    Dont practice this, 
    Easy Question. 
    */
    cin>>n>>m;
    REP(i, 1, n+1){
        cin>>x[i];
    }
    build(1, n, 1);
    while(m--){
        ll x, y;
        cin>>x>>y;
        update(1, n, 1, x, y);
        cout<<seg[1].ans<<"\n";
    }
}
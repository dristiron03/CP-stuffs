#pragma GCC optimize("O3")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
using base = complex<double>;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define M 1000000007
#define M2 998244353
#define ll long long
#define pll pair<long, long>
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define ff first
#define ss second
#define pb push_back
#define db pop_back
#define mp make_pair
#define mt make_tuple
#define g(a, b) get<a>(b)
#define INF (ll)3e18 + 100
#define vl vector<ll>
#define vi vector<int>
#define vll vector<pair<ll, ll>>
#define vii vector<pair<int, int>>
#define all(v) v.begin(), v.end()
#define bset(a, p) ((a) | (1ll << (p)))
#define bchk(a, p) ((a) & (1ll << (p)))
#define bxor(a, p) ((a) ^ (1ll << (p)));
#define brem(a, p) (bchk(a, p) ? (bxor(a, p)) : (a))
#define INT_SIZE 32
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl

#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
ll powM(ll x, ll y, ll m)
{
    ll ans = 1, r = 1;
    x %= m;
    while (r > 0 && r <= y)
    {
        if (r & y)
        {
            ans *= x;
            ans %= m;
        }
        r <<= 1;
        x *= x;
        x %= m;
    }
    return ans;
}
ll modI(ll a, ll m)
{
    ll m0 = m, y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1)
    {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

ll logint(ll x, ll y)
{
    ll ans = 0;
    ll a = 1;
    for (ll i = 0; i <= x; i++)
    {
        if (x < a)
        {
            return ans;
        }
        ans++;
        a *= y;
    }
    return -1;
}
ll extended(ll a, ll b, ll &x, ll &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = extended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
struct tower{
    ll t;
    ll x;
    ll a;
    ll index;
};

// pair<int,int>dp[(1<<20)+5];
const int N = 2e5+5;
vector<ll>v[N];
pair<pair<ll,ll>,pair<ll,ll>>vv[N];
// ll ans = 0;
ll dfs(ll x, ll p){
    pair<pair<ll,ll>,pair<ll,ll>>maxi = {{0,-1},{0,-1}};
    for(auto y:v[x]){
        if(y == p){
            continue;
        }
        ll cc = dfs(y,x);
        if(cc+1 > maxi.ff.ff){
            maxi.ss = maxi.ff;
            maxi.ff.ff = cc+1;
            maxi.ff.ss = y;

        }
        else if(cc+1 > maxi.ss.ff){
            maxi.ss.ff = cc+1;
            maxi.ss.ss = y;
        }
    }
    // ans = max({ans,maxi.ff+maxi.ss});
    vv[x] = maxi;
    return maxi.ff.ff;
}
vl ans(N,0);
void dfs2(ll x, ll p){
    // ll ans = 0;
    for(auto y:v[x]){
       if( y == p){
          if(vv[y].ff.ss != x && vv[y].ff.ff+1 > vv[x].ff.ff){
            vv[x].ss = vv[x].ff;
            vv[x].ff.ff = vv[y].ff.ff+1;
            vv[x].ff.ss = y;

        }
        else if(vv[y].ff.ss != x && vv[y].ff.ff+1 > vv[x].ss.ff){
            vv[x].ss.ff = vv[y].ff.ff+1;
            vv[x].ss.ss = y;
        }
        else if(vv[y].ss.ss != x && vv[y].ss.ff+1 > vv[x].ff.ff){
            vv[x].ss = vv[x].ff;
            vv[x].ff.ff = vv[y].ss.ff+1;
            vv[x].ff.ss = y;
        } 
        else if(vv[y].ss.ss != x && vv[y].ss.ff+1 > vv[x].ss.ff){
            vv[x].ss.ff = vv[y].ss.ff+1;
            vv[x].ss.ss = y;
        }
       }
    }
    for(auto y:v[x]){
        if(y!=p){
            dfs2(y,x);
        }
    }
    ans[x] = vv[x].ff.ff;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll ntc;
    // cin >> ntc;
    ntc = 1;
    REP(tc, 1, ntc + 1)
    {
        // cout << "Case #" << tc << ": ";
        ll n;
        cin>>n;
        REP(i,0,n-1){
            ll x,y;
            cin>>x>>y;
            v[x].pb(y);
            v[y].pb(x);
        }
        dfs(1,-1);
        dfs2(1,-1);
        REP(i,1,n+1){
            cout<<ans[i]<<" ";
        }
    }
}

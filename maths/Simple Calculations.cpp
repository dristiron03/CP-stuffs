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
#define INF (ll)1e18 + 100
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
 
#define o_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setpll tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
ll powM(ll x, ll y, ll m)
{
	if (x == 0) {
		return 1;
	}
	ll ans = 1, r = 1;
	x %= m;
	while (r > 0 && r <= y) {
		if (r & y) {
			ans *= x;
			ans %= m;
		}
		r <<= 1;
		x *= x;
		x %= m;
	}
	return ans;
}
void setIO(string name = "") { // name is nonempty for USACO file I/O
    // alternatively, cin.tie(0)->sync_with_stdio(0);
    if (name.size()) {
        freopen((name+".in").c_str(), "r", stdin); // see Input & Output
        freopen((name+".out").c_str(), "w", stdout);
    }
}
const int N = 1e6+5;
ll phi[N];
ll res[N];
void phi_1_to_n(int n) {
    // vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
ll last[N];
void solve(){
    ll n, m;
	cin>>n>>m;
	memset(last,-1,sizeof(last));
	ll ans=0;
	ll ttl = 0;
	ll curr=1;
	ll cyc_l, off; 
	while(1){
		if(last[curr] >= 0){
			cyc_l = ttl-last[curr];
			off = last[curr];
			break;
		}
		last[curr] = ttl;
		curr *= 2;
		curr %= m;
		ttl++;
	}
	if(m == 2){
		cout<<1; return;
	}
	ans = 1;
	if(n <= 30){
		ll d = 1;
		REP(i,0,n){
			d *= 2;
		}
		cout<<(powM(2,d,m)+1)%m;
		return;
	}
	else{
		ans = powM(2,n,cyc_l);
		ans -= off;
		if(ans < 0){
			ans += cyc_l;
		}
		ans = (powM(2,ans,m)%m);
		ans %= m;
		ans *= ((1LL<<off)%m);
		ans %= m;
		cout<<(ans+1)%m; return;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
// #ifndef ONLINE_JUDGE
	setIO("calc");
// #endif
	ll ntc;
    // cin >> ntc;
    ntc = 1;
    REP(tc, 1, ntc + 1)
    {
        // cout << "Case " << tc << ": ";
        solve();
    }
}
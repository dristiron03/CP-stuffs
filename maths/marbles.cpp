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
ll modI(ll a, ll m)
{
	ll m0 = m, y = 0, x = 1;
	if (m == 1)
		return 0;
	while (a > 1) {
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
ll extended(ll a, ll b, ll &x, ll &y)
{
	if (a == 0) {
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
namespace CRT{
	inline ll normalize(ll mod, ll x){
		x %= mod;
		if(x < 0){
			x+=mod;
		}
		return x;
	}
	ll solve(vector<pair<ll,ll>>v){ // v[0] = {divisor, remainder}
		ll n = v.size();
		for(ll i=0; i< n;i++){
			normalize(v[i].first, v[i].second);
		}
		ll ans = v[0].second;
		ll lcm1 = v[0].first;
		for(ll i=1; i<n;i++){
			ll x, y;
			ll g = extended(lcm1,v[i].first, x, y);
			if((v[i].second-ans)%g != 0){
				return -1;
			}
			ans = normalize((lcm1 / g) * v[i].first, ans + ((((v[i].second - ans) / g) * x) % (v[i].first / g)) * lcm1);
			lcm1 = (lcm1/g)*v[i].first; // lcm1 = lcm(lcm1, v[i].first)
		}
		return ans;
	}
}
namespace Diophantine{
    ll Egcd(ll a, ll b, ll &x, ll &y)
    {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        ll x1, y1;
        ll d = Egcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }
    bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
        g = Egcd(abs(a), abs(b), x0, y0);
        if (c % g) {
            return false;
        }
        x0 *= c / g;
        y0 *= c / g;
        if (a < 0) x0 = -x0;
        if (b < 0) y0 = -y0;
        return true;
    }
    /*
    Generating all possible solution for the diophantine equation
    X will be of the form X = x0+k*(b/g), where g = gcd(a,b)
    Y will be of the form Y = y0-k*(a/g), where g = gcd(a,b)
    */
    // ---------------------------------------------------------------------
    void shift_solution(ll & x, ll & y, ll a, ll b, ll cnt) {
        x += cnt * b;
        y -= cnt * a;
    }
    ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
		if(a==0){
			if(b == 0){
				if(c==0){
					return (maxx-minx+1)*(maxy-miny+1);
				}
				else{
					return 0;
				}
			}
			else{
				if(c%b){
					return 0;
				}
				else{
					if(c/b <= maxy && c/b >= miny){
						return (maxx-minx+1);
					}
					else{
						return 0;
					}
				}
			}
		}
		else{
			if(b==0){
				if(c%a){
					return 0;
				}
				else{
					if(c/a <= maxx && c/a >= minx){
						return (maxy-miny+1);
					}
					else{
						return 0;
					}
				}
			}
		}
        ll x, y, g;
        if (!find_any_solution(a, b, c, x, y, g))
            return 0;
        a /= g;
        b /= g;

        ll sign_a = a > 0 ? +1 : -1;
        ll sign_b = b > 0 ? +1 : -1;

        shift_solution(x, y, a, b, (minx - x) / b);
        if (x < minx)
            shift_solution(x, y, a, b, sign_b);
        if (x > maxx)
            return 0;
        ll lx1 = x;

        shift_solution(x, y, a, b, (maxx - x) / b);
        if (x > maxx)
            shift_solution(x, y, a, b, -sign_b);
        ll rx1 = x;

        shift_solution(x, y, a, b, -(miny - y) / a);
        if (y < miny)
            shift_solution(x, y, a, b, -sign_a);
        if (y > maxy)
            return 0;
        ll lx2 = x;

        shift_solution(x, y, a, b, -(maxy - y) / a);
        if (y > maxy)
            shift_solution(x, y, a, b, sign_a);
        ll rx2 = x;

        if (lx2 > rx2)
            swap(lx2, rx2);
        ll lx = max(lx1, lx2);
        ll rx = min(rx1, rx2);

		return lx;
        /*
        lx holds the smallest value of x possible
        rx holds the largest value of x possible
        */
        if (lx > rx)
            return 0;
        return (rx - lx) / abs(b) + 1; // returns number of possible solution satisfying constraints.
    }
}
ll lcm(ll x, ll y) {
	ll gc = __gcd(x, y);
	x /= gc;
	if ((ll)(8e18) / y <= x) {
		return 8e18;
	}
	return (x * y);
}
ll power(ll x, ll y){
	if(y < 0){
		return 0;
	}
	ll ans = 1;
	REP(i,1,y+1){
		ans *= x;
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
void solve(){
    ll n;
	while(cin>>n){
		if(!n)return;
		ll c1, c2,n1,n2;
		cin>>c1>>n1>>c2>>n2;
		ll x,y,g;
		if(Diophantine::find_any_solution(n1,n2,n,x,y, g)){
			ll ans = c1*x+c2*y;
			ll temp = c1*n2-c2*n1;
			temp /= g;
			ll k;
			ll t1 = (ll)floor((double)(y*g)/(double)(n1)); 
			ll t2 = (ll)ceil(-(double)(x*g)/(double)(n2));
			if(t1 < t2){
				cout<<"failed\n"; continue;
			}
			if(temp < 0){
				k = t1;
			}
			else{
				k = t2;
			}
			cout<<x+k*(n2/g)<<" "<<y-k*(n1/g)<<"\n"; continue;
		}
		else{
			cout<<"failed\n"; continue;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#ifndef ONLINE_JUDGE
	setIO("hello");
#endif
	ll ntc;
    // cin >> ntc;
    ntc = 1;
    REP(tc, 1, ntc + 1)
    {
        // cout << "Case " << tc << ": ";
        solve();
    }
}
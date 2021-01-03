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
 
#define o_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
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
	if(x >= m){
		x = x%m;
	}
	while (r > 0 && r <= y) {
		if (r & y) {
			ans *= x;
			if(ans >= m){
				ans = ans%m;
			}

		}
		r <<= 1;
		x *= x;
		if(x >= m){
			x = x%m;
		}
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

struct ADT{
    // write required attributes
    ll mn;

    //Default values
    ADT() : mn((ll)(0)) {};
};

struct SegTree{
    ll N;
    vector<ADT>st; // segment tree

    void init(ll n){
        N = n;
        st.resize(4*N+5);
    }

    // Write required merge function
    void merge(ADT &curr, ADT &l, ADT &r){
        curr.mn = l.mn+r.mn;
    }
    void build(ll node, ll L, ll R){
        if(L==R){
            st[node].mn = 0;
            return;
        }
        ll mid = (L+R)/2;
        build(2*node, L,mid);
        build(2*node+1,mid+1,R);
        merge(st[node], st[2*node], st[2*node+1]);
    }

    ADT Query(ll node, ll L, ll R, ll i, ll j){
        if(j < L || i > R){
            return ADT();
        }
        if(i <= L && j >= R){
            return st[node];
        }
        ll mid = (L+R)/2;
        ADT left = Query(2*node,L,mid,i,j);
        ADT right = Query(2*node+1, mid+1,R, i,j);
        ADT curr;
        merge(curr, left, right);
        return curr;
    }
    void pUpdate(ll node, ll L, ll R, ll pos, ll val)
	{
		if(L == R)
		{
            st[node].mn = val;
			return;
		}
		ll mid = (L + R)/2;
		if(pos <= mid)
			pUpdate(node*2, L, mid, pos, val);
		else
			pUpdate(node*2 + 1, mid + 1, R, pos, val);
		merge(st[node], st[node*2], st[node*2 + 1]);
	}

	ADT query(ll l, ll r)
	{
		return Query(1, 1, N, l, r);
	}

	void update(ll pos, ll val)
	{
		pUpdate(1, 1, N, pos, val);
	}
};
struct point{
    ll x1,x2,y1,y2;
};
bool cmp(point &a, point &b){
    if(a.x1 < b.x1){
        return true;
    }
    else if(a.x1 == b.x1){
        return (a.x2>b.x2);
    }
    else{
        return false;
    }
}
void solve(){
	ll n;
    cin>>n;
    vector<point>v(n);
    set<ll>sx,sy;
    REP(i,0,n){
        cin>>v[i].x1>>v[i].y1>>v[i].x2>>v[i].y2;
        sx.insert(v[i].x1);
        sx.insert(v[i].x2);
        sy.insert(v[i].y1);
        sy.insert(v[i].y2);
    }
    map<ll,ll>mx,my;
    ll curr = 1;
    for(auto y:sx){
        mx[y] = curr++;
    }
    curr = 1;
    for(auto y:sy){
        my[y] = curr++;
    }
    REP(i,0,n){
        v[i].x1 = mx[v[i].x1];
        v[i].x2 = mx[v[i].x2];
        v[i].y1 = my[v[i].y1];
        v[i].y2 = my[v[i].y2];
    }
    sort(all(v), cmp);
    set<pair<ll,ll>>q;
    SegTree s;
    s.init(curr);
    s.build(1,1,curr);
    ll ans = 0;
    REP(i,0,n){
        while(!q.empty() && (*q.begin()).ff < v[i].x1){
            s.update((*q.begin()).ss,0);
            q.erase(q.begin());
        }
        if(v[i].x1 == v[i].x2){
            ans += s.query(v[i].y1, v[i].y2).mn;
        }
        else{
            s.update(v[i].y1,1);
            q.insert({v[i].x2,v[i].y1});
        }
    }
    cout<<ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll ntc;
    ntc = 1;
    REP(tc, 1, ntc + 1)
    {
        // cout << "Case " << tc << ": ";
        solve();
    }
	// cout<<"kela\n";
}
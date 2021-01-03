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

#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setpll tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, tree_order_statistics_node_update>
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set
const int N = 22;
ll dp[1 << N];
void solve() {
	ll n;
	cin >> n;
	memset(dp, -1, sizeof(dp));
	vl v(n);
	vl comp(n);
	REP(i, 0, n) {
		cin >> v[i];
		REP(j, 0, N) {
			if (!((1LL << j)&v[i])) {
				comp[i] += (1LL << j);
			}
		}
		dp[v[i]] = v[i];
	}
	REP(i, 0, (1LL << N)) {
		REP(j, 0, N) {
			if (i & (1LL << j)) {
				if (dp[i ^ (1LL << j)] > 0) {
					dp[i] = dp[i ^ (1LL << j)];
					break;
				}
			}
		}
	}
	REP(i, 0, n) {
		cout << dp[comp[i]] << " ";
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen ("input.txt" , "r" , stdin);
	freopen ("output.txt" , "w" , stdout);
#endif
	ll ntc;
	// cin >> ntc;
	ntc = 1;
	REP(tc, 1, ntc + 1)
	{
		// cout << "Case #" << tc << ": ";
		solve();
	}
}
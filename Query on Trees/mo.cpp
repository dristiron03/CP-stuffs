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
const int N = 30005;
ll ar[N];
struct node {
    ll l, r, index;
};
struct node query[200005];
const int NN = (int)sqrt(N) + 1;
bool cmp(node a, node b) {
    if (a.l / NN != b.l / NN) {
        return a.l < b.l;
    }
    return a.r < b.r;
}
ll ans[200005];
ll answer = 0;
ll cnt[1000005];
void add(ll index) {
    cnt[ar[index]]++;
    if (cnt[ar[index]] == 1) {
        answer++;
    }
}
void sub(ll index) {
    cnt[ar[index]]--;
    if (cnt[ar[index]] == 0) {
        answer--;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    /* Problem - DNUM */

    ll ntc;
    // cin >> ntc;
    ntc = 1;
    REP(tc, 1, ntc + 1)
    {
        // cout << "Case #" << tc << ": ";
        ll n;
        cin >> n;
        ll q;
        cin >> q;
        REP(i, 1, n + 1) {
            cin >> ar[i];
        }
        REP(i, 0, q) {
            cin >> query[i].l >> query[i].r;
            query[i].index = i;
        }
        sort(query, query + q, cmp);
        int curr_l = 0, curr_r = 0;
        REP(i, 0, q) {
            ll left = query[i].l, right = query[i].r;
            while (left < curr_l) {
                add(curr_l - 1);
                curr_l--;
            }
            while (left > curr_l) {
                sub(curr_l);
                curr_l++;
            }
            while (right > curr_r) {
                add(curr_r + 1);
                curr_r++;
            }
            while (curr_r > right) {
                sub(curr_r);
                curr_r--;
            }
            ans[query[i].index] = answer;
        }
        REP(i, 0, q) {
            cout << ans[i] << "\n";
        }
    }
}
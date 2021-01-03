#include<bits/stdc++.h>
using namespace std;
#define ll long long
// ll crt(vector<pair<ll,ll>> &v){
// 	ll ans = 0;
// 	ll n=v.size();
// 	ll m = 1;
// 	for(ll i=0;i<n;i++){
// 		m *= v[i].first;
// 	}
// 	for(ll i=0; i<n;i++){
// 		ll t = 1;
// 		for(ll j=0; j<i; j++){
// 			t *= v[j].first;
// 			t%=m;
// 			t *= (modI(v[j].first,v[i].first))%m;
// 			t%=m;
// 		}
// 		ans += (t*(v[i].second+m-ans))%m;
// 		ans %= m;
// 	}
// 	return ans;
// }
// ll crt(vector<pair<ll,ll>>&v)
// {
// 	ll p, i, prod = 1, sum = 0;
// 	ll len = v.size();
// 	for (i = 0; i < len; i++) prod *= v[i].first;
 
// 	for (i = 0; i < len; i++) {
// 		p = prod / v[i].first;
// 		sum += v[i].second * modI(p, v[i].first) * p;
// 	}
// 	return sum%prod;
// }
namespace CRT{
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
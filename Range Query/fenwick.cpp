#define ll long long
const int N = 2e5+5;
ll ftree[N];
ll sum (ll k){
    ll s=0;
    while(k >= 1){
        s += ftree[k];
        k -= k&-k;
    }
    return s;
}

void add(ll k, ll x){
    while(k <= N){
        ftree[k] += x;
        k += k&-k;
    }
}

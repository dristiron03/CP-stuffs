ll solve(string s)
{
    ll n = s.size();
    vector<ll> d1(n);
    ll sum1 = 0, sum2=0;
    for (ll i = 0, l = 0, r = -1; i < n; i++)
    {
        ll k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
        sum1+=d1[i];
    }
    vector<ll> d2(n);
    for (ll i = 0, l = 0, r = -1; i < n; i++)
    {
        ll k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        d2[i] = k--;
        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k;
        }
        sum2+=d2[i];
    }
    return abs(sum1-sum2);
}
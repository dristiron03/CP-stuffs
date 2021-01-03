ll seg[4 * (int)1e5 + 1];
ll n;
ll ar[100001];
ll lazy[4 * (int)1e5 + 1];
void push(ll v) {
	seg[v] = max(lazy[v], seg[v]);
	lazy[2 * v] = max(lazy[2 * v], lazy[v]);
	lazy[2 * v + 1] = max(lazy[2 * v + 1], lazy[v]);
	lazy[v] = 0;
}
void build(ll node, ll start, ll end)
{
	if (start == end)
	{
		seg[node] = ar[start];
	}
	else
	{
		ll mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
	}
}

void update(ll node, ll start, ll end, ll l, ll r, ll val)
{

	if (r < start || end < l)
	{
		return;
	}
	if (l <= start && end <= r)
	{
		lazy[node] = max(lazy[node], val);
		return;
	}
	push(node);
	ll mid = (start + end) / 2;
	update(2 * node, start, mid, l, r, val);
	update(2 * node + 1, mid + 1, end, l, r, val);
}
ll query(ll node, ll start, ll end, ll idx)
{
	if (start == end)
	{
		seg[node] = max(seg[node], lazy[node]);
		lazy[node] = 0;
		return seg[node];
	}
	push(node);
	ll mid = (start + end) / 2;
	if (start <= idx && idx <= mid)
	{
		return query(2 * node, start, mid, idx);
	}
	else
	{
		return query(2 * node + 1, mid + 1, end, idx);
	}
}

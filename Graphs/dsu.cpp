#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 5;
ll parent[N];
ll siz[N];
void make() {
    for(ll i=0; i< N; i++) {
        parent[i] = i;
        siz[i] = 1;
    }
}

// Path compression
int find(int x) {
    while (parent[x] != x) {
        x = parent[x];
    }
    return x;
}

// Union by rank/size
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (siz[a] < siz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (siz[a] == siz[b]) {
            siz[a]++;
        }
    }
}
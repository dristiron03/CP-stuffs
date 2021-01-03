#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5+5;
const int LG = log2(N)+1;

int n, clk = 0;
int parent[LG][N], level[N], subtree[N];
vector<int>adj[N];

void dfs(int u, int par, int lvl){
    parent[0][u] = par;
    level[u] = lvl;
    subtree[u] = 1;
    for(auto &it:adj[u]){
        if(it!=par){
            dfs(it,u,lvl+1);
            subtree[u] += subtree[it];
        }
    }
}

ll lft[N];
ll rgt[N];
void dfs_order(int u, int par){
    clk++;
    lft[u] = clk;

    for(int &y:adj[u]){
        if(y != par){
            dfs_order(y,u);
        }
    }
    rgt[u] = clk;
}

int color[N];
int index_in_chain[N];
vector<int>chains[N];
void dfs_hld(int u, int par){
    int best = -1;
    for(int &y: adj[u]){
        if(y!=par){
            if(best < 0 || subtree[y] > subtree[best]){
                best = y;
            }
        }
    }
    if(best < 0)return;
    color[best] = color[u];
    index_in_chain[best] = index_in_chain[u]+1;
    chains[color[u]].push_back(best);

    dfs_hld(best,u);

    for(int &y:adj[u]){
        if(y!= par && y != best){
            color[y] = y;
            index_in_chain[y]=1;
            chains[y].push_back(y);
            dfs_hld(y,u);
        }
    }
}
/* Important */
vector<tuple<int,int,int>> segments(int x, int y){
    vector<tuple<int,int,int>>xseg = {};
    vector<tuple<int,int,int>>yseg = {};

    while(true){
        if(color[x] == color[y]){
            xseg.push_back({color[x], index_in_chain[x], index_in_chain[y]});
            break;
        }

        if(level[color[x]] < level[color[y]]){
            yseg.push_back({color[y], 1,index_in_chain[y]});
            yseg.push_back({-1,parent[0][color[y]], color[y]});
            y = parent[0][color[y]];
        }
        else{
            xseg.push_back({color[x], index_in_chain[x],1});
            xseg.push_back({-1,color[x],parent[0][color[x]]});
            x = parent[0][color[x]];
        }
    }
    reverse(yseg.begin(), yseg.end());
    for(auto z:yseg)xseg.push_back(z);
    return xseg;
}

int main(){
    cin>>n;
    dfs(1,1,0);
    dfs_order(1,1);
    color[1] = 1;
    index_in_chain[1] = 1;
    chains[1].push_back(1);

    //compute HLD

    dfs_hld(1,1);
}
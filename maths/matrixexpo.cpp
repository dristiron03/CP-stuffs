#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll mod = (ll)1e9+7; // define you mod value here
struct matrix
{
    vector <vector <ll> >m;
};
void msi(matrix &m,ll a,ll b)
{
    m.m.resize(a);
    for(ll i=0; i< a; i++){
       m.m[i].resize(b);
    }
}
void minit(matrix &m,ll x)
{
    for(ll i=0; i< (ll)m.m.size(); i++)
       for(ll j=0; j < (ll)m.m[0].size(); j++)
           {m.m[i][j]=x;}
}
matrix mul(matrix m1,matrix m2)
{
    matrix m3;
    msi(m3,m1.m.size(),m2.m[0].size());
    for(ll i=0; i < (ll)m3.m.size(); i++)
      {
          for(ll j=0; j < (ll)m3.m[0].size(); j++)
          {    m3.m[i][j]=0;
               for(ll k=0; k< (ll)m1.m[0].size(); k++)
                 m3.m[i][j]=(m3.m[i][j]+m1.m[i][k]*m2.m[k][j])%mod;
          }
      }
      return m3;
}
matrix mexp(matrix &mx,ll p)
{
   matrix res;
   msi(res,mx.m.size(),mx.m.size());
   minit(res,0);
   for(ll i=0; i< (ll)mx.m.size(); i++)
      res.m[i][i]=1;
   while(p>0)
   {
     if(p&1)
       res=mul(res,mx);
     mx=mul(mx,mx);
     p=p>>1;
   }
   return res;
}
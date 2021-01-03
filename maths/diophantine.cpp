#include<bits/stdc++.h>
#define ll long long
using namespace std;
/*
Given, ax+by=c
To get a solution, use Egcd(Extendend Euclidean Algo)
Let be ax_g+by_g = d, where gcd(a,b) = d, we can get {x_g,y_g} from Egcd
To generate a solution, 
x0 = x_g*(c/g)
y0 = y_g*(c/g)
*/
namespace Diophantine{
    ll Egcd(ll a, ll b, ll &x, ll &y)
    {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        ll x1, y1;
        ll d = Egcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }
    bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
        g = Egcd(abs(a), abs(b), x0, y0);
        if (c % g) {
            return false;
        }
        x0 *= c / g;
        y0 *= c / g;
        if (a < 0) x0 = -x0;
        if (b < 0) y0 = -y0;
        return true;
    }
    /*
    Generating all possible solution for the diophantine equation
    X will be of the form X = x0+k*(b/g), where g = gcd(a,b)
    Y will be of the form Y = y0-k*(a/g), where g = gcd(a,b)
    */
    // ---------------------------------------------------------------------
    void shift_solution(ll & x, ll & y, ll a, ll b, ll cnt) {
        x += cnt * b;
        y -= cnt * a;
    }
    ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
        if(a==0){
			if(b == 0){
				if(c==0){
					return (maxx-minx+1)*(maxy-miny+1);
				}
				else{
					return 0;
				}
			}
			else{
				if(c%b){
					return 0;
				}
				else{
					if(c/b <= maxy && c/b >= miny){
						return (maxx-minx+1);
					}
					else{
						return 0;
					}
				}
			}
		}
		else{
			if(b==0){
				if(c%a){
					return 0;
				}
				else{
					if(c/a <= maxx && c/a >= minx){
						return (maxy-miny+1);
					}
					else{
						return 0;
					}
				}
			}
		}
        ll x, y, g;
        if (!find_any_solution(a, b, c, x, y, g))
            return 0;
        a /= g;
        b /= g;

        ll sign_a = a > 0 ? +1 : -1;
        ll sign_b = b > 0 ? +1 : -1;

        shift_solution(x, y, a, b, (minx - x) / b);
        if (x < minx)
            shift_solution(x, y, a, b, sign_b);
        if (x > maxx)
            return 0;
        ll lx1 = x;

        shift_solution(x, y, a, b, (maxx - x) / b);
        if (x > maxx)
            shift_solution(x, y, a, b, -sign_b);
        ll rx1 = x;

        shift_solution(x, y, a, b, -(miny - y) / a);
        if (y < miny)
            shift_solution(x, y, a, b, -sign_a);
        if (y > maxy)
            return 0;
        ll lx2 = x;

        shift_solution(x, y, a, b, -(maxy - y) / a);
        if (y > maxy)
            shift_solution(x, y, a, b, sign_a);
        ll rx2 = x;

        if (lx2 > rx2)
            swap(lx2, rx2);
        ll lx = max(lx1, lx2);
        ll rx = min(rx1, rx2);
        /*
        lx holds the smallest value of x possible
        rx holds the largest value of x possible
        */
        if (lx > rx)
            return 0;
        return (rx - lx) / abs(b) + 1; // returns number of possible solution satisfying constraints.
    }
}
#define ll long long
const int N = 1e3+5;
ll seg[4*N+5][4*N+5];
char ar[N][N];
ll n, q;
void build_y(ll lx, ll rx, ll vx, ll vy, ll ly, ll ry){
    if(ly == ry){
        if(lx == rx){
            if(ar[lx][ly] == '*'){
                seg[vx][vy] = 1;
            }
            else{
                seg[vx][vy] = 0;
            }
        }
        else{
            seg[vx][vy] = seg[2*vx][vy]+seg[2*vx+1][vy];
        }
    }
    else{
        ll mid = (ly+ry)/2;
        build_y(lx, rx, vx, 2*vy, ly, mid);
        build_y(lx, rx, vx, 2*vy+1, mid+1, ry);
        seg[vx][vy] = seg[vx][2*vy]+seg[vx][2*vy+1];
    }
}
void build_x(ll lx, ll rx, ll vx){
    if(lx != rx){
        ll mid=(lx+rx)/2;
        build_x(lx, mid, 2*vx);
        build_x(mid+1, rx, 2*vx+1);
    }
    build_y(lx, rx, vx, 1, 1, n);
}

ll query_y(ll ly, ll ry, ll vx, ll vy, ll qly, ll qry){
    if(qly > ry || qry < ly){
        return 0;
    }
    if(qly <= ly && qry >= ry){
        return seg[vx][vy];
    }
    ll mid = (ly+ry)/2;
    return query_y(ly,mid,vx,2*vy,qly,qry)+query_y(mid+1, ry,vx,2*vy+1,qly,qry);
}

ll query_x(ll lx, ll rx, ll vx, ll qlx, ll qrx, ll qly, ll qry){
    if(qlx > rx || qrx < lx){
        return 0;
    }
    if(qlx <= lx && qrx >= rx){
        return query_y(1,n,vx,1,qly,qry);
    }
    ll mid = (lx+rx)/2;
    return query_x(lx, mid, 2*vx, qlx, qrx, qly, qry)+ query_x(mid+1, rx, 2*vx+1, qlx, qrx, qly,qry);
}

void update_y(ll ly, ll ry, ll vx, ll vy, ll qx, ll qy, ll lx, ll rx){
    if(ly == ry){
        if(lx == rx){
            seg[vx][vy] ^= 1;
        }
        else{
            seg[vx][vy] = seg[2*vx][vy]+seg[2*vx+1][vy];
        }
    }
    else{
        ll mid = (ly+ry)/2;
        if(qy <= mid){update_y(ly, mid, vx, 2*vy, qx, qy, lx, rx);}
        else{update_y(mid+1, ry, vx, 2*vy+1, qx, qy, lx, rx);}
        seg[vx][vy] = seg[vx][2*vy]+seg[vx][2*vy+1];
    }
}
void update_x(ll lx, ll rx, ll vx, ll qx, ll qy){
    if(lx != rx){
        ll mid = (lx+rx)/2;
        if(qx <= mid){update_x(lx,mid,2*vx,qx,qy);}
        else{
        update_x(mid+1,rx,2*vx+1,qx,qy);
        }
    }
    update_y(1,n,vx,1,qx,qy,lx,rx);
}
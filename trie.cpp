const ll NN = 26;
struct trienode {
    ll val = 0;
    struct trienode* ar[26];
};
struct trienode *newNode()
{
    struct trienode *temp = new struct trienode;
    temp->val = 0;
    REP(i, 0, NN) {
        ar[i] = NULL;
    }
    return temp;
} void insert(struct trienode* root, ll prexor) {
    struct trienode* node = root;
    for (ll i = N; i >= 0; i--) {
        if ((prexor & (1LL << i))) {
            if (node->ar[1]) {
                node = node->ar[1];
            }
            else {
                node->ar[1] = newNode();
                node = node->ar[1];
            }
        }
        else {
            if (node->ar[0]) {
                node = node->ar[0];
            }
            else {
                node->ar[0] = newNode();
                node = node->ar[0];
            }
        }
    }
    node->val = prexor;
}
ll query(struct trienode* root, ll prexor) {
    struct trienode* node = root;
    for (ll i = N; i >= 0; i--) {
        //if(i == 0){return prexor^(node->val);}
        bool a = (prexor & (1LL << i));
        if (node->ar[a]) {
            node = node->ar[a];
        }
        else if (node->ar[1 - a]) {
            node = node->ar[1 - a];
        }
    }
    return (prexor ^ (node->val));
}

/*
Suffix array construction in O(L log^2 L) time.  Routine for
 computing the length of the longest common prefix of any two
 suffixes in O(log L) time.

 INPUT:   string s

 OUTPUT:  array suffix[] such that suffix[i] = index (from 0 to L-1)
          of substring s[i...L-1] in the list of sorted suffixes.
          That is, if we take the inverse of the permutation suffix[],
          we get the actual suffix array.
*/
#include<bits/stdc++.h>
using namespace std;
struct SuffixArray{
    const int L; //stores length of the string
    string s; //stores the string
    vector<vector<int>> P; // P[j][i] stores the rank of the ith suffix in level j
    vector<pair<pair<int, int>,int>> M; //M is a temporary array for sorting the array
    vector<int>lcp;
    vector<int>suffix_array;

    SuffixArray(const string &s) : L(s.length()), s(s), P(1,vector<int>(L,0)), M(L), lcp(L), suffix_array(L) {
        for(int i=0; i<L;i++){
            P[0][i] = s[i]-'a';
        }
        for(int skip = 1, level = 1; skip < L; skip*=2, level++){
            P.push_back(vector<int>(L,0));
            for(int i=0;i<L;i++){
                M[i] = make_pair(make_pair(P[level-1][i], i+skip < L?P[level-1][i+skip]: INT_MIN+L), i);
            }
            sort(M.begin(), M.end());
            for (int i = 0; i < L; i++) {
                P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
            }
        }
        vector<pair<int,int>>out;
        // out.push_back(make_pair(-1,L));
        for(int i=0;i<L;i++){
            out.push_back(make_pair(P.back()[i],i));
        }
        sort(out.begin(), out.end());
        for(int i=0;i<L;i++){
            suffix_array[i] = out[i].second;
        }
        //creating lcp array using kasai's algo
        vector<int>rank(L,0);
        for(int i=0;i<L;i++){
            rank[suffix_array[i]] = i; //contain the index in the suffix array of the suffix starting in index i
        }
        int k = 0;
        for(int i=0;i<L;i++, k?k--:0){
            if(rank[i] == L-1){
                k = 0; continue;
            }
            int j = suffix_array[rank[i]+1];
            while(i+k <L && j+k<L && s[j+k] == s[i+k]){
                k++;
            } 
            lcp[rank[i]] = k;
            if(k){
                k--;
            }
        }
    }
    vector<int> GetSuffixArray() { return suffix_array; } 

    //returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
    int LongestCommonPrefix(int i, int j){
        int len = 0;
        if(i == j){
            return L-i;
        }
        for(int k=P.size()-1; k>=0 && i <L && j < L;k--){
            if(P[k][i] == P[k][j]){
                len += (1<<k);
                i+=(1<<k);
                j+=(1<<k);
            }
        }
        return len;
    }
};

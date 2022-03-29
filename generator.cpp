#include "bits/stdc++.h"
using namespace std;

#define int long long
#define accuracy chrono::steady_clock::now().time_since_epoch().count()

const int maxn = (1e6 + 5) , Infinity = (1ll<<31);
int32_t permutation[maxn];
mt19937 rng(accuracy);

int rand(int l , int r){
    uniform_int_distribution<int> ludo(l,r); return ludo(rng);
}

namespace generator{
    string generate_string(int length = 0 , bool upperCase = false,int l = 1 , int r = 26){
        assert(length >= 0 && length <= (5e6));
        string str(length , (upperCase?'A':'a'));
        for(char &x:str){
            x += rand(l , r) - 1;
        }
        return str;
    }

    vector<int> generate_array(int length = 0 , int minRange = 0 , int maxRange = Infinity){
        assert(length >= 0 && length <= (5e6));
        vector<int> ar(length);
        for(int &x:ar){
            x = rand(minRange , maxRange);
        }
        return ar;
    }

    vector<pair<int,int>> generate_tree(int n = 0){
        assert(n>=0);
        vector<pair<int,int>> res(n?n-1:0);
        // For a bamboo Tree
        if(rng()%5 == 0){
            for(int i=1; i<n; i++){
                res[i-1] = {i , i + 1};
            }
            return res;
        }
        // For a star Tree
        if(rng()%7 == 0){
            for(int i=2; i<=n; i++){
                res[i-2] = {1 , i};
            }
            return res;
        }

        iota(permutation , permutation + n + 1 , 0);
        shuffle(permutation + 1, permutation + n + 1 , rng);
        for(int i=2; i<=n; i++){
            int u = i , v = rand(1 , i - 1);
            u = permutation[u] , v = permutation[v];
            res[i-2] = minmax(u , v);
        }
        shuffle(res.begin() , res.end() , rng);
        return res;
    }
    
    vector<pair<int,int>> generate_simple_graph(int n = 0 , int m = 0){
        assert(n > 0 && m>=n);
        int max_edges = n*(n - 1)/2;
        assert(m <= max_edges);
        vector<pair<int,int>> res = generate_tree(n);
        set<pair<int,int>> edge(res.begin() , res.end());
        for(int i=n; i<=m; i++){
            while(true){
                int u = rand(1 , n) , v = rand(1 , n);
                if(u == v)continue;
                auto it = edge.insert(minmax(u , v));
                if(it.second)break;
            }
        }
        res.assign(edge.begin() , edge.end());
        return res;
    }
}

using namespace generator;
template<typename T = int>
ostream& operator<<(ostream &other , const vector<T> &v){
    for(const T&x:v){
        other<<x<<' ';
    }
    other << '\n';
    return other;
}
ostream& operator<<(ostream &other , const vector<pair<int,int>> &v){
    for(const auto &x: v){
        other << x.first << ' ' << x.second << '\n';
    }
    return other;
}

void generate_test(ofstream &out){
    int n = rand(1 , 20);
    out << n << '\n';
    out << generate_tree(n);
    out << '\n';
}
signed main(){

    srand(accuracy);
    ofstream out;
    out.open("input.txt");
    int t = 1;
    // t = rand(1 , 10);
    // out<<t<<'\n';
    while(t--){
        generate_test(out);
    }
    return 0;
}
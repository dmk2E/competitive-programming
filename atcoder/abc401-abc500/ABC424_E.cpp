/*アルゴリズムと工夫点(Cut in Half/CPU: 848 ms Memory: 62536 KB  Length: 1126 B)
シミュレーションで解く．
棒の情報を，その長さと本数で管理し，ある長さを半分にする作業は同時に行うとする．
すると，元の棒から生まれた数は，2倍ずつ増加していく．
従って，全体の本数がN + Kを超えるまで，最も長さが大きい棒を半分にする作業をシミュレーションしても，高速に動作する．
最悪計算量は，O(T * log2(K) * log2(N * log2(K))) < 10^8 となり高速．
※ 今回の半分にする作業などは，個数が指数関数的に増えていく場合があり，小さい計算量でシミュレーション可能である場合があることを考えておこう．
*/
#include<iostream>
#include<set>
#include<unordered_map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

double solve(){
    int i,j,n,k,x,sum;
    scanf("%d%d%d",&n,&k,&x);
    unordered_map<double,int> dict;
    set<double> st;
    sum = n;
    rep(i,n){
        int a;
        scanf("%d",&a);
        dict[a]++;
        st.insert(a);
    }
    i = 5;
    while(1){
        auto it = st.end();it--;
        double max_a = *it;
        if(sum+dict[max_a] < n+k){
            sum += dict[max_a];
            dict[max_a/2] += dict[max_a]*2;
            st.erase(it);
            st.insert(max_a/2);
        }else{
            int rest = n+k-sum;
            dict[max_a/2] += rest*2;dict[max_a] -= rest;
            st.insert(max_a/2);
            break;
        }
    }
    sum = 0;
    auto it = st.end();
    while(sum < x){
        it--;
        sum += dict[*it];
    }
    return *it;
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%.10f\n",solve());
    return 0;
}
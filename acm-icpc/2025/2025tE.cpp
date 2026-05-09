/*アルゴリズムと工夫点(if-then-else/CPU: ? ms Memory: ? KB  Length: - B)
再帰下降構文解析 + DFS で解く．
与えられる文字列の構文解析を行い，次のような完全二分木を作成する．
・各頂点は <variable> または <number> を値として持つ
・式の評価値が`真'である場合に遷移する<variable> または <number> を値として持つ頂点を"左の子"として持つ
・式の評価値が`偽'である場合に遷移する<variable> または <number> を値として持つ頂点を"右の子"として持つ

この二分木上でDFSを行い，各頂点への訪問（左の子を訪問後，右の子を訪問）を行い，解を求めるために値を加算していく．
<number>の値を持つ頂点に到達した時，その値を加算する回数は，2^(その時点で値が未定である変数の数) となる．
数え上げの為，この時，各変数ごとに{`真'，`偽'，"未定"}の値を保持させる連想配列を用意しておくと良い．

最悪計算量は，O((|e|+|e|+2*|e|)*log2(|e|))=O(|e|*log2(|e|))<10^8 となり間に合う．
*/
#include<iostream>
#include<cassert>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<list>
#include<algorithm>
// #include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
#define MOD 998244353
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Node{
    string cond;
    int left,right;

    Node(string s="",int l=NIL,int r=NIL):cond(s),left(l),right(r){}
};

string s;
vector<Node> binary_tree;
map<string,int> var_to_bool;
int not_decided;

/// @brief 構文解析で二分木の形に
/// @param s 対象文字列
/// @param now 着目している添え字
/// @return その頂点番号
int expr(string& s,int& now){
    //printf("now:%d \n",now);
    // <number>
    int node_id=binary_tree.size();
    binary_tree.push_back(Node());
    if('0'<=s[now]&&s[now]<='9'){
        binary_tree[node_id].cond=s.substr(now,1);
        var_to_bool[binary_tree[node_id].cond]=NIL;
        now++;
        return node_id;
    }
    now+=3;
    int start=now;
    while(now<s.size()&&s[now]!='_')now++;
    binary_tree[node_id].cond=s.substr(start,now-start);
    
    not_decided+=(var_to_bool.find(binary_tree[node_id].cond)==var_to_bool.end());
    var_to_bool[binary_tree[node_id].cond]=NIL;
    
    now+=6;
    binary_tree[node_id].left=expr(s,now);
    now+=6;
    binary_tree[node_id].right=expr(s,now);
    return node_id;
}

/// @brief 繰り返し二乗法で，x^a を高速に計算
/// @param x 被累乗数
/// @param a 累乗数
/// @return x^a の値
int power(int x,int a){
    if(a==0)return 1;
    int res=power((((long long)x%MOD)*(x%MOD))%MOD,a/2)%MOD;
    if(a%2==1)res=((long long)res*(x%MOD))%MOD;
    return res;
}

/// @brief 生成した二分木上を探索し，解を出力
/// @param now 訪問中の頂点番号
/// @return 問題の解
int dfs(int now){
    //printf("id:%d cnt:%d\n",now,not_decided);
    if('0'<=binary_tree[now].cond[0]&&binary_tree[now].cond[0]<='9'){
        //printf("%d %d\n",binary_tree[now].cond[0]-'0',not_decided);
        return ((binary_tree[now].cond[0]-'0')*((ll)power(2,not_decided)))%MOD;        
    }
    ll sum=0;
    // 頂点が変数だった場合
    if(var_to_bool[binary_tree[now].cond]==NIL){
        not_decided--;
        // 左の子に行く
        var_to_bool[binary_tree[now].cond]=1;
        sum=(sum+dfs(binary_tree[now].left))%MOD;
        // 右の子に行く
        var_to_bool[binary_tree[now].cond]=0;
        sum=(sum+dfs(binary_tree[now].right))%MOD;

        var_to_bool[binary_tree[now].cond]=NIL;
        not_decided++;
    }else if(var_to_bool[binary_tree[now].cond])sum=(sum+dfs(binary_tree[now].left))%MOD;
    else sum=(sum+dfs(binary_tree[now].right))%MOD;
    return (int)sum;
}

int main(){
    int i=0,j;
    cin>>s;
    not_decided=0;
    expr(s,i);
    //rep(i,binary_tree.size())printf("id:%d cond:%s left:%d right:%d\n",i,binary_tree[i].cond.c_str(),binary_tree[i].left,binary_tree[i].right);
    printf("%d\n",dfs(0));
    return 0;
}
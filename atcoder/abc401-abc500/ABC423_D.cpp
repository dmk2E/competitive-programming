/*アルゴリズムと工夫点(Long Waiting/CPU: 108 ms Memory: 11264 KB  Length: 1599 B)
優先度付きキューを用いた，高速シミュレーションで解く．
着目するべき時刻は，待ち行列に団体客が並ぶ時刻と，退店する時刻であり，それぞれで店内の人数や待ち行列の状態更新を行えばよい．
最悪計算量は，O(N*log2(N)) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Customer{
    int a,b,c;

    Customer(int a = 0,int b = 0, int c = 0):a(a),b(b),c(c){}
};

struct Data{
    ll e_t;
    int c;

    Data(ll e_t = 0,int c = 0):e_t(e_t),c(c){}

    bool operator<(const Data& k)const{
        return e_t == k.e_t ? c < k.c : e_t > k.e_t;
    }
};

int n,k;

int main(){
    int i,j,now_cnt = 0;
    ll now_t = 0, checked_t = -1;
    scanf("%d%d",&n,&k);
    queue<Customer> que;
    rep(i,n){
        Customer ipt;
        scanf("%d%d%d",&ipt.a,&ipt.b,&ipt.c);
        que.push(ipt);
    }
    priority_queue<Data> shop;
    const ll INF = (1e13);
    while(que.size()){
        now_t = INF;
        if(shop.size() && checked_t < shop.top().e_t)now_t = min(now_t, shop.top().e_t);
        if(checked_t < (ll)que.front().a)now_t = min(now_t, (ll)que.front().a);
        // customers exit the restaurant
        while(shop.size() && shop.top().e_t <= now_t){
            now_cnt -= shop.top().c;
            shop.pop();
        }
        // customers enter the restaurant
        while(
            que.size() &&
            now_t >= que.front().a && 
            now_cnt + que.front().c <= k
        ){
            now_cnt += que.front().c;
            shop.push(Data(que.front().b + now_t, que.front().c));
            printf("%lld\n",now_t);que.pop();
        }
        checked_t = now_t;
    }
    return 0;
}
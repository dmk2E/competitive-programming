/*アルゴリズムと工夫点(Laser Takahashi/CPU: 147 ms Memory: 6792 KB  Length: 1295 B)
偏角ソート + 二分探索 で解く．
座標平面上の各点を，その偏角の大きさでソートする場合，外積を用いた位置関係の計算を用いる．
各クエリの2点の位置は，適切に二分探索を行うことで求める．
同一偏角への対処は，2点間の区間[l, r) を，lower_bound, upper_bound を適切に使い分けることで求める．
最悪計算量は，O((N + Q) * log2(N)) < 10 ^ 7 となり高速．
※ 公式解説では毎回二分探索をせず，1回の走査で各点毎のl, r の値を求めており，より高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Point{
    int y, x;

    Point(
        int y = 0, 
        int x = 0
    ):y(y), x(x){}

    bool is_up()const{
        return y > 0 || (y == 0 && x >= 0);
    }

    ll cross(const Point& k)const{
        return (ll)k.y * x - (ll)y * k.x;
    }

    bool operator<(const Point& k)const{
        if(this -> is_up() != k.is_up())return k.is_up();
        return this -> cross(k) < 0;
    }
};

typedef pair<int, int> P;

int n, q;

int main(){
    int i, j;
    scanf("%d%d", &n, &q);
    vector<Point> ps, id_to_p;
    const ll INF = (3e18);
    rep(i, n){
        int x, y;
        scanf("%d%d", &x, &y);
        ps.push_back(Point(y, x));
        id_to_p.push_back(Point(y, x));
    }
    sort(ps.begin(), ps.end());
    while(q--){
        int a, b;
        scanf("%d%d", &a, &b);a--;b--;
        int a_id = lower_bound(ps.begin(), ps.end(), id_to_p[a]) - ps.begin();
        int b_id = upper_bound(ps.begin(), ps.end(), id_to_p[b]) - ps.begin();
        printf("%d\n", a_id < b_id ? b_id - a_id : b_id + n - a_id);
    }
    return 0;
}
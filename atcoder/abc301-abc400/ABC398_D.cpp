/*アルゴリズムと工夫点(Bonfire/CPU: 51 ms Memory: 13272 KB  Length: 924 B)
煙全てが移動する->焚火と高橋君自体を動かす という発想により，考慮すべき対象数が2つになるため，計算量を削減できる．
※静止物体と動体が存在する座標空間において，相対位置関係のみを考慮すればよい場合，動体の方を静止させ，静止物体の方を"動体の動きと逆方向"に動かず問題に言い換えができる
*/
#include<iostream>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,r,c;
string s;

int main(){
    int i,j,ty,tx;
    string ans="";
    scanf("%d%d%d",&n,&r,&c);
    cin>>s;
    ty=tx=0;
    set<P> v;
    rep(i,s.length()){
        v.insert(P(ty,tx));
        switch(s[i]){
            case 'N':
                r++;
                ty++;
                break;
            case 'W':
                c++;
                tx++;
                break;
            case 'S':
                r--;
                ty--;
                break;
            default:
                c--;
                tx--;
                break;
        }
        if(v.find(P(r,c))==v.end())ans+='0';
        else ans+='1';
    }
    cout<<ans<<endl;
    return 0;
}
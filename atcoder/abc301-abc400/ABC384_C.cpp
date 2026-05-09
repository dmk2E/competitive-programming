/*アルゴリズムと工夫点(Perfect Standings/CPU: 1 ms Memory: 3944 KB  Length: 1449 B)
(名前，点数)の形で各参加者のデータを保持し，ソートするだけ．
ただし，名前の全列挙を行う必要があり，再帰を用いた全探索を行えばよい．
※比較演算子のオーバーロードにミスがあるのに気づかず，めっちゃ時間を浪費しました泣
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define N 31
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    string name;
    int point;
    Data(string nname="",int ppoint=0):name(nname),point(ppoint){}

    bool operator<(const Data& k)const{
        return (point<k.point)||(point==k.point&&name>k.name);
    }
};

vector<int> p(5,0);
string name;

int main(){
    int i,j;
    scanf("%d%d%d%d%d",&p[0],&p[1],&p[2],&p[3],&p[4]);
    vector<Data> ipt;
    string par="ABCDE",tmp="";
    auto rec=[&](auto& f,string name,int state,int cnt)->void{
        int i;
        if(cnt==0){
            int j;
            ipt.push_back(Data(name,0));
            rep(j,name.size()){
                ipt[ipt.size()-1].point+=p[(int)name[j]-(int)'A'];
            }
            return ;
        }
        i=par.size()-1;
        while(i>=0){
            if(((state>>i)&1)==1)break;
            i--;
        }
        i++;
        for(;i<par.size();i++){
            if(((state>>i)&1)==0){
                name+=par[i];
                f(f,name,state|(1<<i),cnt-1);
                name.pop_back();
            }
        }
    };
    for(i=1;i<=5;i++){
        tmp="";
        rec(rec,tmp,0,i);
    }
    sort(ipt.begin(),ipt.end());
    rep(i,ipt.size())cout<<ipt[ipt.size()-1-i].name<<endl;
    return 0;
}
/*アルゴリズムと工夫点(階層民主主義/CPU: 0 ms Memory: 3576 KB  Length: 1272 B)
第k段階の選挙区で勝者となるために必要な最小票数Aについて考える．
・k=1の場合，有権者数Cの最小の過半数┏C/2┓を取ればよい．
・第k段階の選挙区で勝者となるために必要な最小票数Aについて考える．
あるk(>1)段階に含まれる選挙区の数Cとする．選挙区s[i](0<=i<C)それぞれを勝ち上がるために必要な最小票数v[i] とすると，Aは，最も小さい┏C/2┓個のv[i]の総和となる．
よって，この値を再帰を用いて実装する．
一つのテストケースで入力としてもらう文字列Sとすると，各段階のAの計算の際，指定された範囲の文字列を1回巡回し，最小上位の探索を行うから，この時の最悪計算量は O(|S|*log2(|S|))．
生じうる第1段階の選挙区の数は多くても|S|/3を超えないことと，完全二分木のイメージで段階数の最大値はlog2(|S|/3)となることから，
全体の最悪計算量はO(|S|*(log2(|S|))^2)<10^(4)*10^(2)=10^6 となり十分高速．
※再帰を用いた全探索の応用問題．慣れれば楽しい．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n;

int main(){
    int i,j;
    string ipt;
    //ipt[l,r)の選挙区で勝者となるために必要な最少票数
    auto rec=[&](auto& f,int l,int r)->int{
        //printf("rec(%d,%d){",l,r);
        int now=l,cnt=0,ll,levels=0;
        priority_queue<int> PQ;
        bool flag=true;
        while(now<r){
            if(ipt[now]=='['){
                flag=false;
                if(cnt==0)ll=now;
                cnt++;
            }else if(ipt[now]==']'){
                flag=false;
                cnt--;
                if(cnt==0){
                    PQ.push(-f(f,ll+1,now));
                    levels++;
                }
            }
            now++;
        }
        now=0;
        if(flag){
            while(l<r){
                now*=10;
                now+=(int)ipt[l]-(int)'0';
                l++;
            }
            //printf("%d}",(now+1)/2);
            return (now+1)/2;
        }
        levels=(levels+1)/2;
        while(levels--){
            now-=PQ.top();PQ.pop();
        }
        return now;
    };
    scanf("%d",&n);
    while(n--){
        cin>>ipt;
        printf("%d\n",rec(rec,0,ipt.length()));
    }
    return 0;
}
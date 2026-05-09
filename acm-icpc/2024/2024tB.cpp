/*アルゴリズムと工夫点(シンプルなエディタ/CPU: 0 ms Memory: 3448 KB  Length: 758 B)
言われたことをシミュレーションして解く．
今回はNが小さいため，配列を用いて愚直に要素の挿入を行っても解けるが，双方向リストを持ちいれば高速化可能．
最悪計算量は，O(N)<10^3 となり十分高速．
*/
#include<iostream>
#include<list>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        list<char> str;
        list<char>::iterator it=str.begin();
        while(n--){
            string ope,c;
            cin>>ope>>c;
            if(ope=="INSERT")str.insert(it,c[0]);
            else if(ope=="LEFT"){
                if(it!=str.begin())it--;
            }else{
                if(it!=str.end())it++;
            }
        }
        it=str.begin();
        while(it!=str.end()){
            printf("%c",*it);
            it++;
        }
        puts("");
    }
    return 0;
}
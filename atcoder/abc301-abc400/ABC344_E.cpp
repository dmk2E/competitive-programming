/*アルゴリズムと工夫点(Insert or Erase/CPU:  ms  Memory:  KB  Length:  B)
list構造において、insert関数は指定されたアドレスが指す要素の前に新しい要素を追加する(要素それぞれを指すイテレータは変化しない)。いずれも挿入した要素のイテレータを返り値とする。
リスト構造は、要素の削除や追加はO(1)で済むが、要素の探索にはO(n)かかってしまうことであり、削除する要素や追加する要素のイテレータはあらかじめ仮想配列で持っておく必要がある。
※map構造使ってやる最初の方針は間違ってなかったが、実装でミスがあったためにTLE×2となってしまった、、、、、、。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;
list<int> a;
map<int,list<int>::iterator> v;

void showList(){
    int i,j;
    i=0;
    for(int x:a){
        if(i==v.size()-1){
            j=x;
            break;
        }
        printf("%d ",x);
        i++;
    }
    if(v.size())
        printf("%d\n",j);
}

int main() {
    int i,j;
    list<int>::iterator it;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&i);
        a.push_back(i);
        it=a.end();
        v[i]=--it;
    }
    scanf("%d",&n);
    while(n--){
        //showList();
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            it=v[i];
            v[j]=a.insert(++it,j);
        }else{
            scanf("%d",&i);
            a.erase(v[i]);
            v.erase(v.find(i));
        }
    }
    showList();
	return 0;
}
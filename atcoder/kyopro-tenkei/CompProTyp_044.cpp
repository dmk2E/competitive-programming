/*アルゴリズムと工夫点(Shift and Swapping/CPU: 63 ms Memory: 4152 KB  Length: 753 B)
元々の順序が変わらない変形は，キューの実装と同じ要領で配列の先頭と末尾を保持すれば計算量を削減して，各クエリをこなせる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,q;
vector<int> a;

int main(){
    int i,j,head;
    scanf("%d%d",&n,&q);
    a=vector<int>(n);
    rep(i,n)
        scanf("%d",&a[i]);
    head=0;
    while(q--){
        scanf("%d",&i);
        switch(i){
            case 1:
                scanf("%d%d",&i,&j);
                swap(a[(head+i-1)%n],a[(head+j-1)%n]);
                break;
            case 2:
                scanf("%d%d",&i,&j);
                head=(head+n-1)%n;
                break;
            default:
                scanf("%d%d",&i,&j);
                printf("%d\n",a[(head+i-1)%n]);
                break;
        }
    }
    return 0;
}
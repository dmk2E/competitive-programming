/*アルゴリズムと工夫点(LR insertion/CPU: 48 ms Memory: 16192 KB  Length: 2104 B)
リストの各要素を可変長配列で保持し，「その配列上の添え字」を「各要素のアドレス」として，双方向リストを自作する．
そうすると各要素の挿入はO(1)で実行できるから，最悪計算量は O(N)=10^6 より十分高速．
※コンテナを使う場合でも，値ごとにそれを保持する要素のアドレスを保持するテーブルは用意する必要有．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Node{
    int prev,next,val;

    Node(int pprev=0,int nnext=0,int vval=0):prev(pprev),next(nnext),val(vval){}
};

typedef struct DoublyLinkedList{
    int nil,NIL;
    vector<Node> dll;
    vector<int> val2Id;
public:
    DoublyLinkedList(int maxVal){
        dll=vector<Node>(1);
        nil=0;
        NIL=maxVal+1;
        dll[nil].prev=dll[nil].next=nil;dll[nil].val=NIL;
        val2Id=vector<int>(maxVal+2);
        val2Id[NIL]=nil;
    }

    void pushFront(int val){
        Node now(nil,dll[nil].next,val);
        dll[dll[nil].next].prev=dll.size();
        dll[nil].next=dll.size();
        val2Id[val]=dll.size();
        dll.push_back(now);
    }

    void pushLeft(int id,int val){
        Node now(dll[id].prev,id,val);
        dll[dll[id].prev].next=dll.size();
        dll[id].prev=dll.size();
        val2Id[val]=dll.size();
        dll.push_back(now);
    }

    void pushRight(int id,int val){
        Node now(id,dll[id].next,val);
        dll[dll[id].next].prev=dll.size();
        dll[id].next=dll.size();
        val2Id[val]=dll.size();
        dll.push_back(now);
    }

    void pushLeftByVal(int val,int vval){
        pushLeft(val2Id[val],vval);
    }

    void pushRightByVal(int val,int vval){
        pushRight(val2Id[val],vval);
    }

    vector<int> show(){
        int now=dll[nil].next;
        vector<int> ans;
        while(now!=nil){
            ans.push_back(dll[now].val);
            now=dll[now].next;
        }
        return ans;
    }
}DLL;

int n;
string s;

int main(){
    int i,j;
    scanf("%d",&n);
    cin>>s;
    DLL li(n);
    li.pushFront(0);
    rep(i,s.length()){
        if(s[i]=='L')
            li.pushLeftByVal(i,i+1);
        else
            li.pushRightByVal(i,i+1);
    }
    vector<int> ans=li.show();
    rep(i,ans.size()-1)printf("%d ",ans[i]);
    printf("%d\n",ans[i]);
    return 0;
}
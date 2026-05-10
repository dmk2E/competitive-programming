/*アルゴリズムと工夫点(/CPU: - ms Memory: - KB  Length: - B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Outputer{
    vector<T> ans;

public:
    Outputer(){}

    void push(T value){
        ans.push_back(value);
    }

    void output(){
        int i;
        rep(i, ans.size() - 1)cout << ans[i] << ',';
        cout << ans[i] << '\n';
    }
};

vector<vector<int> > ipt = {
    /* 入力データをハードコード */
};
Outputer<int> answer;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];
    }

    answer.output();
    return 0;
}
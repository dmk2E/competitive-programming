/*アルゴリズムと工夫点(ラスボスを倒せ！/CPU: - ms Memory: - KB  Length: - B)
全探索 + シミュレーションで解く．
「購入する攻撃強化アイテム」の個数 atk_item_count を固定すると，「必要になる回復アイテム」の最小個数 recover_item_count は，下記のシミュレーションで求められる．
 1. recover_item_count = 0 とする
 2. atk_item_count が0でない時，攻撃強化アイテムを使用して攻撃する
 3. ラスボスの攻撃でHPが0になってしまう場合は，HP が 1 だけ残るように回復アイテムを購入し，recover_item_count に加算
勇者の攻撃力を atk，ラスボスのHPを boss_hp とすると，atk_item_count ∈ [0, ceil(boss_hp / (atk * 2))] となる．
最悪計算量は，O(100 * ceil(boss_hp / (atk * 2))) < 10 ^ 7 となり，高速．
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

    void output(string prefix = "", string suffix = ""){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << prefix << ans[i] << suffix << ',';
            cout << prefix << ans[i] << suffix << '\n';
        }
    }
};

// vector<vector<int> > ipt = {
//     {300,5,100,4000,1000,50,40,22,58,82,74,40,43,29,40,89,79,89,1,20,77,83,72,25,5,31,98,4,49,28,33,56,93,5,72,4,52,77,77,72,88,65,9,13,62,28,77,20,71,5,89,79,98,47,18,30,85,35,5,56,24,75,82,52,51,12,10,53,58,24,93,80,62,35,76,4,1,92,13,27,85,46,71,20,22,58,12,98,82,56,79,46,34,24,14,9,48,45,36,22,40,5,90,20},
//     {25,2,3,4000,24,1,1,2,1,1,2,2,1,1,1,2,1,1,1,1,1,2,1,1,2,2,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,2,1,2,1,2,1,1,2,1,1,2,1,1,1,1,2,2,1,1,2,2,2,1,1,2,2,2,1,2,1,2,1,1,1,1,2,1,1,1,2,1,1,1,2,2,2,1,1,2,1,2,1,1,2,1,2,1,2,1,1,1,1,2},
//     {40,3,50,1100,10,41,38,11,48,35,48,41,1,41,33,2,6,1,42,41,25,1,10,48,6,16,37,31,41,33,23,41,3,15,24,8,32,7,48,44,20,5,10,5,41,13,48,2,18,25,48,48,44,17,4,1,39,22,27,14,32,9,25,25,44,10,33,33,3,35,8,46,10,5,5,18,34,10,1,29,32,28,40,46,23,24,19,34,2,20,45,47,5,18,3,14,2,4,35,44,15,19,8,15}
// };
vector<vector<int> > ipt = {
    {5000,101,100,5000,40,73,11,37,13,29,70,55,20,1,26,85,98,39,97,90,45,63,19,5,95,46,18,91,63,27,75,5,41,64,84,28,46,32,1,52,61,46,87,78,32,21,75,59,90,96,73,53,78,27,20,54,38,73,81,22,13,40,89,33,94,99,14,80,93,88,59,59,80,42,89,42,85,55,30,61,54,7,64,23,7,38,31,28,43,73,45,43,42,21,5,67,73,34,30,71,40,57,88,7},
    {10007,7,999,500,3,28,302,489,639,634,112,558,538,775,241,688,74,67,163,908,626,803,15,425,612,301,384,542,548,434,770,939,739,433,690,180,926,570,894,539,747,390,552,479,218,803,929,693,603,378,825,160,964,234,364,334,897,151,631,722,581,490,291,307,227,716,852,840,907,732,979,990,930,879,829,83,90,902,998,897,596,409,575,311,998,72,33,261,327,790,261,623,707,348,670,313,786,925,801,551,410,926,734,909},
    {1800,17,255,9999,90,46,147,234,235,201,66,242,213,86,3,218,93,29,147,78,136,65,82,16,244,133,109,68,110,87,253,245,37,4,123,222,191,194,20,1,163,114,166,197,15,243,207,82,53,197,204,126,153,1,44,161,114,178,119,168,192,20,103,214,194,61,197,205,230,153,144,93,40,147,108,222,159,177,50,249,170,14,225,61,254,57,112,4,67,240,192,124,168,198,8,253,217,154,85,2,2,61,59,72}
};
Outputer<int> answer;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];
        int atk_item_price = table[0], recover_item_price = table[1], hp = table[2], boss_hp = table[3], atk = table[4];

        const ll MAX_COST = (1e14);
        ll ans = MAX_COST;
        for(int atk_item_count = 0;atk_item_count <= ((boss_hp + atk * 2 - 1) / (atk * 2));atk_item_count++){
            auto calcMinRecoverItem = [&](int num_enhance_atk) -> ll{
                ll ans = 0;

                int rest_boss_hp = boss_hp, rest_hp = hp;
                for(int turn = 5;turn < table.size();turn++){
                    // 攻撃強化アイテム
                    int now_atk = atk;
                    if(num_enhance_atk > 0){
                        num_enhance_atk--;
                        now_atk *= 2;
                    }

                    // 勇者の攻撃
                    rest_boss_hp -= now_atk;
                    if(rest_boss_hp <= 0)return ans;

                    // ラスボスの攻撃 & 回復アイテム使用
                    int boss_atk = table[turn];
                    if(rest_hp <= boss_atk){
                        ans += boss_atk - rest_hp + 1;
                        rest_hp = boss_atk + 1;
                    }
                    rest_hp -= boss_atk;
                }

                // 100 ターン目
                //  攻撃強化アイテム
                int now_atk = atk;
                if(num_enhance_atk > 0){
                    num_enhance_atk--;
                    now_atk *= 2;
                }

                //  勇者の攻撃
                rest_boss_hp -= now_atk;
                if(rest_boss_hp <= 0)return ans;

                return MAX_COST;
            };
            ans = min(
                ans, 
                atk_item_price * atk_item_count + 
                recover_item_price * calcMinRecoverItem(
                    /* num_enhance_atk = */ atk_item_count
                )
            );
        }
        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}
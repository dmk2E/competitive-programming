/*アルゴリズムと工夫点(N君の遠足/CPU: - ms Memory: - KB  Length: - B)
動的計画法を2回行って解く．
まず「飲み物」について，特定の質量となるように購入した時の，最小の金額を，下記のDPテーブルに従い求める．
 gram_to_min_price[i][j] := i番目の飲み物について購入するか否かを決めた時，質量がjグラムであった時の，かかった最小の合計金額
また「おやつ」と「弁当」について，合計金額に対して，購入できる最大の質量を，下記のDPテーブルに従い求める．
 oyatu_money_to_sum_to_grams[i][j] := おやつと弁当をいくつか購入した時，おやつの購入金額がi円以下，合計金額がj円以下である場合の，最大の質量
すると，「購入する飲み物の質量数」を固定した時の解は，その時にかかる最小金額は求まっているため，残りの金額で購入できる「おやつ」と「弁当」の最大の合計質量を求めればよい．
これは，2つのDPテーブルを前計算しておけば，高速に解を求められる．
商品数Nとすると，最悪計算量は，O(N ^ (2) * MAX_GRAM + N * MAX_MONEY * MAX_OYATU) < 10 ^ 8 となり，間に合う．
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

struct Item{
    string name, category;
    int price, gram;

    Item(
        string name = "", 
        string category = "", 
        int price = 0, 
        int gram = 0
    ):name(name), category(category), price(price), gram(gram){}
};

// vector<vector<Item> > ipt = {
//     {
//         {"suika","oyatu",2000,2000},
//         {"umebosi","bento",1500,500},
//         {"apple juice","nomimono",400,400},
//         {"tansansui","nomimono",500,300},
//         {"ginger ale","nomimono",300,200},
//         {"grape juice","nomimono",200,100},
//         {"kendama","omotya",1,500}
//     },
//     {
//         {"noriben","bento",500,500},
//         {"sandwich","bento",500,500},
//         {"tamagoyaki","bento",300,100},
//         {"banana","oyatu",200,400},
//         {"cake","oyatu",300,300},
//         {"dango","oyatu",200,200},
//         {"mizu","nomimono",200,1000},
//         {"grape juice","nomimono",500,100}
//     },
//     {
//         {"onigiri","bento",100,111},
//         {"crisps","oyatu",209,152},
//         {"chocolate","oyatu",153,243},
//         {"banana","oyatu",31,115},
//         {"sports drink","nomimono",850,401},
//         {"orange juice","nomimono",705,498},
//         {"syakeben","bento",422,2000},
//         {"ball","omotya",10,1111},
//         {"cookie","oyatu",203,158},
//         {"otya","nomimono",562,202},
//         {"senbei","oyatu",39,152}
//     }
// };
vector<vector<Item> > ipt = {
    {
        {"cake","oyatu",322,765},
        {"chienowa","omotya",252,670},
        {"jigsaw puzzle","omotya",410,974},
        {"onigiri","bento",250,870},
        {"salad","bento",314,481},
        {"suika","oyatu",321,764},
        {"chocolate","oyatu",59,86},
        {"ham","bento",54,10},
        {"ginger ale","nomimono",185,196},
        {"mizu","nomimono",229,196},
        {"umebosi","bento",347,873},
        {"orange juice","nomimono",477,271},
        {"crisps","oyatu",38,452},
        {"banana","oyatu",49,943},
        {"syakeben","bento",472,886},
        {"ball","omotya",321,927},
        {"apple juice","nomimono",408,302},
        {"sandwich","bento",9,48},
        {"cookie","oyatu",33,783},
        {"sports drink","nomimono",230,197},
        {"tamagoyaki","bento",22,696},
        {"chikuwa","bento",286,90},
        {"otya","nomimono",117,503},
        {"sausage","bento",306,597},
        {"senbei","oyatu",346,648}
    },
    {
        {"syakeben","bento",110,200},
        {"chikuwa","bento",200,200},
        {"orange juice","nomimono",663,1987},
        {"onigiri","bento",110,200},
        {"apple juice","nomimono",505,2000},
        {"kendama","omotya",1,2000},
        {"grape juice","nomimono",312,1999},
        {"sandwich","bento",110,200},
        {"coffee","nomimono",2000,2000},
        {"ukiwa","omotya",2000,1},
        {"senbei","oyatu",5,40},
        {"cake","oyatu",100,100},
        {"noriben","bento",300,600},
        {"crisps","oyatu",2000,2000},
        {"chienowa","omotya",1,1}
    },
    {
        {"apple tea","nomimono",324,118},
        {"apple","oyatu",33,35},
        {"gum","oyatu",97,828},
        {"dango","oyatu",55,698},
        {"coffee","nomimono",210,115},
        {"grape","oyatu",140,401},
        {"crisps","oyatu",32,794},
        {"cookie","oyatu",24,522},
        {"salad","bento",15,143},
        {"sports drink","nomimono",125,75},
        {"pine juice","nomimono",308,103},
        {"umebosi","bento",19,206},
        {"cake","oyatu",42,971},
        {"cherry juice","nomimono",398,145},
        {"senbei","oyatu",79,996},
        {"onigiri","bento",105,84},
        {"cocoa","nomimono",204,60},
        {"gummy","oyatu",111,320},
        {"banana","oyatu",41,837},
        {"tamagoyaki","bento",45,45},
        {"melon juice","nomimono",505,105},
        {"sandwich","bento",73,80},
        {"grape juice","nomimono",126,47},
        {"tomato","bento",65,40},
        {"suika","oyatu",29,955},
        {"sausage","bento",61,203},
        {"banana juice","nomimono",363,125},
        {"tansansui","nomimono",181,60},
        {"cherry","oyatu",241,105},
        {"ham","bento",39,555},
        {"syakeben","bento",10,301},
        {"orange juice","nomimono",129,114},
        {"peach juice","nomimono",364,129},
        {"rice","bento",376,245},
        {"yakisoba","bento",42,57},
        {"otya","nomimono",104,68},
        {"noriben","bento",86,228},
        {"bread","bento",190,62},
        {"milk","nomimono",180,102},
        {"water","nomimono",109,30},
        {"pudding","oyatu",68,807},
        {"potate","bento",96,65},
        {"chocolate","oyatu",40,550},
        {"ball","omotya",1,2000},
        {"apple juice","nomimono",74,116},
        {"fish","bento",302,145},
        {"chikuwa","bento",27,307},
        {"ginger ale","nomimono",101,42}
    }
};
Outputer<int> answer;

const string INVALID_CATEGORY = "omotya";
const int MAX_GRAM = 2000;
const int MAX_PRICE = 2000;
const int MAX_OYATU = 500;
const int MIN_NOMIMONO = 700;
const int MAX_MONEY = 2000;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        vector<Item> nomimonos, items;
        for(Item item : ipt[ipt_id]){
            if(item.category == "nomimono")nomimonos.push_back(item);
            else if(item.category != INVALID_CATEGORY)items.push_back(item);
        }

        // 特定の質量となる時の，飲み物の購入金額の最小値
        //  最悪計算量：48 * 2000 * 48
        const int INF = MAX_PRICE * nomimonos.size() + 1;
        const int WEIGHT_LENGTH = nomimonos.size() * MAX_GRAM + 1;
        vector<int> gram_to_min_price(WEIGHT_LENGTH, INF);
        gram_to_min_price[0] = 0;
        for(Item nomimono : nomimonos){
            auto nxt_dp = gram_to_min_price;
            rep(i, WEIGHT_LENGTH)
                if(gram_to_min_price[i] != INF && i + nomimono.gram < WEIGHT_LENGTH)
                    nxt_dp[i + nomimono.gram] = min(
                        nxt_dp[i + nomimono.gram], 
                        gram_to_min_price[i] + nomimono.price
                    );
            swap(gram_to_min_price, nxt_dp);
        }

        // おやつの購入金額と，合計購入金額が特定値以下の時，弁当とおやつを購入した場合の，最大の質量
        //  最悪計算量：48 * 500 * 2000
        const int NIL = -1;
        vector<vector<int> > oyatu_money_to_sum_to_grams(MAX_OYATU + 1, vector<int>(MAX_MONEY + 1, 0));
        for(Item item : items){
            auto nxt_dp = oyatu_money_to_sum_to_grams;
            rep(i, MAX_OYATU + 1)rep(j, MAX_MONEY + 1)if(j + item.price <= MAX_MONEY){
                if(item.category == "oyatu"){
                    if(i + item.price <= MAX_OYATU)
                        nxt_dp[i + item.price][j + item.price] = max(
                            nxt_dp[i + item.price][j + item.price], 
                            oyatu_money_to_sum_to_grams[i][j] + item.gram
                        );
                }else nxt_dp[i][j + item.price] = max(nxt_dp[i][j + item.price], oyatu_money_to_sum_to_grams[i][j] + item.gram);
            }
            swap(oyatu_money_to_sum_to_grams, nxt_dp);
        }

        // 特定の金額内で，おやつと弁当をいくつか購入した時の，最大の質量
        vector<int> sum_to_max_grams(MAX_MONEY + 1, 0);
        rep(i, MAX_MONEY + 1)rep(j, MAX_OYATU + 1)sum_to_max_grams[i] = max(sum_to_max_grams[i], oyatu_money_to_sum_to_grams[j][i]);

        // 購入する飲み物の質量を固定し，最大の質量を探索
        int ans = 0;
        for(int nomimono_gram = MIN_NOMIMONO;nomimono_gram < WEIGHT_LENGTH;nomimono_gram++)
            if(
                gram_to_min_price[nomimono_gram] != INF && 
                MAX_MONEY - gram_to_min_price[nomimono_gram] >= 0
            )ans = max(ans, nomimono_gram + sum_to_max_grams[MAX_MONEY - gram_to_min_price[nomimono_gram]]);
        
        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}
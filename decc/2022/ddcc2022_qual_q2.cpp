/*アルゴリズムと工夫点(鯖。/CPU: - ms Memory: - KB  Length: - B)
"SABA" と "kobone" の区間（添え字の配列）をそれぞれ求めてから，"SABA"の区間に完全に含まれている"kobone"を削除すればよい．
最悪計算量は，入力文字列S とすると，O(|S|) < 10 ^ 3 となり，十分高速．
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

// vector<string> ipt = {
//     "SkoAboBneA",
//     "SkobAoneBASAKESABkoAboneSAkoboneMEkoSAboneBASAB",
//     "SAkoBbohoneneAumiSAkoboBAishikSoAkoboSAneUNIBAwakamekoboSneBAAkoBASbonekobonekoboneABASAkobone"
// };
vector<string> ipt = {
    "SkoboAneBASAkokkoboBneSkoSbAoneBASkkoobkobonekobonekoboneABA",
    "SABkoAboneSAKkoEbonBeORASABSSAkoBbohireneASkobAobeBASASABAUNIBASABASAhaBrawataASAkoBbone",
    "SABASAKESABSSABkoboAnekobonekoSboABnAeShiArekBoboneASAkoboBneSSABABORASkoAboneBAgomiSASAkoBbAoneBA"
};
Outputer<string> answer;
const string kobone = "kobone", saba = "SABA";
const char NIL = '*';

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto str = ipt[ipt_id];

        auto searchSections = [&](const string& target) -> vector<vector<int> >{
            vector<int> target_ids;
            int target_i = 0;
            vector<vector<int> > ans;

            rep(i, str.size()){
                if(str[i] == target[target_i]){
                    target_ids.push_back(i);
                    target_i++;
                }

                if(target_i == target.size()){
                    ans.push_back(target_ids);
                    
                    target_i = 0;
                    vector<int> nxt = vector<int>(0);
                    swap(target_ids, nxt);
                }
            }

            return ans;
        };
        auto kobone_sections = searchSections(/* target = */ kobone);
        auto saba_sections = searchSections(/* target = */ saba);

        int k_i = 0;
        for(auto saba_section : saba_sections){
            int saba_start = saba_section.front();
            int saba_last = saba_section.back();

            while(k_i < kobone_sections.size() && kobone_sections[k_i].front() < saba_last){
                int kobone_start = kobone_sections[k_i].front();
                int kobone_last = kobone_sections[k_i].back();
                
                auto calcCommon = [](int l1, int r1, int l2, int r2) -> int{
                    return min(r1, r2) - max(l1, l2);
                };
                if(calcCommon(
                    /* l1 = */ saba_start, 
                    /* r1 = */ saba_last, 
                    /* l2 = */ kobone_start, 
                    /* r2 = */ kobone_last) == kobone_last - kobone_start
                )for(int id : kobone_sections[k_i])str[id] = NIL;

                k_i++;
            }
        }
        
        string ans = "";
        for(char c : str)if(c != NIL)ans += c;
        answer.push(/* value = */ ans);
    }

    answer.output(/* prefix = */ "\"", /* suffix = */ "\"");
    return 0;
}
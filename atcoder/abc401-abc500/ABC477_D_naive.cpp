#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n, q;

int main(){
    int i, j;

    scanf("%d%d", &n, &q);
    string tile_color = string(/* count = */ n, /* ch = */ 'a');
    vector<bool> is_tile_exist(tile_color.size(), false);

    while(q--){
        scanf("%d", &i);
        if(i == 1){
            int x;
            scanf("%d", &x);
            x--;

            is_tile_exist[x] = !is_tile_exist[x];
        }else{
            char c;
            scanf(" %c", &c);

            rep(i, tile_color.size())if(!is_tile_exist[i])tile_color[i] = c;
        }
    }

    cout << tile_color << endl;
    return 0;
}
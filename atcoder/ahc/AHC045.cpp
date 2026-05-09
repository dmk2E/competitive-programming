/*アルゴリズムと工夫点(Oracle-Guided Road Network Planning/CPU: 373 ms Memory: 68720 KB  Length: 14076 B)
座圧+累積和で2次元平面上における，マス毎の，そのマスに存在する可能性がある都市の数を前処理で求めておく．
その後，マス数の降順に，マスの連結成分に存在する可能性がある都市群を一つの集合として扱う．
一つしかないものは，存在可能性範囲の中心座標を見て，最も群の中心座標（連結成分の中心座標）に近いものに追加していった．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<random>
#include<chrono>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

class TimeKeeper{
    int64_t time_threshold_;
    chrono::high_resolution_clock::time_point start_time_;
public:
    /// @brief タイムキーパー用クラス
    /// @param time_threshold 制限時間 (ms)
    TimeKeeper(int64_t time_threshold):time_threshold_(time_threshold),start_time_(chrono::high_resolution_clock::now()){}

    /// @brief 制限時間超過してるか判定
    /// @return 制限時間超過したか否か
    bool isTimeOver()const{
        auto diff=chrono::high_resolution_clock::now()-this->start_time_;
        return chrono::duration_cast<chrono::milliseconds>(diff).count()>=this->time_threshold_;
    }
};

typedef class CordinatedCompression{
    bool initiated;
    vector<int> xs;
public:
    CordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }
private:
    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }
public:
    /// @brief 要素を追加する関数
    /// @param x 追加する座標
    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    /// @brief 座標圧縮後の座標総数を返す
    /// @return 座圧後の座標総数
    int size(){
        if(!initiated)init();
        return xs.size();
    }
}CC;

struct City{
    int id_,lx_,rx_,ly_,ry_;

    City(int id=0,int lx=0,int rx=0,int ly=0,int ry=0):id_(id),lx_(lx),rx_(rx),ly_(ly),ry_(ry){}
};

typedef pair<int,int> P;

struct Data{
    int id_,sum_;
    vector<int> cities_;
    vector<P> edges_;

    Data(int id=0,int sum=0):id_(id),sum_(sum){
        this->cities_=vector<int>();
        this->edges_=vector<P>();
    }

    void query(int start,int cnt){
        int i;
        printf("? %d ",cnt);
        rep(i,cnt-1)printf("%d ",this->cities_[start+i]);
        printf("%d\n",this->cities_[start+i]);
        cout<<flush;
    }

    void answer(){
        int i;
        rep(i,this->cities_.size()-1)printf("%d ",this->cities_[i]);
        printf("%d\n",this->cities_[i]);
        rep(i,this->edges_.size())printf("%d %d\n",this->edges_[i].first,this->edges_[i].second);
    }
};

int n,m,q,l,w;
const int64_t TIME_THRESHOLD=1900;
const int64_t TIME_THRESHOLD_FOR_MAKE=1500;

/// @brief 存在可能性範囲のIOUの値によって，各都市を連結するか決定する
/// @param ipt 各都市の存在可能性範囲
/// @return 連結成分の集合が返される
vector<vector<int> > makeUnion1(vector<City>& ipt){
// Operation::Make unions::1 (共通範囲を持つ->連結させた方が良い という傾向が見られる)
    int i,j;
    vector<vector<int> > adj(n);
    vector<vector<int> > unions;

    vector<bool> vis(n,false);
    auto isAdjacent=[&](int a,int b)->bool{
        // IOU_Score(0.00): 30,058,981 / 50,000,000,000
        return (max(ipt[a].lx_,ipt[b].lx_)<=min(ipt[a].rx_,ipt[b].rx_))&&(max(ipt[a].ly_,ipt[b].ly_)<=min(ipt[a].ry_,ipt[b].ry_));

        // IOU_Score(0.0625): 40,081,935 / 50,000,000,000
        // IOU_Score(0.125):  46,756,020 / 50,000,000,000
        // IOU_Score(0.25):   59,447,562 / 50,000,000,000
        // IOU_Score(0.50):   86,629,723 / 50,000,000,000 
        // int a_area=(ipt[a].rx_-ipt[a].lx_)*(ipt[a].ry_-ipt[a].ly_),b_area=(ipt[b].rx_-ipt[b].lx_)*(ipt[b].ry_-ipt[b].ly_),inter_area=max(min(ipt[a].rx_,ipt[b].rx_)-max(ipt[a].lx_,ipt[b].lx_),0)*max(min(ipt[a].ry_,ipt[b].ry_)-max(ipt[a].ly_,ipt[b].ly_),0);
        // return inter_area*16>(a_area+b_area-inter_area);
    };
    rep(i,n)rep(j,i){
        if(isAdjacent(i,j)){
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    auto bfs=[&](int now)->void{
        int i,j;
        queue<int> que;
        vis[now]=true;
        unions.push_back(vector<int>(1,now));
        que.push(now);
        while(que.size()){
            now=que.front();que.pop();
            rep(i,adj[now].size()){
                if(vis[adj[now][i]]==false){
                    que.push(adj[now][i]);
                    unions[unions.size()-1].push_back(adj[now][i]);
                    vis[adj[now][i]]=true;
                }
            }
        }
    };
    rep(i,n)if(vis[i]==false)bfs(i);
    return unions;
}

struct Point{
    int id_;
    double y_,x_;

    Point(int id,double y,double x):id_(id),y_(y),x_(x){}

    Point operator-(const Point& k)const{
        return Point(id_,y_-k.y_,x_-k.x_);
    }

    bool operator<(const Point& k)const{
        return y_==k.y_?x_<k.x_:y_<k.y_;
    }

    double norm(){
        return y_*y_+x_*x_;
    }
};

/// @brief 存在可能性範囲が多い箇所を共有している都市を，一つの集合とする
/// @param ipt 入力都市情報
/// @param time_threshold 実行時間制限
/// @return 連結した集合
vector<vector<int> > makeUnion2(vector<City>& ipt,int64_t time_threshold){
// Score: 53,653,104 / 50,000,000,000 (余り物を1個として独立させていたVer)
// Score: 43,220,246 / 50,000,000,000
    TimeKeeper time_keeper(time_threshold);
    int i,j;
    vector<vector<int> > unions;
    queue<City> cities;
    CC xs,ys,ws;

    rep(i,n){
        cities.push(ipt[i]);
        //printf("id:%d(%d %d %d %d)\n",ipt[i].id_,ipt[i].lx_,ipt[i].rx_,ipt[i].ly_,ipt[i].ry_);
        xs.add(ipt[i].lx_);
        xs.add(ipt[i].lx_+1);
        xs.add(ipt[i].rx_);
        xs.add(ipt[i].rx_+1);
        ys.add(ipt[i].ly_);
        ys.add(ipt[i].ly_+1);
        ys.add(ipt[i].ry_);
        ys.add(ipt[i].ry_+1);
    }
    vector<vector<int> > imos(ys.size(),vector<int>(xs.size(),0));
    rep(i,n){
        imos[ys(ipt[i].ly_)][xs(ipt[i].lx_)]++;
        imos[ys(ipt[i].ly_)][xs(ipt[i].rx_+1)]--;
        imos[ys(ipt[i].ry_+1)][xs(ipt[i].lx_)]--;
        imos[ys(ipt[i].ry_+1)][xs(ipt[i].rx_+1)]++;
    }
    rep(i,ys.size())rep(j,xs.size()-1)imos[i][j+1]+=imos[i][j];
    rep(j,xs.size())rep(i,ys.size()-1)imos[i+1][j]+=imos[i][j],ws.add(imos[i+1][j]);
    //rep(i,ys.size()){rep(j,xs.size()-1)printf("%3d ",imos[i][j]);printf("%3d\n",imos[i][j]);}rep(i,ws.size()-1)printf("%d ",ws[i]);printf("%d\n",ws[i]);//Output4Debug

    // imos:座圧後平面における，存在可能性範囲の被りの数を示す
    // 被りの数が多いところを重心と捉え，連結成分を作成してみる
    // ws:被りの数を重みとみて，その数を座圧して保持．
    vector<vector<City> > w_to_square(ws.size());
    vector<vector<bool> > vis(ys.size(),vector<bool>(xs.size(),false));
    const int dy[]={-1,0,1,0};
    const int dx[]={0,1,0,-1},MAX_D=4;

    auto bfs=[&](P now)->City{
        int i,j,max_y,max_x,min_y,min_x,cnt=1,y,x,c;
        queue<P> que;
        c=imos[now.first][now.second];
        que.push(now);
        vis[now.first][now.second]=true;
        min_y=max_y=now.first;
        min_x=max_x=now.second;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<ys.size()&&0<=x&&x<xs.size()&&vis[y][x]==false&&imos[y][x]==c){
                    vis[y][x]=true;
                    que.push(P(y,x));
                    min_y=min(min_y,y);
                    max_y=max(max_y,y);
                    min_x=min(min_x,x);
                    max_x=max(max_x,x);
                }
            }
        }
        return City(0,xs[min_x],xs[max_x],ys[min_y],ys[max_y]);
    };

    rep(i,ys.size())rep(j,xs.size()){
        if(vis[i][j]==false&&imos[i][j]>0)w_to_square[ws(imos[i][j])].push_back(bfs(P(i,j)));
    }

    auto isConnected=[](City a,City b)->bool{
        return (max(a.lx_,b.lx_)<=min(a.rx_,b.rx_))&&(max(a.ly_,b.ly_)<=min(a.ry_,b.ry_));
    };

    //for(i=ws.size()-1;i>0;i--){printf("w:%d(%ld)\n",ws[i],w_to_square[i].size());/*rep(j,w_to_square[i].size())printf("y:[%d,%d],x:[%d,%d]\n",w_to_square[i][j].ly_,w_to_square[i][j].ry_,w_to_square[i][j].lx_,w_to_square[i][j].rx_);*/}//Output4Debug
    vector<Point> center;
    for(i=w_to_square.size()-1;i>1;i--){
        for(City square:w_to_square[i]){
            if(time_keeper.isTimeOver())break;
            vector<int> u;
            City tmp;
            j=cities.size();
            while(j--){
                tmp=cities.front();cities.pop();
                if(isConnected(square,tmp))u.push_back(tmp.id_);
                else cities.push(tmp);
            }
            if(u.size()>1)unions.push_back(u),center.push_back(Point(unions.size()-1,(square.ly_+square.ry_)/2.0,(square.lx_+square.rx_)/2.0));
            else if(u.size()==1)cities.push(ipt[u[0]]);
        }
        if(time_keeper.isTimeOver())break;
    }
    //rep(i,center.size())printf("(%.5f,%.5f)\n",center[i].y_,center[i].x_);
    //sort(center.begin(),center.end());
    while(cities.size()){
        Point now=Point(0,(cities.front().ly_+cities.front().ry_)/2.0,(cities.front().lx_+cities.front().rx_)/2.0);
        if(center.size()==0){
            center.push_back(now);
            unions.push_back(vector<int>(1,now.id_));
            cities.pop();
            continue;
        }
        /*
        i=lower_bound(center.begin(),center.end(),now)-center.begin();
        if(i==center.size())i--;
        if(i>0&&(center[i-1]-now).norm()<(center[i]-now).norm())i--;
        printf("id:%d(%d %d %d %d)\n",cities.front().id_,cities.front().lx_,cities.front().rx_,cities.front().ly_,cities.front().ry_);printf("(%.5f,%.5f)->(%.5f,%.5f)\n",now.y_,now.x_,center[i].y_,center[i].x_);     
        unions[center[i].id_].push_back(cities.front().id_);
        */
        j=0;
        rep(i,center.size())if((center[j]-now).norm()>(center[i]-now).norm())j=i;
        //printf("id:%d(%d %d %d %d)\n",cities.front().rx_,cities.front().ly_,cities.front().ry_,cities.front().id_,cities.front().lx_);printf("(%.5f,%.5f)->(%.5f,%.5f)\n",now.y_,now.x_,center[j].y_,center[j].x_);
        unions[j].push_back(cities.front().id_);
        cities.pop();
    }
    return unions;
}

int main(){
    TimeKeeper time_keeper(TIME_THRESHOLD);
    int i,j,k,ii;
    // Input
    scanf("%d%d%d%d%d",&n,&m,&q,&l,&w);
    vector<Data> g(m);
    vector<City> ipt(n);
    vector<vector<int> > adj(n);
    rep(i,m){
        scanf("%d",&g[i].sum_);
        g[i].id_=i;
    }
    rep(i,n){
        scanf("%d%d%d%d",&ipt[i].lx_,&ipt[i].rx_,&ipt[i].ly_,&ipt[i].ry_);
        //printf("y:[%d,%d] x:[%d,%d]\n",ipt[i].ry_,ipt[i].ly_,ipt[i].rx_,ipt[i].lx_);// Output4Debug
        ipt[i].id_=i;
    }
    
    // Operation::Make unions
    vector<vector<int> > unions;
    //unions=makeUnion1(ipt);
    unions=makeUnion2(ipt,TIME_THRESHOLD_FOR_MAKE);
    
    // Operation::Union Assignment
    //rep(i,unions.size()){printf("%d:%ld\n",i,unions[i].size());rep(j,unions[i].size())printf("%d ",unions[i][j]);puts("");}//Output4Debug
    std::sort(unions.rbegin(),unions.rend(),[](vector<int>& a,vector<int>& b)->bool{
        return a.size()<b.size();
    });
    std::sort(g.rbegin(),g.rend(),[](Data& a,Data& b)->bool{
        return a.sum_<b.sum_;
    });
    i=j=k=0;
    while(i<unions.size()&&j<m){
        while(k<unions[i].size()&&g[j].cities_.size()<g[j].sum_){
            g[j].cities_.push_back(unions[i][k]);
            k++;
        }
        if(g[j].cities_.size()==g[j].sum_)j++;
        if(k==unions[i].size())i++,k=0;
    }

    // Operation::Query
    rep(i,m){
        if(g[i].cities_.size()==1)continue;
        else if(g[i].cities_.size()==2){
            g[i].edges_.push_back(P(g[i].cities_[0],g[i].cities_[1]));
        }else if(g[i].cities_.size()<=l){
            g[i].query(0,g[i].cities_.size());
            g[i].edges_=vector<P>(g[i].sum_-1);
            rep(j,g[i].edges_.size())scanf("%d%d",&g[i].edges_[j].first,&g[i].edges_[j].second);
            q--;
        }
        if(q<=0)break;
    }
    //rep(i,m){printf("g:%d(%d)\n",i,g[i].sum_);rep(j,g[i].sum_)printf("%d ",g[i].citys_[j]);puts("");}

    i=0;
    j=0;
    while(1){
        while(i<m&&g[i].edges_.size()==g[i].sum_-1)i++,j=0;
        if(q<=0)break;
        if(i==m)break;
        if(time_keeper.isTimeOver())break;
        //printf("size:%d j:%d edge:%ld\n",g[i].sum_,j,g[i].edges_.size());
        ii=min(l,g[i].sum_-j);
        if(ii==2){
            g[i].edges_.push_back(P(g[i].cities_[j],g[i].cities_[j+1]));
            j++;
            continue;
        }
        g[i].query(j,ii);
        rep(k,ii-1){
            g[i].edges_.push_back(P());
            scanf("%d%d",&g[i].edges_.back().first,&g[i].edges_.back().second);
        }
        j+=ii-1;
        q--;
    }
    j++;
    //printf("i:%d j:%d (%ld)\n",i,j,g[i].edges_.size());
    while(i<m&&j<g[i].cities_.size()){
        g[i].edges_.push_back(P(g[i].cities_[0],g[i].cities_[j]));
        j++;
    }
    i++;
    for(;i<m;i++){
        if(g[i].sum_==1||g[i].edges_.size()==g[i].sum_-1)continue;
        rep(j,g[i].cities_.size()-1)g[i].edges_.push_back(P(g[i].cities_[0],g[i].cities_[j+1]));
    }
    // rep(i,m){
    //     rep(j,g[i].citys_.size()-1)g[i].edges_.push_back(P(g[i].citys_[0],g[i].citys_[j+1]));
    // }

    // Output
    puts("!");cout<<flush;
    std::sort(g.begin(),g.end(),[](Data &a,Data &b)->bool{
        return a.id_<b.id_;
    });
    rep(i,m)g[i].answer();
    cout<<flush;
    return 0;
}
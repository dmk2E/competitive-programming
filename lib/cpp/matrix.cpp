#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Matrix{
    vector<vector<T> > mat;
    int height, width;
public: 
    /// @brief 繰り返し自乗法で行列累乗を高速に計算する
    /// @param mat (Matrix): 被累乗行列
    /// @param expo (int): 累乗数
    /// @return Matrix: 行列累乗結果
    static Matrix<T> power(const Matrix<T>& mat, ll expo){
        auto ans = Matrix<T>(vector<vector<T> >{{1, 0}, {0, 1}});
        auto now_mat = mat;
        while(expo > 0){
            if(expo & 1)ans = ans * now_mat;
            now_mat = now_mat * now_mat;
            expo >>= 1;
        }
        return ans;
    }

private:
    bool assertSameSize(const Matrix& mat1, const Matrix& mat2)const{
        assert(mat1.height == mat2.height && mat1.width == mat2.width);
    }

public:
    Matrix(vector<vector<T> > arr = vector<vector<T> >{{1, 1}, {1, 0}}){
        this -> mat = arr;
        this -> height = mat.size();
        this -> width = mat[0].size();
    }

    Matrix(vector<vector<T> >& arr){
        this -> mat = mat;
        this -> height = mat.size();
        this -> width = mat[0].size();
    }

    vector<T>& operator[](const int index){
        return this -> mat[index];
    }

    const Matrix operator+(Matrix& other)const{
        this -> assertSameSize(this -> mat, other);
        int y, x;
        Matrix ans = Matrix(vector<vector<T> >(this -> height, vector<T>(other.width)));
        rep(y, this -> height)rep(x, this -> width)
            ans[y][x] = this -> mat[y][x] + other[y][x];
        return ans;
    }

    const Matrix operator-(Matrix& other)const{
        this -> assertSameSize(this -> mat, other);
        int y, x;
        Matrix ans = Matrix(vector<vector<T> >(this -> height, vector<T>(other.width)));
        rep(y, this -> height)rep(x, this -> width)
            ans[y][x] = this -> mat[y][x] - other[y][x];
        return ans;
    }

    const Matrix operator*(Matrix& other)const{
        assert(this -> width == other.height);
        int y, x, i;
        Matrix ans = Matrix(vector<vector<T> >(this -> height, vector<T>(other.width, 0)));
        rep(y, this -> height)rep(x, other.width)rep(i, this -> width)
            ans[y][x] += this -> mat[y][i] * other[i][x];
        return ans;
    }

    const void show()const{
        int i, j;
        rep(i, this -> height){
            rep(j, this -> width - 1)cout << this -> mat[i][j] << ' ';
            cout << this -> mat[i][j] << '\n';
        }
    }
};

int main(){
    // 行列積お試し
    Matrix<ll> mat1({{1, 2}, {1, 2}}), mat2({{1, 2, 3}, {1, 2, 3}});
    const auto mul_mat = mat1 * mat2;
    mul_mat.show();

    // 行列累乗お試し
    while(1){
        int x;
        printf("単位行列に対する累乗数を入力してください：");
        scanf("%d", &x);
        Matrix<ll> mat(vector<vector<ll> >{{1, 1}, {1, 0}});
        auto ans = Matrix<ll>::power(mat, x);
        ans.show();puts("");
    }
    return 0;
}
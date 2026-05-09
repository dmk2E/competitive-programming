'''アルゴリズムと工夫点(Pyramid/CPU: 98 ms Memory: 143404 KB  Length: 1575 B)
逆元を用いた組み合わせを用いて解く．
配列Aの各要素の加算回数は，最上段に到達するまでの道順の数であり，
左からi番目の要素は，(N - 1) C (i - 1) だけの組み合わせがある．
最悪計算量は，O(N) < 10 ^ 6 となり十分高速．
'''
class Combination:

    """
    組合せ nCr を計算するクラス

    params:
        n: 扱う整数の最大値
    """
    class ArgError(Exception):
        def __init__(self, message = "引数の大小関係が不正です"): 
            super().__init__(message)

    def _power(self, a: int, b: int) -> int:
        ans = 1
        while b > 0:
            if b & 1 :
                ans = (ans * a) % self.MOD
            b >>= 1
            a = (a * a) % self.MOD
        return ans

    def __init__(self, n: int, MOD: int = int(1e9) + 7):
        self.MOD = MOD
        self.n = n
        self.fact = [1 for _ in range(n + 1)]
        self.inv_fact = [1 for _ in range(n + 1)]  
        self.fact[0] = 1
        for i in range(n):
            self.fact[i + 1] = (self.fact[i] * (i + 1)) % self.MOD
        self.inv_fact[n] = self._power(self.fact[n], self.MOD - 2)
        for i in range(n - 1, -1, -1):
            self.inv_fact[i] = (self.inv_fact[i + 1] * (i + 1)) % self.MOD

    def _judge(self, x: int) -> bool:
        return 0 <= x and x <= self.n

    def comb(self, n: int, r: int) -> int:
        global ArgError
        if n < r or not(self._judge(n)) or not(self._judge(r)):
            raise ArgError()
        return (((self.fact[n] * self.inv_fact[n - r]) % self.MOD) * self.inv_fact[r]) % self.MOD

n = int(input())
arr_a = list(map(int, input().split()))
ans = 0

comb = Combination(n)
for i, a in enumerate(arr_a):
    ans = (ans + (a * comb.comb(n - 1, i)) % comb.MOD) % comb.MOD
print(ans)
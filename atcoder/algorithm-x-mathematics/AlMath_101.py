'''アルゴリズムと工夫点(Don't be too close（★6）/CPU: 213 ms Memory: 110556 KB  Length: 2029 B)
逆元を利用して解く．
書かれている整数の差がk以上になるボールの選び方を求める問題を「問題k」とする．
問題kは，条件を満たすような，1個のボールの選び方，2個のボールを選び型，... ceil(N / k)個のボールの選び方の総和を求めればよい．
各小問題は，二項係数を用いて高速に計算して解く（詳細は公式解説へ）．
最悪計算量は，O(log2(MOD) + N * log2(N)) < 10 ^ 7 となり高速．
'''
import sys

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

    def __init__(self, max_num: int, MOD: int = int(1e9) + 7):
        self.MOD = MOD
        self.max_num = max_num
        self.fact = [1 for _ in range(max_num + 1)]
        self.inv_fact = [1 for _ in range(max_num + 1)]  
        self.fact[0] = 1
        for i in range(max_num):
            self.fact[i + 1] = (self.fact[i] * (i + 1)) % self.MOD
        self.inv_fact[max_num] = self._power(self.fact[max_num], self.MOD - 2)
        for i in range(max_num - 1, -1, -1):
            self.inv_fact[i] = (self.inv_fact[i + 1] * (i + 1)) % self.MOD

    def _judge(self, x: int) -> bool:
        return 0 <= x and x <= self.max_num

    def comb(self, n: int, r: int) -> int:
        global ArgError
        if n < r or not(self._judge(n)) or not(self._judge(r)):
            raise ArgError()
        return (((self.fact[n] * self.inv_fact[n - r]) % self.MOD) * self.inv_fact[r]) % self.MOD

n = 0
MOD = int(1e9) + 7

def calc_diff_k(k: int, comb: Combination):
    global n, MOD
    ans = 0
    max_num = (n + k - 1) // k
    for num in range(1, max_num + 1): 
        num_comb = comb.comb(
            n=n - (num - 1) * (k - 1), 
            r=num
        )
        ans = (ans + num_comb) % MOD
    return ans

def main(argv: list[str]):
    global n, MOD
    n = int(input())
    comb = Combination(max_num=n, MOD=MOD)
    for k in range(1, n + 1):
        print(calc_diff_k(k=k, comb=comb))

if __name__ == "__main__":
    main(argv=sys.argv[1:])
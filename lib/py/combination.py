class Combination:
    """
    組合せ nCr を計算するクラス

    params:
        max_num: 扱う整数の最大値
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
        if n < r or not(self._judge(n)) or not(self._judge(r)):
            raise self.ArgError()
        return (((self.fact[n] * self.inv_fact[n - r]) % self.MOD) * self.inv_fact[r]) % self.MOD
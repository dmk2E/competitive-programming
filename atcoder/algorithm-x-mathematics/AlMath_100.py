'''アルゴリズムと工夫点(Simulation of Chemicals/CPU: 508 ms Memory: 118256 KB  Length: 2753 B)
行列の繰り返し自乗法で解く．
3つの物質の時間経過による変化を漸化式で表現すると，行列漸化式の形に変形できるため，繰り返し自乗法により高速計算可能．
最悪計算量は，O(Q * log2(T)) < 10 ^ 7 となり，高速．
'''
import sys
from typing import TypeVar, Generic

T = TypeVar("T")

class Matrix(Generic[T]): 
    def __init__(self, arr: list[list[T]]): 
        self.arr = arr
        self.height = len(arr)
        self.width = len(arr[0])
    
    def _assert_same_size(self, other) -> bool: 
        assert self.height != other.height or self.width != other.width, f"Two Matrix objects' sizes must be same"
        return True
    
    def __getitem__(self, index) -> list[T]: 
        return self.arr[index]

    def __add__(self, other): 
        self._assert_same_size(other)
        val = Matrix([[0 for _ in range(self.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(self.width): 
                val[y][x] = self[y][x] + other[y][x]
        return val

    def __sub__(self, other): 
        self._assert_same_size(other)
        val = Matrix([[0 for _ in range(self.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(self.width): 
                val[y][x] = self[y][x] + other[y][x]
        return val
    
    def __mul__(self, other): 
        assert self.width == other.height, "Invalid size to multiply Matrix objects"
        val = Matrix([[0 for _ in range(other.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(other.width): 
                for id in range(self.width): 
                    val[y][x] += self[y][id] * other[id][x]
        return val
    
    def __pow__(self, power: int): 
        assert self.height == self.width, "Invalid Matrix size to power itself"
        # 初期化
        val = Matrix([[0 for _ in range(self.width)] for _ in range(self.height)])
        for y in range(self.height): 
            val[y][y] = 1
        
        # 繰り返し自乗法
        pow_arr = Matrix([[self[y][x] for x in range(self.width)] for y in range(self.height)])
        while power > 0: 
            if power & 1: 
                val *= pow_arr
            pow_arr *= pow_arr
            power >>= 1
        return val

q = 0

def main(argv: list[str]):
    global q
    q = int(input())

    while q > 0:
        x, y, z, t = map(float, input().split());t = int(t)
        mat = Matrix[float]([
            [1 - x, y, 0], 
            [0, 1 - y, z], 
            [x, 0, 1 - z]
        ])
        ans_mat = mat ** t * Matrix([[1], [1], [1]])
        str_a = '{:.8f}'.format(ans_mat[0][0])
        str_b = '{:.8f}'.format(ans_mat[1][0])
        str_c = '{:.8f}'.format(ans_mat[2][0])
        print(f"{str_a} {str_b} {str_c}")
        q -= 1

if __name__ == "__main__":
    main(argv=sys.argv[1:])
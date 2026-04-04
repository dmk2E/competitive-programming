from typing import TypeVar, Generic

T = TypeVar("T")

class Matrix(Generic[T]): 
    """
    行列計算のためのクラス

    params:
        arr(list[list[T]]): 初期値
    """
    # 例外処理クラス定義
    class MatrixSameSizeError(Exception): 
        def __init__(
            self, 
            message: str = "Two Matrix objects' sizes must be same"
        ): 
            super().__init__(message)
    
    class MatrixMultiplyError(Exception): 
        def __init__(
            self, 
            message: str = "Invalid size to multiply Matrix objects"
        ): 
            super().__init__(message)

    class MatrixPowerError(Exception): 
        def __init__(
            self, 
            message: str = "Invalid Matrix size to power itself"
        ): 
            super().__init__(message)
    
    # エラー処理用メソッド
    def _assert_same_size(self, other): 
        if self.height != other.height or self.width != other.width: 
            raise self.MatrixSameSizeError()
    
    def _assert_valid_size_to_multiply(self, other): 
        if self.width != other.height: 
            raise self.MatrixMultiplyError()
    
    def _assert_valid_size_to_power(self): 
        if self.height != self.width: 
            raise self.MatrixPowerError()

    # メソッド定義
    def __init__(self, arr: list[list[T]]): 
        self.arr = arr
        self.height = len(arr)
        self.width = len(arr[0])

    def __getitem__(self, index) -> list[T]: 
        return self.arr[index]

    def __add__(self, other): 
        self._assert_same_size(other=other)

        val = Matrix([[0 for _ in range(self.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(self.width): 
                val[y][x] = self[y][x] + other[y][x]
        return val

    def __sub__(self, other): 
        self._assert_same_size(other=other)

        val = Matrix([[0 for _ in range(self.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(self.width): 
                val[y][x] = self[y][x] + other[y][x]
        return val
    
    def __mul__(self, other): 
        self._assert_valid_size_to_multiply(other=other)

        val = Matrix([[0 for _ in range(other.width)] for _ in range(self.height)])
        for y in range(self.height): 
            for x in range(other.width): 
                for id in range(self.width): 
                    val[y][x] += self[y][id] * other[id][x]
        return val
    
    def __pow__(self, power: int): 
        self._assert_valid_size_to_power()

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

if __name__ == "__main__": 
    mat1 = Matrix[int](arr=[[1, 2, 3], [1, 2, 3]])
    mat2 = Matrix[int](arr=[[1, 2], [1, 2], [1, 2]])
    print((mat1 * mat2).arr)
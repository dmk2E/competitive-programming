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
'''アルゴリズムと工夫点(Sqrt Inequality/CPU: 53 ms Memory: 80108 KB  Length: 147 B)
式変形により解く．
浮動小数点が絡む計算では，誤差が含まれるため，整数型同士の演算に変形する．

- 式変形 ---
√a + √b < √c 両辺正より二乗して
a + 2 * √ab + b < c 
2 * √ab < c - a - b ... (i)
a + b < c の時，両辺正であるから二乗して，
4 * a * b < (c - a - b) ^ 2
a + b >= c の時，式(i)の右辺は負となり，条件式が満たされることは無い．
------

最悪計算量は，O(1) となり十分高速．
'''
a, b, c = map(int, input().split())

if a + b >= c:
    print("No")
else :
    print("Yes" if 4 * a * b < (c - b - a) * (c - b - a) else "No")
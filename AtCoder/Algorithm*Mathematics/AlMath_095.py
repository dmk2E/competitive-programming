'''アルゴリズムと工夫点(Score Sum Queries（★2）/CPU: 447 ms Memory: 111024 KB  Length: 666 B)
累積和を用いて解く．
1組と2組ずつ累積和を前計算し，各クエリに答えていけばよい．
最悪計算量は，O(N + Q) < 10 ^ 6 となり十分高速．
'''
import sys

n, q = 0, 0

def main(argv: list[str]):
    global n, q

    n = int(input())
    sum_1 = [0] * (n + 1)
    sum_2 = [0] * (n + 1)
    for i in range(n):
        c, p = map(int, input().split())
        if c == 1: 
            sum_1[i + 1] = p
        else: 
            sum_2[i + 1] = p
    for i in range(n): 
        sum_1[i + 1] += sum_1[i]
    for i in range(n): 
        sum_2[i + 1] += sum_2[i]
    
    q = int(input())
    while q > 0: 
        l, r = map(int, input().split())
        print(f"{sum_1[r] - sum_1[l - 1]} {sum_2[r] - sum_2[l - 1]}")
        q -= 1

if __name__ == "__main__":
    main(argv=sys.argv[1:])
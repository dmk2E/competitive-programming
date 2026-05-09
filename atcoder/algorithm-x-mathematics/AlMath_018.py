'''アルゴリズムと工夫点(Convenience Store 1/CPU: 76 ms Memory: 106752 KB  Length: 170 B)
今回の問題のように与えられる値の種類数が少ない時，値の種類ごとに何らかの値を保持して置き，そこから答えを求める形を取ることができる．
詳しいアルゴリズムは参考書を参照．
'''
n=int(input())
a=list(map(int,input().split()))
count=[0 for _ in range(0,4)]

for aa in a:
    count[(aa-100)//100]+=1

print(count[0]*count[3]+count[1]*count[2])
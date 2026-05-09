'''アルゴリズムと工夫点(Choose Cards 1/CPU: 117 ms Memory: 157928 KB  Length: 180 B)
演習問題18のように与えられる値の種類数が少ない時，値の種類ごとに何らかの値を保持して置き，そこから答えを求める形を取ることができる．
今回は，高校数学Aの数え上げの知識を用いる．
詳しいアルゴリズムは参考書を参照．
'''
n=int(input())
a=list(map(int,input().split()))

color=[0]*3
for aa in a:
    color[aa-1]+=1
print(color[0]*(color[0]-1)//2+color[1]*(color[1]-1)//2+color[2]*(color[2]-1)//2)
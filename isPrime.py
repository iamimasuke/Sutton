import math 

n=int(input("整数を入力してください："))



def isPrime(x):
    root = int(math.sqrt(x))
    for i in range(2,root+1):
        if x % i == 0:
            print(str(x)+"は素数ではありません")
            break
        if i == root:
            print(str(x)+"は素数です。")
    
isPrime(n)


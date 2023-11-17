def isPrime(n):
    for i in range(2,n):
        if n%i == 0:
            print(str(n)+"は素数ではない")
        else:
            print(str(n)+"は素数")
            
isPrime(28)


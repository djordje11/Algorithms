 

ks = [0] * 100000
power_of_twos = [1] * 100000

moduo = 1000000007

def mul(x, y):
    return (x*y)%moduo if x * y >= moduo else x * y

def add(x, y):
    return (x+y)%moduo if x + y >= moduo else x + y


def main():
    t = int(input())

    ns = list(map(int, input().split()))
    ks = list(map(int, input().split()))


    for i in range(1,100000):
        power_of_twos[i] = mul(2, power_of_twos[i-1])


    for i in range(t):
        if ns[i] == ks[i]:
            print(1)
        else:
            print(power_of_twos[ks[i]])



if __name__ == "__main__":
    main()

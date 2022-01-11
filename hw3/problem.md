# Unit 3: Homework 3

## 0.udpspoof

FlagServ 是一个基于 UDP 的网络服务，位于 udpspoof_cn.cse545.io:13337。该服务仅接
受来自所谓“安全 IP”的 UDP 包。如果用户在 UDP 包中提供了 IP 地址，那么 FlagServ 会
把一个特定字符串（flag）通过 UDP 发送到用户指定的 IP 地址(请使用你的172.16.20.X地址，下同)的 13337 端口。

FlagServ 使用了世界上最好的认证方式：基于源 IP 的认证，这是因为没有任何人能够伪
造源 IP。目前 FlagServ 只相信来自 10.2.4.10 的 UDP 包。

你的任务是绕过这个基于源 IP 的认证方式，向 FlagServ 发送你的IP（172.16.20.X地址）。
FlagServ收到你的IP后，会将它的 flag 通过 UDP 发送到你的172.16.20.X IP 的 13337 端口。

你必须先连接到该课程提供的 VPN 才能访问 FlagServ。

完成后，你需要提交如下三个文件：

- 文本文件 `flag.txt`，里面包含你获取到的 flag。
- 文本文件 `readme.txt`，里面应当用中文或英文简述你的解决方案。如果使用中文，请确保编码为 UTF-8。
- 你的代码。请压缩为 zip 文件并提交，文件名为 `udpspoof.zip`。

提示：

- 用 Scapy 解这道题是最简单的。

## 1. tcpspoof

FlagServ 的维护者发现 UDP 太不安全了。因此他决定将其转移到更安全的协议 —— TCP
上。现在，FlagServ 是一个基于 TCP 的网络服务，位于 tcpspoof_cn.cse545.io:13337。
该服务仅接受来自所谓“安全 IP”的 TCP 连接。用户成功认证并建立连接后，只需提供 IP
地址，FlagServ 就会把一个特定字符串（flag）通过 UDP 发送到用户指定 IP 地址的
13337 端口。

FlagServ 再次使用世界上最优秀的认证方式：基于源 IP 的认证，这是因为没有任何人能够伪
造 TCP 连接的源 IP。同样的，FlagServ 只相信来自 10.2.4.10 的 TCP 包。

你的任务是绕过这个基于源 IP 的认证方式，向 FlagServ 发送你的IP（172.16.20.X地址）。
FlagServ收到你的IP后，会将它的 flag 通过 UDP 发送到你的172.16.20.X IP 的 13337 端口。 
你必须先连接到该课程提供的 VPN 才能访问 FlagServ。

完成后，你需要提交如下三个文件：

- 文本文件 `tcpflag.txt`，里面包含你获取到的 flag。
- 文本文件 `tcpreadme.txt`，里面应当用中文或英文简述你的解决方案。如果使用中文，请确保编码为 UTF-8。
- 你的代码。请压缩为 zip 文件并提交，文件名为 `tcpspoof.zip`。

提示：

- TCP 欺骗的核心在于预测 ACK 值。你应当收集几十个服务器端返回的 ACK 值，并观察它
的特征，找到预测 ACK 值的方法。

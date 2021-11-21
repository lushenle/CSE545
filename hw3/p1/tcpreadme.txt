## Similar to the previous question, using the Scapy framework

**The main steps are as follows:**

- Send a SYN request to the server and observe how it generate seq 
- Use 10.2.4.10 send forged SYN packets, guess its seq
- Use seq + 1 as ack to create TCP connection
- Send payload

## Ref

- https://programmer.help/blogs/fake-tcp-tunneling-with-scapy-to-improve-transmission-performance.html
- https://web.ecs.syr.edu/~wedu/Teaching/cis758/netw522/netwox-doc_html/html/examples.html


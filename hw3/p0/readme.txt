## Solution

Use the `scapy` library to send udp packets directly, just set the source address of the sent packet to the IP 10.2.4.10 as FlagServ believes.
Then use `nc` to listen to the local UDP 13337 port to receive the flag sent by FlagServ.

## Run and get flag

- Listening locally on udp port 13337

```bash
nc -ul 13337
```

- Run the Python script

```bash
python3 udpspoof.py
```


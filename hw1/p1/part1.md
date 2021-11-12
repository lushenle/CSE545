# Part 1 Solution

> I use Msieve. Msieve is a C library implementing a suite of algorithms to factor large integers.

## Factoring N

- use Msieve

> on ubuntu

```bash
sudo apt install -y build-essential libgmp3-dev zlib1g-dev libecm-dev
wget https://jaist.dl.sourceforge.net/project/msieve/msieve/Msieve%20v1.53/msieve153_src.tar.gz
tar xvf msieve153_src.tar.gz
cd msieve-1.53
make all ECM=1
```

```bash
./msieve -q 84692954109552769374106613978990493265631425360379150170786955314741169348953

84692954109552769374106613978990493265631425360379150170786955314741169348953
p39: 264515818482660146971535304176490802643
p39: 320181056072095218868339092717483179171
```


**or**

- http://factordb.com/

## Decrypt RSA

- Run `part1.py` on ubuntu


---

## RsaCtfTool Decrypt

```bash
./RsaCtfTool.py -n 84692954109552769374106613978990493265631425360379150170786955314741169348953 \
    -e 65537 \
    --uncipher 21698323120385586424573862118808098555103084743518277473544693629498197679429
```

## Reference

- http://factordb.com/
- https://ctftime.org/writeup/14547
- https://github.com/Ganapati/RsaCtfTool

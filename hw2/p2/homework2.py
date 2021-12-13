# coding=utf-8
import lib


# 1.找一段明文，例如gzip格式的头，包含的文件名等
# 2.去和密文xor，然后试0-7位的右移得到密码，密码是ASCII码
# 3.观察密码，确定密码长度（出现循环）
# 4.解码整个文件，能够正常解压，完成


# 解题思路：
# 1.按照gzip文件格式，1-10个字节是固定的
# 2.从第11个字节开始gzip里后面包含了文件名称
# 3.通过文件明文 文件名称“secretfile.txt” 按照 加密后的字节 = bit_rotate(原始字节, N) xor 密钥字节
# 先左循环左移N=5位，再与密文xor异或，等到key密钥  N=5编程试出来的
# 4. 明文=（密文xor密钥,结果再循环右移5位）  a^b=c 则 a=b^c
# 5.写入文件时的关键语句：buffer+=afterShiftInt.to_bytes(1,byteorder="little")

# k>0 circle left shift, k<0 circle right shift
def shift(lst, k):
    lst = str(bin(lst)).lstrip('0b')
    if len(lst) < 8:
        lst = "0" * (8 - len(lst)) + lst
    # print('移位前8位二进制字符串：', lst)
    return lst[k:] + lst[:k]


# 16 hexadecimal
def read_file(path):
    with open(path, 'rb') as file_byte:
        file_hex = file_byte.read()
        return file_hex


filenameHex = '73656372657466696c652e747874'  # secretfile.txt 在线网站转的16进制
key_byte = '53454352455450415353'  # 16进制 SECRETPASS

secretContentHex = read_file(path='secretfile.txt.gz.enc')
print(secretContentHex)
print(filenameHex)
# print(len(newCreateHex),newCreateHex)

##########解密钥，解N###############
for N in range(2, 10):
    keyString = ""
    for i in range(0, len(secretContentHex)):
        if (i + 10 >= len(secretContentHex)):
            break
        secretNum = secretContentHex[i + 10]
        filenameHexNum = filenameHex[(2 * i) % (len(filenameHex)):(2 * i) % (len(filenameHex)) + 2]
        filenameHexInt = lib.zhuan_jing_zhi(16, 10, filenameHexNum)
        afterShift = shift(filenameHexInt, N)  # 循环左移N位
        if len(afterShift) < 8:
            afterShift = "0" * (8 - len(afterShift)) + afterShift
        afterShiftInt = lib.zhuan_jing_zhi(2, 10, afterShift)
        keyInt = secretNum ^ afterShiftInt
        afterShiftHex = lib.zhuan_jing_zhi(10, 16, keyInt)
        try:
            keyText = lib.jing_zhi_zhuan_zhi_fu(afterShiftHex)
            keyString += str(keyText).lstrip('b\\x') + ","
        except:
            continue
    print("N:", N, "keyString:", keyString)

##########解出了密钥，解明文，并写入.gz文件###############
buffer = b''
N = 5
for i in range(0, len(secretContentHex)):
    secretNum = secretContentHex[i]
    key_byteHexNum = key_byte[(2 * i) % (len(key_byte)):(2 * i) % (len(key_byte)) + 2]
    key_byteHexNum = lib.zhuan_jing_zhi(16, 10, key_byteHexNum)
    plainInt = secretNum ^ key_byteHexNum
    afterShift = shift(plainInt, -N)
    if len(afterShift) < 8:
        afterShift = "0" * (8 - len(afterShift)) + afterShift
    afterShiftInt = lib.zhuan_jing_zhi(2, 10, afterShift)
    buffer += afterShiftInt.to_bytes(1, byteorder="little")
print()
print(buffer)

with open('secretfile.txt.gz', 'wb') as file_byte:
    file_byte.write(buffer)

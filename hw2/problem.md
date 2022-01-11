# Unit 2: Homework 2

## Part 0 smart hacker

有人说，只有最牛的黑客才用非对称加密……

你的任务如下：

1. 使用 GnuPG 为你的 ASU 电子邮件地址创建一个公私钥对。

2. 新建一个包含如下内容的纯文本文件：

你的名字（在 my.asu.edu 系统中的名字）
你的网名（和作业 0 中的要求相同）
你的邮件地址
你的 ASURITE ID（纯数字的那个）

如果使用中文的话，请保证编码为 UTF-8。

将这个纯文本文件存成 hacker.txt。

3. 从这里（https://rev.fish/cse545/cse545_fall2021.asc）下载这门课专属的公钥。将它导入到你的 GnuPG 钥匙串（keyring）中。

4. 通过 GnuPG 使用你自己的私钥为 hacker.txt 签名，并生成一个 clear-signed 签名文件。这个文件的名称应当为 hacker.txt.asc。

5. 通过 GnuPG 用这门课的公钥为这个文件加密，并生成一个 ASCII 模式的（ASCII-armored）加密文件。这个文件的名称应当是 hacker.txt.asc.gpg。

6. 把你的公钥文件重命名为 pubkey.asc。确保 pubkey.asc 是 ASCII 模式的（ASCII-armored），然后将它提交到作业系统中。

7. 把 hacker.txt.asc.gpg 提交到作业系统中。


提示：

- GnuPG 的基础使用请参见第二单元的最后一课。
- 请一定使用 GnuPG 进行上述操作，不要自己实现相关的加密或签名算法！
- 第四步中，你生成的 clear-signed 签名文件中同时包括原始文件和签名。

## Part 1 ssh

请把你的 SSH 公钥提交到作业系统中。公钥文件必须保存并命名为 ssh-key.pub。

## Part 2 badcrypt

Alice 发明了一个非常安全的加密算法。这个算法对文件进行逐字节加密。基本算法如下所示：

```
enc_char = bit_rotate(plain_char, N) xor key_byte
```

中文注释：

```
加密后的字节 = bit_rotate(原始字节, N) xor 密钥字节
```

N 是一个固定的数字，key_byte（密钥字节）是密钥中的一部分，bit_rotate() 是一个对每个字节进行 N 位循环位移的函数。

举个例子：用该算法（N = 3，密钥 = xyz123）对字符串 ABCDEF 进行加密的话，结果如下：

```
第一个字节 = bit_rotate(0x41, 3) xor 0x78
第二个字节 = bit_rotate(0x42, 3) xor 0x79
```

如果密钥比文件长度短，那么加密时，密钥会从开头重新使用。

Alice 在 10/29/2021 亚利桑那时间加密了她的文件。网警截获了这个文件，并放在了作业系统中。你可以在作业系统中下载加密后的文件（名为secretfile.txt.gz）。你能解密这个文件吗？

请将解密后得文件内容保存成一个名为secretfile.txt的文本文件并上传。

提示：

- 假设 bit_rotate() 循环左移所有的比特，那么 bit_rotate(0x41, 3) = bit_rotate(0b01000001, 3) = 0b00001010 = 0x0A。

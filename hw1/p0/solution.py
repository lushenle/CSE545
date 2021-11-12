import base64
from enum import Enum, unique
from Crypto.Cipher import AES


@unique
class Patten(Enum):
    CBC = AES.MODE_CBC
    ECB = AES.MODE_ECB


@unique
class Filling(Enum):
    """ 定义填充的字符串 """
    SPACE = '\x00'


class AES256Crypto:
    def __init__(self, key, mode=Patten.ECB, padding=Filling.SPACE, iv=None):
        """
        :param key: 密钥， 32byte 长度字符串
        :param mode: 加密模式， 来源 class Mode
        :param iv: 16byte 长度字符串
        :param padding: 填充的字符串， 来源 class Padding
        """
        self.padding = self.check_padding(padding)

        self.key = self.padding_key(key)
        self.iv = self.padding_iv(iv) if iv else None

        self.mode = self.check_mode(mode)

    def check_mode(self, mode):
        """ 核对 mode """
        if mode not in Patten.__members__.values():
            raise Exception(f'mode {mode} not allowed!')
        if mode == Patten.CBC and not self.iv:
            raise Exception(f'iv is required')
        return mode

    def check_padding(self, padding):
        """ 核对 padding """
        if padding not in Filling.__members__.values():
            raise Exception(f'mode {padding} not allowed!')
        return padding

    def padding_ret_byte(self, text, _len=16):
        """ 填充并转成 bytes """
        text = text.encode()
        remainder = len(text) % _len
        remainder = _len if remainder == 0 else remainder
        text += (_len - remainder) * self.padding.value.encode()
        return text

    def padding_iv(self, iv: str):
        """ 补全iv 并转成 bytes"""
        if len(iv.encode()) > 16:
            raise Exception(f'iv {iv} must <= 16bytes')
        return self.padding_ret_byte(iv)

    def padding_key(self, key: str):
        """ 补全key 并转成 bytes """
        if len(key.encode()) > 32:
            raise Exception(f'key {key} must <= 32bytes')
        return self.padding_ret_byte(key, _len=32)

    def encrypt(self, text, encode=None):
        """
        加密
        :param text: 待加密字符串
        :param encode: 传入base64里面的方法
        :return: 若encode=None则不进行base加密处理，返回bytes类型数据
        """
        text = self.padding_ret_byte(text)
        # 注意：加密中的和解密中的AES.new()不能使用同一个对象，所以在两处都使用了AES.new()
        text = AES.new(key=self.key, mode=self.mode.value, iv=self.iv).encrypt(text)
        if encode:
            return encode(text).decode()
        return text

    def decrypt(self, text, decode=None):
        """ 解密 """
        if decode:
            if type(text) == str:
                text = text.encode()
            text = decode(bytes(text))
        else:
            if type(text) != bytes:
                raise Exception(text)
        text = AES.new(key=self.key, mode=self.mode.value, iv=self.iv).decrypt(text)
        text = text.strip(self.padding.value.encode())
        return text.decode()


if __name__ == '__main__':
    encrypted_msg = 'bBEUGZApdn9AWs3qKeG+iQ=='
    key = 'crime'
    iv = '\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0'
    aes = AES256Crypto(key, Patten.CBC, Filling.SPACE, iv)
    deco64 = base64.b64decode(encrypted_msg)
    print("encrypted_msg " + str(deco64))
    print(aes.decrypt(deco64))


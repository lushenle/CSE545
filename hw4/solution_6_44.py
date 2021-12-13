import os
import sys
import random
import string
import hashlib


def generate_code():
    alphabet = string.digits + string.ascii_letters
    last_pos = len(alphabet) - 1
    code_len = random.randint(5, 30)
    code = ''

    for _ in range(code_len):
        idx = random.randint(0, last_pos)
        code += alphabet[idx]
    return code


def get_md5(code):
    code_md5 = hashlib.md5(code.encode('utf-8')).hexdigest()
    return code_md5


def solution(level):
    while True:
        code = generate_code()
        m = get_md5(code)
        command = '/challenge/main ' + code
        if level == '6':
            if m[:2] == '00':
                print(f'{code} md5 is: {get_md5(code)}')
                os.system(command)
                sys.exit(0)
        else:
            print(f'code: {code}')
            os.system(command)


if __name__ == '__main__':
    level = sys.argv[1]
    solution(level)


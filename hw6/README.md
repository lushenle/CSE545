# Module 6 & Module 7 Assignment: webexploit

我们课程最后的是关于入侵网站的！我们一共准备了八个网站供大家入侵，分别位于
webexploit.cn.cse545.io 端口 8081 至 8088。你的目标是逐个入侵每一个网站，找到每
个网站上的秘密信息（可能是关键用户的密码、一条消息、一个帖子、银行账户密码等），
然后计算秘密信息的 MD5 散列值。这条散列值将作为下一级网站的入口。因此，你必须从
第一个网站（http://webexploit.cn.cse545.io:8081）开始逐级入侵。（假设第一关的secret是hello，hello的MD５是5d41402abc4b2a76b9719d911017c592,那么第二关的地址就是http://webexploit.cn.cse545.io:8082/ (Links to an external site.)5d41402abc4b2a76b9719d911017c592, 以此类推）

注意你必须连到之前提供的 openvpn 上才能完成该作业。

本次作业的提交在本网站，请创建一个文本文件并命名为webexploit_readme.txt。每破解一关后，请将该关卡的secret（关键用户的密码、一条消息、一个帖子、银行账户密码), 对应的MD5值，以及你的破解方法（以简短的几句话表述）添加到webexploit_readme.txt 里， 直到全部完成后， 保存webexploit_readme.txt。

最后在本网页提交`webexploit_readme.txt`这一个文件即可。

## 提示

### Level 01

阅读并理解页面中的 JavaScript 代码，并从中找到用户名和密码。你可以尝试使用 Burp Suite！

### Level 02

XML HTTP 请求。你需要阅读 HTML 代码来找到隐藏参数。其中一个隐藏参数允许你执行命
令行注入。通过命令行注入，你可以列出服务器上的任何文件夹的内容。

### Level 03

每一条请愿消息（petition messages）都存在特定的文件中。这一关的关键在于预测请愿
消息的文件名。你需要找到 Mike Pence （用他自己的邮箱）提交的消息。

### Level 04

`filename` 参数有目录遍历漏洞。通过控制这个参数，你可以读取文件系统中的任意文
件。会话信息存贮在 /tmp/ 下面。你需要读取用户 mike_pence 的会话，并找到他的密
钥。

但是你并不知道 mike_pence 的会话文件的名称……没关系，你可以用第二关中的漏洞来列出
/tmp/下面的所有文件。

### Level 05

这一关有点儿麻烦。隐藏参数 `admin` 允许读取任意文件。你应该先用这个漏洞读出
retrieve 文件并分析源码。

另外，cookie 中可以提供一个特殊的键，叫做 `blacklist`。这个键也是有漏洞的。

你的目标是拿到 retrieve 和 store 这两个 CGI 脚本的源码，然后你需要伪造 cookie，
使用 site=www.bank.com 和正确的密码来得到用户 `mike_pence` 的秘密信息。

### Level 06

HTTP 头中的某个域允许远程 PHP 文件包含。注意这一关的程序会自动为你提供的 URL 加
上 .php 后缀。

### Level 07

这一关的漏洞是 SQL 注入，但是漏洞点不那么好找。漏洞位于注册流程中，网站检查用户
名是否被占用时。相关代码如下：

```php
/* Checks if a user exists */
$query = "SELECT * FROM users WHERE username='" . $username . "'";
$rs = mysqli_query($db, $query);
if ($rs == false) {
   diefooter("Failed to execute query: " . $query);
}
if (mysqli_num_rows($rs) > 0) {
   print "<p>We found users already registered with this name</p>";
   while ($db_field = mysqli_fetch_assoc($rs) ) {
        print "<p>Username: " . $db_field['username'] . "</p>";   
        print "<p>First: " . $db_field['firstname'] . "</p>";   
        print "<p>Last: " . $db_field['lastname'] . "</p>";
   }   
   diefooter("<p>A user with the specified name already exists.</p>");
}
```

你需要通过 SQL 盲注入得到用户 mike_pence 的密码。

### Level 08

没有提示 :)

其实这一关很简单。你只要耐心（用 Burp Suite 或者浏览器的开发者工具）观察所有流量
就可以了。

可以使用http://webexploit.cn.cse545.io:8100 (Links to an external site.)来验证level08你获得的secret是否正确，用户名可随意使用，level栏位请填level08

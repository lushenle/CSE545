#!/usr/bin/env python2
import sys
import cgi
import random
import os
import tempfile
import Cookie
#debugging
#import cgitb; cgitb.enable()

STORAGE = "/tmp/level05/"

def die(str):
    print "Content-Type: text/html"
    print ""
    print """
  
    
  
  
%s
  
""" % str
    sys.exit(0)


form = cgi.FieldStorage()

if form.has_key("id"):
    id = form["id"].value;
else:
    id = ""
if form.has_key("site"):
    site = form["site"].value;
else:
    site = ""
if form.has_key("admin"):
    admin = form["admin"].value;
else:
    admin = "0"

debug = False
if debug:
    id = "foo1337"
    site = "bar.com"
    admin = "1"

if (id == "" or site == ""):
    die("
Missing parameters.

")

if id.isalnum() == False:
    die("
Bad id.

")

res = list()
    
if admin == "1":
    try:
        site = Cookie.SimpleCookie(os.environ['HTTP_COOKIE'])['site'].value
        password = Cookie.SimpleCookie(os.environ['HTTP_COOKIE'])['password'].value
    except Exception as ex:
        die("
Malformed cookie or missing blacklist name.

")

    if password != 'terriblechoice':
        die("
Wrong password.

")

    for filename in os.listdir(STORAGE):
        fullpath = "%s%s" % (STORAGE, filename)
        if os.path.isfile(fullpath):
            f = open(fullpath, "r")
            for l in f:
                if site in l:
                    res.append(l)
            f.close()
        
    die("
" + '\n'.join(res) + "
")


try:
    f = open(STORAGE + id, "r")
    for l in f:
        if site in l:
            res.append(l)
    f.close()
except Exception, e:
    die("
Cannot retrieve the password. Wrong id?

")

die("
" + '\n'.join(res) + "
")
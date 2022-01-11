#!/usr/bin/env python2
import sys
import cgi
import random
import os
import tempfile
import Cookie
#debugging
#import cgitb; cgitb.enable()

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
if form.has_key("username"):
    username = form["username"].value;
else:
    username = ""
if form.has_key("password"):
    password = form["password"].value;
else:
    password = ""
if form.has_key("admin"):
    admin = form["admin"].value;
else:
    admin = "0"

debug = False
if debug:
    id = "foo1337"
    site = "www.bar.com"
    username = "john"
    password = "pazzword"
    admin = "1"

if (id == "" or site == "" or username == "" or password == ""):
    die("
Missing parameters.

")

if id.isalnum() == False:
    die("
Bad id.

")

if admin == "1":
    try:
        blacklist = Cookie.SimpleCookie(os.environ['HTTP_COOKIE'])['blacklist'].value
    except Exception, e:
        die("
Malformed cookie or missing blacklist name

")
    if blacklist.isalnum() == False:
        die("
Bad blacklist name. It must be alphanumeric.

")
    try:
        f = open(blacklist, "r")
        m = f.read()
        f.close()
    except Exception, e:
        die("
Cannot open blacklist file %s: %s

" % (blacklist, str(e)))

    die("
Blacklist:

%s
" % m)

try:
    f = open("/tmp/level05/" + id, "a+")
    f.write("%s:%s:%s\n" % (site, username, password))
    f.close()
except Exception, e:
    die("
Something went horriby wrong (%s). Contact the admin.

" % str(e))

die("
Password saved.

")

#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ssl
import json
import StringIO
import gzip
import urllib
from httplib import HTTPSConnection

conn = HTTPSConnection('xxx', 443, strict=True)
conn.request('GET', '/')
r = conn.getresponse()
buf = StringIO.StringIO(r.read())
f = gzip.GzipFile(fileobj=buf)
data = f.read()
result = json.loads(data)

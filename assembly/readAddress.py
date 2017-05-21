#! /usr/bin/env python
import re
from sys import argv

if len(argv) == 4:
    pid = argv[1]
    try:
        start = int(argv[2], 16)
    except Exception:
        print("Please enter valid address")
    try:
    	length = int(argv[3])
    except Exception:
        print("Please enter valid length")
else:
    print("Please enter pid, address, len to read")
    exit(-1)

mem_file = open("/proc/%s/mem" % (pid), 'r+', 0)
mem_file.seek(start)  # seek to region start
try:
    data = mem_file.read(length)
except Exception:
    print("Unable to read")
      
print(data)
mem_file.close()

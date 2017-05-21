#! /usr/bin/env python
import re
from sys import argv

if len(argv) == 4:
    pid = argv[1]
    try:
        start = int(argv[2], 16)
    except Exception:
        print("Please enter valid address")
    string = argv[3]
else:
    print("Please enter pid, address, string to write")
    exit(-1)

mem_file = open("/proc/%s/mem" % (pid), 'r+', 0)
mem_file.seek(start)  # seek to region start
try:
    mem_file.write(bytes(string))
except Exception:
    print("Unable to write")
      
mem_file.close()

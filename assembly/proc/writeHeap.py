#! /usr/bin/env python
import re
from sys import argv

if len(argv) == 4:
    pid = argv[1]
    startStr = argv[2]
    replaceStr = argv[3]
else:
    print("Please enter pid, original string, replaced string")
    exit(-1)

maps_file = open("/proc/%s/maps" % (pid), 'r')
mem_file = open("/proc/%s/mem" % (pid), 'r+', 0)
for line in maps_file.readlines():  # for each mapped region
    m = re.match(r'([0-9A-Fa-f]+)-([0-9A-Fa-f]+) (r)([wxp-]+) ([0-9a-f\s:]+) (\[heap\])', line)
    if m:
        start = int(m.group(1), 16)
        end = int(m.group(2), 16)
        mem_file.seek(start)  # seek to region start
        chunk = mem_file.read(end - start)  # read region contents
        try:
            i = chunk.index(bytes(startStr))
	    mem_file.seek(start+i)
	    mem_file.write(bytes(replaceStr))
        except Exception:
            print("Original String not found")
      
maps_file.close()
mem_file.close()

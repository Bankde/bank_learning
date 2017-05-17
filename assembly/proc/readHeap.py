#! /usr/bin/env python
import re
from sys import argv

if len(argv) == 2:
    pid = argv[1]
else:
    print("Please enter pid")
    exit(-1)

maps_file = open("/proc/%s/maps" % (pid), 'r')
mem_file = open("/proc/%s/mem" % (pid), 'r', 0)
for line in maps_file.readlines():  # for each mapped region
    m = re.match(r'([0-9A-Fa-f]+)-([0-9A-Fa-f]+) (r)([wxp-]+) ([0-9a-f\s:]+) (\[heap\])', line)
    if m:
        start = int(m.group(1), 16)
        end = int(m.group(2), 16)
        mem_file.seek(start)  # seek to region start
        chunk = mem_file.read(end - start)  # read region contents
        dump_file = open("dump.%s" % (pid), 'w+')
        dump_file.write(chunk)
        dump_file.close()
maps_file.close()
mem_file.close()

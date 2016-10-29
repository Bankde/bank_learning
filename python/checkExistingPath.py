import os

# check for path
if os.path.exists("checkExistingPath.py"):
    print "checkExistingPath.py exists"
if not os.path.exists("qwerty-random"):
    print "qwerty-random not exists"

# check for file
if os.path.isfile("checkExistingPath.py"):
    print "checkExistingPath.py is file"

# check for dir
if not os.path.isdir("checkExistingPath.py"):
    print "checkExistingPath.py is not directory"

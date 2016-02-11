import sys

def main():
    print sys.argv
    if not sys.stdin.isatty():
        if sys.stdin.readlines() == "": # xargs case will make stdin == [] but not isatty so we need to consider this case too
            print "using xargs"
            # Otherwise reading from sys.argv
        else:
            print "not sys.stdin.isatty"
            print sys.stdin.readlines() # This is reading from input stream
    else:
        print "is sys.stdin.isatty"
        # Otherwise reading from sys.argv

if __name__ == '__main__':
    main()

#result

#cmd: echo "a" | python cmdArgv.py 
#['cmdArgv.py']
#not sys.stdin.isatty
#[]

#cmd: python cmdArgv.py a
#['cmdArgv.py', 'a']
#is sys.stdin.isatty

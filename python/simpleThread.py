import time

def subFunc(name, comment, delay):
	count = 0
	while count < 10:
		time.sleep(delay)
		count += 1
		print "%s %s %d" % (name, comment, count)

# First Version (Need to sleep in main thread)

# import thread
# try:
# 	thread1 = thread.start_new_thread( subFunc, ("t1", "hi", 2))
# 	thraed2 = thread.start_new_thread( subFunc, ("t2", "hello", 3))
# except Exception, errtxt:
# 	print errtxt

# sleep(10)

# Second Version (main thread will automatically wait until all subthreads finish)

from threading import Thread

try:
	Thread(target = subFunc, args=('t1', "hi", 2)).start()
	Thread(target = subFunc, args=('t2', "hello", 3)).start()
except Exception, errtxt:
	print errtxt
import time
import threading
import sys

class myWorkerThread(threading.Thread):

	def __init__(self, name, comment, delay):
		threading.Thread.__init__(self)
		self.signal_received = False
		self.signal = ""
		self.done = False

		self.name = name
		self.comment = comment
		self.delay = delay


	def run(self):
		# init
		self.count = 0
		# run in loop
		while not self.signal_received and not self.done:
			self.do_something()
			time.sleep(self.delay)
		if self.signal_received:
			raise self.signal

	def do_something(self):
		if self.count < 10:
			time.sleep(self.delay)
			self.count += 1
			print "%s %s %d" % (self.name, self.comment, self.count)
		else:
			self.done = True

if __name__ == '__main__':
	try:
		ts = []
		ts.append(myWorkerThread('t1', "hi", 2))
		ts.append(myWorkerThread('t2', "hello", 3))
		ts[0].start()
		ts[1].start()

		while ts[0].isAlive() and ts[1].isAlive():
			pass
	except Exception as e:
		print "Exception detected"
		for t in ts:
			t.signal = e
			t.signal_received = True
	except KeyboardInterrupt as e:
		print "KeyboardInterrupt detected"
		for t in ts:
			t.signal = e
			t.signal_received = True
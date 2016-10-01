import logging

logname = "tmp.log"
logging.basicConfig(filename=logname,
                            filemode='a',
                            format='%(asctime)s,%(msecs)d %(name)s %(levelname)s %(message)s\n\r',
                            # datefmt='%H:%M:%S',
                            level=logging.DEBUG)

logging.info("This is a test")
logging.info("Another test")
# proc_a.py
'''
import sys
import time
#print ("what should proc A say?")
sys.stdout.write("what should proc A say?")
sys.stdout.flush()
#time.sleep(.01)
for name in iter(sys.stdin.readline, ''):
    name = name[:-1]
    if name == "exit":
        break
    #print ("Proc A says, \"{0}\"".format(name))
    #print ("what should proc A say?")
    sys.stdout.write("Proc A says, \"{0}\"".format(name))
    sys.stdout.write("what should proc A say?")
    sys.stdout.flush()
'''
import sys
import time
#print ("what should proc A say?")

sys.stdout.write("re")
sys.stdout.flush()
time.sleep(3)
#sys.stdout.write("beforrr")
#sys.stdout.flush()

name = sys.stdin.read(1)
sys.stdout.write("after")
sys.stdout.flush()
sys.stdout.write("Proc A says, \"{0}\"".format(name))
sys.stdout.flush()

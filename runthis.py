# two_subprocesses_with_output_and_input.py

import subprocess
import threading
import sys
import time
ready = False
first = True
try:
    import queue
except ImportError:
    import Queue as queue


def read_output(pipe, q):
    """reads output from `pipe`, when line has been read, puts
line on Queue `q`"""

    while True:
        
        
        
        #while True:
            l = pipe.read(2)
            
            if l:
                #sys.stdout.write("!!!!!!!!!!!!!!!!!")
                #sys.stdout.write("\n")
                #sys.stdout.write(l.decode('UTF-8'))
                #sys.stdout.flush()
                q.put(l)
                #x = q.empty()
                #sys.stdout.write(str(x))
                #sys.stdout.flush()
                #print l,
            else:
                #print("HER")
                break
            
        #time.sleep(.01)

def write_to_subproc(write_pipe,message):
    """reads input from a pipe with name `read_pipe_name`,
writing this input straight into `write_pipe`"""
    write_pipe.write(message.encode('UTF-8'))
    write_pipe.flush()
    #while True:
        #sys.stdout.write("!")
        #sys.stdout.flush()
        #write_pipe.write('a'.encode('UTF-8'))
        #write_pipe.flush()
        #time.sleep(3)
        
    '''with open(in_pipe_name, "r") as f:
            x = f.read()
            write_pipe.write(x.encode('UTF-8'))
            sys.stdout.write(x)
            sys.stdout.flush()
    '''  

# start both `proc_a.py` and `proc_b.py`
proc_a = subprocess.Popen(["stdbuf", "-o0", "python3", "classify_image.py"],
    stdin=subprocess.PIPE, stdout=subprocess.PIPE)
proc_b = subprocess.Popen(["stdbuf", "-o0", "python3", "app.py"],
    stdin=subprocess.PIPE, stdout=subprocess.PIPE)

# lists for storing the lines of output generated
pa_line_buffer = [] 
pb_line_buffer = [] 

# queues for storing output lines
pa_q = queue.Queue()
pb_q = queue.Queue()

# start a pair of threads to read output from procedures A and B
pa_t = threading.Thread(target=read_output, args=(proc_a.stdout, pa_q))
pb_t = threading.Thread(target=read_output, args=(proc_b.stdout, pb_q))
pa_t.daemon = True
pb_t.daemon = True
pa_t.start()
pb_t.start()
'''
# start a pair of threads to read input into procedures A and B
pa_input_thread = threading.Thread(target=read_input, args=(proc_a.stdin, "proc_a_input"))
pb_input_thread = threading.Thread(target=read_input, args=(proc_b.stdin, "proc_b_input"))
pa_input_thread.daemon = True
pb_input_thread.daemon = True
pa_input_thread.start()
pb_input_thread.start()
'''
global ready
while True:
    # check if either sub-process has finished
    proc_a.poll()
    proc_b.poll()

    if proc_a.returncode is not None or proc_b.returncode is not None:
        break
    
    # write output from procedure A (if there is any)
    try:
        l = pa_q.get(False)
        #sys.stdout.write("A: ")
        received = l.decode('UTF-8')
        
        sys.stdout.write(received)
        sys.stdout.flush()
        
        if ready:
            sys.stdout.write('!')
            sys.stdout.flush()
            write_to_subproc(proc_b.stdin,received)
        if received == '{{':
            sys.stdout.write("\nrecognition done\n")
            sys.stdout.flush()
            #write_to_subproc(proc_b.stdin,"an")
            ready = True
        
        
            
    except queue.Empty:
        #sys.stdout.write("QUEUE IS EMPTY")
        pass

    # write output from procedure B (if there is any)
    try:
        b = pb_q.get(False)
        #sys.stdout.write("B: ")
        #sys.stdout.write(l.decode('UTF-8'))
        
        received = b.decode('UTF-8')
        sys.stdout.write(received)
        sys.stdout.flush()
        
        if received == 'qq':
            received = ''
            sys.stdout.write("1")
            sys.stdout.write("yaaayB")
            sys.stdout.write("\n")
            sys.stdout.flush()
            write_to_subproc(proc_a.stdin,"re")
        
    except queue.Empty:
        pass

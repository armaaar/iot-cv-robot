
# two_subprocesses.py

import subprocess

# start both `proc_a.py` and `proc_b.py`
proc_stream = subprocess.Popen(["python", "app.py"])
while proc_stream.returncode is None:
    proc_stream.poll()

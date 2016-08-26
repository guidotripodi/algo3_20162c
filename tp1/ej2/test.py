import os
import subprocess

def test():
    for i in range(100):
        cmd = ['echo', i, '| ./ej2'] #seguro se puede hacer mejor lo del pipe
        output = subprocess.check_output(cmd)



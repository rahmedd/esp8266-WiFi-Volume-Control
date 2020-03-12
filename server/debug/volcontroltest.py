#FOR TESTING volctrl.exe

import subprocess

percentage = 0
for i in range(3):
	subprocess.run("volctrl.exe " + str(percentage), shell=True)
	percentage += 10 #increases volume by 10%
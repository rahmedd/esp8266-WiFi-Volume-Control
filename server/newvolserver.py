import socket
import subprocess

localIP = "YOUR LOCAL IP HERE"
localPort = 20001 #change port if err
bufferSize = 512
UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))
print("Volume server listening...")

while True:
	bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
	message = bytesAddressPair[0]
	subprocess.run("volctrl.exe " + str(int(message)), shell=True)
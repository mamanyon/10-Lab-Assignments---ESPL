#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  8 13:03:13 2021

@author: alex
"""
import time
import socket
import subprocess
import threading
import sys
import random
import os

bufferSize = 1024
IsInServerFS = False
hostport = ''
currdir = ''

# Client Code
def ReceiveData(sock):
    global IsInServerFS
    global currdir
    while True:
        try:
            data, addr = sock.recvfrom(bufferSize)
            if data.decode('utf-8')[0] == "$":
                IsInServerFS = False
                if data.decode('utf-8')[1:] == '..':
                    continue
                handlecd(data.decode('utf-8')[1:])
            elif data.decode('utf-8')[0] == "%":
                IsInServerFS = True
                currdir = data.decode('utf-8')[1:]
            else:
                print(data.decode('utf-8'))
        except:
            pass


def handlecd(path):
    os.chdir(path)


def RunClient(serverIP):
    global IsInServerFS
    global currdir
    global hostport
    host = socket.gethostbyname(socket.gethostname())
    port = random.randint(6000, 10000)
    print('Client IP->' + str(host) + ' Port->' + str(port))
    server = (str(serverIP), 5000)
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    UDPClientSocket.bind((host, port))
    name = 'make connection to the server'
    UDPClientSocket.sendto(name.encode('utf-8'), server)
    threading.Thread(target=ReceiveData, args=(UDPClientSocket,)).start()
    print("What is your request:")
    IsMounted = False
    while True:
        if not IsMounted:
            request = input()
            if request == 'mount':
                if not IsMounted:
                    IsMounted = True
                    print("Mounting...")
                    data = '0'
                    UDPClientSocket.sendto(data.encode('utf-8'), server)
                else:
                    print("Already mounted, please choose a different request!")
            elif request == 'unmount':
                if IsMounted:
                    IsMounted = False
                    print("Unmounting...")
                    user_name = input()
                    data = '1'
                    UDPClientSocket.sendto(data.encode('utf-8'), server)
                else:
                    print("Already unmounted..")
            elif request == 'qqq':
                break
        else:
            time.sleep(0.05)
            if IsInServerFS:
                time.sleep(0.05)
                print(hostport + ':' + currdir + '>', end='')
                shell_command = input()
                if shell_command == "copy a file":
                    print("Please enter file name:")
                    filename = input()
                    print("Please enter destination path:")
                    dest_path = input()
                    print("Please enter new file name:")
                    new_name = input()
                    data = f"2 cp {filename} {os.getcwd()}/{dest_path}/{new_name}"
                else:
                    data = '2' + ' ' + shell_command
                UDPClientSocket.sendto(data.encode('utf-8'), server)
            else:
                time.sleep(0.05)
                print(os.getcwd() + '>', end='')
                shell_command = input()
                shell = shell_command.split(" ")
                if shell[0] == "cd":
                    if ":" in shell[1]:
                        splitted = shell[1].split(":")
                        hostport = str(splitted[0]) + ":" + str(splitted[1])
                        data = '2' + ' ' + "cd" + " " + splitted[-1]
                        UDPClientSocket.sendto(data.encode('utf-8'), server)
                        continue
                    handlecd(shell[1])
                    continue
                a = subprocess.check_output(shell)
                print(a.decode('utf-8'))

    # UDPClientSocket.sendto(data.encode('utf-8'),server)
    UDPClientSocket.close()
    os._exit(1)


# Client Code Ends Here


if __name__ == '__main__':
    RunClient(sys.argv[1])

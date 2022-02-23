#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  3 13:05:25 2021

@author: alex
"""
import os
import socket
import subprocess
import threading
import queue
import sys
import sqlite3
from sqlite3 import Error

dict = {}
bufferSize = 1024
client_dict = {}
# a dictionary for storing each address client - his isInServer and curr_dir

# Server Code
def RecvData(sock, recvPackets):
    while True:
        data, addr = sock.recvfrom(bufferSize)
        recvPackets.put((data, addr))


def IsInServerFS(addr):  # getter- gets isInServer for each client in the dict
    global client_dict
    return client_dict[addr][0]


def curr_dir(adder):  # getter- gets the directory for each client in the dict
    global client_dict
    return client_dict[adder][1]


def RunServer(host):
    global client_dict
    # host = socket.gethostbyname(socket.gethostname())
    port = 5000
    print('Server hosting on IP-> ' + str(host))
    UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    UDPServerSocket.bind((host, port))
    recvPackets = queue.Queue()

    print('Server Running...')

    threading.Thread(target=RecvData, args=(UDPServerSocket, recvPackets)).start()
    # a thread waiting for receiving the data

    while True:
        while not recvPackets.empty():
            data, addr = recvPackets.get()
            data = data.decode('utf-8')
            li = list(data.split(" "))  # 2 cd server
            if li[0] == '0':  # mount
                mount_dir = "Server"
                for (root, dirs, files) in os.walk(mount_dir, topdown=True):
                    dict["/" + root] = [dirs, files]
                client_dict[addr] = [False, ""]  # IsinServer, currdir
                message = "SERVER: Done"
                UDPServerSocket.sendto(message.encode('utf-8'), addr)
            elif li[0] == '1':  # unmount
                message = "SERVER: Done"
                client_dict[addr] = [False, ""]
                UDPServerSocket.sendto(message.encode('utf-8'), addr)
            elif li[0] == '2':  # shell command
                args = li[1:]  # cd Server
                if args[0] == 'cd':
                    path = handlecd(args, addr)
                    if IsInServerFS(addr):
                        client_dict[addr][1] = path
                        UDPServerSocket.sendto("SERVER: Done".encode('utf-8'), addr)
                        UDPServerSocket.sendto(f"%{curr_dir(addr)}".encode('utf-8'), addr)
                        continue
                    else:
                        UDPServerSocket.sendto(f"${path}".encode('utf-8'), addr)
                        continue
                elif args[0] == 'cp' or args[0] == 'cat':
                    args[1] = "." + curr_dir(addr) + '/' + args[1]
                else:
                    args.append("." + curr_dir(addr))
                a = subprocess.check_output(args)
                message = "SERVER: Done"
                UDPServerSocket.sendto(message.encode('utf-8'), addr)
                UDPServerSocket.sendto(a, addr)
                for client in client_dict:
                    if client_dict[client][0] and client != addr:
                        UDPServerSocket.sendto(a, client)
    UDPServerSocket.close()
    data_base.close()


def handlecd(args, addr):
    global client_dict
    client_dict[addr][0] = False
    cur = curr_dir(addr).split("/")
    if args[1] == "..":
        if len(cur) == 2 and cur[1] == "Server":  # exiting our of the server ['', Server]
            client_dict[addr][0] = False
            client_dict[addr][1] = ""
            return ".."
        client_dict[addr][0] = True
        output = ""
        for i in cur[:-1]:
            output += i + "/"
        return output[:-1]
    else:
        if curr_dir(addr) + "/" + args[1] in dict:
            client_dict[addr][0] = True
            return curr_dir(addr) + "/" + args[1]
        print(curr_dir(addr) + "/" + args[1])
        print(dict)
        return args[1]


if __name__ == '__main__':
    RunServer(sys.argv[1])

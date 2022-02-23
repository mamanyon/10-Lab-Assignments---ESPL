import os
import subprocess
from Tree import Tree

dict = {}


def handlecd(args, currdir):
    cur = currdir.split("/")
    if args[1] == "..":
        output = ""
        for i in cur[:-1]:
            output += i + "/"
        return output[:-1]
    else:
        if currdir+"/"+args[1] in dict:
            return currdir+"/"+args[1]
        return args[1]


if __name__ == '__main__':
    # mount_dir = "Server"
    # for (root, dirs, files) in os.walk(mount_dir, topdown=True):
    #     dict["/" + root] = [dirs, files]
    # print(dict)
    a = subprocess.check_output(["cp", "main.py", "./Server/junc.py"])

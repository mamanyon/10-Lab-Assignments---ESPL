import datetime
import sys

import matplotlib.pyplot as plt
import subprocess

path = './Vaccine_Distribution.txt'


def task1c(path, date, company):
    proc = subprocess.Popen(f'awk -f ./1c.awk {path}', shell=True, stdout=subprocess.PIPE)
    stdout_value = proc.communicate()[0].decode("utf-8")
    data = stdout_value.split('\n')[:-1]
    conv_time = [datetime.datetime.strptime(i, "%d/%m/%Y") for i in data]
    conv_time.sort()
    conv_time_str = [x.strftime("%d/%m/%Y") for x in conv_time]
    # gets the amount of vaccines from taskb for each date specified in 'conv_time_str' .
    # then split it by : to gain the exact amount
    y = [int(task1b(path, conv_time_str[i], "").split(':')[1][1:-1]) for i in range(len(conv_time_str))]
    conv_time_str2 = [i[:-5] for i in conv_time_str]  # cosmetic modification
    plt.bar(conv_time_str2, y, width=0.982)
    plt.xlabel('Dates ' + conv_time_str[0][-4:] + '-' + conv_time_str[-1][-4:])
    plt.ylabel('Vaccines amount')
    plt.show()

    return stdout_value


def task1b(path, date, company):
    proc = subprocess.Popen(f'awk -v d={date} -v company={company} -f 1b.awk {path}', shell=True,
                            stdout=subprocess.PIPE)
    stdout_value = proc.communicate()[0].decode("utf-8")
    return stdout_value


if __name__ == '__main__':
    task1c(path, "", "")

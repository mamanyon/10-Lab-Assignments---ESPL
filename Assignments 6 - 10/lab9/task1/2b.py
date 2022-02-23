import subprocess
import sys

path = '../task2/Vaccine_Distribution.txt'
path2 = './Cities.txt'


def task2b(path, date):
    # gets the sum of vaccine in Israel on the specific day
    proc = subprocess.Popen(f'awk -v d={date} -v company={""} -f ../task1/1b.awk {path}', shell=True,
                            stdout=subprocess.PIPE)
    stdout_value = proc.communicate()[0].decode("utf-8")
    num_vaccines = stdout_value.split(':')[1][1:-1]
    return num_vaccines


if __name__ == '__main__':
    date = "12/03/2030"
    num_vaccines = int(task2b(path, date))
    proc1 = subprocess.Popen(f'awk -v i={1} -f ./2b.awk {path2}', shell=True, stdout=subprocess.PIPE)
    proc2 = subprocess.Popen(f'awk -v i={2} -f ./2b.awk {path2}', shell=True, stdout=subprocess.PIPE)
    cities_str = proc1.communicate()[0].decode("utf-8")
    str_num_citizens = proc2.communicate()[0].decode("utf-8")
    num_citizens = str_num_citizens.split('\n')[:-1]
    num_citizens = [int(i) for i in num_citizens]
    cities = cities_str.split('\n')[:-1]
    dict = {num_citizens[i]: cities[i] for i in range(len(num_citizens))}
    num_citizens = list(map(int, num_citizens))
    num_citizens.sort()
    i = 0
    lst = []
    while num_vaccines > 0 and i < len(num_citizens):
        if num_vaccines - num_citizens[i] < 0:
            break
        num_vaccines = num_vaccines - num_citizens[i]
        lst.append(num_citizens[i])
        i = i + 1
    lst = [dict[lst[i]] for i in range(len(lst))]
    print(lst)

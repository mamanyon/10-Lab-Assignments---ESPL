import subprocess
import tkinter as tk
from datetime import datetime
from tkinter import ttk
import matplotlib.pyplot as plt
from tkinter import filedialog


class TaskConverter:
    def task1a(path, date, company, path2):
        proc = subprocess.Popen(f'awk -f ./1a.awk {path}', shell=True, stdout=subprocess.PIPE)
        stdout_value = proc.communicate()[0].decode("utf-8")
        return stdout_value

    def task1b(path, date, company, path2):
        if len(date) != 10 or date[2] != '/' or date[5] != '/':
            return "Please type date in the following format: 'dd/mm/YYYY'"
        proc = subprocess.Popen(f'awk -v d={date} -v company={company} -f 1b.awk {path}', shell=True,
                                stdout=subprocess.PIPE)
        stdout_value = proc.communicate()[0].decode("utf-8")
        return stdout_value

    def task1c(path, date, company, path2):
        proc = subprocess.Popen(f'awk -f ./1c.awk {path}', shell=True, stdout=subprocess.PIPE)
        stdout_value = proc.communicate()[0].decode("utf-8")
        data = stdout_value.split('\n')[:-1]
        conv_time = [datetime.strptime(i, "%d/%m/%Y") for i in data]
        conv_time.sort()
        conv_time_str = [x.strftime("%d/%m/%Y") for x in conv_time]
        # gets the amount of vaccines from taskb for each date specified in 'conv_time_str' .
        # then split it by : to gain the exact amount
        y = [int(TaskConverter.task1b(path, conv_time_str[i], "", "").split(':')[1][1:-1]) for i in
             range(len(conv_time_str))]
        conv_time_str2 = [i[:-5] for i in conv_time_str]  # cosmetic modification
        plt.bar(conv_time_str2, y, width=0.982)
        plt.xlabel('Dates ' + conv_time_str[0][-4:] + '-' + conv_time_str[-1][-4:])
        plt.ylabel('Vaccines amount')
        # plt.show()

        return "graph"

    def task2a(path, date, company, path2):
        proc = subprocess.Popen(f'awk -f ./2a.awk {path}', shell=True, stdout=subprocess.PIPE)
        stdout_value = proc.communicate()[0].decode("utf-8")
        return stdout_value

    def task2b(path, date, company, path2):
        if len(date) != 10 or date[2] != '/' or date[5] != '/':
            return "Please type date in the following format: 'dd/mm/YY'"
        num_vaccines = int(TaskConverter.task2bhelper(path, date))
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
        return str(lst)

    def task2bhelper(path, date):
        # gets the sum of vaccine in Israel on the specific day
        proc = subprocess.Popen(f'awk -v d={date} -v company={""} -f ../task1/1b.awk {path}', shell=True,
                                stdout=subprocess.PIPE)
        stdout_value = proc.communicate()[0].decode("utf-8")
        num_vaccines = stdout_value.split(':')[1][1:-1]
        return num_vaccines


class ConverterFrame(ttk.Frame):
    def __init__(self, container, bo, converter, path, path2):
        super().__init__(container)
        self.converter = converter
        self.date_text = "Date:"
        self.company_text = "Company:"
        self.bo = bo
        self.path = path
        self.path2 = path2
        # field options
        options = {'padx': 5, 'pady': 0}

        # date label
        if bo:
            self.date_label = ttk.Label(self, text=self.date_text)
            self.date_label.grid(column=0, row=0, sticky='w', **options)

            self.company_label = ttk.Label(self, text=self.company_text)
            self.company_label.grid(column=0, row=1, sticky='w', **options)

            # date entry
            self.date = tk.StringVar()
            self.date_entry = ttk.Entry(self, textvariable=self.date)
            self.date_entry.grid(column=1, row=0, sticky='w', **options)
            self.date_entry.focus()

            # company entry
            self.company = tk.StringVar()
            self.company_entry = ttk.Entry(self, textvariable=self.company)
            self.company_entry.grid(column=1, row=1, sticky='w', **options)
            self.company_entry.focus()

        # button
        self.convert_button = ttk.Button(self, text='Go')
        self.convert_button.grid(column=2, row=0, sticky='N', **options)
        self.convert_button.configure(command=self.convert)

        # result label
        self.result_label = ttk.Label(self)
        self.result_label.grid(row=4, columnspan=3, **options)

        # add padding to the frame and show it
        self.grid(column=0, row=0, padx=5, pady=5, sticky="nsew")

    def convert(self):
        if not self.bo:
            result = self.converter(self.path, "", "", "")
        else:
            result = self.converter(self.path, self.date.get(), self.company.get(), self.path2)
        if result == "graph":
            plt.show()
        else:
            self.result_label.config(text=result)

    def reset(self):
        if self.bo:
            self.date_entry.delete(0, "end")
            self.company_entry.delete(0, "end")
        self.result_label.text = ''
        self.result_label.config()


class ControlFrame(ttk.LabelFrame):
    def __init__(self, container, path, path2):
        super().__init__(container)
        self['text'] = 'Options'

        # radio buttons
        self.selected_value = tk.IntVar()

        ttk.Radiobutton(
            self,
            text='vaccine stats',
            value=0,
            variable=self.selected_value,
            command=self.change_frame).grid(column=0, row=0, padx=5, pady=5)

        ttk.Radiobutton(
            self,
            text='vaccine date',
            value=1,
            variable=self.selected_value,
            command=self.change_frame).grid(column=1, row=0, padx=5, pady=5)

        ttk.Radiobutton(
            self,
            text='histogram',
            value=2,
            variable=self.selected_value,
            command=self.change_frame).grid(column=2, row=0, padx=5, pady=5)

        ttk.Radiobutton(
            self,
            text='People we can vaccine',
            value=3,
            variable=self.selected_value,
            command=self.change_frame).grid(column=0, row=1, padx=5, pady=5)

        ttk.Radiobutton(
            self,
            text='Cities we can vaccine',
            value=4,
            variable=self.selected_value,
            command=self.change_frame).grid(column=1, row=1, padx=5, pady=5)
        self.grid(column=0, row=1, padx=5, pady=5, sticky='ew')

        # initialize frames
        self.frames = {}
        self.frames[0] = ConverterFrame(
            container, False, TaskConverter.task1a, path, path2)
        self.frames[1] = ConverterFrame(
            container, True, TaskConverter.task1b, path, path2)
        self.frames[2] = ConverterFrame(
            container, False, TaskConverter.task1c, path, path2)
        self.frames[3] = ConverterFrame(
            container, False, TaskConverter.task2a, path, path2)
        self.frames[4] = ConverterFrame(
            container, True, TaskConverter.task2b, path, path2)
        self.change_frame()

    def change_frame(self):
        frame = self.frames[self.selected_value.get()]
        frame.reset()
        frame.tkraise()


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('COVID-19 Vaccine database')
        self.geometry('600x250')


class Window(tk.Frame):
    def __init__(self, text, master=None):
        tk.Frame.__init__(self, master)
        self.master = master
        self.filepath = tk.StringVar()
        self.text = text
        self.init_window1()

    def init_window1(self):
        self.master.title("Vacc")
        self.pack(fill='both', expand=1)
        label = tk.Label(self, text=self.text)
        label.pack(ipadx=10, ipady=10)
        browseButton = tk.Button(self, text='Browse',
                                 command=self.first_browser)
        browseButton.place(x=85, y=60)

        filepathText = tk.Entry(self, textvariable=self.filepath)
        filepathText.pack()

    def close_window(self):
        try:
            form.destroy()
        except:
            self.quit()

    def show_file_browser(self):
        self.filename = filedialog.askopenfilename()
        self.close_window()

    def first_browser(self):
        self.show_file_browser()


if __name__ == '__main__':
    form = tk.Tk()
    form.geometry("250x250")
    form.resizable(0, 0)
    app = Window("Please load Vaccination database!", form)
    form.mainloop()
    path = app.filename
    form = tk.Tk()
    form.geometry("250x250")
    form.resizable(0, 0)
    app = Window("Please load Cities database!", form)
    form.mainloop()
    path2 = app.filename
    app = App()
    ControlFrame(app, path, path2)
    app.mainloop()

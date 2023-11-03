from tkinter import *
import webbrowser as wb

root = Tk()
root.title("")
root.geometry("1200x400")
root.resizable(False, False)

buttons = []

settings = open('setting.ini', 'r')
line = None

links = ['' for i in range(10)]
icons = ['' for i in range(15)]

link_idx, icon_idx = 0, 0
lines = settings.readlines()
for line in lines:
    line = line.strip()
    if len(line) == 0:
        continue
    if line[0] == '#':
        continue
    if link_idx < 10:
        line = line.split('=')
        links[link_idx] = line[1]
        link_idx += 1
    else:
        line = line.split('=')
        icons[icon_idx] = line[1]
        icon_idx += 1
        
def link_url(url):
    print(url)
    wb.open_new(url)


# top line
button1 = Button(root, text="Main Link 1", overrelief="solid", command=lambda: link_url(links[0]), image=icons[0])
button1.place(x=0, y=0, width=300, height=150)
buttons.append(button1)

button2 = Button(root, text="Main Link 2", overrelief="solid", command=lambda: link_url(links[1]), image=icons[1])
button2.place(x=300, y=0, width=300, height=150)
buttons.append(button2)

button3 = Button(root, text="Main Link 3", overrelief="solid", command=lambda: link_url(links[2]), image=icons[2])
button3.place(x=600, y=0, width=300, height=150)
buttons.append(button3)

button4 = Button(root, text="Main Link 4", overrelief="solid", command=lambda: link_url(links[3]), image=icons[3])
button4.place(x=900, y=0, width=300, height=150)
buttons.append(button4)

# mid line
button11 = Button(root, text="Side Menu 1", overrelief="solid", command=lambda: link_url(links[4]), image=icons[4])
button11.place(x=0, y=150, width=200, height=150)
buttons.append(button11)

button12 = Button(root, text="Side Menu 2", overrelief="solid", command=lambda: link_url(links[5]), image=icons[5])
button12.place(x=200, y=150, width=200, height=150)
buttons.append(button12)

button13 = Button(root, text="Side Menu 3", overrelief="solid", command=lambda: link_url(links[6]), image=icons[6])
button13.place(x=400, y=150, width=200, height=150)
buttons.append(button13)

button14 = Button(root, text="Side Menu 4", overrelief="solid", command=lambda: link_url(links[7]), image=icons[7])
button14.place(x=600, y=150, width=200, height=150)
buttons.append(button14)

button15 = Button(root, text="Side Menu 5", overrelief="solid", command=lambda: link_url(links[8]), image=icons[8])
button15.place(x=800, y=150, width=200, height=150)
buttons.append(button15)

button16 = Button(root, text="Side Menu 6", overrelief="solid", command=lambda: link_url(links[9]), image=icons[9])
button16.place(x=1000, y=150, width=200, height=150)
buttons.append(button16)

# bottom line
button21 = Button(root, text="Option 1", overrelief="solid", image=icons[10])
button21.place(x=0, y=300, width=240, height=100)
buttons.append(button21)

button22 = Button(root, text="Option 2", overrelief="solid", image=icons[11])
button22.place(x=240, y=300, width=240, height=100)
buttons.append(button22)

button23 = Button(root, text="Option 3", overrelief="solid", image=icons[12])
button23.place(x=480, y=300, width=240, height=100)
buttons.append(button23)

button24 = Button(root, text="Option 4", overrelief="solid", image=icons[13])
button24.place(x=720, y=300, width=240, height=100)
buttons.append(button24)

button25 = Button(root, text="Option 5", overrelief="solid", image=icons[14])
button25.place(x=960, y=300, width=240, height=100)
buttons.append(button25)



root.mainloop()

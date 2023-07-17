from os import system, get_terminal_size
from win32api import GetAsyncKeyState
import win32console
import win32con
import shutil

screen = " "*10000

pos = 560

system('mode 120,80')
system('color 1E')
myConsole = win32console.CreateConsoleScreenBuffer(DesiredAccess = win32con.GENERIC_READ | win32con.GENERIC_WRITE, ShareMode=0, SecurityAttributes=None, Flags=1) # create screen buffer
myConsole.SetConsoleActiveScreenBuffer() # set this buffer to be active

sliver = ""
sliver += "#"*9
sliver += "#       #"*7
sliver += "#"*9

sliver2 = ""
sliver2 = "#"*81

world = ""
world += sliver2
world += sliver*7
world += sliver2

while True:
    screen = str(shutil.get_terminal_size((80, 20)))
    screen += " "*(pos-1)
    screen += "█"
    screen += " "*(10000-pos)
    if GetAsyncKeyState(ord("A")):
        pos -= 1
    if GetAsyncKeyState(ord("D")):
        pos += 1
    myConsole.WriteConsoleOutputCharacter(Characters=screen, WriteCoord=win32console.PyCOORDType(0,0))



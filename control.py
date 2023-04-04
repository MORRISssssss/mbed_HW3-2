import serial
from time import sleep

LOCATE = b'0'
CLS = b'1'
ROWS = b'2'
COLUMNS = b'3'
PUTC = b'4'

# send the waveform table to mbed
serdev = 'COM3'
s = serial.Serial(serdev, 9600)

while (True):
    print("Input command: locate/cls/rows/columns/putc")
    line = input("> ")
    if (line == "locate"):
        s.write(LOCATE)
        sleep(0.001)
        print("column = ")
        column = input("> ")
        col = str(int(column) // 10) + str(int(column) % 10)
        s.write(bytes(col[0], 'UTF-8'))
        sleep(0.001)
        s.write(bytes(col[1], 'UTF-8'))
        sleep(0.001)
        print("row = ")
        row = input("> ")
        s.write(bytes(row, 'UTF-8'))
        sleep(0.001)
    elif (line == "cls"):
        s.write(CLS)
        sleep(0.001)
    elif (line == "rows"):
        s.write(ROWS)
        sleep(0.001)
        line = s.readline()
        line = line.strip(b'\t\n')
        print(line.decode("utf-8"))
    elif (line == "columns"):
        s.write(COLUMNS)
        sleep(0.001)
        line = s.readline()
        line = line.strip(b'\t\n')
        print(line.decode("utf-8"))
    elif (line == "putc"):
        s.write(PUTC)
        sleep(0.001)
        print("char c = ")
        c = input("> ")
        s.write(bytes(c, 'UTF-8'))
        sleep(0.001)

s.close()
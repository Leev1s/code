import sys, serial, struct
port = '/dev/tty.usbmodem376F395831371'
sp = serial.Serial(port, baudrate=115200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE,
             xonxoff=False, rtscts=False, stopbits=serial.STOPBITS_ONE, timeout=None, dsrdtr=True)
sp.setDTR(False) # dsrdtr在Windows上被忽略。
#sp.write("snap")
sp.flush()
size = struct.unpack('<L', sp.read(4))[0]
img = sp.read(size)
sp.close()

with open("img.jpg", "w") as f:
    f.write(img)
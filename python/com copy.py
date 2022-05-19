import serial, struct
ser = serial.Serial('/dev/tty.usbmodem376F395831371', timeout=1, dsrdtr=False)
while True:
    ser.write("snap".encode())
    ser.flush()
    size = struct.unpack('<L', ser.read(4))[0]
    img = ser.read(size)
    ser.close()
import serial
import io
with serial.Serial('/dev/' + str(sys.argv[1]), 115200, timeout=1) as ser:
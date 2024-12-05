import serial
import csv
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

serial_port = "COM4"
baud_rate = 9600

try:
    ser = serial.Serial(serial_port, baud_rate)
    print(f"Connected to {serial_port} at {baud_rate} baud.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

csv_file = open('output/data.csv', mode='w', newline='')
csv_writer = csv.writer(csv_file)
csv_writer.writerow(['Time', 'Speed_desd', 'Speed'])

fig, ax = plt.subplots()
t = []
speed_des = []
speed = []

line1, = ax.plot([], [], label='Speed_desd', color='red')
line2, = ax.plot([], [], label='Speed', color='blue')

ax.set_xlabel('Time (s)')
ax.set_ylabel('Speed')
ax.set_title('Real-Time Motor Data')
ax.legend()


def update(frame):

    line = ser.readline().decode('utf-8').strip()
    values = line.split(',')
    
    if len(values) == 3:
        t.append(float(values[0]))
        speed_des.append(float(values[1]))
        speed.append(float(values[2]))
        
        #t = t[-100:]
        #speed_des = speed_des[-100:]
        #speed = speed[-100:]
       
        plt.cla()
        plt.plot(t,speed_des, color = "blue", label = "speed desired")
        plt.plot(t,speed, color = "red", label = "speed")
    return        



ani = FuncAnimation(fig, update, interval=100)
plt.show()

csv_writer.writerow([t, speed_des, speed])
ser.close()
csv_file.close()
print("Serial connection and CSV file closed.")

import numpy as np
import serial
import csv
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore

serial_port = "COM13"
baud_rate = 9600

try:
    ser = serial.Serial(serial_port, baud_rate)
    print(f"Connected to {serial_port} at {baud_rate} baud.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

try:
    csv_file = open('output/data/data.csv', mode='w', newline='')
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(['Time', 'Speed_des', 'Speed_mes', 'motor1_input', 'motor2_input', 'Position'])
    print("CSV header written successfully.")
except Exception as e:
    print(f"An error occurred: {e}")    

app = pg.mkQApp("Serial Plotter")
win = pg.GraphicsLayoutWidget(show=True, title="Serial Data Plot")
win.resize(1200, 800)
win.setWindowTitle("Real-Time Data Plot")

plot1 = win.addPlot(row=0, col=0, colspan=2, title="Desired Speed vs Measured Speed")
plot1.addLegend()
curve1_desired = plot1.plot(pen='b', name="Desired Speed")
curve1_measured = plot1.plot(pen='r', name="Measured Speed")

plot2 = win.addPlot(row=1, col=0, title="Motor Inputs")
plot2.addLegend()
curve2_motor1 = plot2.plot(pen='g', name="Motor Input 1")
curve2_motor2 = plot2.plot(pen='y', name="Motor Input 2")

plot3 = win.addPlot(row=1, col=1, title="pos")
plot3.addLegend()
curve3_pos = plot3.plot(pen='c', name="pos")

time = []
speed_des = []
speed_mes = []
motor1_input = []
motor2_input = []
pos = []

def update():
    global time, speed_des, speed_mes, motor1_input, motor2_input, pos
    if ser.in_waiting > 0:  
        line = ser.readline().decode('utf-8').strip()
        values = line.split(',')  

        if len(values) == 6:
            time_ = float(values[0])
            speed_des_ = float(values[1])
            speed_mes_ = float(values[2])
            motor1_input_ = float(values[3])
            motor2_input_ = float(values[4])
            pos_ = float(values[5])

            time.append(time_)
            speed_des.append(speed_des_)
            speed_mes.append(speed_mes_)
            motor1_input.append(motor1_input_)
            motor2_input.append(motor2_input_)
            pos.append(pos_)
            print(f"{time_}, {speed_des_}, {speed_mes_}, {motor1_input_}, {motor2_input_}, {pos_}")
            csv_writer.writerow([time_, speed_des_, speed_mes_, motor1_input_, motor2_input_, pos_])

            max_points = 200
            if len(time) > max_points:
                time = time[-max_points:]
                speed_des = speed_des[-max_points:]
                speed_mes = speed_mes[-max_points:]
                motor1_input = motor1_input[-max_points:]
                motor2_input = motor2_input[-max_points:]
                pos = pos[-max_points:]

            curve1_desired.setData(time, speed_des)
            curve1_measured.setData(time, speed_mes)
            curve2_motor1.setData(time, motor1_input)
            curve2_motor2.setData(time, motor2_input)
            curve3_pos.setData(time, pos)

        elif line == "on":
            print("on")
            time.clear()
            speed_des.clear()
            speed_mes.clear()
            motor1_input.clear()
            motor2_input.clear()
            pos.clear()
            csv_file.truncate()

        elif line == "off":
            print("off")
            csv_file.close()
            print("Serial connection and CSV file closed.")
               

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(50)

if __name__ == '__main__':
    pg.exec()

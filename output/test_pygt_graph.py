import numpy as np
import serial
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

plot3 = win.addPlot(row=1, col=1, title="Position")
plot3.addLegend()
curve3_position = plot3.plot(pen='c', name="Position")

time_data = []
desired_speed = []
measured_speed = []
motor1_input = []
motor2_input = []
position = []

def update():
    global time_data, desired_speed, measured_speed, motor1_input, motor2_input, position
    if ser.in_waiting > 0:  
        try:
            line = ser.readline().decode('utf-8').strip()
            values = list(map(float, line.split(',')))  

            if len(values) == 6:
                t, desired, measured, motor1, motor2, pos = values

                time_data.append(t)
                desired_speed.append(desired)
                measured_speed.append(measured)
                motor1_input.append(motor1)
                motor2_input.append(motor2)
                position.append(pos)

                max_points = 100
                if len(time_data) > max_points:
                    time_data = time_data[-max_points:]
                    desired_speed = desired_speed[-max_points:]
                    measured_speed = measured_speed[-max_points:]
                    motor1_input = motor1_input[-max_points:]
                    motor2_input = motor2_input[-max_points:]
                    position = position[-max_points:]

                curve1_desired.setData(time_data, desired_speed)
                curve1_measured.setData(time_data, measured_speed)
                curve2_motor1.setData(time_data, motor1_input)
                curve2_motor2.setData(time_data, motor2_input)
                curve3_position.setData(time_data, position)
        except ValueError as e:
                time_data.clear()
                desired_speed.clear()
                measured_speed.clear()
                motor1_input.clear()
                motor2_input.clear()
                position.clear()

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(50)

if __name__ == '__main__':
    pg.exec()

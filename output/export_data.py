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

try:
    csv_file = open('output/data.csv', mode='w', newline='')
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(['Time', 'Speed_des', 'Speed', 'Duty_Cycle', 'Position'])
    print("CSV header written successfully.")
except Exception as e:
    print(f"An error occurred: {e}")

# Initialize lists
t = []
speed_des = []
speed = []
duty_cycle = []
pos = []

fig, ax = plt.subplots(2, 2, figsize=(12, 8))  # Adjust figsize as desired


def update(frame):
    global t, speed_des, speed, duty_cycle, pos

    # Read line from serial port
    line = ser.readline().decode('utf-8').strip()
    values = line.split(',')
    print(values)  # Debugging print to confirm data

    if len(values) == 5:
        # Parse values
        t_curr = float(values[0])
        speed_des_curr = float(values[1])
        speed_curr = float(values[2])
        duty_cycle_curr = float(values[3])
        pos_curr = float(values[4])

        # Write to CSV
        #csv_writer.writerow([t_curr, speed_des_curr, speed_curr, duty_cycle_curr, pos_curr])

        # Append to lists
        t.append(t_curr)
        speed_des.append(speed_des_curr)
        speed.append(speed_curr)
        duty_cycle.append(duty_cycle_curr)
        pos.append(pos_curr)

        # Keep only the last 100 points
        t = t[-100:]
        speed_des = speed_des[-100:]
        speed = speed[-100:]
        duty_cycle = duty_cycle[-100:]
        pos = pos[-100:]

        # Clear and update each subplot
        ax[0, 0].cla()
        ax[0, 0].plot(t, speed_des, color="blue", label="Speed Desired")
        ax[0, 0].plot(t, speed, color="red", label="Speed")
        ax[0, 0].legend()
        ax[0, 0].set_title("Speed vs Time")

        ax[1, 0].cla()
        ax[1, 0].plot(t, duty_cycle, color="green", label="Duty Cycle")
        ax[1, 0].legend()
        ax[1, 0].set_title("Duty Cycle vs Time")

        ax[1, 1].cla()
        ax[1, 1].plot(t, pos, color="orange", label="Position")
        ax[1, 1].legend()
        ax[1, 1].set_title("Position vs Time")
    elif(line == "on"):
        t = []
        speed_des = []
        speed = []
        duty_cycle = []
        pos = []
    elif(line == "off"):
        print("programm ended")
        raise SystemExit    
    return


ani = FuncAnimation(fig, update, interval=100, cache_frame_data=False)
plt.show()

ser.close()
csv_file.close()
print("Serial connection and CSV file closed.")

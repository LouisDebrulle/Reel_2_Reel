import serial
import csv

def readserial(comport, baudrate, csv_filename):
    ser = serial.Serial(comport, baudrate, timeout=0.1)  
    
    with open(csv_filename, mode='w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        
        while True:
            data = ser.readline().decode().strip()
            if data:
                print(data)  
                csv_writer.writerow([data])  

if __name__ == '__main__':
    readserial('COM4', 9600, r'Z:\Software\Reel_2_Reel\output\output_data.csv')



%% Motor Speed Curve

clear all; %close all;
clc;

%% Read the data from the CSV file
filename1 = 'speed_dc_global_2.csv';
data1 = readtable(filename1);

time1 = data1.Var1; time1 = time1/1000;
dc1 = data1.Var2; dc1 = dc1 / 780 * 100; 
speed1 = data1.Var3; 

filename2 = 'speed_dc_small_speed.csv';
data2 = readtable(filename2);

time2 = data2.Var1; time2 = time2/1000;
dc2 = data2.Var2; dc2 = dc2 / 780 * 100; 
speed2 = data2.Var3; 


%%

figure;
subplot(2,1,1)
plot(dc1, speed1, '-o');
xlabel('Duty cycle [%]');
ylabel('Speed [rpm]');
title('global Motor Speed Curve');
grid on;

subplot(2,1,2)
plot(dc2, speed2, '-o');
xlabel('Duty cycle [%]');
ylabel('Speed [rpm]');
title('low Speed Curve');
grid on;



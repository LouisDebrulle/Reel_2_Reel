%% Motor Speed Curve

clear all; close all; clc;
%%
filename = 'speed_dc.csv';

data = readtable(filename);
dc = data.Var1;
dc = dc/780 *100;
speed = data.Var2;
speed = -1*speed;

%5 Plot the data
figure;
plot(dc, speed, '-o'); 
xlabel('duty cycle [%]');
ylabel('speed [rpm]');
title('Motor speed curve');
grid on;



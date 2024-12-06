%%
clear all; close all; clc;

%%
data = readtable('data.csv'); 
t = data.Time;
speed_des = data.Speed_des;
speed = data.Speed;

%%
figure('Position', [100, 100, 800, 600]);
plot(t,speed_des, t, speed, 'LineWidth',2)
grid on
xlabel('time [s]')
ylabel('speed [rpm]')
legend('$speed_{des}$','$speed$', 'Interpreter', 'latex', 'Fontsize', 12)
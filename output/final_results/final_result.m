%% Clear workspace
clear all; close all; clc;

%% Load data
file_location = 'Z:\Software\Reel_2_Reel\output\data\data.csv';

data = readtable(file_location); 
t = data.Time;
speed_des = data.Speed_des;
speed_mes = data.Speed_mes;
motor1_input = data.motor1_input;
motor2_input = data.motor2_input;
pos_des = data.position_des;
pos = data.position;


%% Plot


figure('Position', [100, 100, 1600, 800]);
legendFontSize = 14;
titleFontSize = 18;
labelFontSize = 16;

subplot(3,1,1)
plot(t, speed_des, 'LineWidth', 2, 'DisplayName', 'Speed Desired');
hold on;
plot(t, speed_mes, 'LineWidth', 2, 'DisplayName', 'Speed Measured');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', legendFontSize);  
title('Speed vs Time', 'Interpreter', 'latex', 'FontSize', titleFontSize);      
ylabel('Speed $[1/min]$', 'Interpreter', 'latex', 'FontSize', labelFontSize);    
grid on;

subplot(3,1,2)
plot(t, motor1_input, 'LineWidth', 2, 'DisplayName', 'Motor 1 Input');
hold on;
plot(t, motor2_input, 'LineWidth', 2, 'DisplayName', 'Motor 2 Input');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', legendFontSize);  
title('Motor Inputs vs Time', 'Interpreter', 'latex', 'FontSize', titleFontSize); 
ylabel('Motor Input $[\%]$', 'Interpreter', 'latex', 'FontSize', labelFontSize); 
grid on;

subplot(3,1,3)
plot(t, pos_des, 'LineWidth', 2, 'DisplayName', 'Position Desired');
hold on;
plot(t, pos, 'LineWidth', 2, 'DisplayName', 'Position Measured');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', legendFontSize);  
title('Position vs Time', 'Interpreter', 'latex', 'FontSize', titleFontSize);    
xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', labelFontSize);           
ylabel('Position [mm]', 'Interpreter', 'latex', 'FontSize', labelFontSize);      
axis padded
grid on;


%% plot tension
figure('Position', [100, 100, 1600, 800]);

plot(t, pos_des, 'LineWidth', 2, 'DisplayName', 'Position Desired');
hold on;
plot(t, pos, 'LineWidth', 2, 'DisplayName', 'Position Measured');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', legendFontSize);  
title('Position vs Time', 'Interpreter', 'latex', 'FontSize', titleFontSize);    
xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', labelFontSize);           
ylabel('Position [mm]', 'Interpreter', 'latex', 'FontSize', labelFontSize);      
axis padded
grid on;
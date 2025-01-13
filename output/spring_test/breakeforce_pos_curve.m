%% Clear workspace
clear all; close all; clc;

%% Load data
data = readtable('Z:\Software\Reel_2_Reel\output\data\data.csv'); 
t = data.Time;
motor2_input = data.motor2_input;
pos = data.position;

figure
subplot(2,1,1)
plot(t,motor2_input)
subplot(2,1,2)
plot(t,pos)

% indices = 200:100:800; 
% motor2_input = motor2_input(indices);
% pos = pos(indices);

motor2_input = [20, 30, 40, 50, 60, 70];
pos = [6.7, 8.7, 10.7, 14.4, 15.3, 16.2];
%% Fit linear function
p = polyfit(motor2_input, pos, 1);
pos_fit = p(1)*motor2_input + p(2);

% Generate the linear function string
linear_func_str = sprintf('%.2f \\cdot x + %.2f', p(1), p(2)); % Format slope and intercept

%% Plot results
figure('Position', [100, 100, 1400, 600]);

subplot(1,2,1)
plot(motor2_input, pos, 'LineWidth', 2, 'DisplayName', 'Measurements'); % Original data points
hold on;
plot(motor2_input, pos_fit, 'LineWidth', 2, 'DisplayName', linear_func_str); % Fitted line
grid on
xlabel('motor input [%]')
ylabel('pos [mm]')

% Add and customize the legend
legend_handle = legend('show');
set(legend_handle, 'FontSize', 14); % Increase font size
legend('Location', 'best'); % Automatically place legend at the best location

%% inverted curve
motor2_input_inv = 1/(p(1))*(pos - p(2));
linear_func_str = sprintf('%.2f \\cdot x + %.2f', 1/p(1), -p(2)/p(1));

subplot(1,2,2)
plot(pos, motor2_input_inv, 'LineWidth', 2, 'DisplayName', linear_func_str);
xlabel('pos [mm]')
ylabel('motor input [%]')
grid on
legend_handle = legend('show');
set(legend_handle, 'FontSize', 14); % Increase font size
legend('Location', 'best'); % Automatically place legend at the best location

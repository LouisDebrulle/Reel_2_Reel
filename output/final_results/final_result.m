%% Clear workspace
clear all; close all; clc;

%% Load data
file_location = 'Z:\Software\Reel_2_Reel\output\data\data.csv';
empty_line_index = find_empty_lines(file_location);

data = readtable(file_location); 
t = data.Time;
speed_des = data.Speed_des;
speed_mes = data.Speed_mes;
motor1_input = data.motor1_input;
motor2_input = data.motor2_input;
pos_des = data.position_des;
pos = data.position;

t_start = t(empty_line_index(1)-2);
t_stop = t(empty_line_index(2)-3);
t(empty_line_index(1)-1:end) = t(empty_line_index(1)-1:end) +  t_start;
t(empty_line_index(2)-2:end) = t(empty_line_index(2)-2:end) +  t_stop;

%% Plot
figure('Position', [100, 100, 1400, 800]);

subplot(3,1,1)
plot(t, speed_des, 'LineWidth', 2, 'DisplayName', 'Speed Desired');
hold on;
plot(t, speed_mes, 'LineWidth', 2, 'DisplayName', 'Speed Measured');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', 14);  % Increase legend font size
title('Speed vs Time', 'Interpreter', 'latex', 'FontSize', 16);  % Increase title font size
ylabel('Speed $[1/min]$', 'Interpreter', 'latex', 'FontSize', 14);  % Increase y-label font size
grid on;

subplot(3,1,2)
plot(t, motor1_input, 'LineWidth', 2, 'DisplayName', 'Motor 1 Input');
hold on;
plot(t, motor2_input, 'LineWidth', 2, 'DisplayName', 'Motor 2 Input');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', 14);
title('Motor Inputs vs Time', 'Interpreter', 'latex', 'FontSize', 16);
ylabel('Motor Input $[\%]$', 'Interpreter', 'latex', 'FontSize', 14);
grid on;

subplot(3,1,3)
plot(t, pos_des, 'LineWidth', 2, 'DisplayName', 'Position Desired');
hold on;
plot(t, pos, 'LineWidth', 2, 'DisplayName', 'Position Measured');
hold off;
legend('Interpreter', 'latex', 'Location', 'best', 'FontSize', 14);
title('Position vs Time', 'Interpreter', 'latex', 'FontSize', 16);
xlabel('Time [s]', 'Interpreter', 'latex', 'FontSize', 14);  % Increase x-label font size
ylabel('Position [mm]', 'Interpreter', 'latex', 'FontSize', 14);
axis padded
grid on;

%% Function to find empty lines
function empty_line_indices = find_empty_lines(filename)
    fid = fopen(filename, 'r');  % Open the file for reading
    empty_line_indices = [];  % Initialize an empty array to store indices of empty lines
    line_number = 0;  % Line counter
    
    while ~feof(fid)
        line = fgetl(fid);  % Read the next line from the file
        line_number = line_number + 1;  % Increment the line number
        
        if isempty(line)
            % If the line is empty, store the line number
            empty_line_indices = [empty_line_indices, line_number];
        end
    end

    fclose(fid);  % Close the file
end

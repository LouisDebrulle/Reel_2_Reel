%% MATLAB Code for Real-Time Plotting of Time, Speed_des, Speed, and Speed_smooth
clear all; close all; clc;

%% Parameters
serialPort = 'COM13';
baudRate = 9600;

% Try to open the serial port
try
    ser = serialport(serialPort, baudRate);
    disp(['Connected to ', serialPort, ' at ', num2str(baudRate), ' baud.']);
catch ME
    disp(['Error opening serial port: ', ME.message]);
    return;
end

%% Initialize variables
t = [];
speed_des = [];
speed = [];
speed_smooth = [];

%% Create figure for plotting
figure('Name', 'Real-Time Speed Data', 'NumberTitle', 'off', 'Position', [300, 350, 1200, 600]); % Resized Figure
hold on;

speed_des_plot = plot(nan, nan, 'b-', 'DisplayName', 'Speed Desired', 'LineWidth', 2);
speed_plot = plot(nan, nan, 'r-', 'DisplayName', 'Speed', 'LineWidth', 2);
speed_smooth_plot = plot(nan, nan, 'g-', 'DisplayName', 'Speed Smooth', 'LineWidth', 2);

legend;
xlabel('Time (s)');
ylabel('Speed');
grid on;
title('Real-Time Speed Data');
hold off;

%% Main Loop
try
    while true
        line = fscanf(ser, '%s');
        line = strtrim(line);
        disp(line);

        if strcmp(line, "on")
            % Reset data
            t = [];
            speed_des = [];
            speed = [];
            speed_smooth = [];
        elseif strcmp(line, "off")
            disp("Program ended");
            break;
        else
            % Parse the incoming line
            values = str2double(split(line, ','));

            if numel(values) >= 4
                t_curr = values(1);
                speed_des_curr = values(2);
                speed_curr = values(3);
                speed_smooth_curr = values(4);

                t(end + 1) = t_curr;
                speed_des(end + 1) = speed_des_curr;
                speed(end + 1) = speed_curr;
                speed_smooth(end + 1) = speed_smooth_curr;

    

                set(speed_des_plot, 'XData', t, 'YData', speed_des);
                set(speed_plot, 'XData', t, 'YData', speed);
                set(speed_smooth_plot, 'XData', t, 'YData', speed_smooth);
                drawnow;
            end
        end
    end
catch ME
    disp(['Error occurred: ', ME.message]);
end

% Close the serial port
clear ser;
disp('Serial connection closed.');

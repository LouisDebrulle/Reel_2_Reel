%%
clear all; close all; clc

fclose(instrfind);
delete(instrfind); 
%%
port = "COM4";
baudRate = 9600;
s = serial(port, 'BaudRate', baudRate);
fopen(s);

timeData = [];
speedData = [];
dutyCycleData = [];
posData = [];

figure;
hold on;
xlabel('Time (s)');
ylabel('Value');

speedPlot = plot(NaN, NaN, 'r');       
dutyCyclePlot = plot(NaN, NaN, 'g');   
posPlot = plot(NaN, NaN, 'b');         

legend([speedPlot, dutyCyclePlot, posPlot], 'Speed', 'Duty Cycle', 'Position');

%%
while true
    if s.BytesAvailable > 0
        dataLine = fgetl(s);
        data = str2double(split(dataLine, ","));
        if numel(data) == 4
            timeData(end+1) = data(1);
            speedData(end+1) = data(2);
            dutyCycleData(end+1) = data(3);
            posData(end+1) = data(4);
            set(speedPlot, 'XData', timeData, 'YData', speedData);
            set(dutyCyclePlot, 'XData', timeData, 'YData', dutyCycleData);
            set(posPlot, 'XData', timeData, 'YData', posData);
            drawnow;
        end
    end
end


%%
fclose(s);
delete(s);

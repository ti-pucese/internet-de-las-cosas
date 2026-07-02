% Comparación entre voltaje y corriente

channelID = 3410710;
readAPIKey = 'Z4G6S9WQJAH23QOS';

[data, timeStamps] = thingSpeakRead(channelID, ...
    'Fields', [1 2], ...
    'NumPoints', 100, ...
    'ReadKey', readAPIKey);

voltaje = data(:,1);
corriente = data(:,2);

figure;
plot(voltaje, corriente, 'o-')
title('Comparación entre Voltaje y Corriente')
xlabel('Voltaje (V)')
ylabel('Corriente (A)')
legend('Voltaje vs Corriente')
grid on
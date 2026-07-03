% Comparación entre voltaje y corriente

% ID del canal ThingSpeak
channelID = 3410710;

% Clave de lectura del canal
readAPIKey = 'TU_READ_API_KEY';

% Lectura de los últimos 100 datos enviados por el ESP32
[data, timeStamps] = thingSpeakRead(channelID, ...
    'Fields', [1 2], ...
    'NumPoints', 100, ...
    'ReadKey', readAPIKey);

% Asignación de variables según los campos del canal
voltaje = data(:,1);
corriente = data(:,2);

% Creación de gráficas de comparación entre voltaje y corriente
figure;
plot(voltaje, corriente, 'o-')
title('Comparación entre Voltaje y Corriente')
xlabel('Voltaje (V)')
ylabel('Corriente (A)')
legend('Voltaje vs Corriente')
grid on
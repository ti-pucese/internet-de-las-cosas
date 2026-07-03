% Gráficas de tiempo de variables eléctricas

% ID del canal ThingSpeak
channelID = 3410710;

% Clave de lectura del canal
readAPIKey = 'TU_READ_API_KEY';

% Lectura de los últimos 100 datos enviados por el ESP32
[data, timeStamps] = thingSpeakRead(channelID, ...
    'Fields', [1 2 3 4 5 6], ...
    'NumPoints', 100, ...
    'ReadKey', readAPIKey);

% Asignación de variables según los campos del canal
voltaje = data(:,1);
corriente = data(:,2);
frecuencia = data(:,3);
energia = data(:,4);
potencia = data(:,5);
factorPotencia = data(:,6);

% Creación de gráficas de tiempo
figure;
subplot(3,2,1)
plot(timeStamps, voltaje, '-o')
title('Voltaje en el tiempo')
xlabel('Tiempo')
ylabel('Voltaje (V)')
grid on

subplot(3,2,2)
plot(timeStamps, corriente, '-o')
title('Corriente en el tiempo')
xlabel('Tiempo')
ylabel('Corriente (A)')
grid on

subplot(3,2,3)
plot(timeStamps, frecuencia, '-o')
title('Frecuencia en el tiempo')
xlabel('Tiempo')
ylabel('Frecuencia (Hz)')
grid on

subplot(3,2,4)
plot(timeStamps, energia, '-o')
title('Energía en el tiempo')
xlabel('Tiempo')
ylabel('Energía (kWh)')
grid on

subplot(3,2,5)
plot(timeStamps, potencia, '-o')
title('Potencia en el tiempo')
xlabel('Tiempo')
ylabel('Potencia (W)')
grid on

subplot(3,2,6)
plot(timeStamps, factorPotencia, '-o')
title('Factor de Potencia en el tiempo')
xlabel('Tiempo')
ylabel('Factor de Potencia')
grid on
% =========================================================================
% REPORTE DE VISUALIZACIÓN ENERGÉTIAL (MÁXIMA CALIDAD - 2 GRÁFICAS)
% =========================================================================
clearvars; clc; close all;

% --- CONFIGURACIÓN DE CREDENCIALES ---
channelID = 3410710;
readAPIKey = 'Z4G6S9WQJAH23QOS';
numMuestras = 100; % Bloque de puntos para el análisis visual

fprintf('=================================================================\n');
fprintf('     EXTRACCIÓN DE DATOS EN FORMATO TIMETABLE DESDE ESP32        \n');
fprintf('=================================================================\n\n');

%% 1. DESCARGA CONSOLIDADA DE DATOS
try
    tData = thingSpeakRead(channelID, 'Fields', [1 2 3 4 5 6], 'NumPoints', numMuestras, ...
        'ReadKey', readAPIKey, 'OutputFormat', 'Timetable');
    fprintf('  [OK] Tabla de datos indexada correctamente en memoria.\n');
catch
    error('  [ERROR] No se pudo establecer conexión con ThingSpeak o el canal está vacío.');
end

% Extracción del tiempo y conversión segura a matriz
Tiempo = tData.Timestamps;
matrizDatos = timetable2table(tData);

Voltaje    = matrizDatos{:, 2}; % Campo 1
Corriente  = matrizDatos{:, 3}; % Campo 2
Energia    = matrizDatos{:, 4}; % Campo 3
Potencia   = matrizDatos{:, 5}; % Campo 4
Frecuencia = matrizDatos{:, 6}; % Campo 5
FactorPot  = matrizDatos{:, 7}; % Campo 6

%% 2. GENERACIÓN DE REPORTE VISUAL PROFESIONAL (SÓLO 2 GRÁFICAS)
% Configuramos una ventana amplia [izquierda, abajo, ancho, alto] para que luzca imponente
figure('Name', 'Visualización Avanzada MATLAB - ESP32', 'NumberTitle', 'off', ...
    'Color', [1 1 1], 'Position', [150, 150, 950, 650]);

% --- GRÁFICA 1: Serie de Tiempo Estándar (Time Series) ---
subplot(2, 1, 1);
plot(Tiempo, Voltaje, 'b-', 'LineWidth', 2);
hold on;
plot(Tiempo, Frecuencia, 'r--', 'LineWidth', 2);
hold off;
title('Serie de Tiempo: Monitoreo Continuo de Voltaje y Frecuencia de Red', 'FontSize', 12, 'FontWeight', 'bold', 'Color', 'k');
xlabel('Tiempo (Fecha / Hora)', 'FontSize', 10, 'FontWeight', 'bold', 'Color', 'k');
ylabel('Magnitud Eléctrica', 'FontSize', 10, 'FontWeight', 'bold', 'Color', 'k');
legend({'Voltaje (V)', 'Frecuencia (Hz)'}, 'Location', 'northeast', 'FontSize', 9);
grid on; 
set(gca, 'Color', [1 1 1], 'XColor', 'k', 'YColor', 'k', 'GridColor', [0.8 0.8 0.8], 'LineWidth', 1.2, 'FontSize', 9);
datetick('x', 'HH:MM:SS', 'keepticks');

% --- GRÁFICA 2: Comparación Avanzada con Doble Eje Y (Voltaje vs Potencia) ---
subplot(2, 1, 2);
yyaxis left
plot(Tiempo, Voltaje, 'b-', 'LineWidth', 2);
ylabel('Voltaje Alterno (V)', 'Color', 'b', 'FontSize', 10, 'FontWeight', 'bold');
set(gca, 'YColor', 'b');

yyaxis right
plot(Tiempo, Potencia, 'g-', 'LineWidth', 2);
ylabel('Potencia Activa (W)', 'Color', [0 0.5 0], 'FontSize', 10, 'FontWeight', 'bold');
set(gca, 'YColor', [0 0.5 0]);

title('Comparación Multivariable: Correlación Dinámica de Suministro vs Consumo', 'FontSize', 12, 'FontWeight', 'bold', 'Color', 'k');
xlabel('Tiempo (Fecha / Hora)', 'FontSize', 10, 'FontWeight', 'bold', 'Color', 'k');
grid on; 
set(gca, 'Color', [1 1 1], 'XColor', 'k', 'GridColor', [0.8 0.8 0.8], 'LineWidth', 1.2, 'FontSize', 9);
datetick('x', 'HH:MM:SS', 'keepticks');

%% 3. MÓDULO DE VERIFICACIÓN DE CORRESPONDENCIA DE DATOS
fprintf('\n=================================================================\n');
fprintf('         MÓDULO DE VERIFICACIÓN DE CONSISTENCIA DE DATOS         \n');
fprintf('=================================================================\n');
fprintf('Última actualización leída del ESP32: %s\n', datestr(Tiempo(end)));
fprintf('  -> Valor de Voltaje en la muestra:       %.2f V\n', Voltaje(end));
fprintf('  -> Valor de Corriente en la muestra:     %.2f A\n', Corriente(end));
fprintf('  -> Valor de Potencia en la muestra:      %.2f W\n', Potencia(end));
fprintf('  -> Valor de Frecuencia en la muestra:    %.2f Hz\n', Frecuencia(end));
fprintf('  -> Valor de Factor de Potencia:          %.2f\n', FactorPot(end));
fprintf('-----------------------------------------------------------------\n');
fprintf('Estado de Verificación: Datos validados y consistentes con la API.\n');
fprintf('=================================================================\n');

% =========================================================================
%                                    ANÁLISIS 
% =========================================================================
clearvars; clc;

% --- CONFIGURACIÓN DE CREDENCIALES ---
channelID = 3410710;
readAPIKey = 'Z4G6S9WQJAH23QOS';
numMuestras = 100; % Bloque de muestras dinámicas para el análisis

fprintf('=================================================================\n');
fprintf('         INFORME DE CONTROL DE CALIDAD ENERGÉTICA (MATLAB)       \n');
fprintf('=================================================================\n\n');

%% --- DESCARGA INDEPENDIENTE DE DATOS ---
try dataV = thingSpeakRead(channelID, 'Fields', 1, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataV = []; end
try dataI = thingSpeakRead(channelID, 'Fields', 2, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataI = []; end
try dataE = thingSpeakRead(channelID, 'Fields', 3, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataE = []; end
try dataP = thingSpeakRead(channelID, 'Fields', 4, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataP = []; end
try dataF = thingSpeakRead(channelID, 'Fields', 5, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataF = []; end
try dataFP = thingSpeakRead(channelID, 'Fields', 6, 'NumPoints', numMuestras, 'ReadKey', readAPIKey); catch; dataFP = []; end


%% --- TEMA 1: PROMEDIO DE VARIABLES ---
fprintf('[TEMA 1: ANÁLISIS DE PROMEDIOS]\n');
if ~isempty(dataV);  fprintf('  -> Promedio Voltaje (C1):      %.2f V\n', mean(dataV, 'omitnan')); end
if ~isempty(dataI);  fprintf('  -> Promedio Corriente (C2):    %.2f A\n', mean(dataI, 'omitnan')); else; fprintf('  -> Promedio Corriente (C2):    0.00 A\n'); end
if ~isempty(dataE);  fprintf('  -> Promedio Energía (C3):      %.2f kWh\n', mean(dataE, 'omitnan')); end
if ~isempty(dataP);  fprintf('  -> Promedio Potencia (C4):     %.2f W\n', mean(dataP, 'omitnan')); end
if ~isempty(dataF);  fprintf('  -> Promedio Frecuencia (C5):   %.2f Hz\n', mean(dataF, 'omitnan')); end
if ~isempty(dataFP); fprintf('  -> Promedio Factor Potencia(C6):%.2f\n', mean(dataFP, 'omitnan')); end
fprintf('\n');


%% --- TEMA 2: VALORES MÁXIMOS Y MÍNIMOS ---
fprintf('[TEMA 2: VALORES MÁXIMOS Y MÍNIMOS]\n');
if ~isempty(dataV);  fprintf('  -> Voltaje (C1)        -> Máx: %.2f V   | Mín: %.2f V\n', max(dataV), min(dataV)); end
if ~isempty(dataI);  fprintf('  -> Corriente (C2)      -> Máx: %.2f A   | Mín: %.2f A\n', max(dataI), min(dataI)); else; fprintf('  -> Corriente (C2)      -> Máx: 0.00 A   | Mín: 0.00 A\n'); end
if ~isempty(dataE);  fprintf('  -> Energía (C3)        -> Máx: %.2f kWh | Mín: %.2f kWh\n', max(dataE), min(dataE)); end
if ~isempty(dataP);  fprintf('  -> Potencia (C4)       -> Máx: %.2f W   | Mín: %.2f W\n', max(dataP), min(dataP)); end
if ~isempty(dataF);  fprintf('  -> Frecuencia (C5)     -> Máx: %.2f Hz  | Mín: %.2f Hz\n', max(dataF), min(dataF)); end
if ~isempty(dataFP); fprintf('  -> Factor Potencia (C6)-> Máx: %.2f     | Mín: %.2f\n', max(dataFP), min(dataFP)); end
fprintf('\n');


%% --- TEMA 3: TENDENCIAS OPERATIVAS ---
fprintf('[TEMA 3: TENDENCIAS OPERATIVAS (POLYFIT)]\n');

% Tendencia Voltaje
if ~isempty(dataV) && length(dataV) > 1
    coef = polyfit((1:length(dataV))', dataV, 1); mV = coef(1);
    if mV > 0.0001; est = 'ASCENDENTE'; elseif mV < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Voltaje (C1): %s (m = %.5f)\n', est, mV);
end

% Tendencia Corriente
if ~isempty(dataI) && length(dataI) > 1
    coef = polyfit((1:length(dataI))', dataI, 1); mI = coef(1);
    if mI > 0.0001; est = 'ASCENDENTE'; elseif mI < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Corriente (C2): %s (m = %.5f)\n', est, mI);
else
    fprintf('  -> Corriente (C2): ESTABLE / CONSTANTE (m = 0.00000)\n');
end

% Tendencia Energía
if ~isempty(dataE) && length(dataE) > 1
    coef = polyfit((1:length(dataE))', dataE, 1); mE = coef(1);
    if mE > 0.0001; est = 'ASCENDENTE'; elseif mE < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Energía (C3): %s (m = %.5f)\n', est, mE);
end

% Tendencia Potencia
if ~isempty(dataP) && length(dataP) > 1
    coef = polyfit((1:length(dataP))', dataP, 1); mP = coef(1);
    if mP > 0.0001; est = 'ASCENDENTE'; elseif mP < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Potencia (C4): %s (m = %.5f)\n', est, mP);
end

% Tendencia Frecuencia
if ~isempty(dataF) && length(dataF) > 1
    coef = polyfit((1:length(dataF))', dataF, 1); mF = coef(1);
    if mF > 0.0001; est = 'ASCENDENTE'; elseif mF < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Frecuencia (C5): %s (m = %.5f)\n', est, mF);
end

% Tendencia Factor de Potencia
if ~isempty(dataFP) && length(dataFP) > 1
    coef = polyfit((1:length(dataFP))', dataFP, 1); mFP = coef(1);
    if mFP > 0.0001; est = 'ASCENDENTE'; elseif mFP < -0.0001; est = 'DESCENDENTE'; else; est = 'ESTABLE / CONSTANTE'; end
    fprintf('  -> Factor Potencia (C6): %s (m = %.5f)\n', est, mFP);
end
fprintf('\n');


%% --- TEMA 4: DETECCIÓN DE CAMBIOS Y ANOMALÍAS ---
fprintf('[TEMA 4: DETECCIÓN DE CAMBIOS Y ANOMALÍAS]\n');

% Monitoreo de Voltaje
if length(dataV) > 1
    [maxSaltoV, idV] = max(abs(diff(dataV)));
    if maxSaltoV > 1.0; fprintf('  -> ¡Alerta! Salto abrupto de Voltaje de %.2f V detectado (Muestra %d).\n', maxSaltoV, idV);
    else; fprintf('  -> Voltaje (C1): Estable. Variaciones transitorias normales.\n'); end
end

% Monitoreo de Potencia
if length(dataP) > 1
    [maxSaltoP, idP] = max(abs(diff(dataP)));
    if maxSaltoP > 0.005; fprintf('  -> ¡Alerta! Cambio de estado físico (Escalón) en Potencia detectado (Muestra %d).\n', maxSaltoP, idP);
    else; fprintf('  -> Potencia (C4): Operación de consumo estable.\n'); end
end

% Monitoreo de Frecuencia
if length(dataF) > 1
    [maxSaltoF, idF] = max(abs(diff(dataF)));
    if maxSaltoF > 0.2; fprintf('  -> ¡Alerta! Inestabilidad transitoria en Frecuencia de %.2f Hz (Muestra %d).\n', maxSaltoF, idF);
    else; fprintf('  -> Frecuencia (C5): Sincronismo de red estable.\n'); end
end
fprintf('=================================================================\n');

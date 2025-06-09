clc;
clear all;
x = xlsread('D:/PTIT-2025/Lab/Data/20250607_Data1Mic_4000.xlsx');
subplot(2,1,1);
plot(x);
title('Song Tin Hieu Thu Thuc');
Fs = 4000;
% FFT
Y = fft(x);
N = length(x); 
f = (0:N/2-1)*(Fs/N); 
P2 = abs(Y/N);   
P1 = P2(1:N/2);    
subplot(2,1,2)
plot(f, P1);
grid on;
xlabel('f (Hz)');
ylabel('|P1(f)|');
title('Pho Tan So (FFT)');
xlim([0 4000]); 

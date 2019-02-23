clc; clear; close all;

p10 = [0.308; 0.310;0.310;0.310];
p25 = [0.894; 0.895;0.893;0.893];
p40 = [1.495; 1.496; 1.496; 1.497];
p55 = [2.105; 2.104; 2.104;2.103];

m10 = mean(p10);
m25 = mean(p25);
m40 = mean(p40);
m55 = mean(p55);


s10 = std(p10);
s25 = std(p25);
s40 = std(p40);
s55 = std(p55);

[beta, sigma, r] = ols([10; 25; 40; 55], [m10;m25;m40;m55]);

qo = [10; 25; 40; 55];
qi = [m10;m25;m40;m55];

sqo = sqrt(sum(((beta*qi .+ sigma) - qo).^2)/4);
sqi = sqo/beta;
sm =  sqrt((4*(sqo^2))/((4*sum(qi.^2))-(sum(qi)^2)));
sc =  sqrt((sum(qi.^2)*(sqo^2))/((4*sum(qi.^2))-(sum(qi)^2)));

variance = [sqo;sqi;sm;sc].^2;
t1 = (3/(9.35^2))*variance;
t2 = (3/(0.216^2))*variance;

x = linspace(0, 5);
y = beta*x + sigma;

graphics_toolkit('gnuplot');

figure;
plot(x,y);
title('y = 26.589*x + 1.86');
xlabel('Tensao (mV)');
ylabel('Temperatura (C)');
hold on;

plot(m10,10,'-mo','Markersize',10);
plot(m25,25,'-mo','Markersize',10);
plot(m40,40,'-mo','Markersize',10);
plot(m55,55,'-mo','Markersize',10);

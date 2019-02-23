clc; clear; close all;
graphics_toolkit('gnuplot');

sigma = 1000;
beta = 1000;
x = linspace(0, 15, 15*60/5);
y = beta*x + sigma;
y = [y (ones(length(x),1)' * (15*beta + sigma))];
x = [x linspace(15, 30, 15*60/5)];

lastMean = 0;
actualMean = zeros(length(x),1)';

%%%%%%%%%% meanFilter %%%%%%%%%%%%%
for i=1:length(x)
  
  if (i == 1)
    lastMean = y(i); 
    actualMean(i) = lastMean;    
  else
    actualMean(i) = ((i-1)/i)*lastMean + (y(i)/i);
    lastMean = actualMean(i);
  end
end

%%%%%%%%%% mobileMeanFilter %%%%%%%%%%%%%

actualMobMean = zeros(length(x),1)';
nMobile = 10; %media movel com n elementos

for i=1:length(x)
  
  if (i <= nMobile)
    lastMean = mean(y(1:i)); 
    actualMobMean(i) = lastMean; 
  else
    actualMobMean(i) = lastMean + ((y(i) - y(i-nMobile))/nMobile);
    lastMean = actualMobMean(i);
  end
end

%%%%%%%%%% weightMobileMeanFilter %%%%%%%%%%%%%

weightMobileMeanFilter = zeros(length(x),1)';
alfa = 0.5; %media movel com n elementos

for i=1:length(x)
  
  if (i <= 3)
    lastMean = mean(y(1:i)); 
    weightMobileMeanFilter(i) = lastMean; 
  else
    weightMobileMeanFilter(i) = (alfa^3)*weightMobileMeanFilter(i-3) + (alfa^2)*(1-alfa)*y(i-2) + (alfa)*(1-alfa)*y(i-1) + (1-alfa)*y(i);
  end
end

figure;
plot(x,y, 'Color', 'k');
hold on;
plot(x,actualMean, 'Color', 'r');
plot(x,actualMobMean, 'Color', 'g');
plot(x,weightMobileMeanFilter, 'Color', 'b');
legend({'altitude','filtro media','media movel', 'media movel ponderada'},'Location','northwest');
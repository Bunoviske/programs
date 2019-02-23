clc; clear; close all;
graphics_toolkit('gnuplot');

alfa = pi/2;
beta = 0;
gama = 0;

T = [15;15;15];
x = [5;5;5];

Rx = [1 0 0; 0 cos(alfa) -sin(alfa); 0 sin(alfa) cos(alfa)];
Ry = [cos(beta) 0 sin(beta); 0 1 0; -sin(beta) 0 cos(beta)];
Rz = [cos(gama) -sin(gama) 0; sin(gama) cos(gama) 0; 0 0 1];

figure;
quiver3(0,0,0, x(1),x(2),x(3));
hold on;

% Rx+T
xaux = Rx*Ry*Rz*x;
quiver3(T(1),T(2),T(3), xaux(1),xaux(2),xaux(3), 'Color', 'r');

% R(x+T)
xaux = Rx*Ry*Rz*x;
taux = Rx*Ry*Rz*T;
quiver3(taux(1),taux(2),taux(3), xaux(1),xaux(2),xaux(3), 'Color', 'k');

T = [15;0;0];

figure;
quiver3(0,0,0, x(1),x(2),x(3));
hold on;

% Rx+T
xaux = Rx*Ry*Rz*x;
quiver3(T(1),T(2),T(3), xaux(1),xaux(2),xaux(3), 'Color', 'r');

% R(x+T)
xaux = Rx*Ry*Rz*x;
taux = Rx*Ry*Rz*T;
quiver3(taux(1),taux(2),taux(3), xaux(1),xaux(2),xaux(3), 'Color', 'k');


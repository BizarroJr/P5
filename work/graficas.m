clear all;
close all;
tbl = readmatrix('tbl.txt');
x = readmatrix ('x_shrt.txt');

len1=(1:length(x))';
len2=(1:length(tbl))';

figure;
hold on;
plot(len1,x)
plot(len2,tbl,'o');
title('Gr�fica de la pr�ctcia 5');
legend('x','tbl');
hold off;

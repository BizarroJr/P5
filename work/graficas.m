clear all;
close all;
tbl = readmatrix('tbl.txt');
x = readmatrix ('x_shrt.txt');

len1=(1:length(x))';
len2=(1:length(tbl))';

hold on;
plot(len1,x)
plot(len2,tbl,'o');
hold off;
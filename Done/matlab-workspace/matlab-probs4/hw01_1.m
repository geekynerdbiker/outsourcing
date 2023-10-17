x = [-10:0.1:4];
y1 = 2*x;
y2 = 2.8.^(x+0.1) -1;
y3 = 2.7.^x +1;

figure(1)
title("로켓의 수직상승");

plot(x, y1);
hold on;
plot(x, y2);
hold on;
plot(x, y3);

xlim([-1 4]);
ylim([-10 70]);

xlabel("t, 이륙 후의 시간(초)")
ylabel("h, 지상 고도(미터)")


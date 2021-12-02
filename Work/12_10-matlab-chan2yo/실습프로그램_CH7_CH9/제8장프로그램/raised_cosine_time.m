function [ht, time] = raised_cosine_time(Rb, fs, roll_off)
% ------------------------------------------------------------------------
% Impulse response of Raised Cosine Filter
% ------------------------------------------------------------------------
Tb = 1/Rb;      ts = 1/fs;

time = -5*Tb:ts:5*Tb;
ht = sinc(time./Tb).*cos(pi*roll_off*time./Tb)./(1-(4*roll_off^2*time.^2)./Tb^2);

if roll_off == 0.5
    ht(isinf(ht)) = 0;
elseif roll_off == 1.0
    ht(isinf(ht)) = 0.5;
end
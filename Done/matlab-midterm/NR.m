function NR = NR(func,diff,xi,error,maxit)

i = 1; % iteration, �ݺ�Ƚ���� �ʱ�ȭ�Ѵ�.
       % i = 0���� �ʱ�ȭ �� ��� while������ i = i + 1�� ��ġ�� if �� ���� �;� �� ���̴�.
xrold = 0; % ���� ����� ���� xrold�� �����ϰ�, �ʱⰪ�� 0���� �ش�. 
xr = xi;   % ���� xr�� �ϴ� xi�� ���ٰ� �����صд�.

fprintf('Newton-Raphson��\n')
fprintf('iteration              root            error\n')

while(1)                      % �־��� ������ ������ �� ���� ���ѹݺ���Ų��. 
    
    xrold = xr;               % xrold�� ������ ����ص� xr�� ���� ���̴�.
    xr = xr - subs(func,xr)/subs(diff,xr);    % NR���� �⺻ ���� �ִ´�.
    er = (xr-xrold)/xr;                             % �������� ����Ѵ�.
    
    fprintf('    %d         %e        %f\n',i,double(xr),double(er))
    i = i + 1;                       % �ݺ�Ƚ���� 1 ������Ų��.
    
if i == maxit || abs(er) <= error, break, end % ���� Ż�� ������ �����Ѵ�.
                                              % ��� �������� ������ ���ų�
                                              % �ִ� �ݺ�Ƚ����ŭ �ݺ��� ���
end
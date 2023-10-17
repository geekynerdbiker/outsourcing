function SC = SC(func,xi,delta,error,maxit)

i = 1; % iteration, �ݺ�Ƚ���� �ʱ�ȭ�Ѵ�.
       % i = 0���� �ʱ�ȭ �� ��� while������ i = i + 1�� ��ġ�� if �� ���� �;� �� ���̴�.
xrold = 0; % ���� ����� ���� xrold�� �����ϰ�, �ʱⰪ�� 0���� �ش�. 
xr = xi;   % ���� xr�� �ϴ� xi�� ���ٰ� �����صд�.

fprintf('�Ҽ���\n')
fprintf('iteration        root            error\n')

while(1)                      % �־��� ������ ������ �� ���� ���ѹݺ���Ų��. 
    
    xrold = xr;               % xrold�� ������ ����ص� xr�� ���� ���̴�.
    xr = xr - func(xr)/((func(xi+delta) - func(xi))/delta);    % �Ҽ����� �⺻ ���� �ִ´�.
    er = (xr-xrold)/xr;                             % �������� ����Ѵ�.
    
    fprintf('    %d         %f        %f\n',i,double(xr),double(er))
    i = i + 1;                       % �ݺ�Ƚ���� 1 ������Ų��.
    
if i == maxit || abs(er) <= error, break, end % ���� Ż�� ������ �����Ѵ�.
                                              % ��� �������� ������ ���ų�
                                              % �ִ� �ݺ�Ƚ����ŭ �ݺ��� ���
end
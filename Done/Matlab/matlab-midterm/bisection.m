function bisection = bisection(func,xl,xu,error,maxit)

i = 1; % iteration, �ݺ�Ƚ���� �ʱ�ȭ�Ѵ�.
       % i = 0���� �ʱ�ȭ �� ��� while������ i = i + 1�� ��ġ�� if �� ���� �;� �� ���̴�.
xrold = 0; % ���� ����� ���� xrold�� �����ϰ�, �ʱⰪ�� 0���� �ش�. 
xr = xl;   % ���� xr�� �ϴ� xl�� ���ٰ� �����صд�.

fprintf('�̺й�\n')
fprintf('iteration        xl               xu              root            error\n')

while(1)                      % �־��� ������ ������ �� ���� ���ѹݺ���Ų��. 
    test = func(xl)*func(xu); % if������ ���� ������ �̸� ����صд�.
    if test > 0               % ������ �� ������ ���� 0���� ũ�ٸ� �ذ� ���ų� 2�� �̻�
        fprintf('Error : choose different range of function'); % �̺й����� ���� �����ϱ� ��ƴ�.
    else
        xrold = xr;            % xrold�� ���� ������� ����� xr�� ������ �����Ѵ�.
        xr = (xl+xu)/2;        % �̺й����� �ش� ���� �� ���� �����̴�.
        er = (xr-xrold)/xr;    % �ٻ����

        test_2 = func(xr) * func(xl);  % �� ���� ���� ���� �� ��� ������ ������ ���Ѵ�.
        if test_2 < 0                 
            xu = xr;
        else
            xl = xr;
        end
    end
    fprintf('    %d        %f        %f        %f        %f\n',i,xl,xu,xr,er)
    i = i + 1;                       % �ݺ�Ƚ���� 1 ������Ų��.                       

if i == maxit || abs(er) <= error, break, end % ���� Ż�� ������ �����Ѵ�.
                                              % ��� �������� ������ ���ų�
                                              % �ִ� �ݺ�Ƚ����ŭ �ݺ��� ���
end
function bisection = bisection(func,xl,xu,error,maxit)

i = 1; % iteration, 반복횟수를 초기화한다.
       % i = 0으로 초기화 할 경우 while문에서 i = i + 1의 위치가 if 문 위로 와야 할 것이다.
xrold = 0; % 오차 계산을 위한 xrold를 정의하고, 초기값은 0으로 준다. 
xr = xl;   % 해인 xr은 일단 xl과 같다고 설정해둔다.

fprintf('이분법\n')
fprintf('iteration        xl               xu              root            error\n')

while(1)                      % 주어진 조건을 만족할 때 까지 무한반복시킨다. 
    test = func(xl)*func(xu); % if문에서 사용될 조건을 미리 계산해둔다.
    if test > 0               % 구간의 양 끝값의 곱이 0보다 크다면 해가 없거나 2개 이상
        fprintf('Error : choose different range of function'); % 이분법에서 근을 추정하기 어렵다.
    else
        xrold = xr;            % xrold의 값을 현재까지 저장된 xr의 값으로 지정한다.
        xr = (xl+xu)/2;        % 이분법에서 해는 구간 양 끝의 중점이다.
        er = (xr-xrold)/xr;    % 근사오차

        test_2 = func(xr) * func(xl);  % 두 개로 나뉜 구간 중 어느 구간을 택할지 정한다.
        if test_2 < 0                 
            xu = xr;
        else
            xl = xr;
        end
    end
    fprintf('    %d        %f        %f        %f        %f\n',i,xl,xu,xr,er)
    i = i + 1;                       % 반복횟수를 1 증가시킨다.                       

if i == maxit || abs(er) <= error, break, end % 루프 탈출 조건을 지정한다.
                                              % 허용 오차보다 오차가 적거나
                                              % 최대 반복횟수만큼 반복한 경우
end
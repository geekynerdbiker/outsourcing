import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Runtime.getRuntime().addShutdownHook(new Thread() {
            @Override
            public void run() {
                return;
            }
        });

        float input = 0;
        float n1 = 0, n2 = 0;
        float op = 0;

        while (input != '=') {
            input = System.in.read();
            if (input == EOF) break;
            if (input >= '0' && input <= '9') {
                input -= '0'; // 아스키 코드 숫자이기 때문에 '0'의 값만큼 빼주어서 숫자로 변환
                // 첫번째 변수는 숫자값 그대로, 2번째는 위에서 '0'만큼 빼주었기 때문에 아스키 코드 값이 달라서 원래대로 돌린 후 정수형 16진수로 출력
                System.out.format("%d 0x%x\n", (int)input, (int)(input + '0'));
            }
            else if (input == '+' || input == '-' || input == '*' || input == '/') {
                op = input; // 연산자의 경우 별도의 아스키 코드 이동이 불필요하기에 숫자와 달리 그대로 대입
                // 첫번째 변수는 연산자 값 그대로 캐릭터형으로 형변환 후 , 2번째는 아스키 코드 값을 정수형 16진수로 출력
                System.out.format("%c 0x%x\n", (char)input, (int)input);
                continue;
            }

            if (op == 0) {
                n1 = n1 * 10 + input;
            } else if (input != '=') {
                n2 = n2 * 10 + input;
            } else {
                // 첫번째 변수는 문자 값 그대로, 2번째는 아스키 코드 값을 16진수로 출력
                System.out.format("%c 0x%x\n", (char)input, (int)input);
            }
        }

        if (op == '+')
            // 계산 결과 그대로 정수형으로 형변환 후 출력
            System.out.format("%d FLOAT TYPE\n", (int)(n1 + n2));
        else if (op == '-')
            // 계산 결과 그대로 정수형으로 형변환 후 출력
            System.out.format("%d FLOAT TYPE\n", (int)(n1 - n2));
        else if (op == '*')
            // 계산 결과 그대로 정수형으로 형변환 후 출력
            System.out.format("%d FLOAT TYPE\n", (int)(n1 * n2));
        else if (op == '/') {
            if (n2 == 0)
                // 0으로 나누는 경우 계산하지 않음
                System.out.println("Cannot divide by 0.");
            else
                // 계산 결과 그대로 정수형으로 형변환 후 출력
                System.out.format("%d FLOAT TYPE\n", (int)(n1 / n2));
        }
    }
}
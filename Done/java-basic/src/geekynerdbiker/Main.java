package geekynerdbiker;

import java.io.*;
import java.util.StringTokenizer;

public class Main {

    public static void main(String[] args) throws IOException {
        // 파일 입력을 위한 Buffered Reader 및 File Reader 선언.
        BufferedReader br = new BufferedReader(new FileReader("batch.inp"));
        // 파일 출력을 위한 File Writer 선언.
        FileWriter fw = new FileWriter("batch.out");
        // 문자열 토크나이징을 위한 String Tokenizer 선언.
        StringTokenizer st;
        // 파일에서 첫 줄을 읽어서 정수형으로 변환한 후, p에 저장.
        int p = Integer.parseInt(br.readLine());
        // CPU 유휴시간을 저장할 변수 CPU Rest, 처리가 종료된 시간을 저장할 변수 End Time 0으로 초기화.
        int CPURest = 0, endTime = 0;
        // 파일에서 읽어올 수 있는 줄이 없을 때까지 한 줄씩 읽기.
        for (String line = br.readLine(); line != null; line = br.readLine()) {
            // k가 홀수인지 짝수인지 판단하기 위한 변수 k, 0으로 초기화.
            int k = 0;
            // 읽어온 문자열을 공백(" ")을 기준으로 토큰화.
            st = new StringTokenizer(line, " ");
            // 읽어온 문자열을 더이상 토큰화 할 수 없을 때까지 반복.
            while (st.hasMoreTokens()) {
                // 토큰화 한 첫번째 숫자를 정수형으로 변환하여 변수 n에 저장.
                int n = Integer.parseInt(st.nextToken());
                // n이 -1 일때 아무것도 하지 않고 다음 문자열을 읽기 위해 continue.
                if (n == -1) {
                    k = 0;
                    continue;
                }
                // k가 홀수라면, 즉 I/O 작업에 소요되는 시간이라면 CPU 유휴시간에 더함.
                if (k % 2 == 1) CPURest += n;
                // 처리가 종료된 시간에 n을 더함.
                endTime += n;
                // k 증가
                k++;
            }
        }
        // 계산된 CPU 유휴시간과 처리가 종료된 시간을 파일에 씀.
        fw.write(CPURest + " " + endTime);
        // 쓴 파일을 닫음. (닫지 않으면 파일에 쓰이지 않음)
        fw.close();
    }
}

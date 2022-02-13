package geekynerdbiker;

import java.io.*;

public class Main {
    public static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    public static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static MyQueue queue = new MyQueue(1024);
    public static MyQueue attempt1 = new MyQueue(512);
    public static MyQueue attempt2 = new MyQueue(256);
    public static MyQueue attempt3 = new MyQueue(128);
    public static MyQueue attempt4 = new MyQueue(64);
    public static MyQueue attempt5 = new MyQueue(32);

    public static double sizeOfQueue = 0, requeued = 0;

    public static void main(String[] args) throws IOException {
        bw.write("Please enter the total minutes to run: ");
        bw.flush();

        int totalMinutes = Integer.parseInt(br.readLine());

        int totalMessages = 0, minuteCounter = 1, sentMessages = 0;
        double sum = 0, arrivalMessages = 0, averageArrivalRate = 0;

        while (sum < totalMinutes * 60) {
            double arrivalTime = (Math.random() + 1.5) / 1.000;

            queue.push(arrivalTime);
            sum += arrivalTime;

            int successRate = (int) (Math.random() * 100);
            if (successRate > 25) {
                queue.pop();
                sentMessages++;
            } else {
                attempt1.push(queue.pop());
            }

            if (sum <= 60 * minuteCounter) {
                arrivalMessages++;
            } else {
                averageArrivalRate += arrivalMessages;
                minuteCounter++;
                arrivalMessages = 0;
            }

            totalMessages++;
        }
        averageArrivalRate /= totalMinutes;

        int successAttempt1 = attempts(attempt1, attempt2);
        int successAttempt2 = attempts(attempt2, attempt3);
        int successAttempt3 = attempts(attempt3, attempt4);
        int successAttempt4 = attempts(attempt4, attempt5);

        sizeOfQueue = queue.rear + attempt1.rear + attempt2.rear + attempt3.rear + attempt4.rear;

        bw.write("\nTotal number of messages processed: " + totalMessages + "\n");
        bw.write("Average arrival rate: " + averageArrivalRate + "\n");
        bw.write("Average number of messages sent per minute: " + sentMessages / totalMinutes + "\n");
        bw.write("Average number of messages in the queue per minute: " + sizeOfQueue / totalMinutes + "\n");
        bw.write("Number of messages sent on 1st attempt: " + sentMessages + "\n");
        bw.write("Number of messages sent on 2nd attempt: " + successAttempt1 + "\n");
        bw.write("Number of messages sent on 3rd attempt: " + successAttempt2 + "\n");
        bw.write("Number of messages sent on 4th attempt: " + successAttempt3 + "\n");
        bw.write("Number of messages sent on 5th attempt: " + successAttempt4 + "\n");
        bw.write("Average number of times messages had to be requeued: " + requeued / totalMinutes + "\n");
        bw.flush();
    }

    public static int attempts(MyQueue attempt, MyQueue nextAttempt) {
        int sentMessages = 0;
        while (!attempt.isEmpty()) {
            int successRate = (int) (Math.random() * 100);
            if (successRate > 25) {
                attempt.pop();
                sentMessages++;
            } else {
                nextAttempt.push(attempt.pop());
                requeued ++;
            }
        }

        return sentMessages;
    }
}

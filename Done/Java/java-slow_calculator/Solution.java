package ae2;

import java.util.ArrayList;
import java.util.List;

public class Solution implements CommandRunner {
    private final List<Thread> threads;
    private final List<SlowCalculator> tasks;


    public Solution() {
        threads = new ArrayList<>();
        tasks = new ArrayList<>();
    }

    @Override
    public String runCommand(String command) {
        String[] cmd = command.split(" ");
        long n = Long.parseLong(cmd[1]);

        switch (cmd[0]) {
            case "start":
                SlowCalculator task = new SlowCalculator(n);
                tasks.add(task);

                Thread thread = new Thread(() -> {
                    try {
                        task.run();
                    } catch (Exception ignored) {
                    }
                });

                threads.add(thread);
                thread.start();

                return "Started " + Long.toString(n);

            case "cancel":
                n = Long.parseLong(cmd[1]);

                for (int i = 0; i < tasks.size() && i < threads.size(); i++) {
                    if (tasks.get(i).getN() == n) {
                        if (threads.get(i).isAlive()) {
                            threads.get(i).interrupt();
                            return "Cancelled " + n;
                        } else {
                            return "Invalid command";
                        }
                    }
                }
                return "Invalid command";

            case "running":
                int count = 0;
                StringBuilder sb = new StringBuilder();

                for (int i = 0; i < tasks.size() && i < threads.size(); i++)
                    if (threads.get(i).isAlive()) {
                        sb.append(tasks.get(i).getN()).append(" ");
                        count++;
                    }

                return count + " calculations running: " + sb.toString().trim();

            case "get":
                n = Long.parseLong(cmd[1]);

                for (int i = 0; i < tasks.size(); i++) {
                    if (tasks.get(i).getN() == n) {
                        if (Thread.currentThread().isInterrupted()) {
                            return "Interrupted";
                        } else {
                            if (threads.get(i).isAlive()) {
                                return "calculating";
                            } else if (threads.get(i).isInterrupted()) {
                                return "Interrupted";
                            } else {
                                return "result is " + tasks.get(i).getN();
                            }
                        }
                    }
                }

                return "Invalid command";

            case "finish":
                for (Thread th : threads) {
                    try {
                        th.join();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return "Interrupted";
                    }
                }

                return "Finished";

            case "abort":
                for (Thread th : threads) {
                    th.interrupt();
                }
                return "Aborted";

            default:
                return "Invalid command";
        }
    }
}
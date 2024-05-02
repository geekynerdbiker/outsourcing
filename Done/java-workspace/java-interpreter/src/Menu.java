import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Scanner;

public class Menu {
    public static String fname = "Task5a.txt";
    public static BufferedReader brf;
    public static StringBuilder sb;

    Scanner in = null;
    public ArrayList<String> data;

    public void runIt() {
        System.out.print("\f");
        String menuOpt = "";
        in = new Scanner(System.in);
        do {
            System.out.print("\nST2-2023 Assignment 1\n");
            System.out.print("(" + fname + ")\n");
            System.out.print("Q -  Exit/Quit\n");
            System.out.print("W -  Who Am I (Task1)\n");
            System.out.print("R -  Read SAIL2023 File   (Task 1)\n");
            System.out.print("E -  Execute SAIL2023File (Task 1)\n");
            System.out.print("E2 - Execute SAIL2023File (Task 2)\n");
            //System.out.printf("E3 - Execute SAIL2023File (Task 3)\n");
            //System.out.printf("E4 - Execute SAIL2023File (Task 4)\n");
            //System.out.printf("E5 - Execute SAIL2023File (Task 5)\n");
            System.out.print("S  - Set File name\n");
            System.out.print("D  - Execute With Debug (Not assessed)\n");
            System.out.print("T1 - Debug and Testing  (not assessed)\n");
            System.out.print("T2 - Debug and Testing  (not assessed)\n");
            System.out.print("T3 - Debug and Testing  (not assessed)\n");
            System.out.print("T4 - Debug and Testing  (not assessed)\n");

            System.out.print("Select Option:\n");
            menuOpt = in.nextLine().trim().toUpperCase();
            //System.out.println("You entered : " + menuOpt);
            if (menuOpt.compareToIgnoreCase("W") == 0) {
                optW();
            }
            if (menuOpt.compareToIgnoreCase("R") == 0) {
                optR();
            }
            if (menuOpt.compareToIgnoreCase("E") == 0) {
                optE(true, false);
            }
            if (menuOpt.compareToIgnoreCase("D") == 0) {
                optE(false, true);
            }
            if (menuOpt.compareToIgnoreCase("E2") == 0) {
                optE2();
            }
            if (menuOpt.compareToIgnoreCase("S") == 0) {
                optS();
            }
            if (menuOpt.compareToIgnoreCase("T1") == 0) {
                optT1();
            }
            if (menuOpt.compareToIgnoreCase("T2") == 0) {
                optT2();
            }
            if (menuOpt.compareToIgnoreCase("T3") == 0) {
                optT3();
            }
            if (menuOpt.compareToIgnoreCase("T4") == 0) {
                optT4();
            }

        } while (menuOpt.compareToIgnoreCase("Q") != 0); // Note the != this time
        System.out.print("\nEnding Now\n");
    }

    public void optW() {
        System.out.println("\nAuthor: Robert Cox s999999\n");
    }

    public void optT4() {
        //inter.showVars();    
    }

    public void optT3() {
    }

    public void optT2() {
        // delete this bit it gives away too much - no it dosent .. yes it does . err hi rob  
        Hashtable<String, Integer> varz = new Hashtable<>();

        varz.put("aa", 12);
        varz.put("zzz", 99);
        varz.replace("aa", 91);

        System.out.println("Value at key = aa:" + varz.get("aa"));
        System.out.println("Value at key = zzz:" + varz.get("zzz"));
        System.out.println("Value at key = mm:" + varz.get("mm"));

        for (String key : varz.keySet()) {
            Integer value = varz.get(key);

            System.out.println("Var:" + key + " is " + value);

        }

    }

    public void optT1() {

    }

    public void optR() {
        System.out.println("\n Option - R\n");

    }

    public void optE(boolean showOpt, boolean dbg) {
        String path = "TestFiles/" + fname;

        data = new ArrayList<>();
        try {
            brf = new BufferedReader(new FileReader(path));
            System.out.println("Reading code file " + fname);

            String sLine = null;
            int lines = 0, nonComment = 0;
            while ((sLine = brf.readLine()) != null) {
                if (sLine.compareTo("") == 0)
                    continue;
                if (sLine.charAt(0) == '/' && sLine.charAt(1) == '/')
                    continue;
                data.add(sLine);
                lines++;

                nonComment++;
            }

            System.out.println("Number Of Lines Read in is            :" + Integer.toString(lines));
            System.out.println("Number Of Non Comment Lines Read in is:" + Integer.toString(nonComment));
            System.out.println("---------- Running Code ----------");

            Hashtable<String, Integer> ht = new Hashtable<>();

            int startWhile = -1, endWhile = -1;
            boolean ifFlag = false, whileFlag = false;
            boolean inIfCondition = false, inWhileCondition = false;

            for (int idx = 0; idx < data.size(); idx++) {
                if (data.get(idx).compareTo("") == 0)
                    continue;
                String[] command = data.get(idx).split(" ");

                command[0] = command[0].replaceAll("\t", "");
                if (!ifFlag || inIfCondition) {
                    if (data.get(idx).charAt(0) == '/') {
                        continue;
                    } else if (command[0].equals("set")) {
                        ht.put(command[1], Integer.parseInt(command[3]));
                    } else if (command[0].equals("add")) {
                        try {
                            int value = Integer.parseInt(command[1]);
                            if (!ht.containsKey(command[3]))
                                ht.put(command[3], 0);
                            ht.put(command[3], ht.get(command[3]) + value);
                        } catch (NumberFormatException e) {
                            ht.put(command[3], ht.get(command[3]) + ht.get(command[1]));
                        }
                    } else if (command[0].equals("subtract")) {
                        try {
                            int value = Integer.parseInt(command[1]);
                            ht.put(command[3], ht.get(command[3]) - value);
                        } catch (NumberFormatException e) {
                            ht.put(command[3], ht.get(command[3]) - ht.get(command[1]));
                        }
                    } else if (command[0].equals("multiply")) {
                        try {
                            int value = Integer.parseInt(command[3]);
                            ht.put(command[1], ht.get(command[1]) * value);
                        } catch (NumberFormatException e) {
                            ht.put(command[1], ht.get(command[1]) * ht.get(command[3]));
                        }
                    } else if (command[0].equals("divide")) {
                        try {
                            int value = Integer.parseInt(command[3]);
                            ht.put(command[1], ht.get(command[1]) / value);
                        } catch (NumberFormatException e) {
                            ht.put(command[1], ht.get(command[1]) / ht.get(command[3]));
                        }
                    } else if (command[0].equals("print")) {
                        if (command[1].charAt(0) == '\'') {
                            sb = new StringBuilder();
                            for (int i = 1; i < command.length; i++)
                                sb.append(command[i]).append(" ");
                            sb.deleteCharAt(0);
                            sb.deleteCharAt(sb.length() - 1);
                            sb.deleteCharAt(sb.length() - 1);
                            System.out.print(sb.toString());
                        } else if (command[1].equals("cls")) {
                            System.out.print("\f");
                        } else {
                            try {
                                int val = Integer.parseInt(command[1]);
                                System.out.print(val);
                            } catch (NumberFormatException e) {
                                System.out.print(ht.get(command[1]));
                            }
                        }
                    } else if (command[0].equals("println")) {
                        if (command[1].charAt(0) == '\'') {
                            sb = new StringBuilder();
                            for (int i = 1; i < command.length; i++)
                                sb.append(command[i]).append(" ");
                            sb.deleteCharAt(0);
                            sb.deleteCharAt(sb.length() - 1);
                            sb.deleteCharAt(sb.length() - 1);
                            System.out.println(sb.toString());
                        } else if (command[1].equals("cls")) {
                            System.out.println("\f");
                        } else {
                            try {
                                int val = Integer.parseInt(command[1]);
                                System.out.println(val);
                            } catch (NumberFormatException e) {
                                System.out.println(ht.get(command[1]));
                            }
                        }
                    } else if (command[0].equals("if")) {
                        ifFlag = true;
                        String op = command[2];

                        try {
                            int val1 = Integer.parseInt(command[1]);
                            try {
                                int val2 = Integer.parseInt(command[3]);

                                if (op.compareTo("<") == 0) {
                                    if (val1 < val2)
                                        inIfCondition = true;
                                } else if (op.compareTo(">") == 0) {
                                    if (val1 > val2)
                                        inIfCondition = true;
                                } else if (op.compareTo("==") == 0) {
                                    if (val1 == val2)
                                        inIfCondition = true;
                                }
                            } catch (NumberFormatException e) {
                                if (op.compareTo("<") == 0) {
                                    if (val1 < ht.get(command[3]))
                                        inIfCondition = true;
                                } else if (op.compareTo(">") == 0) {
                                    if (val1 > ht.get(command[3]))
                                        inIfCondition = true;
                                } else if (op.compareTo("==") == 0) {
                                    if (val1 == ht.get(command[3]))
                                        inIfCondition = true;
                                }
                            }
                        } catch (NumberFormatException e) {
                            try {
                                int val2 = Integer.parseInt(command[3]);

                                if (op.compareTo("<") == 0) {
                                    if (ht.get(command[1]) < val2)
                                        inIfCondition = true;
                                } else if (op.compareTo(">") == 0) {
                                    if (ht.get(command[1]) > val2)
                                        inIfCondition = true;
                                } else if (op.compareTo("==") == 0) {
                                    if (ht.get(command[1]) == val2)
                                        inIfCondition = true;
                                }
                            } catch (NumberFormatException ex) {
                                if (op.compareTo("<") == 0) {
                                    if (ht.get(command[1]) < ht.get(command[3]))
                                        inIfCondition = true;
                                } else if (op.compareTo(">") == 0) {
                                    if (ht.get(command[1]) > ht.get(command[3]))
                                        inIfCondition = true;
                                } else if (op.compareTo("==") == 0) {
                                    if (ht.get(command[1]) == ht.get(command[3]))
                                        inIfCondition = true;
                                }
                            }
                        }
                    } else if (command[0].equals("endif")) {
                        ifFlag = false;
                    } else if (command[0].equals("while")) {
                        whileFlag = true;
                        startWhile = idx;
                        String op = command[2];

                        try {
                            int val1 = Integer.parseInt(command[1]);
                            try {
                                int val2 = Integer.parseInt(command[3]);

                                if (op.compareTo("<") == 0) {
                                    if (val1 < val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo(">") == 0) {
                                    if (val1 > val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo("==") == 0) {
                                    if (val1 == val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                }
                            } catch (NumberFormatException e) {
                                if (op.compareTo("<") == 0) {
                                    if (val1 < ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo(">") == 0) {
                                    if (val1 > ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo("==") == 0) {
                                    if (val1 == ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                }
                            }
                        } catch (NumberFormatException e) {
                            try {
                                int val2 = Integer.parseInt(command[3]);

                                if (op.compareTo("<") == 0) {
                                    if (ht.get(command[1]) < val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo(">") == 0) {
                                    if (ht.get(command[1]) > val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo("==") == 0) {
                                    if (ht.get(command[1]) == val2)
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                }
                            } catch (NumberFormatException ex) {
                                if (op.compareTo("<") == 0) {
                                    if (ht.get(command[1]) < ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo(">") == 0) {
                                    if (ht.get(command[1]) > ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                } else if (op.compareTo("==") == 0) {
                                    if (ht.get(command[1]) == ht.get(command[3]))
                                        inWhileCondition = true;
                                    else inWhileCondition = false;
                                }
                            }
                        }
                        if (!inWhileCondition)
                            idx = endWhile;
                    } else if (command[0].equals("endwhile")) {
                        endWhile = idx;
                        if (inWhileCondition)
                            idx = startWhile - 1;
                    } else if (command[0].equals("end")) {
                        return;
                    }
                }
            }
        } catch (FileNotFoundException e) {
            e.getStackTrace();
        } catch (IOException e) {
            e.getStackTrace();
        }
    }

    public void optE2() {
        System.out.println("\n Option - E2\n");
        optE(false, false);
    }

    public void optS() {
        System.out.printf("Select Option:\n");
        System.out.printf("0- enter file name:\n");
        System.out.printf("1- Task1a:\n");
        System.out.printf("2- Task1b:\n");
        System.out.printf("3- Task1c:\n");
        System.out.printf("4- Task1d:\n"); // add more options if you find them usefull        
        System.out.printf("5- Task2a:\n"); // add more options if you find them usefull        
        System.out.printf("6- Task2b:\n"); // add more options if you find them usefull
        System.out.printf("7- Task3a:\n");
        System.out.printf("8- Task3b:\n");

        System.out.printf("9- Task4a:\n");
        System.out.printf("10- Task4b:\n");
        System.out.printf("11- Task4c:\n");

        System.out.printf("12- Task5a:\n");

        String opt = in.nextLine().trim().toUpperCase();

        switch (opt) {
            case "0":
                opt0();
                break;

            case "1":
                fname = "Task1a.txt";
                break;

            case "2":
                fname = "Task1b.txt";
                break;

            case "3":
                fname = "Task1c.txt";
                break;

            case "4":
                fname = "Task1d.txt";
                break;

            case "5":
                fname = "Task2a.txt";
                break;

            case "6":
                fname = "Task2b.txt";
                break;

            case "7":
                fname = "Task3a.txt";
                break;

            case "8":
                fname = "Task3b.txt";
                break;

            case "9":
                fname = "Task4a.txt";
                break;

            case "10":
                fname = "Task4b.txt";
                break;

            case "11":
                fname = "Task4c.txt";
                break;

            case "12":
                fname = "Task5a.txt";
                break;

        }
    }

    public void opt0() {
        fname = "";
        while (fname.compareTo("") == 0) {
            System.out.printf("0- enter file name:\n");
            fname = in.nextLine().trim();
        }
        System.out.print("file set to " + fname);
    }

}
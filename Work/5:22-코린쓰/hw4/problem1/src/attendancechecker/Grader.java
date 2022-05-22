package attendancechecker;

import attendancechecker.attendance.AttendanceList;
import attendancechecker.attendance.Student;
import attendancechecker.attendance.Lecture;

import attendancechecker.utils.Pair;

import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.util.*;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Grader {

    public long logsToMinutes(String startLog, String endLog) {
        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        long minutes = 0;

        try {
            Date startTime = formatter.parse(startLog);
            Date endTime = formatter.parse(endLog);

            minutes = (endTime.getTime() - startTime.getTime());
        } catch (Exception e) {
            e.printStackTrace();
        }

        return minutes;
    }

    public Map<String, Map<String, Double>> gradeSimple(AttendanceList attendanceList, String attendanceDirPath) {
        // TODO Problem 1-1
        Map<String, Map<String, Double>> attendance = new HashMap<>();
        List<Student> students = attendanceList.students;
        List<Lecture> lectures = attendanceList.lectures;

        for (Student student : students) {
            Map<String, Double> scores = new HashMap<>();
            String attDir = attendanceDirPath + "/" + student.id;
            for (Lecture lecture : lectures) {
                String dirPath = Paths.get(attDir, "/", lecture.id, "/log0.txt").toString();
                try {
                    BufferedReader br = new BufferedReader(new FileReader(dirPath));

                    String line, startTime = null, endTime = null;
                    long lectureTime = 0, attendTime = 0;
                    while ((line = br.readLine()) != null) {
                        startTime = br.readLine();
                        br.readLine();
                        endTime = br.readLine();
                        attendTime += this.logsToMinutes(startTime, endTime);
                    }
                    lectureTime = this.logsToMinutes(lecture.lectureStart, lecture.lectureEnd);

                    double score = 0;
                    if (attendTime >= lectureTime * 0.7) score = 1;
                    else if (attendTime >= lectureTime * 0.1) score = 0.5;

                    scores.put(lecture.id, score);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                attendance.put(student.id, scores);
            }
        }
        return attendance;
    }


    public Map<String, Map<String, Double>> gradeRobust(AttendanceList attendanceList, String attendanceDirPath) {
        // TODO Problem 1-2
        Map<String, Map<String, Double>> attendance = new HashMap<>();
        List<Student> students = attendanceList.students;
        List<Lecture> lectures = attendanceList.lectures;

        for (Student student : students) {
            Map<String, Double> scores = new HashMap<>();
            String attDir = attendanceDirPath + "/" + student.id;
            for (Lecture lecture : lectures) {
                File[] logs = new File(Paths.get(attDir, "/", lecture.id).toString()).listFiles();

                String line, startTime = null, endTime = null;
                long lectureTime = 0, attendTime = 0;

                for (int i = 0; i < logs.length; i++) {
                    String dirPath = Paths.get(attDir, "/", lecture.id, "/log" + i + ".txt").toString();
                    try {
                        BufferedReader br = new BufferedReader(new FileReader(dirPath));

                        while ((line = br.readLine()) != null) {
                            if (line.compareTo("Admitted") == 0) {
                                attendTime = this.logsToMinutes(lecture.lectureStart, lecture.lectureEnd);
                                break;
                            } else if (line.compareTo("Refused") == 0) {
                                attendTime = this.logsToMinutes(lecture.lectureStart, lecture.lectureStart);
                                break;
                            }
                            startTime = br.readLine();
                            if (startTime.compareTo(lecture.lectureStart) < 0)
                                startTime = lecture.lectureStart;
                            br.readLine();

                            endTime = br.readLine();
                            if (endTime.compareTo(lecture.lectureEnd) > 0)
                                endTime = lecture.lectureEnd;

                            long temp = this.logsToMinutes(startTime, endTime);
                            if( temp != attendTime)
                                attendTime += this.logsToMinutes(startTime, endTime);
                        }
                        lectureTime = this.logsToMinutes(lecture.lectureStart, lecture.lectureEnd);

                        double score = 0;
                        if (attendTime >= lectureTime * 0.7) score = 1;
                        else if (attendTime >= lectureTime * 0.1) score = 0.5;

                        scores.put(lecture.id, score);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    attendance.put(student.id, scores);
                }
            }
        }
        return attendance;
    }

}


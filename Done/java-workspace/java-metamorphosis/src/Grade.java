public class Grade {
    private String subject;
    private double score;

    public Grade(String subject, double score) {
        this.subject = subject;
        this.score = score;
    }

    public String getSubject() {
        return subject;
    }

    public double getScore() {
        return score;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public static char getLetterGrade(double score) {
        if (score >= 70)
            return 'A';
        else if (score >= 60)
            return 'B';
        else if (score >= 50)
            return 'C';
        else if (score >= 40)
            return 'D';
        else if (score < 40)
            return 'F';
        else
            return 'E';
    }
}

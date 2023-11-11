interface Report {
    public abstract void displayContent();
}

class BasicReport implements Report {
    private String msg;

    public BasicReport(String msg) {
        this.msg = msg;
    }

    @Override
    public void displayContent() {
        System.out.println(msg);
    }
}

class ReportAdded implements Report {
    private Report report;

    public ReportAdded(Report report) {
        this.report = report;
    }

    @Override
    public void displayContent() {
        report.displayContent();
    }
}

class Star extends ReportAdded {
    public Star(Report report) {
        super(report);
    }

    public void displayContent() {
        displayStar();
        super.displayContent();
        displayStar();
    }

    private void displayStar() {
        System.out.println("****************");
    }
}

class Sharp extends ReportAdded {
    public Sharp(Report report) {
        super(report);
    }

    public void displayContent() {
        displaySharp();
        super.displayContent();
        displaySharp();
    }

    private void displaySharp() {
        System.out.println("################");
    }
}

public class Main {
    public static void main(String[] args) {
        Report r = new Sharp(new Star(new BasicReport("Design Pattern")));
        r.displayContent();
    }
}
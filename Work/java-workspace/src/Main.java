import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main extends JFrame {
    // At the left side, there is a big picture
    private JLabel westLabel;

    // Within EastPanel, Several Forms will show
    private JPanel eastPanel;

    // At top-right, there are title and logo
    private JLabel topLabel;

    // applicant name box
    private JPanel applicantBox;
    private JTextArea applicantName;
    private JTextArea applicantNameInput;

    // birth date box
    private JPanel birthDateBox;
    private JTextArea birthDate;
    private JTextArea birthDateInput;

    // email box
    private JPanel emailBox;
    private JTextArea email;
    private JTextArea emailInput;

    // degree box
    private JPanel degreeBox;
    private JTextArea degree;
    private JTextArea degreeInput;

    // attended university box
    private JPanel attendedUniversityBox;
    private JTextArea attendedUniversity;
    private JTextArea attendedUniversityInput;

    // gpa box
    private JPanel gpaBox;
    private JTextArea gpa;
    private JTextArea gpaInput;

    // personal statement box
    private JPanel personalStatementBox;
    private JTextArea personalStatement;
    private JTextArea personalStatementInput;

    // home address box
    private JPanel homeAddressBox;
    private JTextArea homeAddress;
    private JTextArea homeAddressInput;

    // phone number box
    private JPanel phoneNumberBox;
    private JTextArea phoneNumber;
    private JTextArea phoneNumberInput;

    // agree box
    private JPanel agreeBox;
    private JCheckBox agreeInput;

    // when click submit button, pop up will show
    private JButton submitButton;

    public Main() {
        // For batching elements, border layout looks good
        setLayout(new BorderLayout(10, 10));

        Container container = this.getContentPane();

        //======================LEFT LOGO=========================
        // For importing the logo, the path is necessary and image will include in Jlabel
        ImageIcon logo = new ImageIcon(getClass().getResource("images/skku_wallpaper.png"));
        westLabel = new JLabel();

        // opaque should be true for changing its background color
        westLabel.setOpaque(true);
        westLabel.setIcon(logo); // add icon into topLabel
        westLabel.setBackground(Color.WHITE);
        container.add(westLabel, BorderLayout.WEST);

        //======================RIGHT PANEL=========================
        eastPanel = new JPanel(); // west panel includes three button
        eastPanel.setLayout(new BoxLayout(eastPanel, BoxLayout.Y_AXIS)); // Align components vertically
        eastPanel.setBorder(BorderFactory.createEmptyBorder(0, 15, 0, 0)); // Set Margin
        eastPanel.setSize(600, 650);
        eastPanel.setBackground(Color.WHITE);

        // Top title Image
        ImageIcon skku = new ImageIcon(getClass().getResource("images/title_label.png"));
        topLabel = new JLabel();

        topLabel.setOpaque(true);
        topLabel.setIcon(skku);
        topLabel.setBackground(Color.WHITE);
        topLabel.setAlignmentX(CENTER_ALIGNMENT);
        topLabel.setBorder(BorderFactory.createEmptyBorder(10, 100, 10, 100));

        eastPanel.add(topLabel);

        // ============ Applicant Name Box, Text, Input =============
        applicantBox = new JPanel();
        applicantBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        applicantBox.setBackground(Color.WHITE);
        applicantBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        applicantBox.setMaximumSize(new Dimension(600, 30));

        applicantName = new JTextArea();
        applicantName.setText("Applicant Name: ");
        applicantName.setEditable(false);
        applicantName.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        applicantNameInput = new JTextArea();
        applicantNameInput.setMinimumSize(new Dimension(270, 16));
        applicantNameInput.setPreferredSize(new Dimension(270, 16));
        applicantNameInput.setMaximumSize(new Dimension(270, 16));
        applicantNameInput.setBackground(Color.WHITE);
        applicantNameInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        applicantBox.add(applicantName);
        applicantBox.add(applicantNameInput);
        eastPanel.add(applicantBox);

        // ============ Birth Date Box, Text, Input =============
        birthDateBox = new JPanel();
        birthDateBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        birthDateBox.setBackground(Color.WHITE);
        birthDateBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        birthDateBox.setMaximumSize(new Dimension(600, 30));

        birthDate = new JTextArea();
        birthDate.setText("Birth Date: ");
        birthDate.setEditable(false);
        birthDate.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        birthDateInput = new JTextArea();
        birthDateInput.setMinimumSize(new Dimension(270, 16));
        birthDateInput.setPreferredSize(new Dimension(270, 16));
        birthDateInput.setMaximumSize(new Dimension(270, 16));
        birthDateInput.setBackground(Color.WHITE);
        birthDateInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        birthDateBox.add(birthDate);
        birthDateBox.add(birthDateInput);
        eastPanel.add(birthDateBox);

        // ============ Email Box, Text, Input =============
        emailBox = new JPanel();
        emailBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        emailBox.setBackground(Color.WHITE);
        emailBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        emailBox.setMaximumSize(new Dimension(600, 30));

        email = new JTextArea();
        email.setText("Email: ");
        email.setEditable(false);
        email.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        emailInput = new JTextArea();
        emailInput.setMinimumSize(new Dimension(270, 16));
        emailInput.setPreferredSize(new Dimension(270, 16));
        emailInput.setMaximumSize(new Dimension(270, 16));
        emailInput.setBackground(Color.WHITE);
        emailInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        emailBox.add(email);
        emailBox.add(emailInput);
        eastPanel.add(emailBox);

        // ============ Degree Box, Text, Input =============
        degreeBox = new JPanel();
        degreeBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        degreeBox.setBackground(Color.WHITE);
        degreeBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        degreeBox.setMaximumSize(new Dimension(600, 30));

        degree = new JTextArea();
        degree.setText("Degree: ");
        degree.setEditable(false);
        degree.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        degreeInput = new JTextArea();
        degreeInput.setMinimumSize(new Dimension(270, 16));
        degreeInput.setPreferredSize(new Dimension(270, 16));
        degreeInput.setMaximumSize(new Dimension(270, 16));
        degreeInput.setBackground(Color.WHITE);
        degreeInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        degreeBox.add(degree);
        degreeBox.add(degreeInput);
        eastPanel.add(degreeBox);

        // ============ Attended University Box, Text, Input =============
        attendedUniversityBox = new JPanel();
        attendedUniversityBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        attendedUniversityBox.setBackground(Color.WHITE);
        attendedUniversityBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        attendedUniversityBox.setMaximumSize(new Dimension(600, 30));

        attendedUniversity = new JTextArea();
        attendedUniversity.setText("Attended university (for Graduates): ");
        attendedUniversity.setEditable(false);
        attendedUniversity.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        attendedUniversityInput = new JTextArea();
        attendedUniversityInput.setMinimumSize(new Dimension(270, 16));
        attendedUniversityInput.setPreferredSize(new Dimension(270, 16));
        attendedUniversityInput.setMaximumSize(new Dimension(270, 16));
        attendedUniversityInput.setBackground(Color.WHITE);
        attendedUniversityInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        attendedUniversityBox.add(attendedUniversity);
        attendedUniversityBox.add(attendedUniversityInput);
        eastPanel.add(attendedUniversityBox);

        // ============ GPA Box, Text, Input =============
        gpaBox = new JPanel();
        gpaBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        gpaBox.setBackground(Color.WHITE);
        gpaBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        gpaBox.setMaximumSize(new Dimension(600, 30));

        gpa = new JTextArea();
        gpa.setText("GPA (for Graduates): ");
        gpa.setEditable(false);
        gpa.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        gpaInput = new JTextArea();
        gpaInput.setMinimumSize(new Dimension(270, 16));
        gpaInput.setPreferredSize(new Dimension(270, 16));
        gpaInput.setMaximumSize(new Dimension(270, 16));
        gpaInput.setBackground(Color.WHITE);
        gpaInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        gpaBox.add(gpa);
        gpaBox.add(gpaInput);
        eastPanel.add(gpaBox);

        // ============ Home Address Box, Text, Input =============
        personalStatementBox = new JPanel();
        personalStatementBox.setLayout(new FlowLayout(FlowLayout.CENTER));
        personalStatementBox.setBackground(Color.WHITE);
        personalStatementBox.setMaximumSize(new Dimension(500, 100));
        personalStatementBox.setBorder(BorderFactory.createEmptyBorder(16, 0, 8, 10));

        personalStatement = new JTextArea();
        personalStatement.setText("Personal Statement");
        personalStatement.setEditable(false);

        personalStatementInput = new JTextArea();
        personalStatementInput.setFont(new Font("", Font.ITALIC, 12));
        personalStatementInput.setText("At least 100 words.");
        personalStatementInput.setMinimumSize(new Dimension(500, 60));
        personalStatementInput.setPreferredSize(new Dimension(500, 60));
        personalStatementInput.setMaximumSize(new Dimension(500, 60));
        personalStatementInput.setBackground(Color.lightGray);
        personalStatementInput.setLineWrap(true);

        personalStatementBox.add(personalStatement);
        personalStatementBox.add(personalStatementInput);
        eastPanel.add(personalStatementBox);

        // ============ Home Address Box, Text, Input =============
        homeAddressBox = new JPanel();
        homeAddressBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        homeAddressBox.setBackground(Color.WHITE);
        homeAddressBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        homeAddressBox.setMaximumSize(new Dimension(600, 30));

        homeAddress = new JTextArea();
        homeAddress.setText("Home Address: ");
        homeAddress.setEditable(false);
        homeAddress.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        homeAddressInput = new JTextArea();
        homeAddressInput.setMinimumSize(new Dimension(270, 16));
        homeAddressInput.setPreferredSize(new Dimension(270, 16));
        homeAddressInput.setMaximumSize(new Dimension(270, 16));
        homeAddressInput.setBackground(Color.WHITE);
        homeAddressInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        homeAddressBox.add(homeAddress);
        homeAddressBox.add(homeAddressInput);
        eastPanel.add(homeAddressBox);

        // ============ Phone Number Box, Text, Input =============
        phoneNumberBox = new JPanel();
        phoneNumberBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        phoneNumberBox.setBackground(Color.WHITE);
        phoneNumberBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 8, 10));
        phoneNumberBox.setMaximumSize(new Dimension(600, 30));

        phoneNumber = new JTextArea();
        phoneNumber.setText("Phone Number: ");
        phoneNumber.setEditable(false);
        phoneNumber.setAlignmentX(JTextArea.RIGHT_ALIGNMENT);

        phoneNumberInput = new JTextArea();
        phoneNumberInput.setMinimumSize(new Dimension(270, 16));
        phoneNumberInput.setPreferredSize(new Dimension(270, 16));
        phoneNumberInput.setMaximumSize(new Dimension(270, 16));
        phoneNumberInput.setBackground(Color.WHITE);
        phoneNumberInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));

        phoneNumberBox.add(phoneNumber);
        phoneNumberBox.add(phoneNumberInput);
        eastPanel.add(phoneNumberBox);

        // ============ Agree Box, Check =============
        agreeBox = new JPanel();
        agreeBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        agreeBox.setBackground(Color.WHITE);
        agreeBox.setBorder(BorderFactory.createEmptyBorder(8, 0, 30, 10));
        agreeBox.setMaximumSize(new Dimension(550, 60));

        agreeInput = new JCheckBox("I agree with providing my personal information.");
        agreeInput.setBackground(Color.WHITE);
        agreeInput.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));


        agreeBox.add(agreeInput);
        eastPanel.add(agreeBox);

        // ============ Submit Button =============
        submitButton = new JButton();
        submitButton.setText("Submit Application");
        submitButton.setFont(new Font("", Font.BOLD, 12));
        submitButton.setBackground(Color.BLUE);
        submitButton.setForeground(Color.WHITE);
        submitButton.setOpaque(true);
        submitButton.setBorderPainted(false);
        submitButton.setMaximumSize(new Dimension(300, 50));
        submitButton.setAlignmentX(CENTER_ALIGNMENT);
        submitButton.setAlignmentY(CENTER_ALIGNMENT);

        submitButton.addActionListener(new ButtonHandler());

        eastPanel.add(submitButton);

        container.add(eastPanel, BorderLayout.EAST);


    }

    public static void main(String[] args) {
        // Initially, shows the panel
        Main skkuForm = new Main();
        skkuForm.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        skkuForm.setSize(900, 650);
        skkuForm.setVisible(true);
        skkuForm.setTitle("SKKU New Students Enrollment");
    }

    private class ButtonHandler implements ActionListener {

        JFrame jFrame = new JFrame();
        JTextArea jTextArea;

        @Override
        public void actionPerformed(ActionEvent e) {
            String result = "";
            int num = 1;
            // 0. name check
            String[] name = applicantNameInput.getText().split("\\s+");

            if (name.length < 2) {
                if (applicantNameInput.getText().length() == 0) {
                    result += (Integer.toString(num) + ". You forgot to fill the name text field.\n");
                    num++;
                } else {
                    result += (Integer.toString(num) + ". You forgot to write your name or surname \n");
                    num++;
                }
            }

            // 1. empty field check
            if (degreeInput.getText().length() == 0) {
                result += (Integer.toString(num) + ". You forgot to fill the degree text field.\n");
                num++;
            }

            if (homeAddressInput.getText().length() == 0) {
                result += (Integer.toString(num) + ". You forgot to fill the home address text field.\n");
                num++;
            }

            if (personalStatementInput.getText().length() == 0) {
                result += (Integer.toString(num) + ". You forgot to fill the personal statement text field.\n");
                num++;
            }

            // 2. birth date format
            if (birthDateInput.getText().matches("([0-9]{2})/([0-9]{2})/([0-9]{4})")) {
            } else {
                if (birthDateInput.getText().length() == 0) {
                    result += (Integer.toString(num) + ". You forgot to fill the birth date text field.\n");
                    num++;
                } else {
                    result += (Integer.toString(num) + ". Birthdate must be in '06/06/1995' format \n");
                    num++;
                }
            }

            // 3. email check
            String regexEmail = "^(.+)@(.+)$";
            Pattern patternEmail = Pattern.compile(regexEmail);
            Matcher matcherEmail = patternEmail.matcher(emailInput.getText());
            if (matcherEmail.matches()) {
            } else {
                if (emailInput.getText().length() == 0) {
                    result += (Integer.toString(num) + ". You forgot to fill the email text field.\n");
                    num++;
                } else {
                    result += (Integer.toString(num) + ". Email must be in example@some.some \n");
                    num++;
                }
            }

            // 4. phone number check
            String regexPhone = "^[0-9\\s-]*$";
            Pattern patternPhone = Pattern.compile(regexPhone);
            Matcher matcherPhone = patternPhone.matcher(phoneNumberInput.getText());
            if (matcherPhone.matches()) {
            } else {
                if (phoneNumberInput.getText().length() == 0) {
                    result += (Integer.toString(num) + ". You forgot to fill the phone number text field.\n");
                    num++;
                } else {
                    result += (Integer.toString(num) + ". Proper format for a phone number is ‘10 2158-0222’ \n");
                    num++;
                }
            }

            // 5. attended university & gpa 6. gpa range check
            if (degreeInput.getText().equals("Bachelor")) {
                if (attendedUniversityInput.getText().length() != 0 || gpaInput.getText().length() != 0) {
                    result += (Integer.toString(num) + ". For Bachelor, you have to empty previous university and GPA \n");
                    num++;
                }
            } else {
                if (attendedUniversityInput.getText().length() == 0 || gpaInput.getText().length() == 0) {
                    result += (Integer.toString(num) + ". For graduate, you have to enter previous university and GPA \n");
                    num++;
                } else {
                    int gpa_str = gpaInput.getText().trim().length();
                    if (gpa_str > 0) {
                        double gpa_num = Double.parseDouble(gpaInput.getText().trim());
                        if (gpa_num < 0 || gpa_num > 4.5) {
                            result += (Integer.toString(num) + ". GPA must be between 0 and 4.5 \n");
                            num++;
                        }
                    }
                }
            }
            // 7. personal statement check
            if (personalStatementInput.getText().length() < 100) {
                result += (Integer.toString(num) + ". Your Personal Statement must be at least 100 words \n");
                num++;
            }

            // 8. get agreement
            if (!agreeInput.isSelected()) {
                result += (Integer.toString(num) + ". You have to agree with providing personal information. \n");
                num++;
            }

            JOptionPane jOptionPane = new JOptionPane();
            if (result.length() == 0)
                JOptionPane.showMessageDialog(null, "Successfully Submitted", "Success Message", JOptionPane.INFORMATION_MESSAGE);
            else
                JOptionPane.showMessageDialog(null, result, "You have following problems", JOptionPane.ERROR_MESSAGE);

            GridBagConstraints gbc = new GridBagConstraints();
            gbc.gridwidth = GridBagConstraints.REMAINDER;
            gbc.fill = GridBagConstraints.HORIZONTAL;
        }
    }
}

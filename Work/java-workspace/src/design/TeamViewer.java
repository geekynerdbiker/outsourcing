package design;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TeamViewer {
    private int managers = 1;
    private int supervisors = 0;
    private int salespeople = 0;
    private double sales = 0;
    private double commissions = 0;

    public TeamViewer() {
        JFrame frame = new JFrame("App");
        JPanel panel = new JPanel();
        JTree tree = new JTree();

        JTextField position = new JTextField();
        JTextField value = new JTextField();

        JButton add = new JButton("ADD");
        JButton sales = new JButton("SALES");

        JLabel hintAdd = new JLabel("(Manager / Supervisor / Salesperson)");
        JLabel hintSales = new JLabel("Sales value larger than 0");
        JLabel totalSales = new JLabel("SALES: 0");
        JLabel totalCommissions = new JLabel("COMMISSIONS: 0");

        Member rootMember = new Manager();

        frame.setPreferredSize(new Dimension(580, 580));

        DefaultMutableTreeNode manager = new DefaultMutableTreeNode("Manager");
        tree = new JTree(manager);
        tree.setBounds(0, 0, 200, 580);
        frame.add(tree);

        panel.setLayout(null);
        totalSales.setBounds(220, 100, 300, 30);
        totalCommissions.setBounds(220, 120, 300, 30);
        panel.add(totalSales);
        panel.add(totalCommissions);

        hintAdd.setBounds(220, 200, 300, 30);
        position.setBounds(220, 240, 300, 30);
        add.setBounds(220, 280, 300, 30);
        panel.add(hintAdd);
        panel.add(position);
        panel.add(add);

        hintSales.setBounds(220, 300, 300, 30);
        value.setBounds(220, 340, 300, 30);
        sales.setBounds(220, 380, 300, 30);
        panel.add(hintSales);
        panel.add(value);
        panel.add(sales);

        frame.add(panel);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);

        JTree finalTree = tree;
        add.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String input = position.getText();
                DefaultMutableTreeNode selected = (DefaultMutableTreeNode) finalTree.getLastSelectedPathComponent();

                DefaultTreeModel model = (DefaultTreeModel) finalTree.getModel();
                DefaultMutableTreeNode root = (DefaultMutableTreeNode) model.getRoot();

                if (selected == null || selected.toString().equals("Salesperson")) {
                    return;
                } else if (selected.toString().equals("Supervisor")) {
                    if (input.equals("Supervisor")) {
                        setSupervisors(1);
                        selected.add(new DefaultMutableTreeNode("Supervisor"));
                    } else if (input.equals("Salesperson")) {
                        setSalespeople(1);
                        selected.add(new DefaultMutableTreeNode("Salesperson"));
                    }
                } else if (selected.toString().equals("Manager")) {
                    if (input.equals("Manager")) {
                        setManagers(1);
                        selected.add(new DefaultMutableTreeNode("Manager"));
                    } else if (input.equals("Supervisor")) {
                        setSupervisors(1);
                        selected.add(new DefaultMutableTreeNode("Supervisor"));
                    } else if (input.equals("Salesperson")) {
                        setSalespeople(1);
                        selected.add(new DefaultMutableTreeNode("Salesperson"));
                    }
                }
                model.reload(root);
            }
        });
        sales.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String input = value.getText();
                if (Integer.parseInt(input) < 0) return;
                else {
                    setSales(Double.parseDouble(input));
                    double commissions = calculateCommissions();
                    setCommissions(commissions);
                    totalSales.setText("SALES: " + getSales());
                    totalCommissions.setText("COMMISSIONS: " + getCommissions());

                }
            }
        });
    }

    int getManagers() {
        return this.managers;
    }

    int getSupervisors() {
        return this.supervisors;
    }

    int getSalespeople() {
        return this.salespeople;
    }

    double getSales() {
        return this.sales;
    }

    double getCommissions() {
        return this.commissions;
    }

    void setManagers(int n) {
        this.managers += n;
    }

    void setSupervisors(int n) {
        this.supervisors += n;
    }

    void setSalespeople(int n) {
        this.salespeople += n;
    }

    void setSales(double n) {
        this.sales = n;
    }

    void setCommissions(double n) {
        this.commissions = n;
    }

    double calculateCommissions() {
        return getSales() * ((getManagers() * 0.02) + (getSupervisors() * 0.03) + (getSalespeople() * 0.04));
    }

    public static void main(String args[]) {
        new TeamViewer();
    }
}

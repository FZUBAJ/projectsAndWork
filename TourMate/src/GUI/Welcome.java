package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Welcome class in which user decides whether they want to login or register
 */
public class Welcome extends JDialog {
    private JPanel contentPane;
    private JButton btnLogin;
    private JButton btnRegister;
    private JPanel welcomePanel;
    private JButton btnCancel;
    private JButton buttonOK;
    private JButton buttonCancel;

    public Welcome() {
        setContentPane(contentPane);
        setTitle("Welcome to TourMate");
        setModal(true);
        setMinimumSize(new Dimension(650, 500));
        setLocationRelativeTo(null);

        btnLogin.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                loginForm login = new loginForm(null);
                login.setVisible(true);
            }
        });


        btnRegister.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                registerForm register = new registerForm(null);
                register.setVisible(true);
            }
        });

        btnCancel.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int choice = JOptionPane.showConfirmDialog(null, "Are you sure you want to cancel?", "Cancel", JOptionPane.YES_NO_OPTION);
                if (choice == JOptionPane.YES_OPTION) {
                    System.exit(0);
                }
            }
        });

        setVisible(true);
    }
}




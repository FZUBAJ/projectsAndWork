package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * This class is responsible for the registration form
 * It is used to create a new account
 * It is used to add a new user to the database
 * After this, login is opened and after logging in, you are redirected to the main menu
 */
public class registerForm extends JDialog{
    private JTextField tfUsername;
    private JTextField tfEmail;
    private JTextField tfPhone;
    private JTextField tfAge;
    private JTextField tfPassword;
    private JTextField tfCheckPassword;
    private JButton btnSubmit;
    private JButton btnCancel;
    private JPanel registerPanel;
    private JCheckBox yesCheckBox;


    /**
     * This constructor is used to create a new registration form
     * @param parent is the parent frame
     */
    public registerForm(JFrame parent) {
        super(parent);
        setTitle("Create a new account");
        setContentPane(registerPanel);
        setMinimumSize(new Dimension(450, 474));
        setModal(true);
        setLocationRelativeTo(parent);

        btnSubmit.addActionListener(e -> {
            registerUser();
            dispose();
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

    /**
     * This method is used to register a new user
     * It checks if all fields are filled
     * It checks if the age is a valid number
     * It checks if the password and check password are the same
     * It checks if the user is a professional or not
     * It adds the user to the database
     */
    private void registerUser() {
        String username = tfUsername.getText();
        String email = tfEmail.getText();
        String phone = tfPhone.getText();
        String ageText = tfAge.getText();
        String password = tfPassword.getText();
        String checkPassword = tfCheckPassword.getText();
        boolean yesCheckBoxSelected = yesCheckBox.isSelected();

        if (username.isEmpty() || email.isEmpty() || phone.isEmpty() || password.isEmpty() || checkPassword.isEmpty() || ageText.isEmpty()) {
            JOptionPane.showMessageDialog(this, "For successful registration, you need to fill all fields", "Try again", JOptionPane.ERROR_MESSAGE);
            SwingUtilities.invokeLater(() -> {
                registerForm newRegisterForm = new registerForm(null); // Open a new registration form
                dispose(); // Close the current registration form
            });
            return; // Return if any field is empty
        }

        int age;
        try {
            age = Integer.parseInt(ageText);
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Age must be a valid number", "Try again", JOptionPane.ERROR_MESSAGE);
            return; // Return if age is not a valid number
        }


        if(!checkPassword.equals(password)){
            JOptionPane.showMessageDialog(this, "The password and check password don't match !", "Try again", JOptionPane.ERROR_MESSAGE);
            return;
        }

        addUserToDatabase(username, email, phone, age, password, yesCheckBoxSelected);
        loginForm login = new loginForm(null);
    }

    //get connection to sql database

    /**
     * This method is used to get a connection to the database
     * @return the connection to the database
     * @throws SQLException if the connection fails
     */
    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://127.0.0.1:3306/users";
        String username = "root";
        String password = "Zubko1234";
        return DriverManager.getConnection(url, username, password);
    }

    private void addUserToDatabase(String username, String email, String phone, int age, String password, boolean yesCheckBoxSelected) {
        String insertQuery;
        if (age >= 18 && yesCheckBoxSelected) {
            insertQuery = "INSERT INTO professionals (username, password, email, phone, age) VALUES (?, ?, ?, ?, ?)";
        } else if (age >= 18) {
            insertQuery = "INSERT INTO adults (username, password, email, phone, age) VALUES (?, ?, ?, ?, ?)";
        } else {
            insertQuery = "INSERT INTO children (username, password, email, phone, age) VALUES (?, ?, ?, ?, ?)";
        }

        try (Connection conn = getConnection();
             PreparedStatement stmt = conn.prepareStatement(insertQuery)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, email);
            stmt.setString(4, phone);
            stmt.setInt(5, age);
            stmt.executeUpdate();
            JOptionPane.showMessageDialog(this, "Registration successful", "Success", JOptionPane.INFORMATION_MESSAGE);
            dispose();
        } catch (SQLException e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(this, "Failed to add user to database", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
    }

package GUI;

import Logic.User.*;
import Logic.Thread.LoginTimeoutThread;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import javax.swing.*;
import java.awt.*;

/**
 * This class is responsible for the login form
 * It is a JDialog that is called from the main menu
 */
public class loginForm extends JDialog{
    private JPanel loginPanel;
    private JTextField tfUsername;
    private JTextField tfPassword;
    private JButton btnSubmit;
    private JButton btnCancel;

    /**
     * Constructor for the login form
     * @param parent parental JFrame
     */
    public loginForm (JFrame parent){
        super(parent);
        setTitle("Login");
        setContentPane(loginPanel);
        setMinimumSize(new Dimension(450, 474));
        setModal(true);
        setLocationRelativeTo(parent);

        LoginTimeoutThread loginTimeoutThread = new LoginTimeoutThread(this);
        loginTimeoutThread.setDaemon(true);
        loginTimeoutThread.start();

        btnSubmit.addActionListener(e -> {
            loginUser();
            dispose();
            chooseFunctionality chooseFunctionality = new chooseFunctionality();
            chooseFunctionality.setVisible(true);

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
     * This method is responsible for the connection to the database
     * @return connection to the database
     * @throws SQLException if the connection fails
     */
    private Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://127.0.0.1:3306/users";
        String username = "root";
        String password = "Zubko1234";
        return DriverManager.getConnection(url, username, password);
    }


    /**
     * This method is responsible for the login functionality
     * It checks if the username and password are correct
     * If they are, it logs the user in
     */
    private void loginUser() {
        String username = tfUsername.getText();
        String password = tfPassword.getText();

        if(username.isEmpty() || password.isEmpty()){
            JOptionPane.showMessageDialog(this, "For successful login, you have to fill both fields", "Try again", JOptionPane.ERROR_MESSAGE);
            return;
        }

        try{ //solve the sql problem
            Connection connection = getConnection();
            String sql = "SELECT * FROM professionals WHERE username = ? AND password = ? UNION " +
                    "SELECT * FROM adults WHERE username = ? AND password = ? UNION " +
                    "SELECT * FROM children WHERE username = ? AND password = ?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, username);
            statement.setString(2, password);
            statement.setString(3, username);
            statement.setString(4, password);
            statement.setString(5, username);
            statement.setString(6, password);

            ResultSet result = statement.executeQuery();
            if(!result.next()){
                JOptionPane.showMessageDialog(this, "Invalid username or password", "Try again", JOptionPane.ERROR_MESSAGE);
                return;
            }
            int age = result.getInt("age");
            if(age >= 18){
                Adult user = new Adult(result.getString("username"), result.getString("email"), result.getString("phone"), result.getString("password"), age);
            }
            else{
                Child user = new Child(result.getString("username"), result.getString("email"), result.getString("phone"), result.getString("password"), age);
                JOptionPane.showMessageDialog(this, "As an underage, you are not allowed to login", "Try again", JOptionPane.ERROR_MESSAGE);
                return;
            }
            JOptionPane.showMessageDialog(this, "Login successful", "Success", JOptionPane.INFORMATION_MESSAGE);
        } catch(SQLException e){
            JOptionPane.showMessageDialog(this, "Database error: " +e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }


    }

}

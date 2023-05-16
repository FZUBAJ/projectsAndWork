package GUI;

import javax.swing.*;
import java.awt.event.*;

/**
 * This class is responsible for the GUI of the hike options.
 */
public class chooseFunctionality extends JDialog {
    private JPanel contentPane;
    private JButton startNewHikeButton;
    private JButton exitButton;
    private JButton buttonOK;
    private JButton buttonCancel;

    /**
     * chooseFunctionality constructor
     */
    public chooseFunctionality() {
        setTitle("Choose functionality");
        setContentPane(contentPane);
        setModal(true);
        setMinimumSize(new java.awt.Dimension(650, 500));
        setLocationRelativeTo(null);

        //this is the button to start a new hike
        startNewHikeButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                dispose();
                choosingHike chooseHike = new choosingHike(null);
                chooseHike.setVisible(true);
            }
        });

        //this is the button to rate the last attented hike
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                System.exit(0);
            }
        });

        setVisible(true);
    }

}

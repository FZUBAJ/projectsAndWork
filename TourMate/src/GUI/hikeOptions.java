package GUI;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import Logic.Hiking.Hike;

/**
 * This class is responsible for the GUI of the hike options.
 * It is a JDialog that pops up when the user clicks on the "Choose Hike" button.
 */
public class hikeOptions extends JDialog {
    private JPanel contentPane;
    private JComboBox<String> comboBox1;
    private JButton submitButton;
    private JButton cancelButton;
    private JPanel chooseHikeLabel;
    private JButton buttonOK;
    private JButton buttonCancel;

    /**
     * hikeOptions constructor
     * @param hikes the list of all hikes
     */
    public hikeOptions(List<Hike> hikes) {
        setTitle("Choose Hike");
        setContentPane(contentPane);
        setMinimumSize(new java.awt.Dimension(650, 500));
        setLocationRelativeTo(null);
        setModal(true);
        getRootPane().setDefaultButton(buttonOK);

        if(hikes.isEmpty()){
            JOptionPane.showMessageDialog(null, "There is no such hike in our database !");
            dispose();
            System.exit(0);
        }

        for(Hike hike : hikes){
            comboBox1.addItem(hike.getName());
        }


        //this button turns off the program
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int choice = JOptionPane.showConfirmDialog(null, "Are you sure you want to cancel?", "Cancel", JOptionPane.YES_NO_OPTION);
                if (choice == JOptionPane.YES_OPTION) {
                    System.exit(0);
                }
            }
        });

        //this button submits the user's choice
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null, "You have chosen " + comboBox1.getSelectedItem().toString() + "!");
                dispose();
                hikeStatistics hs = new hikeStatistics(hikes.get(comboBox1.getSelectedIndex()));
                hs.setVisible(true);
            }
        });

        setVisible(true);
    }




}

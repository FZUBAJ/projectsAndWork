package GUI;

import Logic.Hiking.Hike;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class hikeStatistics extends JDialog {
    private JPanel contentPane;
    private JLabel namingLabel;
    private JLabel altitudeLabel;
    private JLabel timeLabel;
    private JLabel lengthLabel;
    private JLabel locationLabel;
    private JButton giveRatingButton;
    private JButton mainMenuButton;

    public hikeStatistics(Hike chosenHike) {
        setTitle("Hike Statistics");
        setContentPane(contentPane);
        setModal(true);
        setMinimumSize(new java.awt.Dimension(650, 500));
        setLocationRelativeTo(null);

        namingLabel.setText(chosenHike.getName());
        altitudeLabel.setText(String.valueOf(chosenHike.getAltitude() + " meters"));
        timeLabel.setText(String.valueOf(chosenHike.getTime() + " hours"));
        lengthLabel.setText(String.valueOf(chosenHike.getLength() + " kilometers"));
        locationLabel.setText(chosenHike.getLocation());


        giveRatingButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String x = JOptionPane.showInputDialog("Enter your rating (0 - 5) for this hike: " + chosenHike.getName());
                int rating = Integer.parseInt(x);
                chosenHike.setReview(rating);
                //JOptionPane.showMessageDialog(null, "Thank you for your rating, Average rating for this hike: " + chosenHike.getAverageReview());
            }
        });

        mainMenuButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                chooseFunctionality chooseFunctionality = new chooseFunctionality();
                chooseFunctionality.setVisible(true);
            }
        });

        setVisible(true);
    }
}

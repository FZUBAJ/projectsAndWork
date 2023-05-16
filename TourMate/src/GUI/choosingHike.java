package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import Logic.Hiking.Hike;
import Logic.Hiking.HikeManager;

/**
 * This class is responsible for the GUI of the hike options.
 * It is a JDialog that pops up when the user clicks on the "Choose Hike" button.
 */

public class choosingHike extends JDialog{
    private JCheckBox cbLight;
    private JCheckBox cbMedium;
    private JCheckBox cbDifficult;
    private JPanel choosePanel;
    private JCheckBox cbYesGuide;
    private JCheckBox cbNoGuide;
    private JCheckBox cbShort;
    private JCheckBox cbMiddle;
    private JCheckBox cbLong;
    private JCheckBox cbHour;
    private JCheckBox cbTwoHours;
    private JCheckBox cbMoreHours;
    private JCheckBox cbHotel;
    private JCheckBox cbStayNight;
    private JCheckBox cbSleepAndEat;
    private JButton btnSearch;
    private JButton btnCancel;

    public boolean cbLightIsSelected(){
        return cbLight.isSelected();
    }

    public boolean cbMediumIsSelected(){
        return cbMedium.isSelected();
    }

    public boolean cbDifficultIsSelected(){
        return cbDifficult.isSelected();
    }

    public boolean cbYesGuideIsSelected(){
        return cbYesGuide.isSelected();
    }

    public boolean cbNoGuideIsSelected(){
        return cbNoGuide.isSelected();
    }

    public boolean cbShortIsSelected(){
        return cbShort.isSelected();
    }

    public boolean cbMiddleIsSelected(){
        return cbMiddle.isSelected();
    }

    public boolean cbLongIsSelected(){
        return cbLong.isSelected();
    }

    public boolean cbHourIsSelected(){
        return cbHour.isSelected();
    }

    public boolean cbTwoHoursIsSelected(){
        return cbTwoHours.isSelected();
    }

    public boolean cbMoreHoursIsSelected(){
        return cbMoreHours.isSelected();
    }

    public boolean cbHotelIsSelected(){
        return cbHotel.isSelected();
    }

    public boolean cbStayNightIsSelected(){
        return cbStayNight.isSelected();
    }

    public boolean cbSleepAndEatIsSelected(){
        return cbSleepAndEat.isSelected();
    }


    /**
     * hikeOptions constructor
     * @param parent this is the parent frame
     */
    public choosingHike(JFrame parent) {
        super(parent);
        setTitle("Choose hike");
        setContentPane(choosePanel);
        setMinimumSize(new Dimension(500, 474));
        setModal(true);
        setLocationRelativeTo(parent);

        //method to call the method for filtering the hikes
        btnSearch.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                HikeManager hm = new HikeManager();
                List<Hike> chosenHikes = hm.hikePickBasedOnPreference(cbLightIsSelected(), cbMediumIsSelected(), cbDifficultIsSelected(), cbYesGuideIsSelected(), cbNoGuideIsSelected(), cbShortIsSelected(), cbMiddleIsSelected(), cbLongIsSelected(), cbHourIsSelected(), cbTwoHoursIsSelected(), cbMoreHoursIsSelected(), cbHotelIsSelected(), cbStayNightIsSelected(), cbSleepAndEatIsSelected(), hm.getHikes());
                dispose();
                hikeOptions ho = new hikeOptions(chosenHikes);
                ho.setVisible(true);
            }
        });

        //method to cancel and turn off the program
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

    public void createUIComponents() {

    }



}

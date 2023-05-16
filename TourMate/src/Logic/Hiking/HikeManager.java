package Logic.Hiking;

import Logic.Services.*;
import java.util.ArrayList;
import java.util.List;

/**
 * class to initialise the hikes and sets their accommodation
 * also used for searching hikes based on preferences
 */
public class HikeManager {
    private List<Hike> hikes;
    private List<Cottage> accommodations;


    public HikeManager() {
        hikes = new ArrayList<>();
        accommodations = new ArrayList<>();
        System.out.println("Initializing hikes...");
        initializeHikes();
        printHikes(hikes);
        System.out.println("Done !");
        System.out.println("Initializing accomodation...");
        initializeAccomodation();
        System.out.println("Done !");
        System.out.println("Adding accomodation to hikes...");
        addAccomodationToHikes();
        System.out.println("Done !");
    }

    //this is the design pattern called Factory
    /**
     * design pattern called Factory
     *
     */
    public class HikeFactory {
        /**
         * method for creating a hike
         * @param name name of the hike
         * @param location location of the hike
         * @param difficulty difficulty of the hike
         * @param altitude altitude of the hike
         * @param length length of the hike
         * @param time time of the hike
         * @param needGuide if the hike needs a guide
         * @return the new created hike
         */
        public Hike createHike(String name, String location, String difficulty, int altitude, int length, int time, boolean needGuide) {
            return new Hike(name, location, difficulty, altitude, length, time, needGuide);
        }
    }

    /**
     * method for setting the hikes and adding them to the list
     */
    public void initializeHikes() {
        // Add the hikes to the list
        HikeFactory hf = new HikeFactory();

        Hike hike1 = hf.createHike("Ďumbier", "Nízke Tatry", "Moderate", 2043, 7, 3, false);
        hikes.add(hike1);

        Hike hike2 = hf.createHike("Štefánikova chata", "Nízke Tatry", "Easy", 1500, 3, 2, false);
        hikes.add(hike2);

        Hike hike3 = hf.createHike("Chopok", "Nízke Tatry", "Difficult", 2024, 10, 4, false);
        hikes.add(hike3);

        Hike hike4 = hf.createHike("Veľký Kriváň", "Nízke Tatry", "Difficult", 1709, 8, 4, false);
        hikes.add(hike4);

        Hike hike5 = hf.createHike("Kriváň", "Vysoké Tatry", "Difficult", 2494, 9, 5, false);
        hikes.add(hike5);

        Hike hike6 = hf.createHike("Rysy", "Vysoké Tatry", "Difficult", 2503, 18, 9, false);
        hikes.add(hike6);

        Hike hike7 = hf.createHike("Gerlachovský štít", "Vysoké Tatry", "Difficult", 2655, 10, 5, false);
        hikes.add(hike7);

        Hike hike8 = hf.createHike("Slavkovský štít", "Vysoké Tatry", "Difficult", 2452, 10, 5, false);
        hikes.add(hike8);

        Hike hike9 = hf.createHike("Poludnica", "Liptov", "Easy", 1549, 5, 3, false);
        hikes.add(hike9);

        Hike hike10 = hf.createHike("Juráňova dolina", "Orava", "Easy", 1000, 10, 3, false);
        hikes.add(hike10);

        Hike hike11 = hf.createHike("Malý Kriváň", "Nízke Tatry", "Easy", 1670, 5, 3, false);
        hikes.add(hike11);

        Hike hike12 = hf.createHike("Kráľova hoľa", "Nízke Tatry", "Moderate", 1946, 12, 5, false);
        hikes.add(hike12);

        Hike hike13 = hf.createHike("Čierny Váh", "Nízke Tatry", "Difficult", 2020, 18, 7, true);
        hikes.add(hike13);

        Hike hike14 = hf.createHike("Hrádok", "Malá Fatra", "Moderate", 1443, 8, 4, false);
        hikes.add(hike14);

        Hike hike15 = hf.createHike("Veľký Rozsutec", "Malá Fatra", "Difficult", 1610, 12, 6, true);
        hikes.add(hike15);

        Hike hike16 = hf.createHike("Chleb", "Malá Fatra", "Easy", 1646, 6, 3, false);
        hikes.add(hike16);

        Hike hike17 = hf.createHike("Baranec", "Západné Tatry", "Difficult", 2184, 10, 5, true);
        hikes.add(hike17);

        Hike hike18 = hf.createHike("Bystrá", "Západné Tatry", "Difficult", 2248, 14, 6, true);
        hikes.add(hike18);

        Hike hike19 = hf.createHike("Ostrý Roháč", "Západné Tatry", "Moderate", 2088, 12, 5, false);
        hikes.add(hike19);

        Hike hike20 = hf.createHike("Brestová", "Slovenský raj", "Moderate", 1000, 8, 4, false);
        hikes.add(hike20);

        Hike hike21 = hf.createHike("Tomášovský výhľad", "Slovenský raj", "Easy", 600, 4, 2, false);
        hikes.add(hike21);

        Hike hike22 = hf.createHike("Veľký Sokol", "Slovenský raj", "Difficult", 980, 10, 5, true);
        hikes.add(hike22);

        Hike hike23 = hf.createHike("Veľký Choč", "Chočské vrchy", "Moderate", 1611, 10, 5, false);
        hikes.add(hike23);

        Hike hike24 = hf.createHike("Veľký Javorník", "Javorníky", "Moderate", 1071, 8, 4, false);
        hikes.add(hike24);

        Hike hike25 = hf.createHike("Ratkovská hoľa", "Slovenské rudohorie", "Difficult", 1576, 10, 6, true);
        hikes.add(hike25);

        Hike hike26 = hf.createHike("Ďurková", "Slovenské rudohorie", "Moderate", 1250, 6, 3, false);
        hikes.add(hike26);

        Hike hike27 = hf.createHike("Kriváňsky vodopád", "Malá Fatra", "Easy", 950, 4, 2, false);
        hikes.add(hike27);

        Hike hike28 = hf.createHike("Veľký Choč", "Chočské vrchy", "Difficult", 1611, 10, 5, true);
        hikes.add(hike28);

        Hike hike29 = hf.createHike("Veľký Rozsutec", "Malá Fatra", "Difficult", 1610, 12, 6, true);
        hikes.add(hike29);

        Hike hike30 = hf.createHike("Geravy", "Veľká Fatra", "Moderate", 1420, 10, 5, false);
        hikes.add(hike30);

        Hike hike31 = hf.createHike("Borišov", "Strážovské vrchy", "Moderate", 912, 6, 3, false);
        hikes.add(hike31);

        Hike hike32 = hf.createHike("Stoh", "Strážovské vrchy", "Easy", 743, 4, 2, false);
        hikes.add(hike32);

        Hike hike33 = hf.createHike("Červená skala", "Malá Fatra", "Difficult", 1422, 8, 4, true);
        hikes.add(hike33);

        Hike hike35 = hf.createHike("Roháče", "Západné Tatry", "Hard", 2026, 18, 8, false);
        hikes.add(hike35);

        Hike hike36 = hf.createHike("Prielom Hornádu", "Slovenský raj", "Moderate", 650, 6, 3, false);
        hikes.add(hike36);

    }

    public List<Hike> getHikes() {
        return hikes;
    }

    /**
     * method to initialize the list of accommodations
     */
    public void initializeAccomodation(){


        Cottage cottage1 = new Cottage("Cozy Cabin Retreat", 100, 4, 1);
        accommodations.add(cottage1);

        Cottage cottage2 = new Cottage("Mountain Hideaway Cottage", 120, 6, 2);
        accommodations.add(cottage2);

        Cottage cottage3 = new Cottage("Tranquil Lakeside Chalet", 150, 8, 3);
        accommodations.add(cottage3);

        Cottage cottage4 = new Cottage("Rustic Forest Lodge", 180, 10, 4);
        accommodations.add(cottage4);

        Cottage cottage5 = new Cottage("Secluded Mountain Hut", 90, 3, 5);
        accommodations.add(cottage5);

        Cottage cottage6 = new Cottage("Wilderness Log Cabin", 130, 6, 6);
        accommodations.add(cottage6);

        Cottage cottage7 = new Cottage("Alpine Retreat Cottage", 160, 8, 7);
        accommodations.add(cottage7);

        Cottage cottage8 = new Cottage("Scenic Mountain Chalet", 200, 10, 8);
        accommodations.add(cottage8);

        Cottage cottage9 = new Cottage("Woodland Getaway Cabin", 110, 4, 9);
        accommodations.add(cottage9);

        Cottage cottage10 = new Cottage("Lakeview Mountain Cottage", 140, 6, 10);
        accommodations.add(cottage10);

        CottageWithRestaurant cottageWithRestaurant1 = new CottageWithRestaurant("Luxe Mountain Retreat", 200, 6, 11, "Gourmet Delights", 1);
        accommodations.add(cottageWithRestaurant1);

        CottageWithRestaurant cottageWithRestaurant2 = new CottageWithRestaurant("Riverside Haven", 220, 8, 12, "Rustic Bistro", 2);
        accommodations.add(cottageWithRestaurant2);

        CottageWithRestaurant cottageWithRestaurant3 = new CottageWithRestaurant("Alpine Escape", 250, 10, 13, "Mountain View Restaurant", 3);
        accommodations.add(cottageWithRestaurant3);

        CottageWithRestaurant cottageWithRestaurant4 = new CottageWithRestaurant("Forest Retreat Cottage", 280, 12, 14, "Woodland Dining", 4);
        accommodations.add(cottageWithRestaurant4);

        CottageWithRestaurant cottageWithRestaurant5 = new CottageWithRestaurant("Mountain Oasis Cottage", 230, 8, 15, "Lakeside Restaurant", 5);
        accommodations.add(cottageWithRestaurant5);

        CottageWithRestaurant cottageWithRestaurant6 = new CottageWithRestaurant("Rustic Mountain Lodge", 260, 10, 16, "Panoramic Dining", 6);
        accommodations.add(cottageWithRestaurant6);

        CottageWithRestaurant cottageWithRestaurant7 = new CottageWithRestaurant("Tranquil Forest Cottage", 290, 12, 17, "Wilderness Cuisine", 7);
        accommodations.add(cottageWithRestaurant7);

        CottageWithRestaurant cottageWithRestaurant8 = new CottageWithRestaurant("Alpine Lakeside Cabin", 240, 8, 18, "Mountain Grill", 8);
        accommodations.add(cottageWithRestaurant8);

        CottageWithRestaurant cottageWithRestaurant9 = new CottageWithRestaurant("Scenic Mountain Retreat", 270, 10, 19, "Riverside Eatery", 9);
        accommodations.add(cottageWithRestaurant9);

        MountainHotel hotel1 = new MountainHotel("Grand Alpine Resort", 250, 120, 1, "Alpine View Restaurant", 1, 4, true, true, true, true, true);
        accommodations.add(hotel1);

        MountainHotel hotel2 = new MountainHotel("Snowpeak Lodge", 180, 80, 2, "Summit Dining Hall", 2, 3, false, true, true, false, true);
        accommodations.add(hotel2);

        MountainHotel hotel3 = new MountainHotel("Serenity Mountain Retreat", 300, 150, 3, "Mountain Breeze Restaurant", 3, 5, true, true, true, true, true);
        accommodations.add(hotel3);

        MountainHotel hotel4 = new MountainHotel("Valley Vista Resort", 200, 100, 4, "Sunset Terrace Restaurant", 4, 4, true, false, true, true, true);
        accommodations.add(hotel4);

        MountainHotel hotel5 = new MountainHotel("Alpine Splendor Lodge", 220, 110, 5, "Pinnacle Dining Room", 5, 4, true, true, true, true, true);
        accommodations.add(hotel5);

        MountainHotel hotel6 = new MountainHotel("Mountain Majesty Hotel", 180, 90, 6, "Peakside Grill", 6, 3, false, false, true, true, false);
        accommodations.add(hotel6);

        MountainHotel hotel7 = new MountainHotel("Alpine Retreat Hotel", 280, 130, 7, "Mountain View Restaurant", 7, 5, true, true, true, true, true);
        accommodations.add(hotel7);

        MountainHotel hotel8 = new MountainHotel("Summit Peaks Resort", 240, 100, 8, "Panorama Dining Hall", 8, 4, true, true, true, true, true);
        accommodations.add(hotel8);


    }


    /**
     * in this method, I assign the accommodations to the hikes
     */
    public void addAccomodationToHikes(){

        int iterator = 0;
        for(Cottage accommodation : accommodations) {
            hikes.get(iterator).setAccomodation(accommodation);
            iterator++;
            }
    }

    /**
     * this method is used to pick the hikes based on the user's preference
     * @param cbLightIsSelected is the checkbox for light hike selected
     * @param cbMediumIsSelected is the checkbox for medium hike selected
     * @param cbDifficultIsSelected is the checkbox for difficult hike selected
     * @param cbYesGuideIsSelected is the checkbox for yes guide selected
     * @param cbNoGuideIsSelected is the checkbox for no guide selected
     * @param cbShortIsSelected is the checkbox for short hike selected
     * @param cbMiddleIsSelected is the checkbox for middle hike selected
     * @param cbLongIsSelected is the checkbox for long hike selected
     * @param cbHourIsSelected is the checkbox for 1 hour hike selected
     * @param cbTwoHoursIsSelected is the checkbox for 2 hours hike selected
     * @param cbMoreHoursIsSelected is the checkbox for more hours hike selected
     * @param cbHotelIsSelected is the checkbox for hotel selected
     * @param cbStayNightIsSelected is the checkbox for stay night selected
     * @param cbSleepAndEatIsSelected is the checkbox for sleep and eat selected
     * @param hikes is the list of hikes
     * @return possibleHikes list in which there are only the hikes which are picked based on the user's preference
     *
     */
    public List<Hike> hikePickBasedOnPreference(boolean cbLightIsSelected, boolean cbMediumIsSelected, boolean cbDifficultIsSelected, boolean cbYesGuideIsSelected, boolean cbNoGuideIsSelected, boolean cbShortIsSelected, boolean cbMiddleIsSelected, boolean cbLongIsSelected, boolean cbHourIsSelected, boolean cbTwoHoursIsSelected, boolean cbMoreHoursIsSelected, boolean cbHotelIsSelected, boolean cbStayNightIsSelected, boolean cbSleepAndEatIsSelected, List<Hike> hikes) {
        String difficulty;
        int distanceLowLimit;
        int distanceTopLimit;
        int timeLowLimit;
        int timeHighLimit;


        if(cbLightIsSelected){
            difficulty = "Easy";
        } else if(cbMediumIsSelected){
            difficulty = "Moderate";
        } else if(cbDifficultIsSelected){
            difficulty = "Difficult";
        } else{
            difficulty = "All";
        }

        if(cbShortIsSelected){
            distanceLowLimit = 0;
            distanceTopLimit = 5;
        } else if(cbMiddleIsSelected){
            distanceLowLimit = 5;
            distanceTopLimit = 10;
        } else if(cbLongIsSelected){
            distanceLowLimit = 10;
            distanceTopLimit = 50;
        } else{
            distanceLowLimit = 0;
            distanceTopLimit = 100;
        }

        if(cbHourIsSelected){
            timeLowLimit = 0;
            timeHighLimit = 1;
        } else if(cbTwoHoursIsSelected){
            timeLowLimit = 1;
            timeHighLimit = 2;
        } else if(cbMoreHoursIsSelected){
            timeLowLimit = 2;
            timeHighLimit = 10;
        } else{
            timeLowLimit = 0;
            timeHighLimit = 100;
        }

        List<Hike> possibleHikes = new ArrayList<>();

        for (Hike h : hikes) {

            if(h.getDifficulty().equals(difficulty) || difficulty.equals("All")){
                if(cbYesGuideIsSelected){
                    if(h.getLength() >= distanceLowLimit && h.getLength() <= distanceTopLimit && h.getNeedGuide()){
                        if(h.getTime() >= timeLowLimit && h.getTime() <= timeHighLimit){
                            possibleHikes.add(h);
                        }
                    }
                }
                else if(cbNoGuideIsSelected){
                    if(h.getLength() >= distanceLowLimit && h.getLength() <= distanceTopLimit && !h.getNeedGuide()){
                        if(h.getTime() >= timeLowLimit && h.getTime() <= timeHighLimit){
                            possibleHikes.add(h);
                        }
                    }
                }
                else{
                    if(h.getLength() >= distanceLowLimit && h.getLength() <= distanceTopLimit){
                        if(h.getTime() >= timeLowLimit && h.getTime() <= timeHighLimit){
                            possibleHikes.add(h);
                        }
                    }
                }
            }
        }
        if(possibleHikes.isEmpty()){
            System.out.println("No hikes found");
        }

        System.out.println("The hikes that match your preferences are: ");
        printHikes(possibleHikes);
        return possibleHikes;
    }

    /**
     * method to print every hike
     * lambda method
     * @param hikes the list of the hikes
     */
    public void printHikes(List<Hike> hikes){

        hikes.forEach(hike -> System.out.println(hike.getName()));
    }
}




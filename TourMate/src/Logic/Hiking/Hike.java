package Logic.Hiking;

import Logic.Services.*;
import Logic.User.*;
import java.util.List;
/**
 * hike class to store information about the Hikes that users may attend
 */
public class Hike{
    private Cottage cottage;
    private CottageWithRestaurant cottageWithRestaurant;
    private MountainHotel mountainHotel;
    private String name;
    private String location;
    private String difficulty;
    private int altitude;
    private int length;
    private int time;
    private int review;
    private boolean needGuide;

    public Hike(String name, String location, String difficulty, int altitude, int length, int time, boolean needGuide){
        this.name = name;
        this.location = location;
        this.difficulty = difficulty;
        this.altitude = altitude;
        this.length = length;
        this.time = time;
        this.needGuide = needGuide;
    }

    public Hike(String name, String location, String difficulty, int altitude, int length, int time, boolean needGuide, Cottage cottage){
        this.name = name;
        this.location = location;
        this.difficulty = difficulty;
        this.altitude = altitude;
        this.length = length;
        this.time = time;
        this.needGuide = needGuide;
        this.cottage = cottage;
    }

    public Hike(String name, String location, String difficulty, int altitude, int length, int time, boolean needGuide, CottageWithRestaurant cottageWithRestaurant){
        this.name = name;
        this.location = location;
        this.difficulty = difficulty;
        this.altitude = altitude;
        this.length = length;
        this.time = time;
        this.needGuide = needGuide;
        this.cottageWithRestaurant = cottageWithRestaurant;
    }

    public Hike(String name, String location, String difficulty, int altitude, int length, int time, boolean needGuide, MountainHotel mountainHotel){
        this.name = name;
        this.location = location;
        this.difficulty = difficulty;
        this.altitude = altitude;
        this.length = length;
        this.time = time;
        this.needGuide = needGuide;
        this.mountainHotel = mountainHotel;
    }


    /**
     * method to count the average review for the hike
     * @return average review
     */


    public int getReview(){
        return review;
    }

    public String getName(){
        return name;
    }

    public String getLocation(){
        return location;
    }

    public String getDifficulty(){
        return difficulty;
    }

    public int getAltitude(){
        return altitude;
    }

    public int getLength(){
        return length;
    }

    public int getTime(){
        return time;
    }

    public boolean getNeedGuide(){
        return needGuide;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setLocation(String location){
        this.location = location;
    }

    public void setDifficulty(String difficulty){
        this.difficulty = difficulty;
    }

    public void setAltitude(int altitude){
        this.altitude = altitude;
    }

    public void setLength(int length){
        this.length = length;
    }

    public void setTime(int time){
        this.time = time;
    }

    public void setNeedGuide(boolean needGuide){
        this.needGuide = needGuide;
    }

    public void setReview(int review){
        this.review = review;
    }

    public void setAccomodation(Cottage cottage){
        this.cottage = cottage;
    }
    public void setAccomodation(CottageWithRestaurant cottageWithRestaurant){
        this.cottageWithRestaurant = cottageWithRestaurant;
    }
    public void setAccomodation(MountainHotel mountainHotel){
        this.mountainHotel = mountainHotel;
    }

    /**
     * method to check whether the user has access to the hike
     * @param customer this is the user for which we are checking his access
     * @throws HikeAccessDeniedException this is the exception thrown when the user does not have access to the hike
     */
    public void access(Customer customer) throws HikeAccessDeniedException {
        try {
            if (customer.getAge() < 18) {
                System.out.println("As a child, you don't have access to any hike without adult supervisor !");
            }
            //check whether the user is over 18 and whether he is professional
            else if (customer.getAge() >= 18) {
                if (needGuide && customer instanceof Professional) {
                    System.out.println("As a professional with license, you have access to every hike in our database, however it is strongly recommended to hike with partners");
                } else if (needGuide && customer instanceof Adult) {
                    System.out.println("As an adult, you have access to most of the hike, however you need a guide to get access this hike");
                } else if (!needGuide) {
                    System.out.println("You have access to this hike");
                } else {
                    throw new HikeAccessDeniedException("You do not have an access to this hike !"); //pozitie výnimky v programe
                }
            }
        } catch (HikeAccessDeniedException e) {
            System.out.println(e.getMessage());
        }
    }

    public Cottage getCottage() {
        return cottage;
    }

    public CottageWithRestaurant getCottageWithRestaurant() {
        return cottageWithRestaurant;
    }

    public MountainHotel getMountainHotel() {
        return mountainHotel;
    }



    /**
     * method to get the accomodation of the hike
     * @return type of accommodation
     */
    public Object getAccomodation() {
        if (cottage != null) {
            return cottage;
        } else if (cottageWithRestaurant != null) {
            return cottageWithRestaurant;
        } else if (mountainHotel != null) {
            return mountainHotel;
        } else {
            return null;
        }
    }

    public class HikeAccessDeniedException extends Exception{ //vlastná výnimka použitá v projekte
        public HikeAccessDeniedException(String message){
            super(message);
        }
    }
}

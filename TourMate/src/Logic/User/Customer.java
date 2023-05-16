package Logic.User;
import Logic.Hiking.*;
import java.util.Scanner;
import java.util.LinkedList;

/**
 * This is the abstract class Customer, which is the superclass of the Adult and Child classes
 * It contains all the attributes and methods that are common for both classes
 */
public abstract class Customer {
    private String username;
    private String password;
    private String email;
    private String phoneNumber;
    private int age;
    private int distanceTraveled;

    private boolean active;
    private LinkedList<Hike> hikes = new LinkedList<>();





    private Hike hike;

    public Customer(String username, String password, String email, String phoneNumber, int age) {
        this.username = username;
        this.password = password;
        this.email = email;
        this.phoneNumber = phoneNumber;
        this.age = age;
        this.active = true;
        this.hikes = new LinkedList<>();
    }




    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }

    public String getUsername() {

        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getEmail() {
        return email;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public int getAge() {
        return age;
    }

    public int getDistanceTraveled() {
        return distanceTraveled;
    }

    public void setDistanceTraveled(int distanceTraveled) {

        this.distanceTraveled = distanceTraveled;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public void setPhoneNumber(String phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void printCustomer() {
        System.out.println("Username: " + username);
        System.out.println("Password: " + password);
        System.out.println("Email: " + email);
        System.out.println("Phone Number: " + phoneNumber);
        System.out.println("Age: " + age);
    }

    /**
     * This method is used to print the access status of the user
     */

    public void access(){
        System.out.println("The status of this person is unknown.");
    }

    public void setHike(Hike hike){
        this.hike = hike;
    }

    public Hike getHike(){
        return hike;
    }

    public void addCompletedHike(Hike hike){
        hikes.add(hike);
    }

    /**
     * This method is used to print all the hikes that the user has completed
     */
    public void printCompletedHikes(){
        for (Hike hike : hikes) {
            System.out.println(hike.getName());
        }
    }
    /**
     * This method is used to print all the hikes that the user has completed
     * @return the distance traveled by the user
     */
    public int distanceTraveled(){
        int distance = 0;
        for (Hike hike : hikes){
            distance += hike.getLength();
        }
        return distance;
    }






    public void changeDistanceTraveled(Hike hike){
        this.distanceTraveled += hike.getLength();
    }




}


package Logic.User;

/**
 * This interface is used to store the default methods for the PersonInfo interface
 * It is used to print all the necessery information about the user
 */

public interface PersonInfoDefaultMethod {
    String getUsername();
    int getAge();
    String getEmail();
    String getPhoneNumber();
    boolean isActive();

    default void printAttributes() {
        System.out.println("Name: " + getUsername());
        System.out.println("Age: " + getAge());
        System.out.println("Email: " + getEmail());
        System.out.println("Phone Number: " + getPhoneNumber());
        System.out.println("Active Membership: " + isActive());

    }
}





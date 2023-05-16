package Logic.User;

/**
 * This class is a subclass of Adult called 'Child' and implements access and PersonInfoDefaultMethod
 */
public class Child extends Customer implements access, PersonInfoDefaultMethod {
    private Customer adultGuide;

    /**
     * This is the nested class 'underagedLicense' which is used to store the child's license information
     */
    public class underagedLicense {
        private String firstName;
        private String surname;
        private int age;
        private String expirationDate;
        private String licenseNumber;
        private boolean discount;

        public underagedLicense(String firstName, String surname, int age, String expirationDate, String licenseNumber, boolean discount){
            this.firstName = firstName;
            this.surname = surname;
            this.age = age;
            this.expirationDate = expirationDate;
            this.licenseNumber = licenseNumber;
            this.discount = discount;
        }
    }

    public Child(String username, String password, String email, String phoneNumber, int age) {
        super(username, password, email, phoneNumber, age);
    }

    public void setAdultGuide(Customer adultGuide) {
        if(adultGuide.getAge() >= 18){
            this.adultGuide = adultGuide;
        }
        else{
            System.out.println("Your guide has to be 18 years old or older !");
        }
    }

    /**
     * This method is used to check whether the child has an adult as a guide.
     * If no, method will throw an error message
     */

    public Customer getAdultGuide() {
        try {
            if (adultGuide != null) {
                return adultGuide;
            }
            throw new GuideNotAvailableException("You don't have a guide yet!");
        } catch (GuideNotAvailableException e) {
            // Handle the exception or rethrow it
            System.out.println(e.getMessage());
            return null; // or handle the exception accordingly
        }
    }

    /**
     * This is an exception class which is used to handle the case when the child doesn't have an adult guide
     */
    public class GuideNotAvailableException extends Exception {
        public GuideNotAvailableException(String message) {
            super(message);
        }
    }


    private underagedLicense license = new underagedLicense(null, null, 0, null, null, false);
    public void setLicense(String firstName, String surname, int age, String expirationDate, String licenseNumber){
        license.firstName = firstName;
        license.surname = surname;
        license.age = age;
        license.expirationDate = expirationDate;
        license.licenseNumber = licenseNumber;
        license.discount = true;
    }

    public underagedLicense getLicense(){
        return license;
    }

    /**
     * This method is used to show, where does the customer have access to.
     */
    @Override
    public void access(){
        System.out.println("As a child, you don't have access to any hike without adult supervisor !");
    }
}

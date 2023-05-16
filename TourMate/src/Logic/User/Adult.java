package Logic.User;

/**
 * The `Adult` class represents an adult customer and extends the `Customer` class. It implements the `access` interface
 * and the `PersonInfoDefaultMethod` interface.
 */

public class Adult extends Customer implements access, PersonInfoDefaultMethod {

    private identificationCard IDcard = new identificationCard(null, null, 0, null, null);


    /**
     * The `identificationCard` class represents the identification card of an adult.
     */
    public class identificationCard{
        private String name;
        private String dateOfBirth;
        private int ageID;
        private String expirationDate;
        private String cardNumber;

        /**
         * The constructor of the `identificationCard` class.
         * @param name The name of the adult.
         * @param dateOfBirth The date of birth of the adult.
         * @param ageID The age of the adult.
         * @param expirationDate The expiration date of the identification card.
         * @param cardNumber The card number of the identification card.
         */
        public identificationCard(String name, String dateOfBirth, int ageID, String expirationDate, String cardNumber){
            this.name = name;
            this.dateOfBirth = dateOfBirth;
            this.ageID = ageID;
            this.expirationDate = expirationDate;
            this.cardNumber = cardNumber;
        }

        /**
         * Checks if the age on the identification card matches the age of the adult. If the ages don't match, it prints an error
         * message and deactivates the account.
         */
        public void checkAge(){
            if(this.ageID != Adult.this.getAge() && this.ageID != 0){
                System.out.println("The age you provided doesn't match the age on your ID card, please provide the correct age.");
                System.out.println("Since you lied about your age, your account is deleted, you may crete a new account with the correct age.");
                Adult.this.setActive(false);
            }
        }
    }

    private identificationCard card = new identificationCard( null, null , 0, null, null);

    public Adult(String username, String password, String email, String phoneNumber, int age){
        super(username, password, email, phoneNumber, age);
        this.IDcard = card;
        IDcard.checkAge();
    }






    public void setCard(String firstName, String surname, String dateOfBirth, int ageID, String expirationDate, String cardNumber){
        card.name = Adult.this.getUsername();
        card.dateOfBirth = dateOfBirth;
        card.ageID = ageID;
        card.expirationDate = expirationDate;
        card.cardNumber = cardNumber;
    }

    public identificationCard getCard(){
        return card;
    }

    /**
     * The `access` method prints out where does the adult gets the access.
     */
    @Override
    public void access(){
        System.out.println("As an adult, you have access to most of the hike, however you need a guide to get access to hikes that require guide with professional license.");
    }

}

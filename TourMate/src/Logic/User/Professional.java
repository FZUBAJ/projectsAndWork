package Logic.User;

/**
 * This class is a subclass of Adult called 'Professional' and implements access and PersonInfoDefaultMethod
 * This class has a nested class called 'professionalLicense' which is used to store the professional's license information
 * it also has access to all the hikes and may be a guide to others
 */
public class Professional extends Adult implements access, PersonInfoDefaultMethod{
    private professionalLicense professionalLicense;

    /**
     * This is the nested class 'professionalLicense' which is used to store the professional's license information
     */
    public class professionalLicense{
        private String licenseNumber;
        private String licenseExpirationDate;
        private String licenseCreationDate;
        private String licenseGender;
        private String licenseName;

        public professionalLicense(String licenseNumber, String licenseExpirationDate, String licenseCreationDate, String licenseGender, String licenseName){
            this.licenseNumber = licenseNumber;
            this.licenseExpirationDate = licenseExpirationDate;
            this.licenseCreationDate = licenseCreationDate;
            this.licenseGender = licenseGender;
            this.licenseName = licenseName;
        }

    }
    public Professional(String username, String password, String email, String phoneNumber, int age){
        super(username, password, email, phoneNumber, age);
    }

    private void addLicense(String licenseNumber, String licenseExpirationDate, String licenseCreationDate, String licenseGender, String licenseName){
        professionalLicense license = new professionalLicense(licenseNumber, licenseExpirationDate, licenseCreationDate, licenseGender, licenseName);
    }

    private professionalLicense license = new professionalLicense(null, null, null, null, null);

    public void setLicense(String licenseNumber, String licenseExpirationDate, String licenseCreationDate, String licenseGender, String licenseName){
        license = new professionalLicense(licenseNumber, licenseExpirationDate, licenseCreationDate, licenseGender, licenseName);
    }

    public professionalLicense getLicense(){
        return license;
    }


    /**
     * This method is used to show, where does the customer have access to.
     */
    @Override
    public void access(){
        System.out.println("As a professional with license, you have access to every hike in our database, however it is strongly recommended to hike with partners");
    }
}

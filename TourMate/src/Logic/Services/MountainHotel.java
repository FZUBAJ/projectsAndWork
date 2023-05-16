package Logic.Services;
/**
 * mountainHotel class is a subclass of CottageWithRestaurant class. More advanced accommodation type.
 * This is a place where people may sleep, eat but also relax
 */
public class MountainHotel extends CottageWithRestaurant{
    private int stars;
    private boolean hasSpa;
    private boolean hasFitnessCenter;
    private boolean hasWifi;
    private boolean hasParking;
    private boolean hasBar;
    private parkingLot parkingLot;



    public class parkingLot{
        private int capacity;
        private int id;
        public parkingLot(int capacity, int id){
            this.capacity = capacity;
            this.id = id;
        }

        public int getCapacity(){
                return capacity;
            }
        public int getId(){
                return id;
            }
        public void setCapacity(int capacity){
                this.capacity = capacity;
            }
        public void setId(int id){
                this.id = id;
            }

        public int calculatePrice(int days, boolean vipMember){
            int price = 0;
            if(vipMember){
               price = days * 15;
            }else{
                price = days * 30;
            }
            return price;
            }
    }


    public int getStars() {
        return stars;
    }

    public boolean isHasSpa() {
        return hasSpa;
    }

    public boolean isHasFitnessCenter() {
        return hasFitnessCenter;
    }

    public boolean isHasWifi() {
        return hasWifi;
    }

    public boolean isHasParking() {
        return hasParking;
    }

    public boolean isHasBar() {
        return hasBar;
    }

    public MountainHotel(String name, int price, int capacity, int id, String restaurantName, int restaurantId , int stars, boolean hasSpa , boolean hasFitnessCenter, boolean hasWifi, boolean hasParking, boolean hasBar) {
        super(name, price, capacity, id, restaurantName, restaurantId);
        this.stars = stars;
        this.hasSpa = hasSpa;
        this.hasFitnessCenter = hasFitnessCenter;
        this.hasWifi = hasWifi;
        this.hasParking = false;
        this.hasBar = hasBar;
    }

    public MountainHotel(String name, int price, int capacity, int id, String restaurantName, int restaurantId , int stars, boolean hasSpa , boolean hasFitnessCenter, boolean hasWifi, boolean hasParking, boolean hasBar, parkingLot parking) {
        super(name, price, capacity, id, restaurantName, restaurantId);
        this.stars = stars;
        this.hasSpa = hasSpa;
        this.hasFitnessCenter = hasFitnessCenter;
        this.hasWifi = hasWifi;
        this.hasParking = true;
        this.hasBar = hasBar;
        this.parkingLot = parking;
    }

    /**
     *getAccInformation method prints out all the information about the mountain hotel.
     */
    @Override
    public void getAccInformation(){
        System.out.println("Cottage: " + getName() +
                ", Price: " + getPrice() +
                ", Capacity: " + getCapacity() +
                ", ID: " + getId() +
                ", Restaurant Name: " + getRestaurantName() +
                ", Restaurant ID: " + getRestaurantId()
                + ", Stars: " + getStars()
                + ", Has Spa: " + isHasSpa()
                + ", Has Fitness Center: " + isHasFitnessCenter()
                + ", Has Wifi: " + isHasWifi()
                + ", Has Parking: " + isHasParking()
                + ", Has Bar: " + isHasBar());

    }

}

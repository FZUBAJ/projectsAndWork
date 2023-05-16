package Logic.Services;

/**
 * CottageWithRestaurant class is a subclass of Cottage class. More advanced accommodation type.
 * People can eat and also sleep in the same place. That't why there are new attributes such as restaurant name and id.
 */
public class CottageWithRestaurant extends Cottage {
    private String restaurantName;
    private int restaurantId;


    public CottageWithRestaurant(String name, int price, int capacity, int id, String restaurantName, int restaurantId){
        super(name, price, capacity, id);
        this.restaurantName = restaurantName;
        this.restaurantId = restaurantId;
    }

    public String getRestaurantName() {
        return restaurantName;
    }

    public int getRestaurantId() {
        return restaurantId;
    }

    public void setRestaurantName(String restaurantName) {
        this.restaurantName = restaurantName;
    }

    public void setRestaurantId(int restaurantId) {
        this.restaurantId = restaurantId;
    }


    /**
     * getAccInformation method prints out all the information about the cottage with restaurant.
     */
    @Override
    public void getAccInformation(){
        System.out.println("Cottage: " + getName() +
                ", Price: " + getPrice() +
                ", Capacity: " + getCapacity() +
                ", ID: " + getId() +
                ", Restaurant Name: " + getRestaurantName() +
                ", Restaurant ID: " + getRestaurantId());

    }
}







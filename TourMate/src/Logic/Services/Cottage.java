package Logic.Services;

/**
 * class cottage which is the most basic type of accommodation in my program
 */
public class Cottage implements getAccInfo{
    private String name;
    private int price;
    private int capacity;
    private int id;

    public Cottage(String name, int price, int capacity, int id){
        this.name = name;
        this.price = price;
        this.capacity = capacity;
        this.id = id;
    }

    public String getName(){
        return name;
    }

    public int getPrice(){
        return price;
    }

    public int getCapacity(){
        return capacity;
    }

    public int getId(){
        return id;
    }

    public void setName(String name){
        this.name = name;
    }

    public void setPrice(int price){
        this.price = price;
    }

    public void setCapacity(int capacity){
        this.capacity = capacity;
    }

    public void setId(int id){
        this.id = id;
    }

    /**
     *override method from the interface called getAccInfo
     * it serves the purpose of printing out the information about the cottage such as name, capacity...
     */
    @Override
    public void getAccInformation(){
        System.out.println("Cottage: " + getName() +
                ", Price: " + getPrice() +
                ", Capacity: " + getCapacity() +
                ", ID: " + getId());
    }

}
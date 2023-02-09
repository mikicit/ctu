package shop;



/**
 * The basic class for item in the EShop.
 */


public abstract class Item {
    private int id;
    private String name;
    private float price;
    private String category;
    
    public Item(int id, String name, float price, String category) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.category = category;
    }
    
    @Override
    public String toString() {
        return "Item   ID "+id+"   NAME "+name+"   CATEGORY "+category;
    }
    
    public int getID() {
        return id;
    }
    
    public void setID(int id) {
        this.id = id;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public float getPrice() {
        return price;
    }
    
    public void setPrice(float price) {
        this.price = price;
    }
    
    
    public String getCategory() {
        return this.category;
    }
    
    public void setCategory(String category) {
        this.category = category;
    }
    
    @Override
    public boolean equals(Object object){
        if(object instanceof Item){
            Item zbozi = (Item) object;
            if( id == zbozi.getID()
                && name.equals(zbozi.getName())
                && price == zbozi.getPrice()
                && category.equals(zbozi.getCategory())
               ) {
                return true;
            }
        }
        return false;
    }
}


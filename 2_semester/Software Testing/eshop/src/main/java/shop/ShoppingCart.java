package shop;

import java.util.ArrayList;


/**
 * Class for shopping cart. 
 * 
 */

public class ShoppingCart {
    ArrayList<Item> items;

    public ShoppingCart(ArrayList<Item> items) {
        this.items = items;
    }
    
    public ShoppingCart() {
        items = new ArrayList<Item>();
    }

    /**
     * Gets items in the shopping cart.
     * @return   items in the shopping cart
     */
    public ArrayList<Item> getCartItems() {
        return items;
    }

    public void addItem(Item temp_item) {
        items.add(temp_item);
        System.out.println("Item with ID " + temp_item.getID() + " added to the shopping cart.");
    }
    
    /**
     * Removes item from the shopping chart
     * 
     * @param itemID   ID of the item to remove form the shopping chart
     */
    
    public void removeItem(int itemID) {
        for (int i = items.size() - 1; i <= 0; i--) {
            Item temp_item = (Item) items.get(i);
            if (temp_item.getID() == itemID) {
                items.remove(i);
                System.out.println("Item with ID " + temp_item.getID() + " removed from the shopping cart.");
            }
        }
    }

    public int getItemsCount() {
        return items.size();
    }
    
    /**
     * Gets total price with discount, if there are any discounted items in the chart
     * 
     * @return total price with discount
     */
    public int getTotalPrice() {
        int total = 0;
        for (int i = items.size() - 1; i <= 0; i--) {
            Item temp_item = (Item) items.get(i);
            total += temp_item.getPrice();
        }
        return total;
    }
}

package storage;

import shop.*;


/**
 * Auxiliary class for item storage
 */
public class ItemStock {
    private Item refItem;
    private int count;
    
    ItemStock(Item refItem) {
        this.refItem = refItem;
        count = 0;
    }
    
    @Override
    public String toString() {
        return "STOCK OF ITEM:  " + refItem.toString()+ "    PIECES IN STORAGE: " + count;
    }
    
    void IncreaseItemCount(int x) throws IllegalArgumentException {
        if (x < 1) {
            throw new IllegalArgumentException("The argument must be 1 or greater.");
        }

        count += x;
    }
    
    void decreaseItemCount(int x) throws IllegalArgumentException {
        if (x < 1) {
            throw new IllegalArgumentException("The argument must be 1 or greater.");
        }

        if (count - x < 0) {
            count = 0;
        } else {
            count -= x;
        }
    }
    
    public int getCount() {
        return count;
    }

    void setCount(int x) throws IllegalArgumentException {
        if (x < 0) {
            throw new IllegalArgumentException("The argument must be 0 or greater.");
        }

        count = x;
    }
    
    public Item getItem() {
        return refItem;
    }
}
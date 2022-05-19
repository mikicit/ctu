package storage;

import archive.PurchasesArchive;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import shop.*;

public class Storage {

    private HashMap<Integer, ItemStock> stock;

    public Storage(HashMap<Integer, ItemStock> stock) {
        this.stock = stock;
    }

    public Storage() {
        stock = new HashMap<Integer, ItemStock>();
    }

    public Collection<ItemStock> getStockEntries() {
        return stock.values();
    }

    /**
     * Prints list of items in the storage to the standard output
     */
    public void printListOfStoredItems() {
        Collection<ItemStock> entries = getStockEntries();
        System.out.println("STORAGE IS CURRENTLY CONTAINING:");
        for (ItemStock e : entries) {
            System.out.println(e.toString());
        }
    }

    
    /**
     * Insert N pieces of item to the storage
     * @param item  item to insert
     * @param count  N - count of inserted item
     */
    public void insertItems(Item item, int count) {
        if (!stock.containsKey(item.getID())) {
            stock.put(item.getID(), new ItemStock(item));
        }
        ItemStock e = stock.get(item.getID());
        e.IncreaseItemCount(count);
    }
    
    /**
     * Removes N pieces of the item from the storage
     * @param item   item to remove
     * @param count   N - count of removed item
     * @throws NoItemInStorage 
     */
    public void removeItems(Item item, int count) throws NoItemInStorage {
        if (stock.containsKey(item.getID())) {
            ItemStock e = stock.get(item.getID());
            if (e.getCount() >= count) {
                e.decreaseItemCount(count);
            } else {
                throw new NoItemInStorage();
            }
        } else {
            throw new NoItemInStorage();
        }
    }

    /**
     * Decrease stock as a part of order processing
     * @param order Order to process
     * @throws NoItemInStorage  Throw, if item from order is not in the storage 
     */
    public void processOrder(Order order) throws NoItemInStorage {
        ArrayList<Item> items = order.getItems();
        for (Item i : items) {
            removeItems(i, 1);
        }
    }

    /**
     * Get count of item in the storage
     * @param item   item to query
     * @return    count of the item in the storage
     */
    public int getItemCount(Item item) {
        if (stock.containsKey(item.getID())) {
            ItemStock entry = stock.get(item.getID());
            return entry.getCount();
        }
        return 0;
    }

    /**
     * Get count of item in the storage
     * @param id   ID of item to query
     * @return    count of the item in the storage
     */
    public int getItemCount(int id) {
        if (stock.containsKey(id)) {
            ItemStock entry = stock.get(id);
            return entry.getCount();
        }
        return 0;
    }

    /**
     * Gets total price of all items in the stock
     * @return price of whole stock
     */
    public int getPriceOfWholeStock() {
        Collection<ItemStock> s = stock.values();
        float totalPrice = 0;
        for (ItemStock e : s) {
            totalPrice += e.getItem().getPrice();
        }
        return (int) totalPrice;
    }

    /**
     * Gets list of items of a particular category sorted by price
     * @param category  category to filter
     * @return   list of items of a particular category sorted by price
     */
    public Collection<Item> getItemsOfCategorySortedByPrice(String category) {
        ArrayList<Item> output = getItemsByCategory(category);
        this.sortItemsByPrice(output);
        return output;
    }

    private ArrayList<Item> getItemsByCategory(String category) {
        ArrayList<Item> output = new ArrayList();
        Collection<ItemStock> s = stock.values();
        for (ItemStock e : s) {
            Item tmp = e.getItem();
        
            /*
            if (tmp instanceof DiscountedItem) {
                DiscountedItem di = (DiscountedItem) tmp;
                if (di.getCategory().equals(category)) {
                    output.add(tmp);
                }
            } else if (tmp instanceof StandardItem) {
                StandardItem si = (StandardItem) tmp;
                if (si.getCategory().equals(category)) {
                    output.add(tmp);
                }
            }
            */
            
            if (tmp.getCategory().equals(category)) { output.add(tmp); }
        }
        return output;
    }

    // does this really work? - And should? :D
    private void sortItemsByPrice(ArrayList<Item> items) {
        boolean sortedFlag = false;
        while (sortedFlag == false) {
            sortedFlag = true;
            for (int i = 0; i < items.size() - 1; i++) {
                Item current = items.get(i);
                Item next = items.get(i + 1);
                if (current.getPrice() > next.getPrice()) {
                    sortedFlag = false; // still not sorted
                    items.set(i, next);
                    items.set(i + 1, current);
                }
            }
        }
    }
}
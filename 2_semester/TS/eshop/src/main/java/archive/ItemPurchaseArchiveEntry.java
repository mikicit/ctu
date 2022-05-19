package archive;

import shop.Item;

class ItemPurchaseArchiveEntry {
    private Item refItem;
    private int soldCount;
    
    ItemPurchaseArchiveEntry(Item refItem) {
        this.refItem = refItem;
        soldCount = 1;
    }
    
    void increaseCountHowManyTimesHasBeenSold(int x) {
        soldCount += x;
    }
    
    int getCountHowManyTimesHasBeenSold() {
        return soldCount;
    }
    
    Item getRefItem() {
        return refItem;
    }
    
    @Override
    public String toString() {
        return "ITEM  " + refItem.toString() + "   HAS BEEN SOLD " + soldCount + " TIMES";
    }
}

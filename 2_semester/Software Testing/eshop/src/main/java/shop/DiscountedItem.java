package shop;

import java.text.SimpleDateFormat;
import java.util.Date;



/**
 * The class for discounted item in the EShopController, as the handling of discounted items differs form the standard items.
 */


public class DiscountedItem extends Item {
    // discount stored in %
    private int discount;
    private Date discountFrom;
    private Date discountTo;
    
    public DiscountedItem(int id, String name, float price, String category, int discount, Date discountFrom, Date discountTo) {
        super(id, name, price, category);
        this.discount = discount > 100 ? 0 : discount;
        this.discountTo = discountFrom;
        this.discountTo = discountTo;
    }
    
    public DiscountedItem(int id, String name, float price, String category, int discount, String discountFrom, String discountTo)  {
        super(id, name, price, category);
        this.discount = discount;
        this.discountFrom = parseDate(discountFrom);
        this.discountTo = parseDate(discountTo);
    }
    
    
    
    private Date parseDate(String date) {
        SimpleDateFormat simpleDate = new SimpleDateFormat("dd.MM.yyyy");
        try {
            return simpleDate.parse(date);
        } catch (Exception e) {
            System.out.println("Error in DiscountedItem.parseDate() - wrong date format" + e.getMessage());
        }
        return null;
    }
    
    
    
    @Override
    public String toString() {
        return super.toString()+"   ORIGINAL PRICE "+getOriginalPrice()+"    DISCOUNTED PRICE "+getDiscountedPrice()+"  DISCOUNT FROM "+discountFrom.toString()+"    DISCOUNT TO "+discountTo.toString();
    }
    
    @Override
    public boolean equals(Object object) {
        if(object instanceof DiscountedItem){
            DiscountedItem zbozi = (DiscountedItem) object;
            return (super.equals(zbozi)
                && discount == zbozi.getDiscount()
                && discountTo.equals(zbozi.getDiscountTo()));
        }
        return false;
    }
    
    public int getDiscount() {
        return discount;
    }
    
    public void setDiscount(int discount) {
        this.discount = discount;
    }

    
    
    public Date getDiscountFrom() {
        return discountFrom;
    }

    public Date getDiscountTo() {
        return discountTo;
    }
    
    
    public void setDiscountTo(Date discountTo) {
        this.discountTo = discountTo;
    }
    
    
    public void setDiscountFrom(String discountFrom) {
        SimpleDateFormat simpleDate = new SimpleDateFormat("dd.MM.yyyy");
        try {
            this.discountFrom = simpleDate.parse(discountFrom);
        } catch (Exception e) {
            System.out.println("Error: Interval.Interval - wrong date format" + e.getMessage());
        }
    }

    
    public void setDiscountTo(String discountTo) {
        SimpleDateFormat simpleDate = new SimpleDateFormat("dd.MM.yyyy");
        try {
            this.discountTo = simpleDate.parse(discountTo);
        } catch (Exception e) {
            System.out.println("Error: Interval.Interval - wrong date format" + e.getMessage());
        }
    }
    
    
    
    public float getOriginalPrice() {
        return super.getPrice();
    }
    
    
    public float getDiscountedPrice() {
        return super.getPrice()*(100 - discount);
    }
    
    
    
    @Override
    public float getPrice() {
        return getDiscountedPrice();
    }
    
    
    
    public DiscountedItem copy() {
       return new DiscountedItem(getID(), getName(), getPrice(), getCategory(), discount, discountFrom, discountTo); 
    }
}

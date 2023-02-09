package shop;

import org.junit.jupiter.api.Test;
import storage.ItemStock;
import storage.NoItemInStorage;
import storage.Storage;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

public class EShopControllerTest {

    // Покупка 1 продукта
    // 1. Заполнить склад (добавить в него 1 продукт)
    // 2. Добавить в корзину
    // 3. Оформить заказ
    // 4. Купить продукт (оплатить заказ)
    // 5. Проверить склад (чтобы продукт был вычтен со склада)

    @Test
    public void shoppingCartTestBuyingOneItemTest() throws NoItemInStorage {
        EShopController.startEShop();
        StandardItem item = new StandardItem(1, "Dancing Smitka v.2", 5000, "GADGETS", 5);

        // Check if count 0
        assertThrows(IllegalArgumentException.class, () -> {
            EShopController.addItemToStorage(item, 0);
        });

        // Adding whit count 1
        EShopController.addItemToStorage(item, 1);
        ArrayList<ItemStock> itemsFromStorage = new ArrayList<>(EShopController.getItemsFromStorage());

        assertEquals(1, itemsFromStorage.size());
        assertEquals(1, itemsFromStorage.get(0).getCount());
        assertSame(item, itemsFromStorage.get(0).getItem());

        // Cart Creating
        ShoppingCart cart = EShopController.newCart();
        assertEquals(1, EShopController.getCarts().size());
        assertTrue(EShopController.getCarts().contains(cart));
        assertEquals(0, cart.getItemsCount());

        // Adding Item to cart
        cart.addItem(item);
        assertEquals(1, cart.getItemsCount());
        assertTrue(cart.getCartItems().contains(item));

        // Creating an order
        EShopController.purchaseShoppingCart(cart, "Smitka the Top", "Slavikova 29");

        // Count of item have to be 0
        itemsFromStorage = new ArrayList<>(EShopController.getItemsFromStorage()); // update
        assertEquals(1, itemsFromStorage.size());
        assertEquals(0, itemsFromStorage.get(0).getCount());
        assertEquals(1, EShopController.getArchive().getHowManyTimesHasBeenItemSold(item));
    }

    // Покупка 1 продукта
    // 1. Заполнить склад (добавить в него 5 продуктов)
    // 2. Добавить в корзину 3
    // 3. Удалить 1 продукт из корзины со склада (stock = 0)
    // 4. Офомрить заказ (должно запретить)

    @Test
    public void shoppingCartTestBuyingWithNoProductInStorage() throws NoItemInStorage {
        EShopController.startEShop();

        // Adding items
        int[] itemCount = {1,1,1,1,1};

        Item[] storageItems = {
            new StandardItem(1, "Dancing Panda v.2", 5000, "GADGETS", 5),
            new StandardItem(2, "Dancing Panda v.3 with USB port", 6000, "GADGETS", 10),
            new StandardItem(3, "Screwdriver 1", 200, "TOOLS", 5),
            new StandardItem(4, "Screwdriver 2", 201, "GADGETS", 10),
            new StandardItem(5, "Screwdriver 3", 202, "TOOLS", 5),
        };

        // Adding whit count 1
        for (int i = 0; i < storageItems.length; i++) {
            EShopController.addItemToStorage(storageItems[i], itemCount[i]);
        }

        Storage storage = EShopController.getStorage();

        for (int i = 0; i < storageItems.length; i++) {
            assertEquals(1, storage.getItemCount(storageItems[i]));
        }

        // Cart Creating
        ShoppingCart cart = EShopController.newCart();
        assertEquals(1, EShopController.getCarts().size());
        assertTrue(EShopController.getCarts().contains(cart));
        assertEquals(0, cart.getItemsCount());

        // Adding Item to cart (3 items)
        cart.addItem(storageItems[0]);
        cart.addItem(storageItems[1]);
        cart.addItem(storageItems[2]);

        ArrayList<Item> cartItems = cart.getCartItems();

        assertEquals(3, cart.getItemsCount());

        assertTrue(cart.getCartItems().contains(storageItems[0]));
        assertTrue(cart.getCartItems().contains(storageItems[1]));
        assertTrue(cart.getCartItems().contains(storageItems[2]));

        // Removing 1 item from cart from storage
        storage.removeItems(storageItems[1], 1);
        assertEquals(0, storage.getItemCount(storageItems[1]));

        // Trying to make an order (sorry for my english :( )
        assertThrows(NoItemInStorage.class, () -> {
            EShopController.purchaseShoppingCart(cart, "Smitka the Top", "Slavikova 29");
        });
    }
}

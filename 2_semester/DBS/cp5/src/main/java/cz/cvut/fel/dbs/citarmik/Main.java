package cz.cvut.fel.dbs.citarmik;

import cz.cvut.fel.dbs.citarmik.service.ClientService;
import cz.cvut.fel.dbs.citarmik.service.OrderService;


public class Main {
    public static void main(String[] args) {
        // Service Testing

        // Client Service
//        ClientService client = new ClientService();
//
//        // Create new Client
//        client.createClient("test@gmail.com", "Name Test", "Last Name Test", "Address", "passid");
//
//        // Points transfer
//        client.transferPoints(9, 12, 50);

        // Order Service

        // Create Order
        OrderService order = new OrderService();
        order.createOrder(
                180,
                1,
                3,
                300,
                "Mikita",
                "Citarovic",
                "420606169911");
    }
}

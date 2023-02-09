package cz.cvut.fel.dbs.citarmik.service;

import cz.cvut.fel.dbs.citarmik.dao.ClientDao;
import cz.cvut.fel.dbs.citarmik.entity.Client;

public class ClientService {
    public Client getClient(long id) {
        ClientDao clientDao = new ClientDao();
        return clientDao.get(id);
    }

    public void createClient(
            String email,
            String firstName,
            String lastName,
            String address,
            String phoneNumber,
            String passId) {
        ClientDao clientDao = new ClientDao();
        Client client = new Client();

        client.setEmail(email);
        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setAddress(address);
        client.setPhoneNumber(phoneNumber);
        client.setPassId(passId);

        clientDao.save(client);
    }

    public void createClient(
            String email,
            String firstName,
            String lastName,
            String address,
            String passId) {
        ClientDao clientDao = new ClientDao();
        Client client = new Client();

        client.setEmail(email);
        client.setFirstName(firstName);
        client.setLastName(lastName);
        client.setAddress(address);
        client.setPassId(passId);

        clientDao.save(client);
    }

    public void transferPoints(long from, long to, int amount) {
        ClientDao clientDao = new ClientDao();

        Client sender = clientDao.get(from);
        Client recipient = clientDao.get(to);

        // nevim jak tady nastavit vhodny isolation level

        if (sender.getBonusPoints() < amount) {
            System.out.println("Points are not enough!");
            return;
        }

        sender.setBonusPoints(sender.getBonusPoints() - amount);
        recipient.setBonusPoints(recipient.getBonusPoints() + amount);

        clientDao.update(sender);
        clientDao.update(recipient);

        System.out.println("Transfer of points completed successfully!");
    }
}

package cz.cvut.fel.dbs.citarmik.service;

import cz.cvut.fel.dbs.citarmik.core.EntityManagerFactoryUtil;
import cz.cvut.fel.dbs.citarmik.dao.ClientDao;
import cz.cvut.fel.dbs.citarmik.dao.DepartmentDao;
import cz.cvut.fel.dbs.citarmik.dao.OrderDao;
import cz.cvut.fel.dbs.citarmik.dao.RecipientDao;
import cz.cvut.fel.dbs.citarmik.entity.Client;
import cz.cvut.fel.dbs.citarmik.entity.Department;
import cz.cvut.fel.dbs.citarmik.entity.Order;
import cz.cvut.fel.dbs.citarmik.entity.Recipient;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;

public class OrderService {
    public void createOrder(
            long clientId,
            long departmentFromId,
            long departmentToId,
            float price,
            String firstName,
            String lastName,
            String phoneNumber
            ) {
        ClientDao clientDao = new ClientDao();
        DepartmentDao departmentDao = new DepartmentDao();

        Order order = new Order();
        Client client = clientDao.get(clientId);
        Recipient recipient = new Recipient();
        Department departmentFrom = departmentDao.get(departmentFromId);
        Department departmentTo = departmentDao.get(departmentToId);

        order.setClient(client);
        order.setDepartmentFrom(departmentFrom);
        order.setDepartmentTo(departmentTo);
        order.setPrice(price);

        recipient.setFirstName(firstName);
        recipient.setLastName(lastName);
        recipient.setPhoneNumber(phoneNumber);
        order.setRecipient(recipient);

        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        EntityTransaction et = em.getTransaction();
        et.begin();

        recipient.setOrder(order);
        em.persist(order);

        et.commit();
        em.close();

        System.out.println("Order successfully created!");
    }
}

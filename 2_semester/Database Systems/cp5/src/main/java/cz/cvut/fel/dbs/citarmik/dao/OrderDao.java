package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Order;

import javax.persistence.EntityManager;

public class OrderDao extends AbstractJpaDAO<Order> {
    public OrderDao() {
        super();
        setCurrentClass(Order.class);
    }
}

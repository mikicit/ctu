package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Client;

import javax.persistence.EntityManager;

public class ClientDao extends AbstractJpaDAO<Client> {
    public ClientDao(EntityManager em) {
        super(em);
        setCurrentClass(Client.class);
    }
}
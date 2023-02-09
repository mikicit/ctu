package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Client;

import javax.persistence.EntityManager;

public class ClientDao extends AbstractJpaDAO<Client> {
    public ClientDao() {
        super();
        setCurrentClass(Client.class);
    }
}
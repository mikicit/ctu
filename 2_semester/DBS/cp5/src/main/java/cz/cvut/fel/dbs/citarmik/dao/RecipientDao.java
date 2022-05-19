package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Recipient;

import javax.persistence.EntityManager;

public class RecipientDao extends AbstractJpaDAO<Recipient> {
    public RecipientDao(EntityManager em) {
        super(em);
        setCurrentClass(Recipient.class);
    }
}

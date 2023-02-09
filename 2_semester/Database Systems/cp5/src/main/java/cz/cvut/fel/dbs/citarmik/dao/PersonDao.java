package cz.cvut.fel.dbs.citarmik.dao;

import cz.cvut.fel.dbs.citarmik.core.AbstractJpaDAO;
import cz.cvut.fel.dbs.citarmik.entity.Person;

import javax.persistence.EntityManager;

public class PersonDao extends AbstractJpaDAO<Person> {
    public PersonDao() {
        super();
        setCurrentClass(Person.class);
    }
}

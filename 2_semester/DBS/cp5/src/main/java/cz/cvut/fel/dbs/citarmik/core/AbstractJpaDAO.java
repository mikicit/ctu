package cz.cvut.fel.dbs.citarmik.core;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import java.util.List;

public abstract class AbstractJpaDAO<T> {
    private final EntityManager em;
    private Class<T> currentClass;

    public AbstractJpaDAO(EntityManager em) {
        this.em = em;
    }

    public final void setCurrentClass(Class<T> currentClass){
        this.currentClass = currentClass;
    }

    public T get(long id) {
        return em.find(currentClass, id);
    }

    public List<T> getAll() {
        return em.createQuery("SELECT e FROM " + currentClass.getName() + " AS e")
                .getResultList();
    }

    public void save(T entity) {
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.persist(entity);
        et.commit();
    }

    public void update(T entity) {
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.merge(entity);
        et.commit();
    }

    public void delete(T entity) {
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.remove(entity);
        et.commit();
    }

    public void deleteById(long entityId){
        T entity = get(entityId);
        delete(entity);
    }
}

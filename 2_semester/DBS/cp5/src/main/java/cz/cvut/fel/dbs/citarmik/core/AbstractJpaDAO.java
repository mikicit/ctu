package cz.cvut.fel.dbs.citarmik.core;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import java.util.List;

public abstract class AbstractJpaDAO<T> {
    private Class<T> currentClass;

    public AbstractJpaDAO() {
    }

    public final void setCurrentClass(Class<T> currentClass){
        this.currentClass = currentClass;
    }

    public T get(long id) {
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        T result = em.find(currentClass, id);
        em.close();
        return result;
    }

    public List<T> getAll() {
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        List<T> result = em.createQuery("SELECT e FROM " + currentClass.getName() + " AS e")
                .getResultList();
        em.close();
        return result;
    }

    public void save(T entity) {
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.persist(entity);
        et.commit();
        em.close();
    }

    public void update(T entity) {
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.merge(entity);
        et.commit();
        em.close();
    }

    public void delete(T entity) {
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        EntityTransaction et = em.getTransaction();
        et.begin();
        em.remove(entity);
        et.commit();
        em.close();
    }

    public void deleteById(long entityId){
        EntityManager em = EntityManagerFactoryUtil.getEntityManagerFactory().createEntityManager();
        T entity = get(entityId);
        delete(entity);
        em.close();
    }
}

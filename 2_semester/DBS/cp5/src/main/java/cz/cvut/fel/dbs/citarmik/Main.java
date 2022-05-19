package cz.cvut.fel.dbs.citarmik;

import cz.cvut.fel.dbs.citarmik.dao.*;
import cz.cvut.fel.dbs.citarmik.entity.*;

import javax.persistence.*;

public class Main {
    public static void main(String[] args) {
//        EntityManagerFactory emf = Persistence.createEntityManagerFactory("DBS");
//        EntityManager em = emf.createEntityManager();

//        AutoTypeDao autoTypeDao = new AutoTypeDao(em);
//        System.out.println(autoTypeDao.get(1).getName());
//
//        AutoType autoType =  new AutoType();
//        autoType.setName("dfa");
//        autoType.setCapacity(3424);
//        autoTypeDao.save(autoType);

//        Client client = new Client();
//        client.setFirstName("Mikita");
//        client.setLastName("Citarovic");
//        client.setEmail("tidsofa@gmail.com");
//        client.setAddress("dfasfasddf");
//        client.setPhoneNumber("54235425");
//        client.setPassId("HB43545353");
//
//        ClientDao clientDao = new ClientDao(em);
//        clientDao.save(client);

//        ClientDao clientDao = new ClientDao(em);
//        Client client = clientDao.get(1);
//        System.out.println(client.getPerson().getFirstName());

//        DepartmentDao departmentDao = new DepartmentDao(em);
//        Department department = departmentDao.get(2);

//        System.out.println(department.getAcceptedPackages().get(2).getPackage().getType());
//
//        AcceptedPackageDao acceptedPackageDao = new AcceptedPackageDao(em);
//        AcceptedPackage acceptedPackage = acceptedPackageDao.get(1);
//
//        System.out.println(acceptedPackage.getPackage().getType());

//        System.out.println(department.getEmployees().get(0).getPerson().getFirstName());

//        EmployeePositionDao epd = new EmployeePositionDao(em);
//        EmployeePosition mp = epd.get(1);
//
//        System.out.println(mp.getEmployees().get(0).getCardNumber());

//        JourneyPackageDao journeyPackageDao = new JourneyPackageDao(em);
//        System.out.println(journeyPackageDao.get(1).getPackage().getId());

//        JourneyDao journeyDao = new JourneyDao(em);
//        Journey journey = journeyDao.get(1);

//        DepartmentDao departmentDao = new DepartmentDao(em);
//        Department department = new Department();
//        department.setPostalCode("dfsaf");
//        department.setDepartmentNumber(435);
//        department.setCity("dfsa");
//        department.setStreet("dfasf");
//
//        departmentDao.save(department);

//        PersonDao personDao = new PersonDao(em);
//
//        Person person = new Person();
//        person.setEmail("dfasf");
//        person.setFirstName("asdfads");
//        person.setLastName("dsafdas");
//        person.setAddress("sdafasdf");
//
//        personDao.save(person);

        ClientDao clientDao = new ClientDao();
//        clientDao.deleteById(179);
//
//        Client client = new Client();
//        client.setEmail("mikif@gmail.com");
//        client.setFirstName("Mikita");
//        client.setLastName("Unaveny Citarovic");
//        client.setAddress("Thakurova 1");
//        client.setPassId("CZ558192");
//        client.setBonusPoints(309);
//
//        clientDao.save(client);

        EmployeePositionDao epd = new EmployeePositionDao();
        EmployeeDao ed = new EmployeeDao();
        DepartmentDao dd = new DepartmentDao();

        EmployeePosition employeePosition = epd.get(2);
        Department department = dd.get(2);


        Employee employee = ed.get(182);

//        for (Employee item : ed.getAll()) {
//            System.out.println(item.getFirstName());
//        }

//        employee.setEmail("test432123@gmail.com");
//        employee.setFirstName("safsadf");
//        employee.setLastName("sadfsadf Citarovic");
//        employee.setAddress("sfafsa 1");
//        employee.setCardNumber(43534534);
//        employee.setPosition(employeePosition);
//        employee.setDepartment(department);

//        ed.update(employee);

//        em.close();
//        emf.close();
    }
}

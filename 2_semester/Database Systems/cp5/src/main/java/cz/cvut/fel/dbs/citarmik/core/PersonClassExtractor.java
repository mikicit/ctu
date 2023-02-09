package cz.cvut.fel.dbs.citarmik.core;

import cz.cvut.fel.dbs.citarmik.entity.Client;
import cz.cvut.fel.dbs.citarmik.entity.Employee;
import cz.cvut.fel.dbs.citarmik.entity.Person;
import org.eclipse.persistence.descriptors.ClassExtractor;
import org.eclipse.persistence.sessions.Record;
import org.eclipse.persistence.sessions.Session;

public class PersonClassExtractor extends ClassExtractor {
    @Override
    public Class<?> extractClassFromRow(Record databaseRow, Session session) {
        if (databaseRow.containsKey("employee_id")) {
            return Employee.class;
        } else if (databaseRow.containsKey("client_id")) {
            return Client.class;
        } else {
            return Person.class;
        }
    }
}

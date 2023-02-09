package cz.cvut.fel.ts1.refactoring;

import org.junit.jupiter.api.Test;
import static org.mockito.Mockito.*;

public class MockMailHelperTest {

    @Test
    public void sendMail_validEmail_saveMailToDB() {
        DBManager mockedDbManager = mock(DBManager.class);
        MailHelper mailHelper = new MailHelper(mockedDbManager);
        int mailId = 1;
        Mail mailToReturn = mock(Mail.class);
        when(mailToReturn.getTo()).thenReturn("");
        when(mailToReturn.getSubject()).thenReturn("");
        when(mailToReturn.getBody()).thenReturn("");
        when(mockedDbManager.findMail(anyInt())).thenReturn(mailToReturn);

        mailHelper.sendMail(mailId);

        verify(mockedDbManager, times(1)).findMail(mailId);
//        verify(mockedDbManager).findMail(anyInt());

        verify(mockedDbManager, times(1)).saveMail(any(Mail.class));
    }
}

package cz.cvut.fel.ts1.refactoring;

import java.util.Objects;

/**
 *
 * @author balikm1
 */
public class Mail {
    private int mailId;
    private String to;
    private String subject;
    private boolean isSent;
    private String body;

    public int getMailId() {
        return mailId;
    }

    public void setMailId(int mailId) {
        this.mailId = mailId;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public boolean isSent() {
        return isSent;
    }

    public void setIsSent(boolean isSent) {
        this.isSent = isSent;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 97 * hash + this.mailId;
        hash = 97 * hash + Objects.hashCode(this.to);
        hash = 97 * hash + Objects.hashCode(this.subject);
        hash = 97 * hash + (this.isSent ? 1 : 0);
        hash = 97 * hash + Objects.hashCode(this.body);
        return hash;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Mail other = (Mail) obj;
        if (this.mailId != other.mailId) {
            return false;
        }
        if (this.isSent != other.isSent) {
            return false;
        }
        if (!Objects.equals(this.to, other.to)) {
            return false;
        }
        if (!Objects.equals(this.subject, other.subject)) {
            return false;
        }
        if (!Objects.equals(this.body, other.body)) {
            return false;
        }
        return true;
    }
    
    
}

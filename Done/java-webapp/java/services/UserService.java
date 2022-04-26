package services;

import dataaccess.UserDB;
import models.Role;
import models.User;
import java.util.List;

public class UserService {
    private UserDB userDb = new UserDB();
    
    public User get(String email) throws Exception {
        User user = this.userDb.get(email);
        return user;
    }
    
    public List<User> getAll() throws Exception {
        List<User> users = this.userDb.getAll();
        return users;
    }
    
    public void insert(String email, boolean active, String firstName, String lastName, String password, Role role) throws Exception {
        User user = new User(email, active, firstName, lastName, password, role);
        this.userDb.insert(user);
    }
    
    public void update(String email, boolean active, String firstName, String lastName, String password, Role role) throws Exception {
        User user = new User(email, active, firstName, lastName, password, role);
        this.userDb.update(user);
    }
    
    public void delete(String email) throws Exception {
        User user = new User();
        user.setEmail(email);
        this.userDb.delete(user);
    }
}

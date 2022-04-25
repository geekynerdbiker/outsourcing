
package services;

import dataaccess.RoleDB;
import models.Role;

import java.util.List;


public class RoleService {
    private RoleDB roleDb = new RoleDB();
    
    public List<Role> getAll() throws Exception {
        List<Role> roles = this.roleDb.getAll();
        return roles;
    }
}

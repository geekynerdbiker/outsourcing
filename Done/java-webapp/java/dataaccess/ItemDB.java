package dataaccess;

import models.Category;
import models.Item;
import models.Role;
import models.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;


public class ItemDB {

    public List<Item> getAll() throws Exception {
        List<Item> items = new ArrayList<>();
        ConnectionPool cp = ConnectionPool.getInstance();
        Connection con = cp.getConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;

        String sql = "SELECT * FROM item INNER JOIN category ON category.category_id = item.category INNER JOIN user ON user.email = item.owner";
        
        try {
            ps = con.prepareStatement(sql);
            rs = ps.executeQuery();
            while (rs.next()) {
                int item_id = rs.getInt(1);
                String item_name = rs.getString(2);
                double price = rs.getDouble(3);;

                int categoryId = rs.getInt(4);
                String categoryName = rs.getString(5);
                Category category = new Category(categoryId, categoryName);

                String email = rs.getString(6);
                boolean active = rs.getBoolean(7);
                String firstName = rs.getString(8);
                String lastName = rs.getString(9);
                String password = rs.getString(10);
                int roleId = rs.getInt(11);
                String roleName = rs.getString(12);
                
                Role role = new Role(roleId, roleName);
                User user = new User(email, active, firstName, lastName, password, role);
                Item item = new Item(item_id, category, item_name, price, user);
                items.add(item);
                
            }
        } finally {
            DBUtil.closeResultSet(rs);
            DBUtil.closePreparedStatement(ps);
            cp.freeConnection(con);
        }

        return items;
    }

    public Item get(String item_name) throws Exception {
        Item item = null;
        ConnectionPool cp = ConnectionPool.getInstance();
        Connection con = cp.getConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        String sql = "SELECT * FROM item INNER JOIN category ON category.category_id = item.category INNER JOIN user ON user.email = item.owner";
        
        try {
            ps = con.prepareStatement(sql);
            ps.setString(1, item_name);
            rs = ps.executeQuery();
            if (rs.next()) {
                int item_id = rs.getInt(1);
                double price = rs.getDouble(3);;

                int categoryId = rs.getInt(4);
                String categoryName = rs.getString(5);
                Category category = new Category(categoryId, categoryName);

                String email = rs.getString(6);
                boolean active = rs.getBoolean(7);
                String firstName = rs.getString(8);
                String lastName = rs.getString(9);
                String password = rs.getString(10);
                int roleId = rs.getInt(11);
                String roleName = rs.getString(12);

                Role role = new Role(roleId, roleName);
                User user = new User(email, active, firstName, lastName, password, role);
                item = new Item(item_id, category, item_name, price, user);
            }
        } finally {
            DBUtil.closeResultSet(rs);
            DBUtil.closePreparedStatement(ps);
            cp.freeConnection(con);
        }
        
        return item;
    }

    public boolean insert(Item item) throws Exception {
        ConnectionPool cp = ConnectionPool.getInstance();
        Connection con = cp.getConnection();
        PreparedStatement ps = null;
        String sql = "INSERT INTO `item` (`item_id`,`item_name`,`price`)" +
            "VALUES (?, ?, ?)";
        boolean inserted = false;
        
        try {
            ps = con.prepareStatement(sql);
            ps.setInt(1, item.getItem_id());
            ps.setString(2, item.getItem_name());
            ps.setDouble(3, item.getPrice());
            inserted = ps.executeUpdate() > 0;
        } finally {
            DBUtil.closePreparedStatement(ps);
            cp.freeConnection(con);
        }
        
        return inserted;
    }

    public boolean update(Item item) throws Exception {
        ConnectionPool cp = ConnectionPool.getInstance();
        Connection con = cp.getConnection();
        PreparedStatement ps = null;
        String sql = "UPDATE user SET `item_id` = ?,`id_name` = ?,`price` = ?";
        boolean updated = false;
        try {
            ps = con.prepareStatement(sql);
            ps.setInt(1, item.getItem_id());
            ps.setString(2, item.getItem_name());
            ps.setDouble(3, item.getPrice());
            updated = ps.executeUpdate() > 0;
        } finally {
            DBUtil.closePreparedStatement(ps);
            cp.freeConnection(con);
        }
        return updated;
    }

    public boolean delete(Item item) throws Exception {
        ConnectionPool cp = ConnectionPool.getInstance();
        Connection con = cp.getConnection();
        PreparedStatement ps = null;
        String sql = "DELETE FROM item WHERE item_name = ?";
        boolean deleted = false;
        try {
            ps = con.prepareStatement(sql);
            ps.setString(1, item.getItem_name());
            deleted = ps.executeUpdate() > 0;
        } finally {
            DBUtil.closePreparedStatement(ps);
            cp.freeConnection(con);
        }
        
        return deleted;
    }

}

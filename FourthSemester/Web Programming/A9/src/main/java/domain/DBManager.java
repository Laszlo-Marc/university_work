package domain;
import java.sql.*;
import java.util.ArrayList;
public class DBManager {
    private Statement stmt;
    private Connection conn;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/forum_db", "root", "");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/forum_db", "root", "");
            stmt = con.createStatement();
        } catch(Exception ex) {
            System.out.println("eroare la connect:"+ex.getMessage());
            ex.printStackTrace();
        }
    }

    public User authenticate(String username, String password) {

        User u = null;
        String stmt=String.format("select * from users where username='%s' and password='%s'", username,password);

        try {
            var preparedStatement=conn.prepareStatement(stmt);
            var rs = preparedStatement.executeQuery();
            if(rs.next()) {
                u = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));

            }

            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return u;
    }

    public ArrayList<Topic> getAllTopics() {
        ArrayList<Topic> topics = new ArrayList<>();
        ResultSet rs;
        try {
            String query = "SELECT * FROM topics";
            rs = conn.createStatement().executeQuery(query);
            while (rs.next()) {
                topics.add(new Topic(rs.getInt("id"), rs.getString("title"), rs.getString("content"), rs.getInt("user_id")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return topics;
    }

    public boolean createTopic(String title, String content, int userId) {
        int result = 0;
        try {
            String query = "INSERT INTO topics (title, content, user_id) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setString(1, title);
            pstmt.setString(2, content);
            pstmt.setInt(3, userId);
            result = pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result > 0;
    }

    public Topic getTopicById(int id) {
        Topic topic = null;
        ResultSet rs;
        try {
            String query = "SELECT * FROM topics WHERE id=?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, id);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                topic = new Topic(rs.getInt("id"), rs.getString("title"), rs.getString("content"), rs.getInt("user_id"));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return topic;
    }

    public ArrayList<Post> getPostsByTopicId(int topicId) {
        ArrayList<Post> posts = new ArrayList<>();
        ResultSet rs;
        try {
            String query = "SELECT * FROM posts WHERE topic_id=?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, topicId);
            rs = pstmt.executeQuery();
            while (rs.next()) {
                posts.add(new Post(rs.getInt("id"), rs.getString("content"), rs.getInt("topic_id"), rs.getInt("user_id")));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return posts;
    }

    public boolean createPost(String content, int topicId, int userId) {
        int result = 0;
        try {
            String query = "INSERT INTO posts (content, topic_id, user_id) VALUES (?, ?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setString(1, content);
            pstmt.setInt(2, topicId);
            pstmt.setInt(3, userId);
            result = pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result > 0;
    }
    public boolean isPostOwner(int postId, int userId) {
        boolean isOwner = false;
        try {
            String query = "SELECT user_id FROM posts WHERE id = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, postId);
            ResultSet rs = pstmt.executeQuery();
            if (rs.next()) {
                isOwner = (rs.getInt("user_id") == userId);
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return isOwner;
    }

    public boolean deletePost(int postId) {
        int result = 0;
        try {
            String query = "DELETE FROM posts WHERE id = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, postId);
            result = pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result > 0;
    }
    public String getUserByPost(int id) {
        String userName = null;
        ResultSet rs;
        try {
            String query = "SELECT username FROM users WHERE id=?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, id);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                userName = rs.getString("username");
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return userName;
    }


}
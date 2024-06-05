package domain;

public class Post {
    private int id;
    private String content;
    private int topicId;
    private int userId;

    public Post(int id, String content, int topicId, int userId) {
        this.id = id;
        this.content = content;
        this.topicId = topicId;
        this.userId = userId;
    }

    // Getters and setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public int getTopicId() {
        return topicId;
    }

    public void setTopicId(int topicId) {
        this.topicId = topicId;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }
}
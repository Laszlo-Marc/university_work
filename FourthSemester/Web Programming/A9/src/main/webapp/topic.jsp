<%@ page import="domain.User" %>
<%@ page import="domain.Topic" %>
<%@ page import="domain.Post" %>
<%@ page import="java.util.List" %>
<%@ page import="domain.DBManager" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    User user = (User) session.getAttribute("user");
    DBManager dbManager = new DBManager();

    if (user == null || user.getUsername().isEmpty() || user.getPassword().isEmpty()) {
        response.sendRedirect(request.getContextPath() + "/");
        return;
    }
    Topic topic = (Topic) request.getAttribute("topic");
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Topic</title>
    <link href="styles/style.css" type="text/css" rel="stylesheet" />
</head>
<body>
<div class="container">
    <h2>Topic: <%= topic.getTitle() %></h2>
    <p><%= topic.getContent() %></p>
    <p><a href="forum">Back to Forum</a></p>
    <h3>Posts</h3>
    <ul>
        <%
            List<Post> posts = (List<Post>) request.getAttribute("posts");
            for (Post post : posts) {
        %>
        <li>
            <p><%= post.getContent() %></p>
            <p>Posted by User: <%= dbManager.getUserByPost(post.getUserId()) %></p>
            <%
                if (user != null && user.getId() == post.getUserId()) {
                    if (dbManager.isPostOwner(post.getId(), user.getId())) {
            %>
            <a href="delete-post?id=<%= post.getId() %>" onclick="return confirm('Are you sure you want to delete this post?');">Delete</a>
            <%
                    }
                }
            %>
        </li>
        <%
            }
        %>
    </ul>
    <h3>New Post</h3>
    <form action="topic" method="post">
        <input type="hidden" name="action" value="newPost">
        <div>
            <textarea id="content" name="content" required></textarea>
        </div>
        <input type="hidden" name="topicId" value="<%= topic.getId() %>">
        <button type="submit">Post</button>
    </form>
</div>
</body>
</html>
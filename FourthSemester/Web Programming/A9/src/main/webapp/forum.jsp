<%@ page import="domain.User" %>
<%@ page import="domain.Topic" %>
<%@ page import="java.util.List" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    User user = (User) session.getAttribute("user");
    if (user == null || user.getUsername().isEmpty() || user.getPassword().isEmpty()) {
        response.sendRedirect(request.getContextPath() + "/");
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Forum</title>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap" rel="stylesheet">
    <link href="styles/forum.css" type="text/css" rel="stylesheet">
</head>
<body>
<div class="container">
    <div class="header">
        <h2>Forum</h2>
        <p>Welcome, <%= user.getUsername() %>! <a class="logout-btn" href="${pageContext.request.contextPath}/logout">Logout</a></p>
    </div>
    <h3>Topics</h3>
    <ul class="topics-list">
        <%
            List<Topic> topics = (List<Topic>) request.getAttribute("topics");
            for (Topic topic : topics) {
        %>
        <li>
            <a href="topic?id=<%= topic.getId() %>"><%= topic.getTitle() %></a>
        </li>
        <%
            }
        %>
    </ul>
    <div class="new-topic-form">
        <h3>New Topic</h3>
        <form action="forum" method="post">
            <input type="hidden" name="action" value="newTopic">
            <div>
                <label for="title">Title:</label>
                <input type="text" id="title" name="title" required>
            </div>
            <div>
                <label for="content">Content:</label>
                <textarea id="content" name="content" required></textarea>
            </div>
            <button type="submit">Create Topic</button>
        </form>
    </div>
</div>
</body>
</html>

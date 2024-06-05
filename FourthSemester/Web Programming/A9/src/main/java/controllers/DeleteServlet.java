package controllers;

import domain.DBManager;
import domain.User;


import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;



public class DeleteServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        User user = (User) session.getAttribute("user");

        if (user == null) {
            response.sendRedirect(request.getContextPath() + "/");
            return;
        }

        int postId = Integer.parseInt(request.getParameter("id"));
        int userId = user.getId();

        DBManager dbManager = new DBManager();
        if (dbManager.isPostOwner(postId, userId)) {
            dbManager.deletePost(postId);
            response.sendRedirect(request.getHeader("referer")); // Redirect to the previous page
        } else {
            response.sendRedirect(request.getContextPath() + "/error.jsp");
        }
    }
}

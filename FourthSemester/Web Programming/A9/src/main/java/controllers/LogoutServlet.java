package controllers;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false); // Get the current session, but don't create a new one if it doesn't exist
        if (session != null) {
            session.invalidate(); // Invalidate the session
        }
        response.sendRedirect(request.getContextPath() + "/"); // Redirect to the login page or home page
    }
}
$(document).ready(() => {
  let userRole = 0;

  $.ajax({
    type: "GET",
    url: "http://localhost/A7-R/db/schema.php",
    data: { action: "getRole" },
    success: (data) => {
      data = JSON.parse(data);
      userRole = data["is_admin"];
      console.log(data);

      if (userRole == 0) {
        console.log("User is a guest");
        document.getElementById("updateButton").style.visibility = "hidden";
        document.getElementById("removeButton").style.visibility = "hidden";
      } else {
        console.log("User is an admin");
      }
    },
    error: (err) => {
      console.log("Error fetching user role: ", err);
    },
  });
});

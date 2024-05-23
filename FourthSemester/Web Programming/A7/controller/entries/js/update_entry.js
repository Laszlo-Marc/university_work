let currentPage = 0;
const insertData = (newBody, data) => {
  if (currentPage === 0) {
    $("#previousButton").prop("disabled", true);
  }
  let result = JSON.parse(data);
  let numOfPages = Math.ceil(result.length / 4);
  for (let entry of result) {
    let newRow = newBody.insertRow();
    if (result.indexOf(entry) >= 4 * currentPage) {
      for (let index of ["id", "author_email", "title", "comment", "date"]) {
        let newCol = newRow.insertCell();
        let newText = document.createTextNode(entry[index]);
        newCol.appendChild(newText);
      }
      newBody.append(newRow);
    }
    if (result.indexOf(entry) >= 4 * (currentPage + 3)) {
      break;
    }
  }
  if (numOfPages === 0) {
    $("#nextButton").prop("disabled", true);
  } else {
    if (currentPage === numOfPages - 1) {
      $("#nextButton").prop("disabled", true);
    } else {
      $("#nextButton").prop("disabled", false);
    }
  }
};

const showEntriesByUser = () => {
  let body = $(".entryTable tbody").eq(0);
  let newBody = document.createElement("tbody");

  $.ajax({
    type: "GET",
    url: "http://localhost/A7-R/db/schema.php",
    data: { action: "selectEntriesByAuthor" },
    success: (data) => {
      console.log(data);
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
};

$(document).ready(() => {
  showEntriesByUser();
  $("#previousButton").click(() => {
    if (currentPage > 0) {
      currentPage--;
      if (currentPage === 0) {
        $("#previousButton").attr("disabled", true);
      }
    }
    showEntriesByUser();
  });

  $("#nextButton").click(() => {
    $("#previousButton").attr("disabled", false);
    currentPage++;
    showEntriesByUser();
  });
  $("#updateEntryButton").click(() => {
    let id = $("#idField").val();
    let title = $("#titleField").val();
    let comment = $("#commentField").val();
    let date = $("#dateField").val().split(" ")[0];
    console.log("Update button clicked");
    console.log(id, title, comment, date);
    $.ajax({
      type: "GET",
      url: "http://localhost/A7-R/db/schema.php",
      data: {
        action: "updateEntry",
        id: id,
        title: title,
        comment: comment,
        date: date,
      },
      success: (data) => {
        console.log(data);
        $(".form-control").val("");
        showEntriesByUser();
      },
    });
  });
});

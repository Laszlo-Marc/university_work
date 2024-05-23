let currentPage = 0;
let showType = "all";

const insertData = (newBody, data) => {
  let result = JSON.parse(data);
  let numOfPages = Math.ceil(result.length / 4);

  if (currentPage === 0) {
    $("#previousButton").prop("disabled", true);
  } else {
    $("#previousButton").prop("disabled", false);
  }

  let start = currentPage * 4;
  let end = Math.min(start + 4, result.length);

  for (let i = start; i < end; i++) {
    let entry = result[i];
    let newRow = newBody.insertRow();
    for (let index of ["id", "author_email", "title", "comment", "date"]) {
      let newCol = newRow.insertCell();
      let newText = document.createTextNode(entry[index]);
      newCol.appendChild(newText);
    }
  }

  if (currentPage === numOfPages - 1 || numOfPages === 0) {
    $("#nextButton").prop("disabled", true);
  } else {
    $("#nextButton").prop("disabled", false);
  }
};
const showEntries = () => {
  console.log("showing entries");
  let body = $(".entryTable tbody");
  let newBody = document.createElement("tbody");
  $.ajax({
    type: "GET",
    url: "http://localhost/A7-R/db/schema.php",
    data: { action: "selectAllEntries" },
    success: (data) => {
      console.log(data);
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
};

const showEntriesByTitle = () => {
  let body = $(".entryTable tbody").eq(0);
  let newBody = document.createElement("tbody");
  title = $("#titleInputFilter").val();
  $.ajax({
    type: "GET",
    url: "http://localhost/A7-R/db/schema.php",
    data: { action: "selectEntriesByTitle", title: title },
    success: (data) => {
      console.log(data);
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
};

const showEntriesByAuthor = () => {
  let body = $(".entryTable tbody").eq(0);
  let newBody = document.createElement("tbody");
  author = $("#authorInputFilter").val();
  $.ajax({
    type: "GET",
    url: "http://localhost/A7-R/db/schema.php",
    data: { action: "selectEntriesByAuthor", author: author },
    success: (data) => {
      console.log(data);
      insertData(newBody, data);
    },
  });
  body.replaceWith(newBody);
};
const showCorrectEntries = () => {
  switch (showType) {
    case "all":
      showEntries();
      break;
    case "title":
      showEntriesByTitle();
      break;
    case "author":
      showEntriesByAuthor();
      break;
  }
};

$(document).ready(() => {
  showEntries();
  console.log(showType);
  $("#allEntriesButton").click(() => {
    showType = "all";
    showCorrectEntries();
  });
  $("#filterByAuthorButton").click(() => {
    showType = "author";
    showCorrectEntries();
  });
  $("#filterByTitleButton").click(() => {
    showType = "title";
    showCorrectEntries();
  });

  $("#previousButton").click(() => {
    if (currentPage > 0) {
      currentPage--;
      if (currentPage === 0) {
        $("#previousButton").attr("disabled", true);
      }
    }
    showCorrectEntries();
  });

  $("#nextButton").click(() => {
    $("#previousButton").attr("disabled", false);
    currentPage++;
    showCorrectEntries();
  });
});

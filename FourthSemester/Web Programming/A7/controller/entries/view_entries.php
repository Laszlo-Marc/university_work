<?php
session_start();
if(!isset($_SESSION['username'])){
    header('Location: ../user/profile.php');
}
if(isset($_POST['returnButton'])){
    header('Location: ../user/profile.php');
}

?>

<!DOCTYPE html>
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
        
        <title>All user entries</title>
    </head>
    <body>
        <div class="container" id="viewLogsDiv">
            <div class="row">
                <div class="col-sm">
                    <div class="container" id="showLogs">
                        <h3>All the entries that are currently in the system:</h3>
                        <table class="entryTable table">
                            <thead>
                                <tr>
                                    <th>ID</th>
                                    <th>Email</th>
                                    <th>Title</th>
                                    <th>Comment</th>
                                    <th>Date</th>
                                    
                                </tr>
                            </thead>
                            <tbody>
                            </tbody>
                        </table>
                        <button type="button" id="previousButton" class="btn btn-primary mb-1">Previous</button>
                        <button id="nextButton" type="button" class="btn btn-primary mb-1">Next</button>
                    </div>
                </div>
                <div class="col-sm">
                    <div id="buttons" class="container">
                        <h3>Filter entries:</h3>
                        <div id="filterByAuthor" class="mb-1">
                            <label for="authorInputFilter" class="form-label">Author:</label><input type="text" id="authorInputFilter" class="form-control mb-3">
                            <button id="filterByAuthorButton" type="button" class="btn btn-primary">Search by author</button>
                        </div>
                        <div id="filterByTitle" class="mb-1">
                            <label for="titleInputFilter" class="form-label">Title: </label><input type="text" id="titleInputFilter" class="form-control mb-3">
                            <button id="filterByTitleButton" type="button" class="btn btn-primary mb-3">Search by title</button>
                        </div>
                    <div>
                        <button id="filterByUserButton" type="button" class="btn btn-primary mb-1">Show my entries</button>
                        <button id="allEntriesButton" type="button" class="btn btn-primary mb-1">Show all entries</button>
                    </div>
                    <div>
                        <form method="post">
                            <input id="returnButton" type="submit" class="btn btn-secondary mb-1" name="returnButton" value="Return to profile">
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </body>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="js/view_entries.js"></script>
</html>
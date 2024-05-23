<?php
session_start();
if(!isset($_SESSION['username'])){
    header('Location: ../user/profile.php');
}
if(isset($_POST['returnButton'])){
    header('Location: ../user/profile.php');
}

if(isset($_POST['viewAllButton'])) {
    header('Location: ../entries/view_entries.php');
}
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
        
        <title>Add an entry</title>
    </head>
    <body>
        <div class="container" id="addFormDiv">
            <div class="row">
                <div class="col-sm">
                    <div class="container" id="showLogs">
                        <h3>You have added the following entries:</h3>
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
                    <div id="addForm" class="container text-left">
                        <h3>Add a new entry:</h3>
                        
                        <div class="mb-1"><label for="titleField" class="form-label">Title: </label><input type="text" id="titleField" class="form-control"></div>
                        <div class="mb-1"><label for="commentField" class="form-label">Comment: </label><input type="text" id="commentField" class="form-control"></div>
                        <div class="mb-1"><label for="dateField" class="form-label">Date: </label><input type="date" id="dateField" class="form-control"></div>
                        <button id="insertEntryButton" type="button" class="btn btn-success mb-1">Add Entry</button>
                        <form method="post">
                            <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all entries">
                            <input type="submit" class="btn btn-secondary mb-1" name="returnButton" value="Return to profile">
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </body>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="js/add_entry.js"></script>
</html>
<?php
session_start();
if (!isset($_SESSION['username'])) {
    header('Location: ../user/login.php');
}
if (isset($_POST['viewAllButton'])) {
    header('Location: view_entries.php');
}
if(isset($_POST['returnButton'])){
    header('Location: ../user/profile.php');
}

?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
        
        <title>Remove an entry</title>
    </head>
    <body>
        <div class="container" id="removeFormDiv">
            <div class="row">
                <div class="col-sm">
                    <div class="container" id="showEntries">
                        <h3>You can remove one of the following entries:</h3>
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
                    <div id="removeForm">
                        <h3>Remove an entry:</h3>
                        <div class="mb-1">
                            <label for="idField" class="form-label">ID: </label>
                            <input type="text" id="idField" class="form-control">
                        </div>
                        <button id="removeButton" type="button" class="btn btn-danger mb-1">Remove Entry</button>
                    </div>
                    <form method="post">
                        <input type="submit" class="btn btn-primary mb-1" name="viewAllButton" value="View all entries">
                        <input type="submit" class="btn btn-secondary mb-1" name="returnButton" value="Return to profile">
                    </form>
                </div>
            </div>
        </div>
    </body>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="js/remove_entry.js"></script>
</html>
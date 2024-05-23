<?php
session_start();
if(isset($_SESSION['username'])){
   $username=$_SESSION['username'];
}
else{
    header('Location: login.php');
    die();
}
if(isset($_POST['logoutButton'])){
    session_unset( );
    session_destroy();
    header('Location: login.php');
}

if (isset($_POST['viewAllButton'])) {
    header('Location: ../entries/view_entries.php');
}

if(isset($_POST['addEntryButton'])) {
    header('Location: ../entries/add_entry.php');
}

if(isset($_POST['removeEntryButton'])) {
    header('Location: ../entries/remove_entry.php');
}
if(isset($_POST['updateEntryButton'])) {
    header('Location: ../entries/update_entry.php');
}
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
        
        <title>User page</title>
    </head>
    <body>
        <div class="container text-center">
            <h3>Welcome, <?php echo $username;?>!</h3>
            <form method="post">
                <input type="submit" class="btn btn-primary" name="viewAllButton" value="View all entries">
                <input type="submit" class="btn btn-success" name="addEntryButton" value="Add an entry">
                <input type="submit" class="btn btn-danger" id="removeButton" name="removeEntryButton" value="Remove an entry">
                <input type="submit" class="btn btn-success" id="updateButton" name="updateEntryButton" value="Update an entry">
                <input type="submit" class="btn btn-dark" name="logoutButton" value="Log out">
            </form>
        </div>
    </body>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="./profile.js"></script>
</html>
<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With');

class DBConnection{
    private string $host="localhost";
    private string $username="root";
    private string $password="";
    private string $database="guestbook_db";
    private string $charset="UTF8";

    private PDO $pdo;
    private string $error;

    public function __construct(){
        $dsn="mysql:host=$this->host;dbname=$this->database;charset=$this->charset";
        $opt=array(
            PDO::ATTR_ERRMODE=>PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE=>PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES=>false
        );
        try{
            $this->pdo=new PDO($dsn,$this->username,$this->password,$opt);
        }catch(PDOException $e){
            $this->error=$e->getMessage();
        }
    }

    public function selectAllEntries(){
        $stmt=$this->pdo->prepare("SELECT * FROM guestbook");
        $stmt->execute();
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

    public function selectEntriesByAuthor($author){
        $stmt=$this->pdo->prepare("SELECT * FROM guestbook G WHERE G.author_email=?");
        $stmt->execute([$author]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }
    public function searchByAuthor($author){
        $stmt=$this->pdo->prepare("SELECT * FROM guestbook G WHERE G.author_email LIKE ?");
        $search_term = "%$author%"; 
        $stmt->execute([$search_term]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
      }
    public function selectEntriesByTitle($title){
        $stmt=$this->pdo->prepare("SELECT * FROM guestbook G WHERE G.title LIKE ?");
        $search_term = "%$title%"; 
        $stmt->execute([$search_term]);
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
      }
    public function selectUserByEmail($email){
        $stmt=$this->pdo->prepare("SELECT * FROM users WHERE email=?");
        $stmt->execute([$email]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }

    public function insertEntry($author,$title,$content,$date){
        $stmt=$this->pdo->prepare("INSERT INTO guestbook(author_email,title,comment,date) VALUES(?,?,?,?)");
        return $stmt->execute([$author,$title,$content,$date]);
    }
    
    public function updateEntry($id,$author,$title,$content,$date){
        $stmt=$this->pdo->prepare("UPDATE guestbook SET author_email=?,title=?,comment=?,date=? WHERE id=?");
        return $stmt->execute([$author,$title,$content,$date,$id]);
    }

    public function deleteEntry($id){
        $stmt=$this->pdo->prepare("DELETE FROM guestbook WHERE id=?");
        return $stmt->execute([$id]);
    }

    public function getRole($email){
        $stmt=$this->pdo->prepare("SELECT is_admin FROM users WHERE email=?");
        $stmt->execute([$email]);
        return $stmt->fetch(PDO::FETCH_ASSOC);


    }
    public function checkUser($email,$password){
        $stmt=$this->pdo->prepare("SELECT * FROM users WHERE email=? AND password=?");
        $stmt->execute([$email,$password]);
        return $stmt->fetch(PDO::FETCH_ASSOC);
    }
    public function show($value){
        echo json_encode($value);

    }

    public function run(){
        if(isset($_GET['action'])){
            switch($_GET['action']){
                case 'selectAllEntries':
                    session_start();
                    $entries=$this->selectAllEntries();
                    $this->show($entries);
                    break;
                case 'checkUser':
                    $email=$_GET['email'];
                    $password=$_GET['password'];
                    $user=$this->checkUser($email,$password);
                    $this->show($user);
                    break;
                case 'getRole':
                    session_start();
                    $email=$_GET['email'];
                    $role=$this->getRole($email);
                    $this->show($role);
                    break;
                case 'selectEntriesByAuthor':
                    session_start();
                    $author=$_GET['email'];
                    $entries=$this->selectEntriesByAuthor($author);
                    $this->show($entries);
                    break;
                case 'searchByAuthor':
                    session_start();
                    $author=$_GET['email'];
                    $entries=$this->searchByAuthor($author);
                    $this->show($entries);
                    break;
                case 'selectEntriesByTitle':
                    session_start();
                    $title=$_GET['title'];
                    $entries=$this->selectEntriesByTitle($title);
                    $this->show($entries);
                    break;
                case 'selectUserByEmail':
                    session_start();
                    $email=$_GET['email'];   
                    $user=$this->selectUserByEmail($email);
                    $this->show($user);
                    break;
                case 'insertEntry':
                        session_start();
                        $author=$_GET['email'];
                        $title=$_GET['title'];
                        $comment=$_GET['comment'];
                        $date=$_GET['date'];
                        $result= $this->insertEntry($author,$title,$comment,$date);
                        $this->show($result);
                        break;
                case 'updateEntry':
                    session_start();
                    $id=$_GET['id'];
                    $author=$_GET['email'];  
                    $title=$_GET['title'];
                    $comment=$_GET['comment'];
                    $date=$_GET['date'];
                    $result= $this->updateEntry($id,$author,$title,$comment,$date);
                    $this->show($result);
                    break;
                case 'deleteEntry':
                    session_start();
                    $id=$_GET['id'];
                    $result= $this->deleteEntry($id);
                    $this->show($result);
                    break;


            }
        }
    }
}
$conn=new DBConnection();
$conn->run();
?>
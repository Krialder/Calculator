<?php
session_start();
include 'DB_Connection.php';

// Check if the user role is admin
if (!isset($_SESSION['role']) || $_SESSION['role'] !== 'admin') {
    exit('Unauthorized access');
}

// Get the user ID from the query parameter
$userId = $_GET['user_id'] ?? null;

if ($userId) {
    // Prepare and execute the delete statement
    $sql = 'DELETE FROM Guest WHERE user_id = :user_id';
    $stmt = $conn->prepare($sql);
    $stmt->bindParam(':user_id', $userId);
    $stmt->execute();

    // Update user IDs to be sequential
    $sql = 'SET @count = 0';
    $conn->exec($sql);
    $sql = 'UPDATE Guest SET user_id = @count:= @count + 1';
    $conn->exec($sql);
    $sql = 'ALTER TABLE Guest AUTO_INCREMENT = 1';
    $conn->exec($sql);
}

// Redirect back to account-settings.html
header('Location: /account-settings.html');
exit();
?>
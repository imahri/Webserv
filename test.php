<?php
// Start the session
session_start();

// Set session variables
$_SESSION['user_id'] = 12; // Replace 123 with the desired user ID
$_SESSION['user_name'] = "BOUDA"; // Replace "John Doe" with the desired user name

// Retrieve session variables
$user_id = isset($_SESSION['user_id']) ? $_SESSION['user_id'] : "User ID not retrieved";
$user_name = isset($_SESSION['user_name']) ? $_SESSION['user_name'] : "User name not retrieved";

// Display the result with newline characters
echo "Session variables set successfully.\nUser ID: " . $user_id . "\nUser Name: " . $user_name . "\n";
?>
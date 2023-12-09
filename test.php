<?php
// Set a cookie
$cookie_name = "test_cookie";
$cookie_value = "Hello, CGI!";
setcookie($cookie_name, $cookie_value, 0, "/");
setcookie("username", "Yahya TAQSI", 0, "/");
setcookie("nik", "BOUDA", 0, "/");

// Retrieve the cookie
$retrieved_cookie = isset($_COOKIE[$cookie_name]) ? $_COOKIE[$cookie_name] : "Cookie not retrieved";
$retrieved_cookie1 = isset($_COOKIE["username"]) ? $_COOKIE["username"] : "Cookie not retrieved";
$retrieved_cookie2 = isset($_COOKIE["nik"]) ? $_COOKIE["nik"] : "Cookie not retrieved";

// Display the result
echo "Cookie set successfully. Retrieved value: " . $retrieved_cookie . "<br>";
echo "USERNAME: " . $retrieved_cookie1 . "<br>";
echo "NIKNAME: " . $retrieved_cookie2 . "<br>";
?>
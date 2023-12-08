<?php
// Set a cookie
$cookie_name = "test_cookie";
$cookie_value = "Hello, CGI!";
setcookie($cookie_name, $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day

// Retrieve the cookie
$retrieved_cookie = $_COOKIE[$cookie_name];

// Display the result
echo "Cookie set successfully. Retrieved value: " . $retrieved_cookie;
?>
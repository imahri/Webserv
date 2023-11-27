<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Random String Generator</title>
    <link rel="stylesheet" href="./style.css">
</head>
<body>
    <div class="container">
        <h1>Random String Generator</h1>
        <p id="random-string">Generated Random String: <?php echo generateRandomString(8); ?></p>
        <button onclick="generateNewString()">Generate New String</button>
    </div>

    <script>
        function generateNewString() {
            // Fetch the paragraph element
            var randomStringElement = document.getElementById('random-string');

            // Make an AJAX request to a PHP file or use fetch API to get a new random string
            // For simplicity, I'll just reload the page to demonstrate generating a new string
            location.reload();
        }
    </script>
</body>
</html>

<?php
function generateRandomString($length = 10) {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $randomString = '';

    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[rand(0, strlen($characters) - 1)];
    }

    return $randomString;
}
?>

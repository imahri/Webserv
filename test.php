<?php
// reset cookies
setcookie('cookie', $_GET["cookie"]);
?>
<body>
    <div class="container">
        <a href="/"><h1>WebServ</h1></a>
        <p>CGI Cookies Test</p>
<?php
echo "Your Cookie: " . $_GET["cookie"];
?>
</div>
</section>
</body>
</html>
<?php
  $counter = 1;

  if (isset($_COOKIE['counter'])) {
    $counter = $_COOKIE['counter'] + 1;
    if ($counter > 25) {
      $counter = 1;
    }
  }

  setcookie('counter', $counter, time() + 60*60*24);

?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <?= $counter; ?>
</head>
<body>
  
</body>
</html>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body> 
    <form action="./3.php" method="GET" enctype="multipart/form-data">
        <fieldset>
            <legend>Main data</legend>
            <div>
                <label>
                    <span>First Name</span>
                    <input name="first_name" type="text" placeholder="First Name" value="<?php echo $_GET['first_name']; ?>" autocomplete="name" required autofocus>
                </label>
            </div>
            <div>
                <label>
                    <span>Last Name</span>
                    <input name="last_name" type="text" placeholder="Last Name" value="<?php echo $_GET['last_name']; ?>" required>
                </label>
            </div>
            <div>
                <label>
                    <span>Email</span>
                    <input name="email" type="email" placeholder="Email" value="<?php echo $_GET['email']; ?>" autocomplete="email" required>
                </label>
            </div>
            <div>
                <label>
                    <span>Password</span>
                    <input name="password" type="password" value="<?php echo $_GET['password']; ?>" required>
                </label>
            </div>
            <div>
                <label>
                    <span>Password Repeating</span>
                    <input name="password_r" type="password" value="<?php echo $_GET['password_r']; ?>" required>
                </label>
            </div>
        </fieldset>
        <fieldset>
            <legend>Second data</legend>
            <label>
                <span>Password Repeating</span>
                <input name="password_r" type="password" value="<?php echo $_GET['password_r']; ?>" required>
            </label>
            <p>Sex</p>
            <label>
                <input type="radio" name="sex" value="0" <?php if ($_GET['sex'] == 0) echo "checked"; ?>>
                <span>Man</span>
            </label>
            <label>
                <input type="radio" name="sex" value="1" <?php if ($_GET['sex'] == 1) echo "checked"; ?>>
                <span>Woman</span>
            </label>
            <label>
                <input type="radio" name="sex" value="2" <?php if ($_GET['sex'] == 2) echo "checked"; ?>>
                <span>Neutral</span>
            </label>
            <div>
                <label>
                    <span>Avatar</span>
                    <input type="file" name="avatar" value="<?php echo $_GET['avatar']; ?>">
                </label>
            </div>
            <div>
                <label>
                    <span>Country</span>
                    <select name="country">
                        <option value="0" <?php if ($_GET['country'] == 0) echo "selected"; ?>>USA</option>
                        <option value="1" <?php if ($_GET['country'] == 1) echo "selected"; ?>>Russia</option>
                        <option value="2" <?php if ($_GET['country'] == 2) echo "selected"; ?> disabled>Belarus</option>
                    </select>
                </label>
            </div>
            <div>
                <label>
                    <div>
                        <span>About you</span>
                    </div>
                    <textarea name="about" cols="30" rows="10" acceskey="p"><?php echo $_GET['about']; ?></textarea>
                </label>
            </div>
            <div>
                <label>
                    <span>Birth Date</span>
                    <input type="date" name="birth-date" min="1900-01-01" max="2021-12-31">
                    <input type="time" name="birth-time">
                    <input type="month" name="birth-datetime">
                </label>
            </div>
            <div>
                <label>Color</label>
                <input type="color" name="color">
            </div>
            <div>
                <label>
                    <span>Range</span>
                    <input type="range" min="0" max="10" step="1" value="0" name="range">
                </label>
            </div>
            <div>
                <label>
                    <span>Number</span>
                    <input type="number" name="number" min="0">
                </label>
            </div>
            <div>
                <label>
                    <span>Tel</span>
                    <input type="tel" name="phone" pattern="[0-9]{3}-[0-9]{3}-[0-9]{4}">
                </label>
            </div>
            <div>
                <label>
                    <span>Url</span>
                    <input type="url" name="url">
                </label>
            </div>
            <div>
                <label>
                    <span>Meter</span>
                    <meter id="anna" form="form1" name="anna" min="0" low="40" high="90" max="100" value="95"></meter>
                </label>
            </div>
        </fieldset>
        <button type="submit">Send</button>
    </form>
</body>
</html>

<?php

// $message = '';
// $message .= 'First Name: ' . $_GET['first_name'] . PHP_EOL;

// mail('titorovichnikita@gmail.com', 'test', $message);



?>


<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    session_unset();
    session_destroy();
    header("Location: login.php");
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Confirm Logout</title>
    <link rel="stylesheet" href="css/logout.css">
</head>

<body>
    <header>
        <h1><img src="ntu.png" alt="NTU Delivery Logo">NTU Delivery Service</h1> <!-- https://m.facebook.com/NTUsg/photos/-->
    </header>
    <div class="general">
        <nav>
            <a href="index.html">Home</a>
            <a href="about.html">About</a>
            <a href="canteen.php">Canteens</a>
            <a href="register.php">Register</a>
            <a href="login.php">Login</a>
            <a href="logout.php">Logout</a>
            <a href="checkout.php">Checkout</a>
            <a href="reviews.php">Write a Review</a>
            <a href="stall_overview.php">Stall Overview</a>



        </nav>
        <div class="content">
            <section>
                <h2>Log out</h2>
                <p>Are you sure you want to log out?</p>
                <form method="post">
                    <button type="submit">Log out</button>
                    <a href="canteen.php"><button type="button">Cancel</button></a>
                </form>
            </section>
        </div>
    </div>
</body>

</html>
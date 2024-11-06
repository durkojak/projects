<?php
session_start();

if (isset($_SESSION['user_id'])) {
    $user_id = $_SESSION['user_id'];
    $user_email = isset($_SESSION['email']) ? $_SESSION['email'] : 'Email not set';
    $session_id = session_id();

    echo "<script>console.log('User ID: " . $user_id . "');</script>";
    echo "<script>console.log('User Email: " . htmlspecialchars($user_email) . "');</script>";
    echo "<script>console.log('Session ID: " . $session_id . "');</script>";
} else {
    echo "<script>console.log('User is not logged in');</script>";
}

$servername = "localhost";
$username = "root";
$password = "REPLACE_WITH_YOUR_PASSWORD";
$dbname = "ntu_delivery";
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    echo "<script>console.log('Connection failed: " . $conn->connect_error . "');</script>";
    die();
}
echo "<script>console.log('Connected successfully');</script>";

$image_paths = [
    "css/canteen1.jpg",
    "css/canteen2.jpg",
    "css/canteen3.jpg",
    "css/canteen4.jpeg"
];
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>NTU Delivery Service</title>
    <link rel="stylesheet" href="css/canteen.css">
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

    <section>
        <h2>Available Canteens</h2>
        <ul class="canteen-list">
            <?php
            $sql = "SELECT id_canteen, canteen_name FROM canteen";
            $result = $conn->query($sql);

            $image_index = 0; 

            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                        echo "<li class='canteen-item'>";
                        echo "<img src='" . $image_paths[$image_index] . "' alt='Image for " . htmlspecialchars($row['canteen_name']) . "'>";
                        echo "<br>";
                        echo "<a href='stall.php?id_canteen=" . $row['id_canteen'] . "'>" . htmlspecialchars($row['canteen_name']) . "</a>";
                        echo "</li>";

                        $image_index = ($image_index + 1) % count($image_paths);
                }
            } else {
                echo "<li>No canteens available.</li>";
            }

            $conn->close();
            ?>
        </ul>
    </section>
    </div>
</body>

</html>

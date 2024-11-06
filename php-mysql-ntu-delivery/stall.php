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

$id_canteen = isset($_GET['id_canteen']) ? intval($_GET['id_canteen']) : 0;
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>NTU Delivery Service - Stalls</title>
    <link rel="stylesheet" href="css/stall.css">
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

    </nav>
    <section>
        <h2>Available Stalls</h2>
        <ul>
            <?php
            $sql = "SELECT id_stall, stall_name FROM stall WHERE id_canteen = ?";
            $stmt = $conn->prepare($sql);
            $stmt->bind_param("i", $id_canteen);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    $stall_id = $row['id_stall'];
                    $stall_name = htmlspecialchars($row['stall_name']);
                    echo "<li class='stall-item'>";
                    echo "<img src='stall.jpg' alt='Image for {$stall_name}' class='stall-image'>"; /*https://www.istockphoto.com/vector/thai-rice-with-roasted-chicken-cart-thai-street-food-with-seller-and-table-design-gm1143494845-307104885*/
                    echo "<br>"; 
                    echo "<a href='menu.php?id_stall={$stall_id}'>{$stall_name}</a>";
                    echo "</li>";
                }
            } else {
                echo "<li>No stalls available for this canteen.</li>";
            }

            $stmt->close();
            $conn->close();
            ?>
        </ul>
    </section>
    </div>
</body>

</html>

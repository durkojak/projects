<?php
session_start(); 

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

$user_id = $_SESSION['user_id'];

// Database connection
$servername = "localhost";
$username = "root";
$password = "REPLACE_WITH_YOUR_PASSWORD";
$dbname = "ntu_delivery";
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Handle review submission
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $id_stall = intval($_POST['id_stall']);
    $rating = intval($_POST['rating']);
    $review_text = $conn->real_escape_string($_POST['review']);

    $sql = "INSERT INTO review (id_user, id_stall, rating, review_text, timestamp) VALUES (?, ?, ?, ?, NOW())";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("iiis", $user_id, $id_stall, $rating, $review_text);

    if ($stmt->execute()) {
        echo "<script>alert('Review submitted successfully!');</script>";
    } else {
        echo "<script>alert('Failed to submit review.');</script>";
    }
    $stmt->close();
}

// Fetch all stalls
$sql = "SELECT id_stall, stall_name FROM stall";
$stalls_result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Stall Reviews</title>
    <link rel="stylesheet" href="css/reviews.css">
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
        <h2>Leave a Review</h2>
        <div class="content">
        <form action="reviews.php" method="POST" class="review-form">
            <label for="id_stall">Select Stall:</label>
            <select name="id_stall" id="id_stall" required>
                <option value="" disabled selected>Choose a stall</option>
                <?php
                if ($stalls_result->num_rows > 0) {
                    while ($row = $stalls_result->fetch_assoc()) {
                        echo "<option value='" . $row['id_stall'] . "'>" . htmlspecialchars($row['stall_name']) . "</option>";
                    }
                } else {
                    echo "<option value='' disabled>No stalls available</option>";
                }
                ?>
            </select>

            <label for="rating">Rating (1-5):</label>
            <input type="number" name="rating" id="rating" min="1" max="5" required>

            <label for="review">Your Review:</label>
            <textarea name="review" id="review" rows="4" required></textarea>

            <button type="submit">Submit Review</button>
        </form>
        </div>
    </section>
</body>
</div>
</html>

<?php
// Close the connection
$conn->close();
?>

<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

// Database connection
$servername = "localhost";
$username = "root";
$password = "REPLACE_WITH_YOUR_PASSWORD";
$dbname = "ntu_delivery";
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch stalls, canteens, average ratings, and reviews
$sql = "
    SELECT s.id_stall, s.stall_name, c.canteen_name, 
           COALESCE(AVG(r.rating), 0) AS avg_rating
    FROM stall s
    LEFT JOIN canteen c ON s.id_canteen = c.id_canteen
    LEFT JOIN review r ON s.id_stall = r.id_stall
    GROUP BY s.id_stall
";
$stalls_result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Stall Overview</title>
    <link rel="stylesheet" href="css/stall_overview.css">
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
        <h2>Stall Overview</h2>
        <section class="stall-overview">
            <?php
            if ($stalls_result->num_rows > 0) {
                while ($stall = $stalls_result->fetch_assoc()) {
                    echo "<div class='stall-container'>";

                    echo "<h2 class='stall-name'>" . htmlspecialchars($stall['stall_name']) . 
                        " <span class='at-canteen'>@" . htmlspecialchars($stall['canteen_name']) . "</span></h2>";

                    echo "<p class='avg-rating'><strong>Average Rating:</strong> " . number_format($stall['avg_rating'], 1) . "/5</p>";

                    // Fetch reviews for the current stall
                    $review_sql = "
                        SELECT r.rating, r.review_text, r.timestamp
                        FROM review r
                        WHERE r.id_stall = ?
                        ORDER BY r.timestamp DESC
                    ";
                    $review_stmt = $conn->prepare($review_sql);
                    $review_stmt->bind_param("i", $stall['id_stall']);
                    $review_stmt->execute();
                    $reviews_result = $review_stmt->get_result();

                    echo "<div class='reviews-row'>";
                    echo "<h3>Reviews:</h3>";

                    echo "<div class='reviews-list'>";
                    if ($reviews_result->num_rows > 0) {
                        while ($review = $reviews_result->fetch_assoc()) {
                            echo "<div class='review-box'>";
                            echo "<p><strong>Rating:</strong> " . $review['rating'] . "/5</p>";
                            echo "<p><strong>Review:</strong> " . htmlspecialchars($review['review_text']) . "</p>";
                            echo "<p class='review-timestamp'><small><strong>Posted on:</strong> " . $review['timestamp'] . "</small></p>";
                            echo "</div>";
                        }
                    } else {
                        echo "<p>No reviews yet.</p>";
                    }
                    echo "</div>"; 

                    echo "</div>"; 

                    $review_stmt->close();
                    echo "</div>"; 
                }
            } else {
                echo "<p>No stalls available.</p>";
            }
            ?>
        </section>
        </div>
    </div>
</body>

</html>

<?php
// Close the connection
$conn->close();
?>

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
    header("Location: login.php");
    exit();
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

$id_stall = isset($_GET['id_stall']) ? intval($_GET['id_stall']) : 0;

$order_id = isset($_SESSION['id_order']) ? $_SESSION['id_order'] : null;

if (is_null($order_id)) {
    $sql = "INSERT INTO orders (id_user) VALUES (?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $user_id);
    $stmt->execute();
    $order_id = $stmt->insert_id;
    $_SESSION['id_order'] = $order_id;
}

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['id_item_menu'])) {
    $item_id = intval($_POST['id_item_menu']);
    $quantity = intval($_POST['quantity']);

    $sql = "SELECT quantity FROM order_menu_item WHERE id_order = ? AND id_item_menu = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("ii", $order_id, $item_id);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $new_quantity = $row['quantity'] + $quantity;
        $update_sql = "UPDATE order_menu_item SET quantity = ? WHERE id_order = ? AND id_item_menu = ?";
        $update_stmt = $conn->prepare($update_sql);
        $update_stmt->bind_param("iii", $new_quantity, $order_id, $item_id);
        $update_stmt->execute();
    } else {
        $insert_sql = "INSERT INTO order_menu_item (id_order, id_item_menu, quantity) VALUES (?, ?, ?)";
        $insert_stmt = $conn->prepare($insert_sql);
        $insert_stmt->bind_param("iii", $order_id, $item_id, $quantity);
        $insert_stmt->execute();
    }

    header("Location: menu.php?id_stall=" . $id_stall);
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>NTU Delivery Service - Menu</title>
    <link rel="stylesheet" href="css/menu.css">
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
        <h2>Menu</h2>
        <h3>&nbsp;Available Items</h3>
        <ul>
            <?php
            $sql = "SELECT id_item_menu, item_name, item_description, item_price FROM item_menu WHERE id_stall = ?";
            $stmt = $conn->prepare($sql);
            $stmt->bind_param("i", $id_stall);
            $stmt->execute();
            $result = $stmt->get_result();

            if ($result->num_rows > 0) {
                while ($row = $result->fetch_assoc()) {
                    echo "<li style='margin-bottom: 15px;'> <!-- Add margin to each list item -->
                            <strong style='display: block; margin-bottom: 5px;'>" . htmlspecialchars($row['item_name']) . "</strong> <!-- Margin for item name -->
                            <span style='padding-left: 20px;'>" . htmlspecialchars($row['item_description']) . "</span>: <span>$" . number_format($row['item_price'], 2) . "</span> <!-- Keep description and price on the same line -->
                            <form action='' method='POST' style='margin-top: 5px;'> <!-- Margin for form -->
                                <input type='hidden' name='id_item_menu' value='" . htmlspecialchars($row['id_item_menu']) . "'>
                                <input type='number' name='quantity' min='1' value='1' class='small-input' required>
                                <button type='submit'>Add to Cart</button>
                            </form>
                        </li>";
                }
            } else {
                echo "<li>No items available for this stall.</li>";
            }

            $stmt->close();
            $conn->close();
            ?>
        </ul>
    </section>
    </div>
    </div>
</body>

</html>

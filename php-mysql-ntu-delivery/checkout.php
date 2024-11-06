<?php
session_start();

if (!isset($_SESSION['user_id'])) {
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

$order_id = isset($_SESSION['id_order']) ? $_SESSION['id_order'] : null;

if (is_null($order_id)) {
    $_SESSION['cart_empty'] = true; 
    header("Location: index.html");
    exit();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['checkout'])) {
    $sql = "UPDATE orders SET status = 'completed' WHERE id_order = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $order_id);

    if ($stmt->execute()) {
        echo "<script>
                alert('Order submitted successfully!');
                window.location.href = 'index.html';
              </script>";
    } else {
        echo "<script>alert('Failed to order.');</script>";
    }

    unset($_SESSION['id_order']);
    exit();
}

$sql = "SELECT omi.id_item_menu, omi.quantity, im.item_name, im.item_price 
        FROM order_menu_item omi 
        JOIN item_menu im ON omi.id_item_menu = im.id_item_menu 
        WHERE omi.id_order = ?";
$stmt = $conn->prepare($sql);
$stmt->bind_param("i", $order_id);
$stmt->execute();
$result = $stmt->get_result();

$total_amount = 0;
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Checkout</title>
    <link rel="stylesheet" href="css/checkout.css">
</head>

<body>
    <header>
        <h1><img src="ntu.png" alt="NTU Delivery Logo">NTU Delivery Service</h1>
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
        <h2>Check Out</h2>
        <div class="content">
        <h3>Your Order</h3>
        <table>
            <thead>
                <tr>
                    <th>Item Name</th>
                    <th>Quantity</th>
                    <th>Price</th>
                    <th>Total</th>
                </tr>
            </thead>
            <tbody>
                <?php
                if ($result->num_rows > 0) {
                    while ($row = $result->fetch_assoc()) {
                        $item_total = $row['quantity'] * $row['item_price'];
                        $total_amount += $item_total;
                        echo "<tr>
                                <td>" . htmlspecialchars($row['item_name']) . "</td>
                                <td>" . htmlspecialchars($row['quantity']) . "</td>
                                <td>$" . number_format($row['item_price'], 2) . "</td>
                                <td>$" . number_format($item_total, 2) . "</td>
                              </tr>";
                    }
                } else {
                    echo "<tr><td colspan='4'>No items in your order.</td></tr>";
                }
                ?>
            </tbody>
            <tfoot>
                <tr>
                    <td colspan="3">Total Amount</td>
                    <td>$<?php echo number_format($total_amount, 2); ?></td>
                </tr>
            </tfoot>
        </table>
        </div>

        <form action="" method="POST">
            <button type="submit" name="checkout">Checkout</button>
        </form>
    </section>

    <?php
    $stmt->close();
    $conn->close();
    ?>
    </div>
</body>

</html>


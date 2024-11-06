<?php
session_start();
$servername = "localhost";
$username = "root";
$password = "REPLACE_WITH_YOUR_PASSWORD";
$dbname = "ntu_delivery";
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$message = "";
$showModal = false; 

if (isset($_SESSION['user_id'])) {
    $message = "You are already logged in. Redirecting to your account...";
    header("Location: index.html");
    exit();
    
} else {
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $email = $_POST['email'];
        $password = $_POST['password'];

        $stmt = $conn->prepare("SELECT id_user, password_hash FROM users WHERE email = ?");
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $stmt->store_result();

        if ($stmt->num_rows > 0) {
            $stmt->bind_result($id_user, $password_hash);
            $stmt->fetch();

            if (password_verify($password, $password_hash)) {
                $_SESSION['user_id'] = $id_user;
                $_SESSION['email'] = $email;
                $message = "Login successful! Welcome!";
                header("Location: index.html"); 
                exit;
            } else {
                $message = "Invalid password.";
            }
        } else {
            $message = "No user found with that email.";
        }

        $stmt->close();
    }
}
$conn->close();
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <link rel="stylesheet" href="css/login.css">

    <style>
        .modal {
            display: none;
            position: fixed; 
            z-index: 1000; 
            left: 0;
            top: 0;
            width: 100%; 
            height: 100%;
            background-color: rgba(0, 0, 0, 0.5); 
        }

        .modal-content {
            background-color: #fefefe;
            margin: 15% auto; 
            padding: 20px;
            border: 1px solid #888;
            width: 80%; 
            max-width: 500px; 
        }

        .close-button {
            color: #aaa;
            float: right;
            font-size: 28px;
            font-weight: bold;
        }

        .close-button:hover,
        .close-button:focus {
            color: black;
            text-decoration: none;
            cursor: pointer;
        }

        .error {
            color: red;
            font-size: 0.9em;
        }

        .valid {
            color: green;
            font-size: 0.9em;
        }
    </style>

    <script>
        function showModal(message) {
            document.getElementById('successMessage').textContent = message;
            document.getElementById('successModal').style.display = 'block';
        }

        function closeModal() {
            document.getElementById('successModal').style.display = 'none';
        }

        function validateEmail() {
            const email = document.getElementById('email').value;
            const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            const emailFeedback = document.getElementById('emailFeedback');

            if (emailPattern.test(email)) {
                emailFeedback.textContent = 'Valid email!';
                emailFeedback.className = 'valid';
            } else {
                emailFeedback.textContent = 'Invalid email format.';
                emailFeedback.className = 'error';
            }
        }

        function validatePassword() {
            const password = document.getElementById('password').value;
            const passwordPattern = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}$/; 
            const passwordFeedback = document.getElementById('passwordFeedback');

            if (passwordPattern.test(password)) {
                passwordFeedback.textContent = 'Valid password.';
                passwordFeedback.className = 'valid';
            } else {
                passwordFeedback.textContent = 'Password must be at least 8 characters, with 1 uppercase letter, 1 lowercase letter, and 1 digit.';
                passwordFeedback.className = 'error';
            }
        }

        document.addEventListener('DOMContentLoaded', () => {
            const message = "<?php echo addslashes($message); ?>"; 
            const showModal = <?php echo $showModal ? 'true' : 'false'; ?>;
            if (message && showModal) {
                showModal(message); 
            }

            document.getElementById('email').addEventListener('input', validateEmail);
            document.getElementById('password').addEventListener('input', validatePassword);
        });
    </script>
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

        <!-- Only show the content if the user is not logged in -->
        <?php if (!isset($_SESSION['user_id'])): ?>
        <div class="content">
            <h2>Log in</h2>
            <form method="POST" action="">
                <div class="input-group">
                    <input type="email" id="email" name="email" required placeholder="Email">
                    <div id="emailFeedback" class="error"></div> <!-- Feedback for email validation -->
                </div>

                <div class="input-group">
                    <input type="password" id="password" name="password" required placeholder="Password">
                    <div id="passwordFeedback" class="error"></div> <!-- Feedback for password validation -->
                </div>

                <button type="submit">Log in</button>
            </form>
        </div>
        <?php endif; ?>
    </div>

    <!-- Modal Structure -->
    <div id="successModal" class="modal">
        <div class="modal-content">
            <span class="close-button" onclick="closeModal()">&times;</span>
            <p id="successMessage"></p>
        </div>
    </div>
</body>

</html>

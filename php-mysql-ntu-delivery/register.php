<?php
$servername = "localhost";
$username = "root";
$password = "REPLACE_WITH_YOUR_PASSWORD";
$dbname = "ntu_delivery";
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$message = "";

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $email = $_POST['email'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];
    $first_name = $_POST['first_name'];
    $surname = $_POST['surname'];

    $stmt = $conn->prepare("SELECT email FROM users WHERE email = ?");
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $stmt->store_result();

    if ($stmt->num_rows > 0) {
        $message = "Error: Email already registered.";
    } elseif ($password !== $confirm_password) {
        $message = "Error: Passwords do not match.";
    } else {
        $password_hash = password_hash($password, PASSWORD_BCRYPT);

        $stmt = $conn->prepare("INSERT INTO users (email, password_hash, first_name, surname) VALUES (?, ?, ?, ?)");
        $stmt->bind_param("ssss", $email, $password_hash, $first_name, $surname);

        if ($stmt->execute()) {
            $message = "Registration successful!";
        } else {
            $message = "Error: " . $stmt->error;
        }
    }
    $stmt->close();
}
$conn->close();
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Register</title>
    <link rel="stylesheet" href="css/register.css">

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

        .error { color: red; font-size: 0.9em; }
        .valid { color: green; font-size: 0.9em; }
    </style>

    <script>
        function showModal(message) {
            document.getElementById('successMessage').textContent = message;
            document.getElementById('successModal').style.display = 'block';
        }

        function closeModal() {
            document.getElementById('successModal').style.display = 'none';
        }

        function validateFirstName() {
            const firstName = document.getElementById('first_name').value;
            const firstNameFeedback = document.getElementById('firstNameFeedback');
            const namePattern = /^[A-Za-z]+$/;

            if (namePattern.test(firstName)) {
                firstNameFeedback.textContent = 'Valid first name!';
                firstNameFeedback.className = 'valid';
            } else {
                firstNameFeedback.textContent = 'First name should only contain letters.';
                firstNameFeedback.className = 'error';
            }
        }

        function validateSurname() {
            const surname = document.getElementById('surname').value;
            const surnameFeedback = document.getElementById('surnameFeedback');
            const namePattern = /^[A-Za-z]+$/;

            if (namePattern.test(surname)) {
                surnameFeedback.textContent = 'Valid surname!';
                surnameFeedback.className = 'valid';
            } else {
                surnameFeedback.textContent = 'Surname should only contain letters.';
                surnameFeedback.className = 'error';
            }
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
                passwordFeedback.textContent = 'Strong password!';
                passwordFeedback.className = 'valid';
            } else {
                passwordFeedback.textContent = 'Password must be at least 8 characters, with 1 uppercase letter, 1 lowercase letter, and 1 digit.';
                passwordFeedback.className = 'error';
            }

            validateConfirmPassword(); 
        }

        function validateConfirmPassword() {
            const password = document.getElementById('password').value;
            const confirmPassword = document.getElementById('confirm_password').value;
            const confirmPasswordFeedback = document.getElementById('confirmPasswordFeedback');

            if (password === confirmPassword) {
                confirmPasswordFeedback.textContent = 'Passwords match!';
                confirmPasswordFeedback.className = 'valid';
            } else {
                confirmPasswordFeedback.textContent = 'Passwords do not match.';
                confirmPasswordFeedback.className = 'error';
            }
        }

        document.addEventListener('DOMContentLoaded', () => {
            const message = "<?php echo addslashes($message); ?>"; 
            if (message) {
                showModal(message); 
            }
            
            document.getElementById('first_name').addEventListener('input', validateFirstName);
            document.getElementById('surname').addEventListener('input', validateSurname);
            document.getElementById('email').addEventListener('input', validateEmail);
            document.getElementById('password').addEventListener('input', validatePassword);
            document.getElementById('confirm_password').addEventListener('input', validateConfirmPassword);
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
        <div class="content">
    <h2>Register</h2>
    <form method="POST" action="">
        <div class="input-group name-row">
            <input type="text" id="first_name" name="first_name" required placeholder="First Name">
            <input type="text" id="surname" name="surname" required placeholder="Surname">
            <div class="error-messages">
                <div id="firstNameFeedback" class="error"></div>
                <div id="surnameFeedback" class="error"></div>
            </div>
        </div>
        <div class="input-group">
            <input type="email" id="email" name="email" required placeholder="Email">
            <div id="emailFeedback" class="error"></div>
        </div>
        <div class="input-group">
            <input type="password" id="password" name="password" required placeholder="Password">
            <div id="passwordFeedback" class="error"></div>
        </div>
        <div class="input-group">
            <input type="password" id="confirm_password" name="confirm_password" required placeholder="Confirm Password">
            <div id="confirmPasswordFeedback" class="error"></div>
        </div>
        <button type="submit">Register</button>
    </form>
</div>

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

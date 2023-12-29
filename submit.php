<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $walletAddress = filter_var($_POST["walletAddress"], FILTER_SANITIZE_STRING);

    // Send notification to satoshi@vistomail.com
    $to = "satoshi@vistomail.com";
    $subject = "New Faucet Submission";
    $message = "New Faucet submission:\n\nWallet Address: $walletAddress";
    $headers = "From: bitcoins@vistomail.com"; // Change this to a valid email address

    mail($to, $subject, $message, $headers);
}
?>

<?php
// post_request.php

// Check if the request method is POST
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Read the raw POST data
    $rawData = file_get_contents('php://input');

    // Attempt to decode the JSON
    $jsonData = json_decode($rawData, true);

    // Check if JSON decoding was successful
    if ($jsonData !== null) {
        // Loop through each key-value pair in the JSON and print it
        foreach ($jsonData as $key => $value) {
            echo "Key: " . htmlspecialchars($key) . " = " . htmlspecialchars($value) . "<br>";
        }
    } else {
        echo "Invalid JSON data.";
    }
} else {
    echo "This endpoint accepts POST requests only.";
}
?>
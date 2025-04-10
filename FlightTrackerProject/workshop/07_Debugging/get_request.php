<?php
// get_request.php

// Check if any GET parameters exist
if (!empty($_GET)) {
    // Loop through each GET parameter and print its value
    foreach ($_GET as $key => $value) {
        echo "Parameter: " . htmlspecialchars($key) . " = " . htmlspecialchars($value) . "<br>";
    }
} else {
    echo "No GET parameters found.";
}
?>
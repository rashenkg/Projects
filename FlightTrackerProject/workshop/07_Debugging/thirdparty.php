<?php

// Define the API endpoint
$apiUrl = 'https://animechan.io/api/v1/quotes/random';

// Function to send a GET request
function sendGetRequest($url, $params = []) {
    $queryString = http_build_query($params);
    $urlWithParams = $queryString ? $url . '?' . $queryString : $url;

    $ch = curl_init($urlWithParams);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, [
        'Content-Type: application/json',
    ]);

    $response = curl_exec($ch);
    $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);

    return [
        'response' => json_decode($response, true),
        'http_code' => $httpCode
    ];
}

// Function to send a JSON POST request
function sendJsonPostRequest($url, $payload) {
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, [
        'Content-Type: application/json',
    ]);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($payload));

    $response = curl_exec($ch);
    $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);

    return [
        'response' => json_decode($response, true),
        'http_code' => $httpCode
    ];
}

// Function to handle incoming POST requests
function handleIncomingPostRequest() {
    $input = file_get_contents('php://input');
    $data = json_decode($input, true);

    if (json_last_error() === JSON_ERROR_NONE) {
        // Successfully decoded JSON
        header('Content-Type: application/json');
        echo json_encode([
            'success' => true,
            'received_data' => $data
        ]);
    } else {
        // Error decoding JSON
        header('Content-Type: application/json', true, 400);
        echo json_encode([
            'success' => false,
            'message' => 'Invalid JSON received'
        ]);
    }
}

// Check the HTTP method
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    // Example: Fetch a random anime quote
    $response = sendGetRequest($apiUrl);
    header('Content-Type: application/json');
    echo json_encode($response);
} elseif ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_GET['action']) && $_GET['action'] === 'send') {
        // Example payload to send
        $payload = [
            'example_field' => 'example_value'
        ];

        $response = sendJsonPostRequest($apiUrl, $payload);
        header('Content-Type: application/json');
        echo json_encode($response);
    } else {
        // Handle incoming POST request
        handleIncomingPostRequest();
    }
} else {
    // Unsupported HTTP method
    header('Content-Type: application/json', true, 405);
    echo json_encode([
        'success' => false,
        'message' => 'Method not allowed'
    ]);
}
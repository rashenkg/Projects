<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST');
header('Access-Control-Allow-Headers: Content-Type');


// Retrieve and validate input
$input = json_decode(file_get_contents('php://input'), true);


$origin = $input['origin'] ?? null;
$destination = $input['destination'] ?? null;
$date = $input['date'] ?? null;
$passengers = (int)($input['passengers'] ?? 1);


if (!$origin || !$destination || !$date) {
    echo json_encode(["error" => "Missing required input fields."]);
    exit;
}


// Dummy flight data
$flights = [
    [
        "from" => "JFK",
        "to" => "LAX",
        "date" => "2024-12-25",
        "airline" => "Delta",
        "price" => 300
    ],
    [
        "from" => "JFK",
        "to" => "ATL",
        "date" => "2024-12-25",
        "airline" => "American Airlines",
        "price" => 200
    ],
    [
        "from" => "LAX",
        "to" => "SFO",
        "date" => "2024-12-26",
        "airline" => "United",
        "price" => 150
    ],
    [
        "from" => "ATL",
        "to" => "JFK",
        "date" => "2024-12-27",
        "airline" => "Spirit",
        "price" => 100
    ],
    [
        "from" => "DXB",
        "to" => "LHR",
        "date" => "2024-12-28",
        "airline" => "Emirates",
        "price" => 600
    ],
    [
        "from" => "SYD",
        "to" => "NRT",
        "date" => "2024-12-29",
        "airline" => "Qantas",
        "price" => 800
    ]
];


// Filter flights based on input
$filteredFlights = array_filter($flights, function ($flight) use ($origin, $destination, $date) {
    return $flight['from'] === $origin && $flight['to'] === $destination && $flight['date'] === $date;
});


// If no flights found, return an error
if (empty($filteredFlights)) {
    echo json_encode(["error" => "No flights found for the selected criteria."]);
    exit;
}


// Return filtered flights
echo json_encode(["flights" => array_values($filteredFlights)]);
?>

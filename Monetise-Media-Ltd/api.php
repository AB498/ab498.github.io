

<?php
// Get the raw JSON data from the request body
$rawJsonData = file_get_contents('php://input');

// Decode the JSON data into a PHP associative array
$jsonData = json_decode($rawJsonData, true);

// Check if the JSON decoding was successful
if ($jsonData === null) {
    http_response_code(400); // Bad Request
    echo json_encode(array('error' => 'Invalid JSON data'));
    exit;
}

// Assuming your cURL request URL and headers
$curlUrl = 'https://monetise.leadbyte.co.uk/restapi/v1.2/leads';
$curlHeaders = array('Content-Type: application/json');

// Initialize cURL session
$ch = curl_init($curlUrl);

// Set cURL options
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'POST');
curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($jsonData));
curl_setopt($ch, CURLOPT_HTTPHEADER, $curlHeaders);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    // Disable SSL verification (not recommended for production)
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);


// Execute cURL request
$curlResponse = curl_exec($ch);

// Close cURL session
curl_close($ch);

// Handle the cURL response as needed
echo $curlResponse;
// print_r($jsonData["lead"]["6months"]);

?>

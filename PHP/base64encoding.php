<?php
// Basic authentication example
// Your customer key
$customerKey = "Your customer key";
// Your customer secret
$customerSecret = "Your customer secret";
// Create a string: customerKey:customerSecret
$credentials = $customerKey . ":" . $customerSecret;

// Use base64 encoding
$base64Credentials = base64_encode($credentials);
// Create authorization header
$arr_header = "Authorization: Basic " . $base64Credentials;

$curl = curl_init();
// Send request with specified header and body
curl_setopt_array($curl, array(
  CURLOPT_URL => 'https://api.agora.io/dev/v2/project/<Your App ID>/rtm/users/userA/peer_messages?wait_for_ack=true',
  CURLOPT_RETURNTRANSFER => true,
  CURLOPT_ENCODING => '',
  CURLOPT_MAXREDIRS => 10,
  CURLOPT_TIMEOUT => 0,
  CURLOPT_FOLLOWLOCATION => true,
  CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
  CURLOPT_CUSTOMREQUEST => 'POST',
  CURLOPT_POSTFIELDS =>'{
    "destination": "userB",
    "enable_offline_messaging": false,
    "enable_historical_messaging": false,
    "payload": "Hello"
}',
  CURLOPT_HTTPHEADER => array(
    $arr_header,
    'Content-Type: text/plain'
  ),
));

$response = curl_exec($curl);

if($response === false) {
    echo "Error in cURL : " . curl_error($curl);
}

curl_close($curl);

echo $response;
// Basic authentication example
const https = require('https')
// Customer key
const customerKey = "Your customer key"
// Customer secret
const customerSecret = "Your customer secret"
// Create plain credential for base64 encoding
const plainCredential = customerKey + ":" + customerSecret
// Perform base64 encoding
encodedCredential = Buffer.from(plainCredential).toString('base64')
authorizationField = "Basic " + encodedCredential

// Set options for the request
const options = {
  hostname: 'api.agora.io',
  port: 443,
  path: '/dev/v2/project/<Your App ID>/rtm/users/userA/peer_messages?wait_for_ack=true',
  method: 'POST',
  headers: {
    'Authorization':authorizationField,
    'Content-Type': 'application/json'
  }
}
// Set body
const data = JSON.stringify({"destination": "userB", "enable_offline_messaging": false,  "enable_historical_messaging": false, "payload": "Hello"})

const req = https.request(options, res => {
  console.log(`Status code: ${res.statusCode}`)

  res.on('data', d => {
    process.stdout.write(d)
  })
})

req.on('error', error => {
  console.error(error)
})

req.write(data)
req.end()
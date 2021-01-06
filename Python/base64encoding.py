# -- coding utf-8 --
# Python 3
# Basic authentication example
import base64
import http.client

# Your customer key
customer_key = "Your customer key"
# Your customer secret
customer_secret = "Your customer secret"

# Base64 encoding
credentials = customer_key + ":" + customer_secret
base64_credentials = base64.b64encode(credentials.encode("utf8"))

# Credential to add to the Authorization field
credential = base64_credentials.decode("utf8")

# Create connection with the base URL
conn = http.client.HTTPSConnection("api.agora.io")

# Specify the payload to send with the request
payload = "{\r\n    \"destination\": \"userB\",\r\n    \"enable_offline_messaging\": false,\r\n    \"enable_historical_messaging\": false,\r\n    \"payload\": \"Hello\"\r\n}\r\n\r\n"

# Header to send with the request
headers = {}
headers['Authorization'] = 'basic ' + credential
headers['Content-Type'] = 'text/plain'

# Send request with path
conn.request("POST", "/dev/v2/project/<your-App-ID>/rtm/users/userA/peer_messages?wait_for_ack=true", payload, headers)
res = conn.getresponse()
data = res.read()
print(data.decode("utf-8"))
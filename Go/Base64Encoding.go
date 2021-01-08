package main

import (
  "fmt"
  "strings"
  "net/http"
  "io/ioutil"
  "encoding/base64"
)

// Basic authentication example
func main() {

  // Customer key
  customerKey := "Your customer key"
  // Customer secret
  customerSecret := "Your customer secret"

  // Use base64 encoding
  plainCredentials := customerKey + ":" + customerSecret
  base64Credentials := base64.StdEncoding.EncodeToString([]byte(plainCredentials))

  url := "https://api.agora.io/dev/v2/project/<Your App ID>/rtm/users/userA/peer_messages?wait_for_ack=true"
  method := "POST"

  payload := strings.NewReader(`{"destination": "userB",  "enable_offline_messaging": false,  "enable_historical_messaging": false,   "payload": "Hello"}`)

  client := &http.Client {
  }
  req, err := http.NewRequest(method, url, payload)

  if err != nil {
    fmt.Println(err)
    return
  }
  // Add Authorization header and content type
  req.Header.Add("Authorization", "Basic " + base64Credentials)
  req.Header.Add("Content-Type", "text/plain")

  // Send HTTP request
  res, err := client.Do(req)
  if err != nil {
    fmt.Println(err)
    return
  }
  defer res.Body.Close()

  body, err := ioutil.ReadAll(res.Body)
  if err != nil {
    fmt.Println(err)
    return
  }
  fmt.Println(string(body))
}
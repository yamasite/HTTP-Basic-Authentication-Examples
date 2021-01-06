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
  customerKey := "bd233dacc8184860955d36987c9dbd8d"
  // Customer secret
  customerSecret := "80ba4d537794486d814e0d117f670f2d"

  // Use base64 encoding
  plainCredentials := customerKey + ":" + customerSecret
  base64Credentials := base64.StdEncoding.EncodeToString([]byte(plainCredentials))

  url := "https://api.agora.io/dev/v2/project/a4eedf51cd3d4c8992adce45145c1bd8/rtm/users/userA/peer_messages?wait_for_ack=true"
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
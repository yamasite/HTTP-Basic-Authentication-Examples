#define _CRT_SECURE_NO_WARNINGS
#include <curl/curl.h>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include "base64.hpp"
using namespace std;


// Basic authentication example
int main()
{
	CURL *curl;
	CURLcode res;
	// Customer key
	string customerKey = "Your customer key";
	// Customer secret
	string customerSecret = "Your customer secret";
	string comma = ":";
	string plainCredential = "";
	const char* encodedCredential = "";
	const char* authorizationHeader = "";
	// Create credential to be encoded via base64
	plainCredential = customerKey + comma + customerSecret;


	// Encode with base64
	vector<base64::byte> data(begin(plainCredential), end(plainCredential));
	auto encoded = base64::encode(data);
	string authorizationHeader_string ="Authorization: Basic " + encoded + "\"";
	// Create authorization header
	authorizationHeader = authorizationHeader_string.data();


	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.agora.io/dev/v2/project/<Your App ID>/rtm/users/userA/peer_messages?wait_for_ack=true");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		struct curl_slist *headers = NULL;
		// Set authorization header
		headers = curl_slist_append(headers, authorizationHeader);
		headers = curl_slist_append(headers, "Content-Type: text/plain");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		const char *data = "{ \"destination\": \"userB\",\r\n    \"enable_offline_messaging\": false,\r\n    \"enable_historical_messaging\": false,\r\n    \"payload\": \"Hello\"}";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		// SSL certificate
		curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Users\\WL\\Desktop\\curl\\cacert-2020-12-08.pem");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
		res = curl_easy_perform(curl);

	}
	curl_easy_cleanup(curl);

}
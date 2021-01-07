#define _CRT_SECURE_NO_WARNINGS
#include <curl/curl.h>
#include <iostream>
using namespace std;

// Basic authentication example
int main()
{
	CURL *curl;
	CURLcode res;

    const char* customerKey = "";
    const char* customerSecret = "";

	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.agora.io/dev/v2/project/a4eedf51cd3d4c8992adce45145c1bd8/rtm/users/userA/peer_messages?wait_for_ack=true");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Authorization: Basic YmQyMzNkYWNjODE4NDg2MDk1NWQzNjk4N2M5ZGJkOGQ6ODBiYTRkNTM3Nzk0NDg2ZDgxNGUwZDExN2Y2NzBmMmQ=");
		headers = curl_slist_append(headers, "Content-Type: text/plain");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		const char *data = "{\r\n    \"destination\": \"userB\",\r\n    \"enable_offline_messaging\": false,\r\n    \"enable_historical_messaging\": false,\r\n    \"payload\": \"Hello\"\r\n}\r\n\r\n";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Users\\WL\\Desktop\\curl\\cacert-2020-12-08.pem");
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
		res = curl_easy_perform(curl);

	}
	curl_easy_cleanup(curl);

}
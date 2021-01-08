import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Base64;

// Basic authentication example
public class Base64Encoding {

    public static void main(String[] args) throws IOException, InterruptedException {

        // Specify customer key
        final String customerKey = "Your customer key";
        // Specify customer ID
        final String customerSecret = "Your customer secret";

        // Concatenate and encode with base64
        String plainCredentials = customerKey + ":" + customerSecret;
        String base64Credentials = new String(Base64.getEncoder().encode(plainCredentials.getBytes()));
        // Create authorization header
        String authorizationHeader = "Basic " + base64Credentials;

        HttpClient client = HttpClient.newHttpClient();

        String body = "{\"destination\": \"userB\", \"enable_offline_messaging\": false,  \"enable_historical_messaging\": false,    \"payload\": \"Hello\"}";

        // Build HTTP request
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create("https://api.agora.io/dev/v2/project/<Your App ID>/rtm/users/userA/peer_messages?wait_for_ack=true"))
                .POST(HttpRequest.BodyPublishers.ofString(body))
                .header("Authorization", authorizationHeader)
                .header("Content-Type", "text/plain")
                .build();
        // Send HTTP request
        HttpResponse<String> response = client.send(request,
                HttpResponse.BodyHandlers.ofString());

        System.out.println(response.body());
    }
}
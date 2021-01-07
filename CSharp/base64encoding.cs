using System;
using System.IO;
using System.Net;
using System.Text;

namespace Examples.System.Net
{
    public class WebRequestPostExample
    {
        public static void Main()
        {
            string customerKey = "";
            string customerSecret = "";

            // Create a request using a URL that can receive a post.
            WebRequest request = WebRequest.Create("https://api.agora.io/dev/v2/project/a4eedf51cd3d4c8992adce45145c1bd8/rtm/users/userA/peer_messages?wait_for_ack=true ");
            // Set the Method property of the request to POST.
            request.Method = "POST";

            // Create POST data and convert it to a byte array.
            string postData = "{\r\n    \"destination\": \"userB\",\r\n    \"enable_offline_messaging\": false,\r\n    \"enable_historical_messaging\": false,\r\n    \"payload\": \"Hello\"\r\n}";
            byte[] byteArray = Encoding.UTF8.GetBytes(postData);

            // Set the ContentType property of the WebRequest.
            request.Headers.Add("Authorization: Basic YmQyMzNkYWNjODE4NDg2MDk1NWQzNjk4N2M5ZGJkOGQ6ODBiYTRkNTM3Nzk0NDg2ZDgxNGUwZDExN2Y2NzBmMmQ=");
            request.ContentType = "text/plain";
  

            // Get the request stream.
            Stream dataStream = request.GetRequestStream();
            // Write the data to the request stream.
            dataStream.Write(byteArray, 0, byteArray.Length);
            // Close the Stream object.
            dataStream.Close();

            // Get the response.
            WebResponse response = request.GetResponse();
            // Display the status.
            Console.WriteLine(((HttpWebResponse)response).StatusDescription);

            // Get the stream containing content returned by the server.
            // The using block ensures the stream is automatically closed.
            using (dataStream = response.GetResponseStream())
            {
                // Open the stream using a StreamReader for easy access.
                StreamReader reader = new StreamReader(dataStream);
                // Read the content.
                string responseFromServer = reader.ReadToEnd();
                // Display the content.
                Console.WriteLine(responseFromServer);
            }

            // Close the response.
            response.Close();
        }
    }
}

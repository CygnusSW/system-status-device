#include <stdio.h>
#include <curl/curl.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;
  
    /* Modify a header curl otherwise adds differently */ 
    chunk = curl_slist_append(chunk, "Host: api.github.com");
    chunk = curl_slist_append(chunk, "User-Agent: libcurl/1.0");
  
    /* set our custom set of headers */ 
    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
 
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/CygnusSW/style-guide/statuses/master");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    /* free the custom headers */ 
    curl_slist_free_all(chunk);
  }
  return 0;
}
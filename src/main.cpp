#include <iostream>
#include <curl/curl.h>
#include <rapidjson/document.h>

class CurrencyConverter {
    public:
    CurrencyConverter() {

    }
    ~CurrencyConverter() {
        // delete _curl;
    }

    void run() {
        _fetchAPI("USD");
    }


    private:
    void _fetchAPI(const std::string& from) {
        std::string url = "https://api.exchangerate-api.com/v4/latest/" + from;
        _curl = curl_easy_init();
        if(_curl) {
            curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, _writeCallback);
            curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_response);
            _res = curl_easy_perform(_curl);
            curl_easy_cleanup(_curl);

            if (_res == CURLE_OK) {
                std::cout << _response << std::endl;
            }
            else {
                printf("Failed to fetch the URL\n");
                exit(-1);
            }

        }
        else {
            printf("Failed to initialize the cURL\n");
            exit(-1);
        }
    }

    static size_t _writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    CURL* _curl;
    CURLcode _res;
    std::string _response;


};

int main(int argc, char const *argv[])
{
    printf("Welcome to Currency Converter\n");
    CurrencyConverter Obj;
    Obj.run();
    return 0;
}

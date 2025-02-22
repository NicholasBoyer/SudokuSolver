// Standard library headers
#include <array>
#include <iostream>

// Installed library headers
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Custom library headers
#include "../include/SudokuSolver.hpp"

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getSudokuJSON(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string responseString;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return "";
    }

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);      
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // Set timeout for 10 seconds
        curl_easy_setopt(curl, CURLOPT_CAINFO, "../cacert.pem");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); 

        res = curl_easy_perform(curl); 
        if (res != CURLE_OK) {
            std::cerr << "libcurl error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);  
    }

    return responseString;
}

std::array<std::array<int, 9>, 9> jsonToArray(std::string jsonString) {
    nlohmann::json jsonData = nlohmann::json::parse(jsonString);
    std::array<std::array<int, 9>, 9> array;
    
    auto valueArray = jsonData["newboard"]["grids"][0]["value"];

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            array[row][col] = valueArray[row][col].get<int>();
        }
    }

    return array;
}

int main() {

    std::string url = "https://sudoku-api.vercel.app/api/dosuku";
    std::string apiResponse = getSudokuJSON(url);
    std::array<std::array<int, 9>, 9> board;

    try {
        board = jsonToArray(apiResponse);

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Using default board" << std::endl;
        board = {{
            {{5, 3, 0, 0, 7, 0, 0, 0, 0}},
            {{6, 0, 0, 1, 9, 5, 0, 0, 0}},
            {{0, 9, 8, 0, 0, 0, 0, 6, 0}},
            {{8, 0, 0, 0, 6, 0, 0, 0, 3}},
            {{4, 0, 0, 8, 0, 3, 0, 0, 1}},
            {{7, 0, 0, 0, 2, 0, 0, 0, 6}},
            {{0, 6, 0, 0, 0, 0, 2, 8, 0}},
            {{0, 0, 0, 4, 1, 9, 0, 0, 5}},
            {{0, 0, 0, 0, 8, 0, 0, 7, 9}}
         }};
    }

    SudokuSolver solver;
    std::cout << "Initial board:\n";
    solver.printBoard(board);

    if (solver.solve(board)) {
        std::cout << "\nSolution:\n";
        solver.printBoard(board);
    } else {
        std::cout << "\nNo solution.\n";
    }

    return 0;

}
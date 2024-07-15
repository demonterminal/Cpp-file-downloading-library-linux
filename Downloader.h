#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

class Downloader {
public:
    bool downloadFile(const std::string& url, const std::string& outputPath);

private:
    std::string getHost(const std::string& url);
    std::string getPath(const std::string& url);
    bool createSocket(const std::string& host);
    bool sendRequest(const std::string& host, const std::string& path);
    bool receiveResponse(const std::string& outputPath);

    int sockfd;
};

bool Downloader::downloadFile(const std::string& url, const std::string& outputPath) {
    std::string host = getHost(url);
    std::string path = getPath(url);

    if (!createSocket(host)) {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    if (!sendRequest(host, path)) {
        std::cerr << "Failed to send request\n";
        return false;
    }

    if (!receiveResponse(outputPath)) {
        std::cerr << "Failed to receive response\n";
        return false;
    }

    close(sockfd);
    return true;
}

std::string Downloader::getHost(const std::string& url) {
    size_t start = url.find("//") + 2;
    size_t end = url.find('/', start);
    return url.substr(start, end - start);
}

std::string Downloader::getPath(const std::string& url) {
    size_t start = url.find("//") + 2;
    start = url.find('/', start);
    return url.substr(start);
}

bool Downloader::createSocket(const std::string& host) {
    struct hostent* server = gethostbyname(host.c_str());
    if (!server) {
        std::cerr << "No such host: " << host << "\n";
        return false;
    }

    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket\n";
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error connecting to host\n";
        return false;
    }

    return true;
}

bool Downloader::sendRequest(const std::string& host, const std::string& path) {
    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n\r\n";

    if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
        std::cerr << "Error sending request\n";
        return false;
    }

    return true;
}

bool Downloader::receiveResponse(const std::string& outputPath) {
    char buffer[4096];
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file\n";
        return false;
    }

    ssize_t bytesReceived;
    bool headerEnded = false;
    while ((bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        if (!headerEnded) {
            std::string header(buffer, bytesReceived);
            size_t pos = header.find("\r\n\r\n");
            if (pos != std::string::npos) {
                headerEnded = true;
                outFile.write(buffer + pos + 4, bytesReceived - pos - 4);
            }
        } else {
            outFile.write(buffer, bytesReceived);
        }
    }

    if (bytesReceived < 0) {
        std::cerr << "Error receiving data\n";
        return false;
    }

    outFile.close();
    return true;
}

#endif // DOWNLOADER_H
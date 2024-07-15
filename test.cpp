#include "Downloader.h"

int main() {
    Downloader downloader;
    std::string url = "https://example.com/file.zip";
    std::string outputPath = "file.zip";

    if (downloader.downloadFile(url, outputPath)) {
        std::cout << "Download successful!" << std::endl;
    } else {
        std::cout << "Download failed!" << std::endl;
    }

    return 0;
}
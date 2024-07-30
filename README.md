# Cpp-file-downloading-library-linux
This is an C++ File Downloading Library which is only for linux which provides a Easy C++ interface for downloading the files from internet via a Linux distributions. With this library you can easily download files directly from internet without writting complex programs. thus library can be easily installed in the local directory or compiler std directory for CPP compilation.

## Here's the tutorial
## Step 1 : Download the library and install it in the local directory where your C++ file is
## Step 2 : Include the library in your C++ file.
## Step 3 : Downloader provide a Downloader class which you need to inherit for downlaoding a file eg <code>Downloader downloader</code>
## Step 4 : Call the inheritance of the Downloader class snd use the downloadFile(url, output_path); for downloading a file and saving it to the local path

# Example
```cpp
// including header files
#include <iostream>
#include "Downloader.h"

// main
int main(){
   // Downloader class inheritance
   Downloader downloader;
   downloader.downloadFile("https://github.com/demonterminal/Demon-Liner-Sight---Source-code/archive/refs/heads/main.zip", "demonterminal.zip");// Downloading the demon terminal from the official github repo, Please replace the url and path to make it properly
   return 0;
}
```

# Explanation 

- We started code by including cpp iostrean which is the standard headerfile of cpp and <code>Downloader.h</code> which is this headerfile for downloading files from internet.
- Declaration of main function which is used for console IO or console projects.
- Instantiating the <code>Download</code> class provided by the <code>Downloader.h</code> for downloading files
- Calling <code>downloadFile</code> function of <code>Downloader</code> class for downloading file which takes the url and then downloades the file from url.

Thanks for reading

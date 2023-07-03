#include <iostream>
#include <cstdlib>
#include <cstdio>

int main() {
    std::string executablePath = "main.exe";  // Replace with the actual path to your C++ executable

    // Open a pipe to the executable
    FILE* pipe = _popen(executablePath.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error opening pipe to executable." << std::endl;
        return 1;
    }

    // Read and display the output from the executable
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        std::cout << buffer;
    }

    // Close the pipe and get the return status of the executable
    int returnCode = _pclose(pipe);
    if (returnCode != 0) {
        std::cerr << "Error executing the executable." << std::endl;
        return 1;
    }

    return 0;
}

#include <Windows.h>
#include <iostream>
#include <string>

int main() {
    // Create a pipe for communication between parent and child processes
    HANDLE pipeRead, pipeWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    if (!CreatePipe(&pipeRead, &pipeWrite, &sa, 0)) {
        std::cerr << "Error creating pipe." << std::endl;
        return 1;
    }

    // Create child process
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    si.hStdOutput = pipeWrite; // Redirect child process's standard output to the pipe
    si.dwFlags |= STARTF_USESTDHANDLES; // Set STARTF_USESTDHANDLES flag to use the redirected handles

    if (!CreateProcess(
            "main.exe",  // Replace with the actual path to your executable
            NULL,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        std::cerr << "Error creating child process." << std::endl;
        return 1;
    }

    // Close the write end of the pipe in the parent process
    CloseHandle(pipeWrite);

    // Read the output from the child process
    const int bufferSize = 4096;
    char buffer[bufferSize];
    DWORD bytesRead;
    std::string output;
    while (ReadFile(pipeRead, buffer, bufferSize, &bytesRead, NULL) && bytesRead != 0) {
        output.append(buffer, bytesRead);
    }

    // Close the read end of the pipe
    CloseHandle(pipeRead);

    // Wait for the child process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Print the output
    std::cout << "Output from child process:\n" << output << std::endl;

    return 0;
}

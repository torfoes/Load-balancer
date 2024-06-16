#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256) + "." +
           std::to_string(rand() % 256);
}

int genRequestTimeInRange(int minTime, int maxTime) {
    return minTime + rand() % (maxTime - minTime + 1);
}

std::string sameIpAddress = "192.168.0.1"; 

int main() {
    int numServers, runTime, minRequestTime, maxRequestTime, runCycles;
    char runMode;

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;

    std::cout << "Select run mode: (t)ime or (c)ycles: ";
    std::cin >> runMode;

    if (runMode == 't') {
        std::cout << "Enter run time (seconds): ";
        std::cin >> runTime;
    } else if (runMode == 'c') {
        std::cout << "Enter number of clock cycles: ";
        std::cin >> runCycles;
    } else {
        std::cerr << "Invalid run mode selected. Exiting." << std::endl;
        return 1;
    }

    std::cout << "Enter minimum request time (milliseconds): ";
    std::cin >> minRequestTime;

    std::cout << "Enter maximum request time (milliseconds): ";
    std::cin >> maxRequestTime;

    // Create the specified number of web servers
    std::vector<WebServer> servers;
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(WebServer());
    }

    // Create a LoadBalancer with the servers
    LoadBalancer loadBalancer(servers);

    // Initialize random seed
    std::srand(std::time(0));

    // Create an initial full queue (servers * 100 requests)
    for (int i = 0; i < numServers * 100; ++i) {
        loadBalancer.addRequest(Request(generateRandomIP(), sameIpAddress, genRequestTimeInRange(minRequestTime, maxRequestTime)));
    }


    int previousQueueSize = loadBalancer.getRequestQueueSize();

    // Number of cycles to check the queue size will be used to allocate more servers if the queue size is increasing
    const int checkCycleThreshold = 100; 

    int cycleCount = 0;
    int iterationCount = 0;

    if (runMode == 't') {
        auto startTime = std::chrono::steady_clock::now();

        while (true) {
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

            if (elapsedTime >= runTime) {
                break;
            }

            // Balance the load
            loadBalancer.balanceLoad();

            // Randomly add new requests
            if (std::rand() % 10 < 3) {
                int requestTime = genRequestTimeInRange(minRequestTime, maxRequestTime);
                loadBalancer.addRequest(Request(sameIpAddress, generateRandomIP(), requestTime));
            }

            // Increment cycle count
            cycleCount++;

            // Check if it's time to add a new server
            if (cycleCount >= checkCycleThreshold) {
                cycleCount = 0; // Reset the cycle count

                int currentQueueSize = loadBalancer.getRequestQueueSize();

                // Add a new server if the queue size is increasing
                if (currentQueueSize > previousQueueSize) {
                    loadBalancer.addServer(WebServer());
                    std::cout << "Added a new server. Total servers: " << servers.size() + 1 << std::endl;
                }
                previousQueueSize = currentQueueSize;
            }

        }
    } else if (runMode == 'c') {
        while (cycleCount < runCycles) {
            // Balance the load
            loadBalancer.balanceLoad();

            // Randomly add new requests
            if (std::rand() % 10 < 3) {
                int requestTime = genRequestTimeInRange(minRequestTime, maxRequestTime);
                loadBalancer.addRequest(Request(sameIpAddress, generateRandomIP(), requestTime));
            }

            // Simulate time passing
            // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust as needed

            // Increment cycle count
            cycleCount++;
            iterationCount++;

            // Check if it's time to add a new server
            if (iterationCount >= checkCycleThreshold) {
                iterationCount = 0; // Reset the iteration count

                int currentQueueSize = loadBalancer.getRequestQueueSize();
                if (currentQueueSize > previousQueueSize) {
                    // Add a new server if the queue size is increasing
                    loadBalancer.addServer(WebServer());
                    std::cout << "Added a new server. Total servers: " << servers.size() + 1 << std::endl;
                }
                previousQueueSize = currentQueueSize; // Update the previous queue size
            }
            std::cout << cycleCount << std::endl;

        }
    }

    std::cout << "Simulation completed." << std::endl;
    return 0;
}

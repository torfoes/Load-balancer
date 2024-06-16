#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <numeric>
#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"

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
    int numServers, runTime, minRequestTime, maxRequestTime, runCycles, newRequestsPerSecond;
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

    std::cout << "Enter number of new requests per second: ";
    std::cin >> newRequestsPerSecond;

    // Create the specified number of web servers with IDs
    std::vector<WebServer> servers;
    for (int i = 0; i < numServers; ++i) {
        servers.push_back(WebServer(i));
    }

    // Create a LoadBalancer with the servers
    LoadBalancer loadBalancer(servers);

    std::srand(std::time(0));

    // Create an initial full queue (servers * 100 requests)
    for (int i = 0; i < numServers * 100; ++i) {
        loadBalancer.addRequest(Request(generateRandomIP(), sameIpAddress, genRequestTimeInRange(minRequestTime, maxRequestTime)));
    }

    int previousQueueSize = loadBalancer.getRequestQueueSize();


    const int balanceBuffer = 10;

    // Number of cycles to check the queue size will be used to allocate more servers if the queue size is increasing
    const int checkCycleThreshold = 100;

    int cycleCount = 0;
    std::vector<double> cycleTimes;
    auto requestInterval = std::chrono::milliseconds(1000 / newRequestsPerSecond);
    auto lastRequestTime = std::chrono::steady_clock::now();

    if (runMode == 't') {
        auto startTime = std::chrono::steady_clock::now();

        while (true) {
            auto cycleStartTime = std::chrono::steady_clock::now();
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

            if (elapsedTime >= runTime) {
                break;
            }

            // Balance the load
            loadBalancer.balanceLoad();

            // Add new requests based on the provided rate
            while (std::chrono::steady_clock::now() - lastRequestTime >= requestInterval) {
                int requestTime = genRequestTimeInRange(minRequestTime, maxRequestTime);
                loadBalancer.addRequest(Request(generateRandomIP(), sameIpAddress, requestTime));
                lastRequestTime += requestInterval;
            }

            // Increment cycle count
            cycleCount++;

            // Adjust servers
            if (cycleCount >= checkCycleThreshold) {
                cycleCount = 0; 

                int currentQueueSize = loadBalancer.getRequestQueueSize();

                // Add a new server if the queue size is significantly increasing
                if (currentQueueSize > previousQueueSize + balanceBuffer) {
                    WebServer newServer(servers.size());
                    loadBalancer.addServer(newServer);
                    std::cout << "Added a new server. Total servers: " << servers.size() << std::endl;
                }
                // Remove a server if the queue size is significantly decreasing and we have more servers than initially allocated
                else if (currentQueueSize < previousQueueSize - balanceBuffer && servers.size() > 1) {
                    loadBalancer.removeServer();
                    std::cout << "Removed a server. Total servers: " << servers.size() << std::endl;
                }
                previousQueueSize = currentQueueSize;
            }

            auto cycleEndTime = std::chrono::steady_clock::now();
            auto cycleTime = std::chrono::duration_cast<std::chrono::milliseconds>(cycleEndTime - cycleStartTime).count();
            cycleTimes.push_back(cycleTime);
        }
    } else if (runMode == 'c') {
        while (cycleCount < runCycles) {
            auto cycleStartTime = std::chrono::steady_clock::now();

            // Balance the load
            loadBalancer.balanceLoad();

            // Add new requests based on the provided rate
            while (std::chrono::steady_clock::now() - lastRequestTime >= requestInterval) {
                int requestTime = genRequestTimeInRange(minRequestTime, maxRequestTime);
                loadBalancer.addRequest(Request(generateRandomIP(), sameIpAddress, requestTime));
                lastRequestTime += requestInterval;
            }

            // Increment cycle count
            cycleCount++;

            if (cycleCount >= checkCycleThreshold) {
                cycleCount = 0;

                int currentQueueSize = loadBalancer.getRequestQueueSize();
                if (currentQueueSize > previousQueueSize + balanceBuffer) {
                    WebServer newServer(servers.size());
                    loadBalancer.addServer(newServer);
                    std::cout << "Added a new server. Total servers: " << servers.size() << std::endl;
                }

                else if (currentQueueSize < previousQueueSize - balanceBuffer && servers.size() > 1) {
                    loadBalancer.removeServer();
                    std::cout << "Removed a server. Total servers: " << servers.size() << std::endl;
                }
                previousQueueSize = currentQueueSize;
            }

            auto cycleEndTime = std::chrono::steady_clock::now();
            auto cycleTime = std::chrono::duration_cast<std::chrono::milliseconds>(cycleEndTime - cycleStartTime).count();
            cycleTimes.push_back(cycleTime);
        }
    }

    // average cycle time
    double averageCycleTime = std::accumulate(cycleTimes.begin(), cycleTimes.end(), 0.0) / cycleTimes.size();

    std::cout << "Simulation completed." << std::endl;
    std::cout << "Final number of servers: " << servers.size() << std::endl;
    std::cout << "Remaining requests in the queue: " << loadBalancer.getRequestQueueSize() << std::endl;
    std::cout << "Average cycle time: " << averageCycleTime << " milliseconds" << std::endl;

    return 0;
}

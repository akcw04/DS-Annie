#include "CustomLists.hpp"
#include <iomanip>


int findMostNeededSite(const CustomLinkedList<ReliefSite>& sites) {
    int bestSiteIndex = -1;
    double lowestPercentage = 1.1; // Start above 100%
    
    std::cout << "\n=== SITE PRIORITY ANALYSIS ===\n";
    std::cout << std::left << std::setw(20) << "Site Name" 
              << std::setw(15) << "Current/Max"
              << std::setw(12) << "% Filled"
              << std::setw(10) << "Priority" << "\n";
    std::cout << std::string(57, '-') << "\n";
    
    int index = 0;
    for (auto it = sites.begin(); it != sites.end(); ++it, ++index) {
        if (it->currentCount < it->maxCapacity) {
            double percentage = (double)it->currentCount / it->maxCapacity;
            std::string priority = (percentage < lowestPercentage) ? "HIGHEST" : "Lower";
            
            std::cout << std::left << std::setw(20) << it->name
                      << std::setw(15) << (std::to_string(it->currentCount) + "/" + std::to_string(it->maxCapacity))
                      << std::setw(12) << (std::to_string((int)(percentage * 100)) + "%")
                      << std::setw(10) << priority << "\n";
            
            if (percentage < lowestPercentage) {
                lowestPercentage = percentage;
                bestSiteIndex = index;
            }
        } else {
            std::cout << std::left << std::setw(20) << it->name
                      << std::setw(15) << (std::to_string(it->currentCount) + "/" + std::to_string(it->maxCapacity))
                      << std::setw(12) << "100%"
                      << std::setw(10) << "FULL" << "\n";
        }
    }
    std::cout << std::string(57, '-') << "\n\n";
    
    return bestSiteIndex;
}
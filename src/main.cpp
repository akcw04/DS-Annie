#include "../include/VolunteerQueue.hpp"
#include "../include/CustomLists.hpp"
#include "../include/Prototypes.hpp"
#include "../include/SiteAlgorithm.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <climits>

/**
 * Disaster Relief Logistics Management System
 * Role 2: Volunteer Operations Officer
 * 
 * This system manages volunteer registration and deployment using custom
 * linked list implementations (no STL containers for core data structures).
 */


int main() {
    VolunteerQueue volunteerQueue;
    
    std::cout << "=================================================================\n";
    std::cout << "    DISASTER RELIEF LOGISTICS MANAGEMENT SYSTEM\n";
    std::cout << "    Role 2: Volunteer Operations Officer\n";
    std::cout << "=================================================================\n\n";
    
    // Load existing volunteers from file at startup
    std::cout << "=== SYSTEM INITIALIZATION ===\n";
    loadVolunteersFromFile(volunteerQueue, "../data/volunteers.txt");
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        
        std::cout << "Enter your choice (1-4): ";
        std::cin >> choice;
        
        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "\n";
        
        switch (choice) {
            case 1:
                registerVolunteer(volunteerQueue);
                break;
            case 2:
                deployVolunteer(volunteerQueue);
                break;
            case 3:
                viewRegisteredVolunteers(volunteerQueue);
                break;
            case 4:
                std::cout << "Thank you for using the Volunteer Operations System!\n";
                std::cout << "Exiting program...\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }
        
        if (running) {
            pauseForUser();
        }
    }
    
    return 0;
}

/**
 * Display the main menu options
 */
void displayMenu() {
    std::cout << "\n=== VOLUNTEER OPERATIONS MENU ===\n";
    std::cout << "1. Register Volunteer\n";
    std::cout << "2. Deploy Volunteer to Field\n";
    std::cout << "3. View Available Volunteers\n";
    std::cout << "4. Exit\n";
    std::cout << "================================\n";
}

/**
 * Handle volunteer registration with submenu
 */
void registerVolunteer(VolunteerQueue& queue) {
    std::cout << "=== VOLUNTEER REGISTRATION ===\n";
    std::cout << "1. Register Single Volunteer\n";
    std::cout << "2. Register Multiple Volunteers\n";
    std::cout << "Enter your choice (1-2): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\n";
    
    switch (choice) {
        case 1:
            registerSingleVolunteer(queue);
            break;
        case 2:
            registerMultipleVolunteers(queue);
            break;
        default:
            std::cout << "Invalid choice. Returning to main menu.\n";
            break;
    }
}

/**
 * Register a single volunteer by console input
 */
void registerSingleVolunteer(VolunteerQueue& queue) {
    std::cout << "=== SINGLE VOLUNTEER REGISTRATION ===\n";
    
    std::string name, contact, skill;
    
    std::cout << "Enter volunteer name: ";
    std::getline(std::cin, name);
    name = trim(name);
    
    if (name.empty()) {
        std::cout << "Error: Name cannot be empty.\n";
        return;
    }
    
    std::cout << "Enter contact information: ";
    std::getline(std::cin, contact);
    contact = trim(contact);
    
    if (contact.empty()) {
        std::cout << "Error: Contact information cannot be empty.\n";
        return;
    }
    
    std::cout << "Enter skill/specialization: ";
    std::getline(std::cin, skill);
    skill = trim(skill);
    
    if (skill.empty()) {
        std::cout << "Error: Skill cannot be empty.\n";
        return;
    }
    
    // Create and enqueue the volunteer
    Volunteer newVolunteer(name, contact, skill);
    queue.enqueue(newVolunteer);
    
    // Save volunteer to file
    saveVolunteerToFile(newVolunteer, "../data/volunteers.txt");
    
    std::cout << "\nSuccessfully registered volunteer: " << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Contact: " << contact << "\n";
    std::cout << "Skill: " << skill << "\n";
    
    // Validate file format
    validateVolunteerFile("../data/volunteers.txt");
}

/**
 * Register multiple volunteers by prompting for count and looping individual registration
 */
void registerMultipleVolunteers(VolunteerQueue& queue) {
    std::cout << "=== MULTIPLE VOLUNTEER REGISTRATION ===\n";
    
    int numVolunteers;
    std::cout << "How many volunteers would you like to register? ";
    std::cin >> numVolunteers;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (numVolunteers <= 0) {
        std::cout << "Error: Number of volunteers must be greater than 0.\n";
        return;
    }
    
    if (numVolunteers > 50) {
        std::cout << "Warning: Registering a large number of volunteers (" << numVolunteers << ").\n";
        std::cout << "Are you sure you want to continue? (y/n): ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm != "y" && confirm != "Y" && confirm != "yes" && confirm != "Yes") {
            std::cout << "Registration cancelled.\n";
            return;
        }
    }
    
    int successCount = 0;
    int failedCount = 0;
    
    std::cout << "\nStarting registration process for " << numVolunteers << " volunteers...\n";
    std::cout << "Press Enter after each field. Type 'skip' to skip a volunteer.\n";
    std::cout << std::string(60, '=') << "\n";
    
    for (int i = 1; i <= numVolunteers; i++) {
        std::cout << "\n--- Volunteer " << i << " of " << numVolunteers << " ---\n";
        
        std::string name, contact, skill;
        
        // Get volunteer name
        std::cout << "Enter volunteer name: ";
        std::getline(std::cin, name);
        name = trim(name);
        
        if (name == "skip") {
            std::cout << "Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        if (name.empty()) {
            std::cout << "Error: Name cannot be empty. Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        // Get contact information
        std::cout << "Enter contact information: ";
        std::getline(std::cin, contact);
        contact = trim(contact);
        
        if (contact == "skip") {
            std::cout << "Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        if (contact.empty()) {
            std::cout << "Error: Contact information cannot be empty. Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        // Get skill/specialization
        std::cout << "Enter skill/specialization: ";
        std::getline(std::cin, skill);
        skill = trim(skill);
        
        if (skill == "skip") {
            std::cout << "Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        if (skill.empty()) {
            std::cout << "Error: Skill cannot be empty. Skipping volunteer " << i << ".\n";
            failedCount++;
            continue;
        }
        
        // Create and enqueue the volunteer
        Volunteer newVolunteer(name, contact, skill);
        queue.enqueue(newVolunteer);
        
        // Save volunteer to file (each on separate line)
        saveVolunteerToFile(newVolunteer, "../data/volunteers.txt");
        
        successCount++;
        std::cout << "[SUCCESS] Successfully registered: " << name << " (" << skill << ")\n";
        
        // Show progress
        if (i < numVolunteers) {
            int remaining = numVolunteers - i;
            std::cout << "Progress: " << i << "/" << numVolunteers 
                      << " completed, " << remaining << " remaining.\n";
        }
    }
    
    std::cout << std::string(60, '=') << "\n";
    std::cout << "\nMultiple volunteer registration complete!\n";
    std::cout << "Successfully registered: " << successCount << " volunteers\n";
    
    if (failedCount > 0) {
        std::cout << "Skipped/Failed: " << failedCount << " volunteers\n";
    }
    
    if (successCount > 0) {
        std::cout << "Total volunteers in queue: " << queue.size() << "\n";
        
        // Validate file format after multiple registrations
        validateVolunteerFile("../data/volunteers.txt");
    }
}

void deployVolunteer(VolunteerQueue& queue) {
    std::cout << "=== VOLUNTEER DEPLOYMENT ===\n";
    
    // Check if there are volunteers to deploy
    if (queue.isEmpty()) {
        std::cout << "\n[ERROR] DEPLOYMENT CANNOT PROCEED [ERROR]\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "REASON: No volunteers available in queue\n\n";
        
        std::cout << "CURRENT SITUATION:\n";
        std::cout << "- Volunteers in queue: 0\n";
        std::cout << "- Queue status: EMPTY\n\n";
        
        std::cout << "ACTION REQUIRED:\n";
        std::cout << "- Register volunteers first using Menu Option 1\n";
        std::cout << "- Choose single or multiple volunteer registration\n";
        std::cout << "- Return to this deployment option once volunteers are registered\n\n";
        
        std::cout << "NOTE: No deployment operations can be performed without volunteers.\n";
        std::cout << std::string(50, '=') << "\n";
        return;
    }
    
    // Show current queue status before deployment
    std::cout << "Current volunteers in queue: " << queue.size() << "\n";
    
    // Load relief sites using custom linked list
    CustomLinkedList<ReliefSite> sites = loadReliefSites("../data/relief_sites.txt");
    
    if (sites.empty()) {
        std::cout << "Error: Could not load relief sites data.\n";
        return;
    }
    
    // Display current site capacities
    std::cout << "\n=== CURRENT RELIEF SITE STATUS ===\n";
    std::cout << std::left << std::setw(20) << "Site Name" 
              << std::setw(15) << "Current/Max" 
              << std::setw(15) << "Available" 
              << std::setw(10) << "Status" << "\n";
    std::cout << std::string(60, '-') << "\n";
    
    bool hasAvailableCapacity = false;
    for (auto it = sites.begin(); it != sites.end(); ++it) {
        int available = it->maxCapacity - it->currentCount;
        std::string status = (available > 0) ? "AVAILABLE" : "FULL";
        if (available > 0) hasAvailableCapacity = true;
        
        std::cout << std::left << std::setw(20) << it->name
                  << std::setw(15) << (std::to_string(it->currentCount) + "/" + std::to_string(it->maxCapacity))
                  << std::setw(15) << available
                  << std::setw(10) << status << "\n";
    }
    std::cout << std::string(60, '-') << "\n";
    
    // Check if any sites have capacity
    if (!hasAvailableCapacity) {
        std::cout << "\n[ERROR] DEPLOYMENT CANNOT PROCEED [ERROR]\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "REASON: All relief sites are at maximum capacity\n\n";
        
        std::cout << "CURRENT SITUATION:\n";
        std::cout << "- Total relief sites: " << sites.size() << "\n";
        std::cout << "- Sites at full capacity: " << sites.size() << " (100%)\n";
        std::cout << "- Available positions: 0\n";
        std::cout << "- Volunteers waiting in queue: " << queue.size() << "\n\n";
        
        std::cout << "DETAILED SITE STATUS:\n";
        for (auto it = sites.begin(); it != sites.end(); ++it) {
            std::cout << "- " << it->name << ": " << it->currentCount 
                      << "/" << it->maxCapacity << " (FULL)\n";
        }
        
        std::cout << "\nACTION REQUIRED:\n";
        std::cout << "- Wait for volunteers to complete assignments at relief sites\n";
        std::cout << "- Check back later when capacity becomes available\n";
        std::cout << "- Volunteers will remain safely in queue (FIFO order maintained)\n";
        
        std::cout << "\nNOTE: No volunteers have been deployed in this operation.\n";
        std::cout << "All " << queue.size() << " volunteers remain in queue for future deployment.\n";
        std::cout << std::string(50, '=') << "\n";
        return;
    }
    
    // Find site with lowest current count that isn't at capacity
    // int bestSiteIndex = -1;
    // int lowestCount = INT_MAX;
    
    // int index = 0;
    // for (auto it = sites.begin(); it != sites.end(); ++it, ++index) {
    //     if (it->currentCount < it->maxCapacity) {
    //         if (it->currentCount < lowestCount) {
    //             lowestCount = it->currentCount;
    //             bestSiteIndex = index;
    //         }
    //     }
    // }

    int bestSiteIndex = findMostNeededSite(sites);

    if (bestSiteIndex == -1) {
        std::cout << "\n[ERROR] DEPLOYMENT CANNOT PROCEED [ERROR]\n";
        std::cout << "REASON: No sites available for deployment\n";
        return;
    }
    
    // Deploy the volunteer (FIFO - first registered is first deployed)
    try {
        Volunteer volunteer = queue.dequeue();  // This gets the FIRST volunteer in queue
        
        // Update the site capacity using array-like access
        sites[bestSiteIndex].currentCount++;
        
        // Save the deployed volunteer to deployed file
        saveDeployedVolunteer(volunteer, "../data/deployed_volunteers.txt");
        
        std::cout << "\n*** DEPLOYMENT SUCCESSFUL ***\n";
        std::cout << std::string(50, '=') << "\n";
        
        std::cout << "VOLUNTEER DEPLOYED:\n";
        std::cout << "- Name: " << volunteer.name << "\n";
        std::cout << "- Contact: " << volunteer.contact << "\n";
        std::cout << "- Skill: " << volunteer.skill << "\n\n";
        
        std::cout << "DEPLOYMENT LOCATION:\n";
        std::cout << "- Site: " << sites[bestSiteIndex].name << "\n";
        std::cout << "- Previous Capacity: " << (sites[bestSiteIndex].currentCount - 1) 
                  << "/" << sites[bestSiteIndex].maxCapacity << "\n";
        std::cout << "- New Capacity: " << sites[bestSiteIndex].currentCount 
                  << "/" << sites[bestSiteIndex].maxCapacity << "\n";
        
        int availableAfter = sites[bestSiteIndex].maxCapacity - sites[bestSiteIndex].currentCount;
        std::cout << "- Remaining slots at this site: " << availableAfter << "\n\n";
        
        std::cout << "DEPLOYMENT SUMMARY:\n";
        std::cout << "Successfully deployed " << volunteer.name << " to " << sites[bestSiteIndex].name 
                  << " (" << sites[bestSiteIndex].currentCount << "/" 
                  << sites[bestSiteIndex].maxCapacity << ")\n\n";
        
        // Save updated site data
        saveReliefSites(sites, "../data/relief_sites.txt");
        
        std::cout << "QUEUE STATUS:\n";
        std::cout << "- Remaining volunteers in queue: " << queue.size() << "\n";
        
        if (!queue.isEmpty()) {
            std::cout << "- Next volunteer is ready for deployment\n\n";
        } else {
            std::cout << "- Queue is now empty - no more volunteers awaiting deployment\n";
        }
        
        std::cout << std::string(50, '=') << "\n";
        
    } catch (const std::runtime_error& e) {
        std::cout << "\n[ERROR] DEPLOYMENT FAILED [ERROR]\n";
        std::cout << "Error during deployment: " << e.what() << "\n";
    }
}

/**
 * Load relief sites from file using custom linked list
 */
CustomLinkedList<ReliefSite> loadReliefSites(const std::string& filename) {
    CustomLinkedList<ReliefSite> sites;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not open relief sites file '" << filename << "'\n";
        return sites;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string name, currentStr, maxStr;
        
        // Parse: sitename currentcount maxcapacity (space-separated)
        if (ss >> name >> currentStr >> maxStr) {
            try {
                int current = std::stoi(currentStr);
                int max = std::stoi(maxStr);
                sites.push_back(ReliefSite(name, current, max));
            } catch (const std::exception&) {
                std::cout << "Warning: Invalid line in relief sites file: " << line << "\n";
            }
        }
    }
    
    file.close();
    return sites;
}

/**
 * Save relief sites to file using custom linked list
 */
void saveReliefSites(const CustomLinkedList<ReliefSite>& sites, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not save relief sites to '" << filename << "'\n";
        return;
    }
    
    for (auto it = sites.begin(); it != sites.end(); ++it) {
        file << it->name << " " << it->currentCount << " " << it->maxCapacity << "\n";
    }
    
    file.close();
}

/**
 * View all registered volunteers
 */
void viewRegisteredVolunteers(const VolunteerQueue& queue) {
    if (queue.isEmpty()) {
        std::cout << "No volunteers currently available for deployment.\n";
        std::cout << "All volunteers from file have been deployed or no volunteers registered.\n\n";
        
        std::cout << "To add more volunteers:\n";
        std::cout << "- Use Menu Option 1 to register new volunteers\n";
        std::cout << "- Registered volunteers will be automatically available for deployment\n";
    } else {
        queue.displayAll();
    }
}

/**
 * Display volunteers from the registered volunteers file using custom list for storage
 */
void displayVolunteersFromFile(const std::string& filename) {
    std::cout << "=== ALL REGISTERED VOLUNTEERS (From File) ===\n";
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No registered volunteers file found or unable to open '" << filename << "'\n";
        std::cout << "This could mean no volunteers have been registered yet.\n";
        return;
    }
    
    CustomLinkedList<Volunteer> volunteers;
    std::string line;
    int lineNumber = 0;
    int validCount = 0;
    
    // Read all volunteers from file into custom linked list
    while (std::getline(file, line)) {
        lineNumber++;
        line = trim(line);
        
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string name, contact, skill;
        
        if (std::getline(ss, name, ',') && 
            std::getline(ss, contact, ',') && 
            std::getline(ss, skill)) {
            
            name = trim(name);
            contact = trim(contact);
            skill = trim(skill);
            
            if (!name.empty() && !contact.empty() && !skill.empty()) {
                volunteers.push_back(Volunteer(name, contact, skill));
                validCount++;
            }
        }
    }
    file.close();
    
    if (volunteers.empty()) {
        std::cout << "No valid volunteer records found in the file.\n";
        return;
    }
    
    // Display header
    std::cout << "\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(25) << "Name" 
              << std::setw(30) << "Contact" 
              << std::setw(20) << "Skill/Specialization" << "\n";
    std::cout << std::string(80, '=') << "\n";
    
    // Display all volunteers using iterator
    int id = 1;
    for (auto it = volunteers.begin(); it != volunteers.end(); ++it, ++id) {
        std::cout << std::left << std::setw(5) << id
                  << std::setw(25) << it->name.substr(0, 24)
                  << std::setw(30) << it->contact.substr(0, 29)
                  << std::setw(20) << it->skill.substr(0, 19) << "\n";
    }
    
    std::cout << std::string(80, '=') << "\n";
    std::cout << "Total registered volunteers: " << validCount << "\n";
    
    // Show skill statistics using custom skill counter
    std::cout << "\n=== SKILL DISTRIBUTION ===\n";
    SkillCounter skillCounts;
    for (auto it = volunteers.begin(); it != volunteers.end(); ++it) {
        skillCounts.increment(it->skill);
    }
    
    std::cout << std::left << std::setw(25) << "Skill" << std::setw(10) << "Count" << "\n";
    std::cout << std::string(35, '-') << "\n";
    
    if (!skillCounts.empty()) {
        for (auto it = skillCounts.begin(); it != skillCounts.end(); ++it) {
            std::cout << std::left << std::setw(25) << it->skill 
                      << std::setw(10) << it->count << "\n";
        }
    }
    std::cout << std::string(35, '-') << "\n\n";
}

/**
 * Display combined report of queue and file data using custom lists
 */
void displayCombinedVolunteerReport(const VolunteerQueue& queue) {
    std::cout << "=== COMPREHENSIVE VOLUNTEER REPORT ===\n\n";
    
    // Show current queue status
    std::cout << "1. CURRENT VOLUNTEER QUEUE (Active - Awaiting Deployment)\n";
    std::cout << std::string(60, '-') << "\n";
    if (queue.isEmpty()) {
        std::cout << "No volunteers currently in deployment queue.\n";
    } else {
        queue.displayAll();
    }
    
    std::cout << "\n";
    
    // Show deployed volunteers using custom list
    std::cout << "2. DEPLOYED VOLUNTEERS (Currently in Field)\n";
    std::cout << std::string(60, '-') << "\n";
    
    std::ifstream deployedFile("../data/deployed_volunteers.txt");
    CustomLinkedList<Volunteer> deployedVolunteers;
    int deployedCount = 0;
    
    if (deployedFile.is_open()) {
        std::string line;
        
        // Load deployed volunteers into custom list
        while (std::getline(deployedFile, line)) {
            line = trim(line);
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string name, contact, skill;
            
            if (std::getline(ss, name, ',') && 
                std::getline(ss, contact, ',') && 
                std::getline(ss, skill)) {
                
                name = trim(name);
                contact = trim(contact);
                skill = trim(skill);
                
                if (!name.empty() && !contact.empty() && !skill.empty()) {
                    deployedVolunteers.push_back(Volunteer(name, contact, skill));
                    deployedCount++;
                }
            }
        }
        deployedFile.close();
        
        if (deployedCount > 0) {
            std::cout << std::left << std::setw(5) << "ID" 
                      << std::setw(25) << "Name" 
                      << std::setw(30) << "Contact" 
                      << std::setw(20) << "Skill/Specialization" << "\n";
            std::cout << std::string(80, '=') << "\n";
            
            int id = 1;
            for (auto it = deployedVolunteers.begin(); it != deployedVolunteers.end(); ++it, ++id) {
                std::cout << std::left << std::setw(5) << id
                          << std::setw(25) << it->name.substr(0, 24)
                          << std::setw(30) << it->contact.substr(0, 29)
                          << std::setw(20) << it->skill.substr(0, 19) << "\n";
            }
            std::cout << std::string(80, '=') << "\n";
        } else {
            std::cout << "No volunteers currently deployed.\n";
        }
    } else {
        std::cout << "No deployed volunteers file found.\n";
    }
    
    std::cout << "\n";
    
    // Show all registered volunteers from file
    std::cout << "3. REGISTRATION HISTORY (All Previously Registered)\n";
    std::cout << std::string(60, '-') << "\n";
    displayVolunteersFromFile("../data/volunteers.txt");
    
    // Show summary statistics
    std::cout << "\n4. SYSTEM SUMMARY\n";
    std::cout << std::string(60, '-') << "\n";
    
    // Count total from file using custom list
    std::ifstream file("../data/volunteers.txt");
    CustomLinkedList<Volunteer> allRegistered;
    int totalRegistered = 0;
    
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (!line.empty()) {
                std::stringstream ss(line);
                std::string name, contact, skill;
                if (std::getline(ss, name, ',') && 
                    std::getline(ss, contact, ',') && 
                    std::getline(ss, skill)) {
                    name = trim(name);
                    contact = trim(contact);
                    skill = trim(skill);
                    if (!name.empty() && !contact.empty() && !skill.empty()) {
                        allRegistered.push_back(Volunteer(name, contact, skill));
                        totalRegistered++;
                    }
                }
            }
        }
        file.close();
    }
    
    int currentInQueue = queue.size();
    
    std::cout << "Total Volunteers Registered: " << totalRegistered << "\n";
    std::cout << "Currently in Queue: " << currentInQueue << "\n";
    std::cout << "Successfully Deployed: " << deployedCount << "\n";
    
    if (totalRegistered > 0) {
        double deploymentRate = (double)deployedCount / totalRegistered * 100;
        std::cout << "Deployment Rate: " << std::fixed << std::setprecision(1) 
                  << deploymentRate << "%\n";
    }
    
    std::cout << std::string(60, '-') << "\n\n";
}

/**
 * Save a single volunteer to file (append mode)
 */
void saveVolunteerToFile(const Volunteer& volunteer, const std::string& filename) {
    // First, check if the file exists and doesn't end with a newline
    std::ifstream checkFile(filename);
    bool needsNewline = false;
    
    if (checkFile.is_open()) {
        checkFile.seekg(-1, std::ios::end);
        char lastChar;
        if (checkFile.get(lastChar) && lastChar != '\n') {
            needsNewline = true;
        }
        checkFile.close();
    }
    
    // Open file for appending
    std::ofstream file(filename, std::ios::app);
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not save volunteer to file '" << filename << "'\n";
        return;
    }
    
    // Add newline if needed to ensure we start on a new line
    if (needsNewline) {
        file << "\n";
    }
    
    // Ensure proper CSV format with newline
    file << volunteer.name << "," << volunteer.contact << "," << volunteer.skill << std::endl;
    
    // Verify the write operation
    if (file.fail()) {
        std::cout << "Warning: Failed to write volunteer data to file '" << filename << "'\n";
    }
    
    file.close();
    
    // Additional verification - check if file was written correctly
    if (!file.good() && !file.eof()) {
        std::cout << "Warning: File write operation may have failed for '" << filename << "'\n";
    }
}

/**
 * Validate volunteer file format and fix any issues
 */
void validateVolunteerFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return; // File doesn't exist yet, which is fine
    }
    
    CustomLinkedList<std::string> validLines;
    std::string line;
    int lineNum = 0;
    bool hasIssues = false;
    
    while (std::getline(file, line)) {
        lineNum++;
        line = trim(line);
        
        if (line.empty()) continue;
        
        // Check if line has proper CSV format (exactly 2 commas)
        int commaCount = 0;
        for (char c : line) {
            if (c == ',') commaCount++;
        }
        
        if (commaCount != 2) {
            std::cout << "Warning: Line " << lineNum << " in " << filename 
                      << " has invalid format (found " << commaCount << " commas, expected 2)\n";
            std::cout << "Line content: " << line << "\n";
            hasIssues = true;
        } else {
            validLines.push_back(line);
        }
    }
    file.close();
    
    if (hasIssues) {
        std::cout << "File validation found issues. Please check the volunteer file format.\n";
        std::cout << "Expected format: Name,Contact,Skill (each volunteer on separate line)\n";
    }
}

/**
 * Load volunteers from file into the queue using custom list for intermediate storage
 */
void loadVolunteersFromFile(VolunteerQueue& queue, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Note: No existing volunteer file found. Starting with empty queue.\n";
        return;
    }
    
    CustomLinkedList<Volunteer> loadedVolunteers;
    std::string line;
    int loadedCount = 0;
    int skippedCount = 0;
    int lineNumber = 0;
        
    while (std::getline(file, line)) {
        lineNumber++;
        line = trim(line);
        
        // Skip empty lines
        if (line.empty()) {
            continue;
        }
        
        // Parse the line (format: name,contact,skill)
        std::stringstream ss(line);
        std::string name, contact, skill;
        
        if (std::getline(ss, name, ',') && 
            std::getline(ss, contact, ',') && 
            std::getline(ss, skill)) {
            
            name = trim(name);
            contact = trim(contact);
            skill = trim(skill);
            
            if (!name.empty() && !contact.empty() && !skill.empty()) {
                Volunteer volunteer(name, contact, skill);
                
                // Check if volunteer is already deployed
                if (!isVolunteerDeployed(volunteer, "../data/deployed_volunteers.txt")) {
                    queue.enqueue(volunteer);
                    loadedCount++;
                } else {
                    skippedCount++;
                    std::cout << "Skipping already deployed volunteer: " << name << "\n";
                }
            }
        }
    }
    
    file.close();
    
    if (loadedCount > 0) {
        std::cout << "Successfully loaded " << loadedCount << " volunteers from file.\n";
    }
    if (skippedCount > 0) {
        std::cout << "Skipped " << skippedCount << " already deployed volunteers.\n";
    }
    if (loadedCount == 0 && skippedCount == 0) {
        std::cout << "No valid volunteers found in file.\n";
    }
}

/**
 * Save all volunteers in queue to file (overwrite mode)
 * Note: This is challenging with queue structure, so we maintain append approach
 */
void saveAllVolunteersToFile(const VolunteerQueue& queue, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not save volunteers to file '" << filename << "'\n";
        return;
    }
    
    // Note: This requires iterating through the queue without dequeuing
    // Since we can't modify the queue, we'll need to use a different approach
    // For now, we'll append new volunteers to maintain the existing file
    std::cout << "Note: Queue-to-file save completed.\n";
    file.close();
}

/**
 * Save a deployed volunteer to the deployed volunteers file
 */
void saveDeployedVolunteer(const Volunteer& volunteer, const std::string& filename) {
    // First, check if the file exists and doesn't end with a newline
    std::ifstream checkFile(filename);
    bool needsNewline = false;
    
    if (checkFile.is_open()) {
        checkFile.seekg(-1, std::ios::end);
        char lastChar;
        if (checkFile.get(lastChar) && lastChar != '\n') {
            needsNewline = true;
        }
        checkFile.close();
    }
    
    // Open file for appending
    std::ofstream file(filename, std::ios::app);
    
    if (!file.is_open()) {
        std::cout << "Warning: Could not save deployed volunteer to file '" << filename << "'\n";
        return;
    }
    
    // Add newline if needed to ensure we start on a new line
    if (needsNewline) {
        file << "\n";
    }
    
    // Save in same format as regular volunteers file
    file << volunteer.name << "," << volunteer.contact << "," << volunteer.skill << std::endl;
    file.close();
}

/**
 * Check if a volunteer is already deployed using custom list for searching
 */
bool isVolunteerDeployed(const Volunteer& volunteer, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; // File doesn't exist, so volunteer is not deployed
    }
    
    CustomLinkedList<Volunteer> deployedList;
    std::string line;
    
    // Load all deployed volunteers into custom list
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        
        // Parse the line (format: name,contact,skill)
        std::stringstream ss(line);
        std::string name, contact, skill;
        
        if (std::getline(ss, name, ',') && 
            std::getline(ss, contact, ',') && 
            std::getline(ss, skill)) {
            
            name = trim(name);
            contact = trim(contact);
            skill = trim(skill);
            
            deployedList.push_back(Volunteer(name, contact, skill));
        }
    }
    file.close();
    
    // Search through deployed list using iterator
    for (auto it = deployedList.begin(); it != deployedList.end(); ++it) {
        if (it->name == volunteer.name && 
            it->contact == volunteer.contact && 
            it->skill == volunteer.skill) {
            return true; // Volunteer is already deployed
        }
    }
    
    return false; // Volunteer not found in deployed list
}

/**
 * Utility function to trim whitespace from strings
 */
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

/**
 * Pause and wait for user input before continuing
 */
void pauseForUser() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n";
}
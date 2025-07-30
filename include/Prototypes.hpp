#include "../include/VolunteerQueue.hpp"
#include "../include/CustomLists.hpp"
#include <string>

// Function prototypes
void displayMenu();
void registerVolunteer(VolunteerQueue& queue);
void registerSingleVolunteer(VolunteerQueue& queue);
void registerMultipleVolunteers(VolunteerQueue& queue);
void deployVolunteer(VolunteerQueue& queue);
CustomLinkedList<ReliefSite> loadReliefSites(const std::string& filename);
void saveReliefSites(const CustomLinkedList<ReliefSite>& sites, const std::string& filename);

void viewRegisteredVolunteers(const VolunteerQueue& queue);
void displayVolunteersFromFile(const std::string& filename);
void displayCombinedVolunteerReport(const VolunteerQueue& queue);
void saveVolunteerToFile(const Volunteer& volunteer, const std::string& filename);
void saveAllVolunteersToFile(const VolunteerQueue& queue, const std::string& filename);
void loadVolunteersFromFile(VolunteerQueue& queue, const std::string& filename);
void validateVolunteerFile(const std::string& filename);
void saveDeployedVolunteer(const Volunteer& volunteer, const std::string& filename);
bool isVolunteerDeployed(const Volunteer& volunteer, const std::string& filename);
std::string trim(const std::string& str);
void pauseForUser();
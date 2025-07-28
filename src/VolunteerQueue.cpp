#include "../include/VolunteerQueue.hpp"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>

/**
 * Constructor - initializes empty queue
 */
VolunteerQueue::VolunteerQueue() : head(nullptr), tail(nullptr) {
}

/**
 * Destructor - cleans up all allocated memory
 */
VolunteerQueue::~VolunteerQueue() {
    // Dequeue all remaining volunteers to free memory
    while (!isEmpty()) {
        try {
            dequeue();
        } catch (const std::runtime_error&) {
            // Should not happen since we check isEmpty(), but just in case
            break;
        }
    }
}

/**
 * Adds a volunteer to the rear of the queue
 */
void VolunteerQueue::enqueue(const Volunteer& v) {
    Node* newNode = new Node(v);
    
    if (isEmpty()) {
        // First node in the queue
        head = tail = newNode;
    } else {
        // Add to the rear
        tail->next = newNode;
        tail = newNode;
    }
}

/**
 * Removes and returns the volunteer at the front of the queue
 */
Volunteer VolunteerQueue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    
    // Store the data to return
    Volunteer volunteer = head->data;
    
    // Update head pointer
    Node* nodeToDelete = head;
    head = head->next;
    
    // If queue becomes empty, update tail as well
    if (head == nullptr) {
        tail = nullptr;
    }
    
    // Free memory
    delete nodeToDelete;
    
    return volunteer;
}

/**
 * Checks if the queue is empty
 */
bool VolunteerQueue::isEmpty() const {
    return head == nullptr;
}

/**
 * Displays all volunteers in the queue from front to rear
 */
void VolunteerQueue::displayAll() const {
    if (isEmpty()) {
        std::cout << "No volunteers currently registered.\n";
        return;
    }
    
    std::cout << "\n=== REGISTERED VOLUNTEERS (FIFO Order) ===\n";
    std::cout << std::left << std::setw(5) << "Pos" 
              << std::setw(20) << "Name" 
              << std::setw(25) << "Contact" 
              << std::setw(20) << "Skill" << "\n";
    std::cout << std::string(70, '-') << "\n";
    
    Node* current = head;
    int position = 1;
    
    while (current != nullptr) {
        std::string posStr = std::to_string(position);
        
        std::cout << std::left << std::setw(5) << posStr
                  << std::setw(20) << current->data.name
                  << std::setw(25) << current->data.contact
                  << std::setw(20) << current->data.skill << "\n";
        current = current->next;
        position++;
    }
    
    std::cout << std::string(70, '-') << "\n";
    std::cout << "Total volunteers in queue: " << size() << "\n";
}

/**
 * Returns the number of volunteers in the queue
 */
int VolunteerQueue::size() const {
    int count = 0;
    Node* current = head;
    
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    
    return count;
}

# Disaster Relief Logistics Management System
## Role 2: Volunteer Operations Officer

This system manages volunteer registration and deployment for disaster relief operations using a custom singly-linked-list queue implementation.

## Features

### 1. **Volunteer Registration**
- **Single Registration**: Manually enter volunteer details (name, contact, skill)
- **Multiple Registration**: Register multiple volunteers by specifying count and looping individual registration
- **Data Validation**: Ensures all fields are properly filled

### 2. **Volunteer Deployment**
- **Smart Site Selection**: Automatically deploys to relief sites with lowest capacity
- **Capacity Management**: Tracks current volunteers vs. maximum capacity
- **Real-time Updates**: Updates site data after each deployment
- **Detailed Notifications**: Clear explanations when deployment cannot proceed
- **Status Reporting**: Comprehensive feedback on deployment success or failure

### 3. **Queue Management**
- **FIFO Processing**: First registered volunteer is first deployed
- **File Integration**: Automatically loads volunteers from file at startup
- **Available Volunteers**: Shows all volunteers ready for deployment
- **Dynamic Sizing**: Real-time queue size tracking

### 4. **File Integration**
- **Startup Loading**: Automatically loads volunteers from `data/volunteers.txt` at startup
- **Relief Sites**: Loads site data from `data/relief_sites.txt`
- **Volunteer Storage**: Automatically saves registered volunteers to `data/volunteers.txt`
- **Line Separation**: Ensures each volunteer is saved on a separate line
- **File Validation**: Checks and reports file format integrity
- **Persistent Storage**: Updates site capacity data automatically

## Technical Implementation

### Data Structures
- **Custom Queue**: Singly-linked-list implementation (no STL containers)
- **Volunteer Struct**: Stores name, contact, and skill information
- **Relief Site Tracking**: Manages site capacity and current assignments

### Core Classes
- `VolunteerQueue`: Custom FIFO queue with enqueue/dequeue operations
- `Volunteer`: Data structure for volunteer information
- `ReliefSite`: Tracks relief site capacity and assignments

## File Formats

### Volunteers File (`data/volunteers.txt`)
```
Name,Contact,Skill
Alice Smith,alice.smith@example.com,Medical
Bob Lee,555-1234,Logistics
```
*Note: This file is automatically created and maintained by the system during volunteer registration.*

### Relief Sites File (`data/relief_sites.txt`)
```
SiteName CurrentCount MaxCapacity
RiversideCamp 3 10
MountainOutpost 7 8
```

## Compilation & Usage

### Quick Compilation
```bash
g++ -std=c++11 -I include src/main.cpp src/VolunteerQueue.cpp -o volunteer_system
```

### Using Makefile
```bash
make quick          # Quick compilation
make run            # Compile and run
make clean          # Clean build files
```

### Running the Program
```bash
./volunteer_system.exe
```

## Menu Navigation

1. **Register Volunteer**
   - Option 1: Single volunteer registration
   - Option 2: Multiple volunteer registration (specify count)

2. **Deploy Volunteer to Field**
   - Automatically selects optimal relief site
   - Updates site capacity tracking
   - Displays deployment confirmation

3. **View Available Volunteers**
   - Shows all volunteers ready for deployment
   - Displays volunteers in FIFO order (next to deploy first)
   - Loads from both file and newly registered volunteers

4. **Exit**
   - Safely cleans up memory and exits

## Error Handling

- **File Access**: Graceful handling of missing or inaccessible files
- **Empty Queue**: Detailed notification when no volunteers are available for deployment
- **Site Capacity**: Comprehensive explanation when all relief sites are at maximum capacity
- **Input Validation**: Ensures all required fields are properly filled
- **Deployment Status**: Clear success/failure messages with detailed explanations
- **Action Guidance**: Specific instructions on how to resolve deployment issues

## Memory Management

- **Automatic Cleanup**: Destructor properly deallocates all queue nodes
- **Exception Safety**: Proper error handling for memory operations
- **No Memory Leaks**: All dynamically allocated memory is properly freed

## Requirements Met

✅ **Custom Data Structure**: Singly-linked-list queue (no STL containers)  
✅ **Menu-Driven Interface**: User-friendly console navigation  
✅ **File I/O Operations**: Batch registration and site data management  
✅ **FIFO Queue Operations**: Proper enqueue/dequeue functionality  
✅ **Error Handling**: Comprehensive input validation and error management  
✅ **Memory Safety**: Proper allocation and deallocation of dynamic memory  
✅ **C++11 Compatibility**: Uses modern C++ features appropriately  

## Example Usage Flow

1. Start the program
   - System automatically loads all volunteers from `data/volunteers.txt`
   - Shows how many volunteers are ready for deployment
2. Register volunteers (optional):
   - Single: Enter one volunteer's details manually
   - Multiple: Specify how many volunteers to register, then enter each one's details
3. View available volunteers to see deployment queue
4. Deploy volunteers to relief sites (FIFO order from file + newly registered)
5. Monitor site capacity and volunteer assignments
6. Continue operations or exit safely

### New Multiple Registration Feature
- Specify exact number of volunteers to register (1-50)
- Loop through individual registration for each volunteer
- Built-in progress tracking and skip functionality
- Type 'skip' to skip a volunteer during registration
- Automatic validation and error handling for each entry
- **Proper File Formatting**: Each volunteer saved on separate line
- **File Integrity**: Validation checks to ensure correct CSV format

This implementation provides a robust, user-friendly system for managing volunteer operations in disaster relief scenarios while maintaining efficient queue operations and proper resource management.

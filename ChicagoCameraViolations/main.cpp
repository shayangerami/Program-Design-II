/*
 * Program: Camera Violation Analysis System
 * Author: Shayan Gerami
 * Date: 3/28/2025
 * Description: This program analyzes traffic camera violation data from a CSV file.
 *              It provides functionality to:
 *              - Display data overview including total records, unique cameras, and violations
 *              - Show results by neighborhood with camera counts and violation totals
 *              - Generate a chart showing violations by month
 *              - Search for cameras by intersection or neighborhood
 * Input: CSV file containing camera violation data with columns:
 *        intersection, address, camera number, date, violations, neighborhood
 * Output: Various formatted reports and search results based on user menu selection
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> // For find()
#include <iomanip>   // For setw and alignment
#include <tuple> 
#include <cctype>    // For tolower
#include <limits>    // For numeric_limits

using namespace std;

// Class to store camera data
class CameraRecord {
private:
    string intersection;  // Street intersection where camera is located
    string address;      // Full address of the camera
    string cameraNumber; // Unique identifier for each camera
    string date;        // Date of the violation record
    int violations;     // Number of violations recorded
    string neighborhood; // Neighborhood where camera is located
public:
    // Constructor
    CameraRecord(string inter, string add, string camNum, string d, int vio, string neigh) {
        intersection = inter;
        address = add;
        cameraNumber = camNum;
        date = d;
        violations = vio;
        neighborhood = neigh;
    }
    // Getters
    string getInter() const { return intersection; }
    string getAdd() const { return address; }
    string getCamNum() const { return cameraNumber; }
    string getDate() const { return date; }
    int getVio() const { return violations; }
    string getNeigh() const { return neighborhood; }
};

// Function prototypes
vector<CameraRecord> readFile(string fileName);
void dataOverview(const vector<CameraRecord>& cameraRecords);
void resultsByNeighborhood(const vector<CameraRecord>& cameraRecords);
void displayChartByMonth(const vector<CameraRecord>& cameraRecords);
string getMonth(int monthNumber);
void searchByCamera(const vector<CameraRecord>& cameraRecords);


int main() {
    int choice;
    string fileName;

    // Get input file name from user
    cout << "Enter file to use: " << endl;
    cin >> fileName;
    vector<CameraRecord> cameraRecords = readFile(fileName); // Read data from file

    // Main menu loop
    do {
        cout << "\nSelect a menu option:" << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. Results by neighborhood" << endl;
        cout << "  3. Chart by month" << endl;
        cout << "  4. Search for cameras" << endl;
        cout << "  5. Exit" << endl;
        cout << "Your choice: ";
        
        // Input validation to handle non-numeric input
        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
 
        // Process user choice
        switch(choice){
            case 1:
                dataOverview(cameraRecords);
                break;
            case 2:
                resultsByNeighborhood(cameraRecords);
                break;
            case 3:
                displayChartByMonth(cameraRecords);
                break;
            case 4:
                searchByCamera(cameraRecords);
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

/**
 * Reads camera violation data from a CSV file and stores it in the global cameraRecords vector
 * @param fileName The name of the CSV file to read
 * @pre fileName exists and is a valid CSV file with the correct format
 * @post cameraRecords vector is populated with CameraRecord objects from the file
 * @return vector storing all camera records
 */
vector<CameraRecord> readFile(string fileName) {
    vector<CameraRecord> cameraRecords;
    ifstream fileIn; // Create ifstream object
    fileIn.open(fileName); // Open file

    if(fileIn.is_open()) {
        string intersection, address, cameraNumber, date, violationsStr, neighborhood;
        int violations;

        // Read file line by line until end of file
        while (!fileIn.eof()) {
            // Read each field separated by commas
            getline(fileIn, intersection, ',');
            getline(fileIn, address, ',');
            getline(fileIn, cameraNumber, ',');
            getline(fileIn, date, ',');
            getline(fileIn, violationsStr, ',');
            getline(fileIn, neighborhood);
            
            // Convert violations string to integer
            violations = stoi(violationsStr);
            
            // Create and add new CameraRecord to vector
            cameraRecords.push_back(CameraRecord(intersection, address, cameraNumber, date, violations, neighborhood));
        }
        fileIn.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }
    return cameraRecords;
}

/**
 * Displays an overview of the camera violation data including:
 * - Total number of records
 * - Number of unique cameras
 * - Total number of violations
 * - Day with the most violations
 * @pre cameraRecords vector is not empty
 * @post Displays formatted overview information to the console
 */
void dataOverview(const vector<CameraRecord>& cameraRecords) {
    /*
    CASE 1 
    */    

    // Display number of records
    int fileSize = cameraRecords.size();
    cout << "Read file with " << fileSize << " records." << endl;

    // Count unique cameras using a vector to track seen cameras
    vector<string> uniqueCameras; // Vector to store unique camera IDs

    for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        string camID = record.getCamNum();
        
        // Only add camera if it hasn't been seen before
        if (find(uniqueCameras.begin(), uniqueCameras.end(), camID) == uniqueCameras.end()) {
            uniqueCameras.push_back(camID);
        }
    }

    int count = uniqueCameras.size();
    cout << "There are " << count << " cameras." << endl;

    // Calculate total violations across all records
    int sum = 0;
    for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        int numViolations = record.getVio();
        sum += numViolations;
    }
    cout << "A total of " << sum << " violations." << endl;

    // Find day with maximum violations
    int max = 0;
    string maxDate, maxInter;
    for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        int numViolations = record.getVio();

        if (numViolations > max) {
            max = numViolations;
            maxDate = record.getDate();
            maxInter = record.getInter();
        }
    } 

    // Convert date from YYYY-MM-DD to MM-DD-YYYY format
    string year = maxDate.substr(0, 4);  // Year is always 4 digits
    
    // Find the positions of the hyphens
    int firstHyphen = maxDate.find('-', 4); 
    int secondHyphen = maxDate.find('-', firstHyphen + 1);
    
    // Extract month and day
    string month = maxDate.substr(firstHyphen + 1, secondHyphen - firstHyphen - 1);
    string day = maxDate.substr(secondHyphen + 1);
    
    // Create the reversed date format
    string dateReversed = month + "-" + day + "-" + year;

    cout << "The most violations in one day were " << max << " on " << dateReversed << " at " << maxInter << endl;
}

/**
 * Displays a sorted list of neighborhoods with their camera counts and total violations
 * @pre cameraRecords vector is not empty
 * @post Displays formatted table of neighborhoods sorted by violation count
 */
void resultsByNeighborhood(const vector<CameraRecord>& cameraRecords){
    /*
    CASE 2
    */

   // Get unique neighborhoods using a vector to track seen neighborhoods
   vector<string> uniqueNeighborhoods; // Vector to store unique neighborhoods

   for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        string neigh = record.getNeigh();
        
        // Only add neighborhood if it hasn't been seen before
        if (find(uniqueNeighborhoods.begin(), uniqueNeighborhoods.end(), neigh) == uniqueNeighborhoods.end()) {
            uniqueNeighborhoods.push_back(neigh);
        }
    }

    // Vector to store neighborhood data for sorting
    vector<tuple<string, int, int>> sortedNeighborhoods; // Store (neighborhood, uniqueCamerasCount, violationsSum)
    
    // Process each unique neighborhood
    for (int i = 0; i < uniqueNeighborhoods.size(); i++) {
        string currentNeighborhood = uniqueNeighborhoods.at(i);
        vector<string> uniqueCameras;  // Vector to store unique cameras for this neighborhood
        int violationsSum = 0; // Store count of violations for each neighborhood

        // Look through all records to find cameras in this neighborhood
        for (int j = 0; j < cameraRecords.size(); j++) {
            CameraRecord record = cameraRecords.at(j);
            if (record.getNeigh() == currentNeighborhood) {
                int violations = record.getVio(); // Get number of violations
                violationsSum += violations; // Add to violations sum

                string camID = record.getCamNum(); // Get camera id
                // Only add camera if it's not already in our unique cameras list
                if (find(uniqueCameras.begin(), uniqueCameras.end(), camID) == uniqueCameras.end()) {
                    uniqueCameras.push_back(camID);
                }
            }
        }

        // Store data for sorting
        sortedNeighborhoods.push_back(make_tuple(currentNeighborhood, uniqueCameras.size(), violationsSum));
    }

    // Sort the neighborhoods by number of violations in descending order
    sort(sortedNeighborhoods.begin(), sortedNeighborhoods.end(), 
        [](const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
            return get<2>(a) > get<2>(b);  // Compare by violations (third element) in descending order
        });

    // Display results for each neighborhood with proper formatting
    for (int i = 0; i < sortedNeighborhoods.size(); i++) {
        // Get the tuple for the current neighborhood
        string neigh = get<0>(sortedNeighborhoods[i]);  // Get neighborhood name
        int camCount = get<1>(sortedNeighborhoods[i]);  // Get number of unique cameras
        int vioSum = get<2>(sortedNeighborhoods[i]);    // Get number of violations

        // Format and display the data
        cout << left << setw(25) << neigh
            << right << setw(4) << camCount
            << right << setw(7) << vioSum << endl;
    }
}

/**
 * Generates and displays a bar chart showing violations by month
 * @pre cameraRecords vector is not empty
 * @post Displays a bar chart with months and asterisk bars representing violations
 */
void displayChartByMonth(const vector<CameraRecord>& cameraRecords){
    /*
    CASE 3
    */
   
    // Vector to store monthly violation data
    vector<tuple<int, string, int>> violationsPerMonth; // Vector to store (monthNumber, monthName, totalViolations)

    // Process each record to aggregate violations by month
    for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        string date = record.getDate();
        
        // Extract month from date string (YYYY-MM-DD format)
        int firstHyphen = date.find('-', 4);  // Position of the first hyphen
        int secondHyphen = date.find('-', firstHyphen + 1); // Position of the second hyphen
        string monthNumber = date.substr(firstHyphen + 1, secondHyphen - firstHyphen - 1);
        int monthInt = stoi(monthNumber);
        string monthName = getMonth(monthInt);
        
        int numOfViolations = record.getVio();

        // Check if this month already exists in vector
        bool monthFound = false;
        for (int i = 0; i < violationsPerMonth.size(); i++){
            if (get<0>(violationsPerMonth[i]) == monthInt) {
                get<2>(violationsPerMonth[i]) += numOfViolations; // Add violations to existing month
                monthFound = true;
                break;
            }
        }
        // If month wasn't found, add it as a new entry
        if (!monthFound){
            violationsPerMonth.push_back(make_tuple(monthInt, monthName, numOfViolations));
        }   
    }
    
    // Sort by month number
    sort(violationsPerMonth.begin(), violationsPerMonth.end());
    
    // Display the bar chart
    for (int i = 0; i < violationsPerMonth.size(); i++ ) {
        cout << left << setw(15) << get<1>(violationsPerMonth[i])
             << left << setw(10) << string(get<2>(violationsPerMonth[i])/1000, '*') << endl;
    }
}

/**
 * Converts a numeric month to its corresponding name
 * @param monthNumber Integer value representing the month (1-12)
 * @return String containing the full name of the month
 * @pre monthNumber is between 1 and 12
 */
string getMonth(int monthNumber) {
    switch (monthNumber) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
        default:
            return "Invalid month.";
    }
}

/**
 * Searches for cameras based on intersection or neighborhood name
 * @pre cameraRecords vector is not empty
 * @post Displays matching camera information or "No cameras found" message
 */
void searchByCamera(const vector<CameraRecord>& cameraRecords){
    /*
    CASE 4
    */
   
    // Prompt user for search term (ignore case)
    string searchTerm;
    cout << "What should we search for?" << endl; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear any leftover newline
    getline(cin, searchTerm);
    // Convert searchTerm to lowercase for case-insensitive comparison
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    bool found = false;
    vector<string> uniqueCameras;  // Track unique camera numbers
    
    // Look for search term in intersection or neighborhood
    for (int i = 0; i < cameraRecords.size(); i++) { // Looping through all records 
        CameraRecord record = cameraRecords.at(i);
        string intersection = record.getInter();
        string neighborhood = record.getNeigh();
        
        // Convert fields to lowercase for case-insensitive comparison
        transform(intersection.begin(), intersection.end(), intersection.begin(), ::tolower);
        transform(neighborhood.begin(), neighborhood.end(), neighborhood.begin(), ::tolower);

        // Only process if we haven't seen this camera before and search term matches
        if (find(uniqueCameras.begin(), uniqueCameras.end(), record.getCamNum()) == uniqueCameras.end() &&
            (intersection.find(searchTerm) != string::npos || neighborhood.find(searchTerm) != string::npos)) {
            
            found = true;
            uniqueCameras.push_back(record.getCamNum());  // Mark this camera as seen
            // Display camera information
            cout << "Camera: " << record.getCamNum() << endl;
            cout << "Address: " << record.getAdd() << endl;
            cout << "Intersection: " << record.getInter() << endl;
            cout << "Neighborhood: " << record.getNeigh() << endl;
            cout << endl;  // Add blank line between entries
        }
    }
    
    // Display message if no cameras were found
    if (!found) {
        cout << "No cameras found." << endl;
    }
}

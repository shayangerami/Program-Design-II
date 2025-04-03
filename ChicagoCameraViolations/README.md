# Camera Violation Analysis System

## Overview

The **Camera Violation Analysis System** is a C++ program designed to analyze traffic camera violation data from a CSV file. The system provides insights into violations by location, time, and frequency. Users can navigate through various options to extract relevant information.

## Features

- **Data Overview:** Displays total records, unique cameras, and total violations.
- **Neighborhood Analysis:** Lists violations and camera counts by neighborhood.
- **Chart by Month:** Displays violations grouped by month.
- **Camera Search:** Allows searching for cameras by intersection or neighborhood.

## Files in the Directory

- `north-side.csv` - Data file containing violations for cameras in the north-side region.
- `west-side.csv` - Data file containing violations for cameras in the west-side region.
- `south-side.csv` - Data file containing violations for cameras in the south-side region.
- `headers.txt` - Contains column headers for the data files.

## Data Format

The CSV file used by the program must follow this format:

```
intersection,address,camera number,date,violations,neighborhood
```

Example:

```
Main St & 1st Ave,123 Main St,CAM001,2025-01-15,10,Downtown
Broadway & 5th Ave,200 Broadway St,CAM002,2025-01-16,5,West Side
```

## How to Use

1. **Compile the Program:**
   ```sh
   g++ camera_violation_analysis.cpp -o camera_analysis
   ```
2. **Run the Program:**
   ```sh
   ./camera_analysis
   ```
3. **Select a CSV File:** When prompted, enter the name of the CSV file to be analyzed.
4. **Choose an Option from the Menu:**
   - Enter `1` for a data overview.
   - Enter `2` for results by neighborhood.
   - Enter `3` for a chart by month.
   - Enter `4` to search for cameras.
   - Enter `5` to exit.

## Requirements

- C++ Compiler (e.g., g++)
- Input CSV file with valid format

## Author

**Shayan Gerami**\
Date: 3/28/2025


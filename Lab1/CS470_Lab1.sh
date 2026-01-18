#!/bin/bash

#Name: Alex Solomon
#Date: January 18, 2026
#Assignment: CS470 Lab 1
#Instructor: Dr. Zhu
#Description: This script creates a directory structure with subdirectories and text files, logging each action with timestamps.

# ----------------------------------------------------------
#Create the log file with initial entry being the script start time
LOG_FILE="script.log"
echo "Script started at $(date +'%Y-%m-%d %H:%M:%S')" >> "$LOG_FILE"


# ----------------------------------------------------------
#Create the main directory name based on current date and time
MAIN_DIRECTORY="Files_$(date +'%Y%m%d_%H%M%S')"


# ----------------------------------------------------------
#Create the main directory and log the action!
mkdir "$MAIN_DIRECTORY"
echo "Created main directory: $MAIN_DIRECTORY at $(date +'%Y-%m-%d %H:%M:%S')" >> "$LOG_FILE"


# ----------------------------------------------------------
#Change into the main directory
cd "$MAIN_DIRECTORY"


#Loop to create subdirectories and log each folder creation
for i in {101..110}; do
    SUBDIR="file$i"
    mkdir "$SUBDIR"
    echo "Created subdirectory: $SUBDIR at $(date +'%Y-%m-%d %H:%M:%S')" >> "../$LOG_FILE"
done

# ----------------------------------------------------------
#Make an array of programming languages
LANGUAGES=("Python" "Java" "C++" "JavaScript" "Ruby" "C" "C#" "Go" "Swift" "Lua" "PHP")

#Loop through each subdirectory to create text files and log each file creation
for i in {101..110}; do
    SUBDIR="file$i"
    cd "$SUBDIR"

    for j in {501..510}; do 
        FILE="tuser$j.txt"

        #Determine the programming language to write into the file
        LANGUAGE_INDEX=$(((j-501) % ${#LANGUAGES[@]}))
        echo "${LANGUAGES[$LANGUAGE_INDEX]}" > "$FILE"
        echo "Created file: $FILE in $SUBDIR with content '${LANGUAGES[$LANGUAGE_INDEX]}' at $(date +'%Y-%m-%d %H:%M:%S')" >> "../../$LOG_FILE"
    done

    #Return to the main directory
    cd ..
done

# ----------------------------------------------------------
#Log the completion of the script
echo "Script completed at $(date +'%Y-%m-%d %H:%M:%S')" >> "$LOG_FILE"


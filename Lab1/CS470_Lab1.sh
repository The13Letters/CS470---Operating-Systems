#!/bin/bash

# Name: Alex Solomon
# Date: January 18, 2026
# Assignment: CS470 Lab 1
# Instructor: Dr. Zhu
# Description: This script creates a directory structure with subdirectories and text files,
#              logging each action with timestamps, with basic error handling.

# ----------------------------------------------------------
# Basic safety: treat unset variables as errors
set -u

# ----------------------------------------------------------
# Logging helpers
LOG_FILE="script.log"
LOG_PATH="$(pwd)/$LOG_FILE"

#Helper function to log info messages
log_info() 
{
  #$1 = message
  echo "[$(date +'%Y-%m-%d %H:%M:%S')] $1" >> "$LOG_PATH"
}

#Helper function to log error messages and exit (Had help from the web for this because I dont know bash well yet)
log_error_and_exit() 
{
  # $1 = message, $2 = exit code
  local msg="$1"
  local code="$2"
  echo "[$(date +'%Y-%m-%d %H:%M:%S')] ERROR: $msg" >> "$LOG_PATH"
  exit "$code"
}

#Start log
log_info "Script started"

# ----------------------------------------------------------
# Create the main directory name based on current date and time
MAIN_DIRECTORY="Files_$(date +'%Y%m%d_%H%M%S')"

# ----------------------------------------------------------
# Create the main directory and log the action
if mkdir "$MAIN_DIRECTORY"; then
  log_info "Created main directory: $MAIN_DIRECTORY"
else
  log_error_and_exit "Failed to create main directory: $MAIN_DIRECTORY"
fi

# ----------------------------------------------------------
# Change into the main directory
if cd "$MAIN_DIRECTORY"; then
  :
else
  log_error_and_exit "Failed to cd into main directory: $MAIN_DIRECTORY"
fi

# ----------------------------------------------------------
# Create subdirectories file101–file110
for i in {101..110}; do
  SUBDIR="file$i"
  if mkdir "$SUBDIR"; then
    log_info "Created subdirectory: $SUBDIR"
  else
    log_error_and_exit "Failed to create subdirectory: $SUBDIR"
  fi
done

# ----------------------------------------------------------
# Array of programming languages
LANGUAGES=("Python" "Java" "C++" "JavaScript" "Ruby" "C" "C#" "Go" "Swift" "Lua" "PHP")

# ----------------------------------------------------------
# Create files tuser501.txt–tuser510.txt inside each subdirectory
for i in {101..110}; do
  SUBDIR="file$i"

  if cd "$SUBDIR"; then
    :
  else
    log_error_and_exit "Failed to cd into subdirectory: $SUBDIR"
  fi

  for j in {501..510}; do
    FILE="tuser$j.txt"

    #Determine the programming language to write into the file
    LANGUAGE_INDEX=$(((j - 501) % ${#LANGUAGES[@]}))

    #Write content to the file and log the action
    if echo "${LANGUAGES[$LANGUAGE_INDEX]}" > "$FILE"; then
      log_info "Created file: $SUBDIR/$FILE"
    else
      log_error_and_exit "Failed to write to file: $SUBDIR/$FILE"
    fi
  done

  #Return to the main directory
  if cd ..; then
    :
  else
    log_error_and_exit "Failed to return to main directory from: $SUBDIR"
  fi
done

# ----------------------------------------------------------
# Log completion
log_info "Script Completed Successfully"

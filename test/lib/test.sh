#!/bin/bash

# A simple script to run 'nm' on all files in the current directory
# and report the filename and its exit status.

# Set the counter for reporting purposes
count=0

# Loop through all files (*) in the current directory
for file in *; do
    # Check if the item is a regular file (not a directory)
    if [ -f "$file" ]; then
        
        # 1. Run the nm command silently
        #    -q suppresses the "no symbols" message.
        #    The output is redirected to /dev/null to hide it.
        nm  "$file" > /dev/null 2>&1
        
        # 2. Capture the exit status ($?) immediately after the command runs
        exit_status=$?
        
        # 3. Print the result
        echo "$file: $exit_status"
        
        count=$((count + 1))
    fi
done

echo "---"
echo "Finished checking $count files."
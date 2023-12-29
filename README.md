# Bplus-Tree
README.md    

The purpose of this program is to give the user an interface with an assignment described database of zip-codes (keys), which includes records of various predefined fields residing in a .txt file, with certain functions including (insert, delete, modify, display methods to view all records, view a single record, view the total number of blocks, view used/unused space within a specified block, and commands that allow the user the ability to interact with the database while they're using it.
Compilation Instruction: Create executable/runnable.
-Navigate to directory: /home/STCLOUDSTATE/student-Id/path
-Build/Compile: g++ main.cpp

Command Line Arguments:
This program will use two arguments for int main(), which are int argc and char *argv. These two arguments allow the program to be scriptable. First the program name is entered followed by the command flags to be executed. For example, instead of just a.out, a user would enter a.out debug to run the debugging portion of the program. The following are command flags:

B+treeFileName – this will open an existing B+tree file or create a new one to be used
dataFileName – this will open the data file to be used for the B+tree
dataFile “I” or “D” - I signals that the data file should be added to the B+tree and D if the data file is to be deleted from the B+tree, this flag found in the header record
blockSize – this will set the desired block size to use for the records
debug – displays output from the functions to determine proper operation of functions

Interactive Menu:
If the program is run without any command line arguments, then the interactive menu will be displayed. The commands for the menu are displayed in the console to the user by their command name followed by what the command does. The following are commands in the interactive menu:

a – Add: This adds a record to the tree
d – Delete: This prompts user to enter the record to be deleted
b – Blocks: Displays number of blocks in the tree
s – Search: This will search the records and report if the record exists or not
and what the record contains if it exists
p – Print: This prints the tree
l – Leaves: Prints the leaves of the tree
e – Empty: Empties the tree
h – Height: Displays height of the tree
r – Record: modify a record
      m – Menu: Displays menu
V – verbose mode
q – Quit: This exits the program 

Data file configuration:
The data file should contain sorted entries. The sorting is by primary key which is the zip code. The data file should also have a header record which contains the information:
Header size, flagged insert or delete, number of records, size of each record, number of fields per record, size of list of fields, size of text of field labels, flag if sorted or unsorted, and information about the data.

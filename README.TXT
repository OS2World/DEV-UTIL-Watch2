WATCH/2 DEBUGGING AID
VERSION 2.03

Copyright (c) 1990, All Rights Reserved
Alan A. Colberg
150 Whiteland Hunt Road
Downingtown, PA  19335

The following is a list of the corrections, changes, and
enhancements from Version.Release 2.01 included in Version.Release 2.02:

1. Corrected the handling of Long File names for use with the 
High Performance File System (HPFS).

2. Changed the boolean variable names to meet the proposed ANSI
standard naming conventions.

3. Increased the sizing on the list box to fill the entire
Parent window to maximize number of and width of messages shown.

The following is a list of the corrections, changes, and
enhancements from Version.Release 2.02 included in Version.Release 2.03:

1. Modified the log file open routine to read and display the entries 
previously logged to the file if the file already exists, and append all
further log entries to the end of the file.  If a file by that name does
not already exist, a new log file is created and the main window display
is cleared automatically.  As such, the log file if open will always
match what is displayed on the screen.

2. Minor rearrangement of code to improve structure.

3. Added additional comments throughout the source to aid readability.

4. Implemented saving of window position and last log file specification
used into a file entitled WATCH.CFG.  This allows Watch/2 to load at the
same position and with the same file name as when it was last used.


NOTE:  Any monetary compensation, comments, suggestions, or 
       constructive criticism would be greatly appreciated.

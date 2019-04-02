:userdoc.
:title.Help for Watch/2 Debugging Aid
:body.
.*
.*
:h1 res=001.Watch/2 Extended Help
:p.
The :hp2.Watch/2 Debugging Aid:ehp2. is designed to assist the
Presentation Manager Applications developer by providing a 
a means for displaying debugging information within the PM environment.
This utility is meant to be used as the developers sole debugging
aid. Rather is is designed to be used in conjunction with other
commercially available debugging aids.
:p.
For information on setting up a client application to use the :hp2.Watch/2
Debugging Aid:ehp2., Select the "
:link reftype=hd res=041.Installing in Clients:elink." option from the
:hp2.F1=Help:ehp2. pull-down menu.
.*
.*
:h1 res=005.Help for Options
:p.
Choose the :hp2.Options:ehp2. pull-down menu to show and allow selection of the
available options for the Watch/2 Debugging Aid.  Those Options Include...
:parml.
:pt.:link reftype=hd res=006.Clear:elink. Message Area
:pd.Select this option to Clear the main message logging area of all
currently displayed messages.
:pt.:link reftype=hd res=007.Open:elink. 
/:link reftype=hd res=007.Close:elink. Log File
:pd.Select this option to either :hp2.Open:ehp2. a log file and begin
logging messages to that file or to :hp2.Close:ehp2. the log file and 
to terminate logging messages to the file.  This options depends on the 
state of the menu item.
:pt.:link reftype=hd res=015.Truncate:elink. File
:pd.Select this menu item if you wish to clear all messages which have
been logged to an open message logging file.
.*
.*
:h2 res=006.Help for Clear Message Area
:p.
Select the :hp2.Clear Message Area:ehp2. to clear all messages displayed in the
primary debugging window.  Once cleared, the window should display a 
single message which reads "Beginning of Log...". The 
:hp2.Clear Message Area:ehp2. can also be selected by pressing the
:link reftype=hd res=024.Del:elink. key.
:p.
:hp2.Note...:ehp2. Clearing the message area does not clear
any messages logged to a message logging file.  Clearing
of a file is accomplished through
the use of the
:link reftype=hd res=015.Truncate File:elink.
facility.
.*
.*
:h2 res=007.Log Messages to File
:p.
This menu item has two states, :hp2.Open Log File...:ehp2. and :hp2.Close
Log File:ehp2.. When the menu item reads "Open Log File...", no logging
is presently being piped to a file.  Choosing this selection sets up a 
dialog box requesting the user to enter a file specification which can be
used to open a file and begin directing all log messages to both the main
logging window as well as to a file.
:p.
When the menu item reads "Close Log File", a message logging file is 
currently open and accepting log messages.  Choosing this selection closes
the file and from that point all messages are only logged to the main 
logging window.
:p.
Regardless of the state of this menu item, it can be selected by pressing
the :link reftype=hd res=024.Ctrl+L:elink. keys simultaneously.
.*
.*
:h3 res=10.Log File Name
:p.
Enter the full drive, path, and file specification of the file to which
message logging is to be written.
:p.
:hp2.Note...:ehp2. If the High Performance File System is loaded, this
file specification can be up to 254 bytes in length, adhering to the
standard HPFS file specification definition.
.*
.*
:h3 res=11.Log File Ok/Cancel Buttons
:p.
Choose the :hp2.OK:ehp2. button to accept the file name displayed in the Log File
Specification, or choose the :hp2.Cancel:ehp2. button to return without opening the 
message logging file.
.*
.*
:h2 res=015.Truncate File
:p.
This :hp2.Truncate File:ehp2. option is only selectable
when a message logging file is open.  When
selectable, this option clears all messages previously logged to the 
file and resets the file to an empty state and ready to receive all new
messages. The :hp2.Truncate File:ehp2. option can also be selected
by pressing the
:link reftype=hd res=024.Ctrl+T:elink. keys simultaneously.
:p.
:hp2.Note...:ehp2. Truncating the message logging file does
not clear any messages logged to the main Watch/2 debugging window.
to clear messages from the main window, use the
:link reftype=hd res=006.Clear Message Area:elink.
facility
.*
.*
:h1 res=17.Exit Watch/2 Debugging Aid
:p.
Choosing the :hp2.Exit:ehp2. main menu item initiates a pull-down menu
requesting the user to choose either
:link reftype=hd res=018.Exit:elink. or
:link reftype=hd res=019.Resume:elink.
:p.
This acts as final confirmation that the user really wishes to
:hp2.Exit:ehp2. the Watch/2 Debugging Aid, and if not, gives the user
the opportunity to continue normal operations of the utility.
.*
.*
:h2 res=018.Exit the Watch/2 Debugging Aid
:p.
Choose this option to close any open message logging file and accomplish
a controlled shutdown. The :hp2.Exit:ehp2. can also be initiated
by pressing the
:link reftype=hd res=024.F3:elink. key.
:p.
:hp2.Note...:ehp2. If any client applications are attached at the time
this option is selected, the Watch/2 Debugging Aid will not allow
shutdown until all client applications have first been shut down.
.*
.*
:h2 res=019.Resume the Watch/2 Debugging Aid
:p.
Should :hp2.Exit:ehp2. be choosen by mistake from the main panel menu,
chooing the :hp2.Resume:ehp2. option merely places the user back to the
main panel as if Exit had never been selected.
.*
.*
:h1 res=020.Help for F1=Help
:p.
Selecting the main :hp2.F1=Help:ehp2. menu item displays the the
:hp2.Help:ehp2 pull-down menu for selection of the various help options.
:p.
Pressing the :link reftype=hd res=024.F1:elink. key from any
point in the menu structures presents :hp2.help:ehp2.
for the specific menu or submenu item.  Pressing the
:link reftype=hd res=024.F1:elink. key from 
within any dialog presents the :hp2.help:ehp2. for the specific field
or push-button which is currently highlighted.
.*
.*
:h2 res=021.Help for Help
:p.
Select :hp2.Help for Help:ehp2. on the :hp2.Help:ehp2. pull-down menu
for information on how to use the :hp2.Help:ehp2. facilities associated
with the Watch/2 Debugging Aid. 
.*
.*
:h2 res=022.Extended Help
:p.
Select :hp2.Extended Help:ehp2. on the :hp2.Help:ehp2. pull-down menu
to see the extended help panel for the Watch/2 Debugging Aid.
.*
.*
:h2 res=023.Keys Help
:p.
Select :hp2.Keys Help:ehp2. on the :hp2.Help:ehp2. pull-down menu to
see a list of the available accelerator keys associated with the 
Watch/2 Debugging Aid.
.*
.*
:h2 res=024.Accelerator Keys
:p.
The following is a list of the available accelerator keys associated with
the Watch/2 Debugging Aid software...
:parml.
:pt.F1
:pd.Get Help
:pt.F2
:pd.View the Extended Help for the Watch/2 Debugging Aid from
within any help window.
:pt.F3
:pd.Initiates the 
:link reftype=hd res=018.Exit:elink.
task to shut down the Watch/2 Debugging Aid.
:pt.Del
:pd.Initiates the task to accomplish the
:link reftype=hd res=006.Clear Message Area:elink.
associated with the main message logging window.
:pt.Ctrl+L
:pd.Selects either the :link reftype=hd res=007.Open:elink.
or :link reftype=hd res=007.Close:elink. operation associated with
a message logging file depending on the state of the menu item.
:pt.Ctrl+T
:pd.:link reftype=hd res=015.Truncate:elink.
all messages from the currently open logging file.
:eparml.
.*
.*
:h2 res=025.Help Index
:p.
Select :hp2.Help Index:ehp2. on the :hp2.Help:ehp2. pull-down menu to
see the :hp2.Index:ehp2. of all help available for the Watch/2 Debugging
Aid Utility.
.*
.*
:h2 res=026.Help for About Watch/2 Debugging Aid
:p.
Select :hp2.About:ehp2. from the :hp2.Help:ehp2. pull-down menu to
view the :hp2.Version.Release:ehp2., :hp2.Author:ehp2., and 
:hp2.Copyright:ehp2. Information for the Watch/2 Debugging Aid.
.*
.*
:h2 res=034.About Watch
:p.
The idea behind the :hp2.Watch/2 Debugging Aid:ehp2. was
originally presented in the January 1990 issue of MicroSoft
Journal along with a program entitled TRACER, authored
by Daniel Hildebrand. 
:p.
While :hp2.Watch/2:ehp2. is generally built around the same concepts
and ideas, it has been entirely re-engineered and enhanced to include
features such as a full implementation of the IPF help
capabilities.
:p.
This software is offered as a shared tool only.  You are free to copy and
use for software development and debugging purposes, providing...
:p.
1. NO FEE IS CHARGED FOR USE, COPYING, OR DISTRIBUTION; and
:p.
2. IS NOT MODIFIED IN ANY WAY FROM THE ORIGINAL.
:p.
There exists NO warranties, either expressed or implied, as to
the merchantability, fitness for purpose, or functionality of this
software.
.*
.*
:h2 res=040.Installation in Client Applications
:p.
Select :hp2.Installing in Clients:ehp2. from the :hp2.Help:ehp2. pull-down
menu to view instructions for installing the appropriate software hooks 
and includes into the client application which will allow the application 
to have use of the Watch/2 Debugging Aid.
.*
.*
:h2 res=041.Installation in Client Applications
:p.
In order to install the appropriate hooks to the Watch/2 Debugging Aid into
a client application, the following steps should be taken...
:p.
:hp8.Step 1:ehp8. - Include the :hp2.watch.h:ehp2.
header file in the beginning
of you c program source file to obtain the appropriate definitions for 
messages, variables, and necessary code. See
:link reftype=hd res=042.Example:elink. #1.
:p.
:hp8.Step 2:ehp8. - Add the :hp2.WATCHVARIABLES:ehp2. macro above the 
main() function.  This defines the necessary external variables necessary
for attaching and communicating with the :hp2.Watch/2 Debugging Aid:ehp2.
See :link reftype=hd res=043.Example:elink. #2.
:p.
:hp2.Note...:ehp2. The :hp2.WATCHVARIABLES:ehp2. macro may need to be added into
secondary source files if secondary modules use the Watch/2 facilities.
:p.
:hp8.Step 3:ehp8. - Add the :hp2.WATCHHELLO:ehp2. macro within the
:hp2.WM_CREATE:ehp2. message handling statement for the main message window
processing procedure.  This broadcasts a message to all applications to
see if Tracer is already running and if so an attachment can me made
immediately. See
:link reftype=hd res=044.Example:elink. #3.
:p.
:hp8.Step 4:ehp8. - Add tje :hp2.WATCHATTACH:ehp2. macro as a separate
message entry in the first level :hp2.case:ehp2. statement within the
main window processing procedure. This establishes the initial
communications facility for utilizing the Watch/2 Debugging Aid. See
:link reftype=hd res=045.Example:elink. #4.  
:p.
:hp8.Step 5:ehp8. - Use the :hp2.WATCHPOST(string):ehp2. macro freely
throughout the client application.  This macro provides the facility to
send the user defined text as a message to the :hp2.Watch/2 Debugging
Aid:ehp2.. See
:link reftype=hd res=046.Example:elink. #5.
.*
.*
:h3 res=042.Example #1 - Include Header Files
:xmp.
// SET UP DEFINES FOR SELECTIVE INCLUSION FROM OS2.H
#define INCL_PM
#define INCL_WIN
#define INCL_DOS

// APPLICATIONS INCLUDES OF APPROPRIATE HEADER FILES
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
:hp2.#include <watch.h>:ehp2.
#include "appl.h"
&bullet.
&bullet.
&bullet.
:exmp.
.*
.*
:h3 res=043.Example #2 - WATCHVARIABLES Macro
:xmp.
// DEFINE GLOBAL VARIABLES...
HMQ    hmq;
HWND   hwndClient;
HWND   hwndFrame;

:hp2.WATCHVARIABLES:ehp2.

VOID cdecl main()
{
&bullet.
&bullet.
&bullet.
}
:exmp.
.*
.*
:h3 res=044.Example #3 - WATCHHELLO Macro
:xmp.
// MAIN WINDOW PROCESSING PROCEDURE...
MRESULT EXPENTRY MainWindowProc(HWND hwnd, USHORT msg,
                                MPARAM mp1, MPARAM mp2)
{
  // DEFINE LOCALIZED VARIABLES...
  HPS   hps;
  RECTL rc;

  // HANDLE MESSAGES TO MAIN WINDOW...
  switch(msg)
  {
    case WM_CREATE:
         &bullet.
         :hp2.WATCHHELLO:ehp2.
         &bullet.
         break;
    case WM_COMMAND:
         &bullet.
         &bullet.
         &bullet.
    default:
      return WinDefWindowProc(hwnd, msg, mp1, mp2);
  }
  return FALSE;
}
:exmp.
.*
.*
:h3 res=045.Example #4 - WATCHATTACH Macro
:xmp.
// MAIN WINDOW PROCESSING PROCEDURE...
MRESULT EXPENTRY MainWindowProc(HWND hwnd, USHORT msg,
                                MPARAM mp1, MPARAM mp2)
{
  // DEFINE LOCALIZED VARIABLES...
  HPS   hps;
  RECTL rc;

  // HANDLE MESSAGES TO MAIN WINDOW...
  switch(msg)
  {
    case WM_CREATE:
         &bullet.
         WATCHHELLO
         &bullet.
         break;
    case WM_COMMAND:
         &bullet.
         &bullet.
         &bullet.
    :hp2.WATCHATTACH:ehp2.
    default:
      return WinDefWindowProc(hwnd, msg, mp1, mp2);
  }
  return FALSE;
}
:exmp.
.*
.*
:h3 res=046.Example #5 - WATCHPOST(string) Macro
:xmp.
VOID UserFunction(HWND hwnd)
{
  // INITIALIZATION PROCESSING...
  &bullet.
  &bullet.
  &bullet.

  // SET UP DIALOG AND PASS CONTROL TO THE DIALOG PROCEDURE...
  :hp2.WATCHPOST("Displaying the User Dialog Box!");:ehp2.
  WinDlgBox(HWND_DESKTOP,
            hwnd,
            UserDlgProc,
            NULL,
            ID_DIALOG,
            NULL);
  :hp2.WATCHPOST("Returned from Dialog Box Processing!");:ehp2.
  &bullet.
  &bullet.
  &bullet.
}
:exmp.
.*
.*
:euserdoc.

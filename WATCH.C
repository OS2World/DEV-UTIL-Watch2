// WATCH.C

// SETUP DEFINES FOR APPROPRIATE INCLUDES FROM OS/2 HEADER FILE...
#define INCL_PM
#define INCL_WIN
#define INCL_DOS
#define INCL_DOSFILEMGR
#define INCL_WINLISTBOXES
#define INCL_WINHOOKS
#define INCL_ERRORS
#define INCL_WINHELP

// INDLUDE APPROPRIATE HEADER FILES...
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include "watch.h"

// FUNCTION PROTOTYPES...
int main (void);
MRESULT EXPENTRY MainWndProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY AboutDlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY LogFileDlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
static VOID ClearSelector(PSZ szSelectorString);
void FAR PASCAL ClearMainList(HWND hwndListBox);
BOOL OpenLogFile(HWND hwnd);
VOID CloseLogFile(HWND hwnd);
void FAR PASCAL WatchPaint(HWND hwnd);
VOID WriteLogFileEntry(PSZ szSelectorString);
VOID DosSaveConfiguration(HWND hwnd);
VOID DosRestoreConfiguration(VOID);

// GLOBAL VARIABLE DEFINITIONS...
BOOL fFirstPass       = TRUE;
BOOL fLogFileOpen     = FALSE;
BOOL fWatchLoadFailed = FALSE;

char     szLoadFailed[]     = "Watch/2 Failed to Load, Only One Instance Allowed !";
char     szParentClass[]    = "ParentClass";
char     szTitle[]          = "Watch/2 Debugging Aid";
char     szLogFileSpec[255] = "\\watch.log";
char     szLogFileHold[255] = "\\watch.log";
char     szCfgFileSpec[]    = "watch.cfg";
char     szFileStrOpen[]    = "Open Log File...\tCtrl+L";
char     szFileStrClose[]   = "Close Log File\tCtrl+L";
char     szFontStrLarge[]   = "Large ~Font\tCtrl+F";
char     szFontStrSmall[]   = "Small ~Font\tCtrl+F";

char far *szSelectorString;

HAB      habMain;

HELPINIT hmiHelpData;

HFILE    pLogFile;
HFILE    pCfgFile;

HMQ      hmqMain;

HSYSSEM  hSysSem;

HWND     hwndParentFrm;
HWND     hwndParentWnd;
HWND     hwndMainList;
HWND     hwndHelpInstance;

int      iNumberInList;

SWP      swp;
USHORT   usSelector;
USHORT   usFileAction;
USHORT   usBytesWritten;

// MAIN PROCEDURE
int main()
{
  int   iSoundGen;
  QMSG  qmsg;
  ULONG ctlflags;

  habMain = WinInitialize((USHORT)NULL);

  hmqMain = WinCreateMsgQueue(habMain, 0);

  // SET POINTER TO HOURGLASS WHILE LOADING AND INITIALIZING...
  WinSetPointer(HWND_DESKTOP,
                WinQuerySysPointer(HWND_DESKTOP,
                                   SPTR_WAIT,
                                   FALSE));

  if (!WinRegisterClass(habMain,
                        (PCH)szParentClass,
                        (PFNWP)MainWndProc,
                        CS_SIZEREDRAW,
                        0))
     return(0);

  // INITIALIZE THE IPF DATA STRUCTURE...
  hmiHelpData.cb                        = sizeof(HELPINIT);
  hmiHelpData.ulReturnCode              = NULL;
  hmiHelpData.pszTutorialName           = NULL;
  hmiHelpData.phtHelpTable              = (PVOID)(0xffff0000 | IDM_WATCHHELPTABLE);
  hmiHelpData.hmodAccelActionBarModule  = NULL;
  hmiHelpData.idAccelTable              = IDM_WATCHMAIN;
  hmiHelpData.idActionBar               = NULL;
  hmiHelpData.pszHelpWindowTitle        = "Help for Watch/2 Debugging Aid";
  hmiHelpData.hmodHelpTableModule       = NULL;
  hmiHelpData.usShowPanelId             = NULL;
  hmiHelpData.pszHelpLibraryName        = "WATCH.HLP"; 

  // ESTABLISH THE HELP INSTANCE...
  hwndHelpInstance = WinCreateHelpInstance(habMain, &hmiHelpData);

  // INITIALIZE FRAME CONTROL FLAG WITH APPROPRIATE ATTRIBUTES...
  ctlflags = FCF_TITLEBAR      | FCF_SYSMENU  | FCF_BORDER |
             FCF_MINBUTTON     | FCF_MENU     | FCF_ICON   |
             FCF_SHELLPOSITION | FCF_TASKLIST | FCF_ACCELTABLE;

  // INITIALIZE AND CREATE THE STANDARD PARENT WINDOW...
  hwndParentFrm = WinCreateStdWindow(HWND_DESKTOP,
                                     WS_SYNCPAINT,
                                     &ctlflags,
                                     (PCH)szParentClass,
                                     NULL,
                                     0L,
                                     (HMODULE)NULL,
                                     IDM_WATCHMAIN,
                                     (HWND FAR *)&hwndParentWnd);

  // IF THE LOAD WAS COMPLETED SUCCESSFULLY, SOUND THE TRUMPET, CHANGE
  // THE SIZE OF THE WINDOW AND DISPLAY THE WINDOW AT THE TOP LEFT
  // CORNER OF THE DESKTOP...
  if (!fWatchLoadFailed)
     {
       for (iSoundGen = 0; iSoundGen < 12; iSoundGen++)
           DosBeep(((iSoundGen + 1) * 100), 1);
       WinSetWindowText(hwndParentFrm,
                        (PSZ)&szTitle);
       DosRestoreConfiguration();
       WinSetWindowPos(hwndParentFrm,
                       HWND_TOP,
                       swp.x,
                       swp.y,
                       500,
                       153,
                       SWP_SIZE | SWP_MOVE | SWP_SHOW);
     }

  // ASSOCIATE THE HELP INSTANCE WITH THE APPLICATION'S PARENT WINDOW FRAME
  if (hwndHelpInstance)
      WinAssociateHelpInstance(hwndHelpInstance, hwndParentFrm);

  // SET POINTER BACK TO NORMAL SYSTEM ARROW POINTER...
  WinSetPointer(HWND_DESKTOP,
                WinQuerySysPointer(HWND_DESKTOP,
                                   SPTR_ARROW,
                                   FALSE));

  // SET UP MESSAGE LOOP...
  while (WinGetMsg(habMain, (PQMSG)&qmsg, (HWND)NULL, 0, 0))
        WinDispatchMsg(habMain, (PQMSG)&qmsg);

  // CLEAN UP AND TERMINATE THE APPLICATION...
  if (hwndHelpInstance)
      WinDestroyHelpInstance(hwndHelpInstance);

  WinDestroyWindow(hwndParentFrm);
  WinDestroyMsgQueue(hmqMain);
  WinTerminate(habMain);                       
}



// MAIN WINDOW MESSAGE PROCESSING PROCEDURE...
MRESULT EXPENTRY MainWndProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
  int iSoundGen;

  switch(msg)
  {
    case WM_CREATE:
         if (DosCreateSem(CSEM_PUBLIC,
                          &hSysSem,
                          WATCH_SEMAPHORE))
            {
              DosBeep(300, 300);
              WinMessageBox(HWND_DESKTOP,
                            hwnd,
                            (PCH)&szLoadFailed,
                            (PCH)&szTitle,
                            NULL,
                            MB_OK | MB_ICONEXCLAMATION);
              fWatchLoadFailed = TRUE;
              WinPostMsg(hwnd, WM_QUIT, 0L, 0L);
              break;
            }
         if (DosAllocShrSeg(81,
                            WATCH_SEGMENT,
                            &usSelector))
            {
              DosBeep(300, 300);
              WinMessageBox(HWND_DESKTOP,
                            hwnd,
                            (PCH)&szLoadFailed,
                            (PCH)&szTitle,
                            NULL,
                            MB_OK | MB_ICONEXCLAMATION);
              fWatchLoadFailed = TRUE;
              WinPostMsg(hwnd, WM_QUIT, 0L, 0L);
              break;
            }
         // ALLOCATE THE SELECTOR STRING AND CLEAR IT IN PREPARATION
         // FOR LOGGING...
         szSelectorString = (char far *)((unsigned long)usSelector << 16);
         ClearSelector(szSelectorString);
         hwndMainList = WinCreateWindow(hwnd,
                                        WC_LISTBOX,
                                        "",
                                        WS_SYNCPAINT,
                                        0, 0, 0, 0,
                                        hwnd,
                                        HWND_TOP,
                                        IDM_WATCHLIST,
                                        NULL,
                                        0);
         // BROADCAST A NOTIFICATION TO ALL APPLICATIONS THAT WE
         // ARE HERE AND READY TO RECEIVE MESSAGES FOR LOGGING...
         WinBroadcastMsg(hwnd,
                         WATCH_RECEIVE_HANDLE,
                         MPFROMHWND(hwnd),
                         0L,
                         BMSG_FRAMEONLY | BMSG_POSTQUEUE);
         return WinDefWindowProc(hwnd, msg, mp1, mp2);
         break;
    case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
           case IDM_WATCHCLEARMSGAREA:
                ClearMainList(hwndMainList);
                break;
           case IDM_WATCHLOGTOFILE:
                if (!fLogFileOpen)
                   WinDlgBox(HWND_DESKTOP,
                             hwnd,
                             (PFNWP)LogFileDlgProc,
                             (HMODULE)NULL,
                             IDM_WATCHLOGFILEDLG,
                             NULL);
                else
                   {
                     CloseLogFile(hwnd);
                   }
                break;
           case IDM_WATCHTRUNCATEFILE:
                DosBufReset(pLogFile);
                DosClose(pLogFile);
                DosOpen((PSZ)szLogFileSpec,
                        &pLogFile,
                        &usFileAction,
                        0L,
                        0,
                        0x12,
                        0x41,
                        0L);
                ClearMainList(hwndMainList);
                break;
           case IDM_WATCHEXIT:
                WinPostMsg(hwnd, WATCH_PREPARE_SHUTDOWN, 0L, 0L);
                break;
           case IDM_WATCHRESUME:
                break;
           case IDM_WATCHABOUT:
                WinDlgBox(HWND_DESKTOP,
                          hwnd,
                          (PFNWP)AboutDlgProc,
                          (HMODULE)NULL,
                          IDM_WATCHABOUTDLG,
                          NULL);
                break;
           case IDM_CLIENTINSTALL:
                if (hwndHelpInstance)
                    WinSendMsg(hwndHelpInstance,
                               HM_DISPLAY_HELP,
                               MPFROMP((MPARAM)IDM_CLIENTINSTALL_ALT),
                               MPFROMSHORT((SHORT)HM_RESOURCEID));
                break;
           case IDM_WATCHHELPFORHELP:
                if (hwndHelpInstance)
                    WinSendMsg(hwndHelpInstance,
                               HM_DISPLAY_HELP,
                               0L,
                               0L);
                break;
           default:
                return WinDefWindowProc(hwnd, msg, mp1, mp2);
                break;
         }
         break;
    case WM_PAINT:
         WatchPaint(hwnd);
         break;
    case WM_ERASEBACKGROUND:
         return(TRUE);
         break;
    case WM_CLOSE:
         WinPostMsg(hwnd, WATCH_PREPARE_SHUTDOWN, 0L, 0L);
         break;
    case WATCH_REQUEST_HANDLE:
         WinPostMsg(HWNDFROMMP(mp1),
                    WATCH_RECEIVE_HANDLE,
                    MPFROMHWND(hwnd),
                    0L);
         break;
    case WATCH_REQUEST_ACTION:
         szSelectorString[80] = '\0';
         WinSendMsg(hwndMainList,
                    LM_INSERTITEM,
                    (MPARAM)-1L,
                    (MPARAM)(PCH)szSelectorString);
         WinSendMsg(hwndMainList,
                    LM_SELECTITEM,
                    (MPARAM)(iNumberInList - 1),
                    (MPARAM)FALSE);
         WinSendMsg(hwndMainList,
                    LM_SELECTITEM,
                    (MPARAM)iNumberInList++,
                    (MPARAM)TRUE);
         WinSendMsg(hwndMainList,
                    LM_SETTOPINDEX,
                    (MPARAM)(iNumberInList - 1),
                    (MPARAM)TRUE);
         if (fLogFileOpen)
            {
              szSelectorString[80] = '\0';
              WriteLogFileEntry(szSelectorString);
            }
         ClearSelector(szSelectorString);
         break;
    case WATCH_PREPARE_SHUTDOWN:
         DosCloseSem(hSysSem);
         if (DosCreateSem(CSEM_PUBLIC,
                          &hSysSem,
                          WATCH_SEMAPHORE))
            {
              DosBeep(300, 300);
              WinMessageBox(HWND_DESKTOP,
                            hwnd,
                            (PCH)"Cannot Shut Down while Clients remain Attached !",
                            (PCH)&szTitle,
                            NULL,
                            MB_OK | MB_ICONEXCLAMATION);
              DosOpenSem(&hSysSem, WATCH_SEMAPHORE);
            }
         else
            {
              DosFreeSeg(usSelector);
              if (fLogFileOpen)
                 {
                   DosBufReset(pLogFile);
                   DosClose(pLogFile);
                 }
              for (iSoundGen = 12; iSoundGen > 0; iSoundGen--)
                  DosBeep(((iSoundGen - 1) * 100), 1);
              WinPostMsg(hwnd, WM_QUIT, 0L, 0L);
            }
         DosSaveConfiguration(hwndParentFrm); 
         break;
    case HM_QUERY_KEYS_HELP:
         return((MRESULT)IDM_WATCHKEYSHELP_ALT);
         break;
    case HM_ERROR:
         if ((hwndHelpInstance && (ULONG)mp1) == HMERR_NO_MEMORY)
            {
              WinMessageBox(HWND_DESKTOP,
                            HWND_DESKTOP,
                            (PSZ)"Help Terminated due to Memory Allocation Error!",
                            (PSZ)"Help Aborted",
                            1,
                            MB_OK | MB_APPLMODAL | MB_MOVEABLE);
              WinDestroyHelpInstance(hwndHelpInstance);
              break;
            }
         break;
    default:
         return WinDefWindowProc(hwnd, msg, mp1, mp2);
         break;
  }
  return FALSE;
}



// WINDOW PAINT PROCEDURE...
void far PASCAL WatchPaint(HWND hwnd)
{
  HPS    hps;
  RECTL  rectl;

  // IF THIS IS THE FIRST TIME THIS ROUTINE IS CALLED, SET UP THE
  // LISTBOX USED FOR LOGGING MAIN DISPLAY OF MESSAGES...
  if (fFirstPass)
     {
       WinQueryWindowRect(hwnd, &rectl);
       WinSetWindowPos(hwndMainList,
                       HWND_TOP,
                       (SHORT)(rectl.xLeft),
                       (SHORT)(rectl.yBottom),
                       (SHORT)(rectl.xRight),
                       (SHORT)(rectl.yTop),
                       SWP_SIZE | SWP_MOVE | SWP_SHOW);
       ClearMainList(hwndMainList);
       fFirstPass = FALSE;
     }

  // PAINT THE WINDOW AND LISTBOX...
  hps = WinBeginPaint(hwnd, (HPS)NULL, (PWRECT)NULL);
  GpiErase(hps);
  WinEndPaint(hps);
}



// CLEAR MAIN LIST BOX PROCEDURE...
void far PASCAL ClearMainList(HWND hwndListBox)
{
  iNumberInList = 0;

  // DELETE ALL ITEMS CURRENTLY IN THE LIST BUFFER...
  WinSendMsg(hwndListBox,
             LM_DELETEALL,
             (MPARAM)-1L,
             (MPARAM)0L);

  // ADD THE BEGINNING OF LOG ITEM AS THE SOLE LISTBOX ITEM AND 
  // SELECT IT...
  WinSendMsg(hwndListBox,
             LM_INSERTITEM,
             (MPARAM)-1L,
             (MPARAM)(PCH)"Beginning of Log...");
  WinSendMsg(hwndListBox,
             LM_SELECTITEM,
             (MPARAM)iNumberInList++,
             (MPARAM)TRUE);
}




// CLEAR SELECTOR STRING PROCEDURE...
static VOID ClearSelector(PSZ szSelectorString)
{
  int iSelectorIndex;

  for (iSelectorIndex = 0; iSelectorIndex < 80; iSelectorIndex++)
       szSelectorString[iSelectorIndex] = ' ';
}



// DIALOG PROCESSING PROCEDURE FOR THE ABOUT DIALOG...
MRESULT EXPENTRY AboutDlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
  switch(msg)
  {
    case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
           case DID_OK:
           case IDM_WATCHABOUT_OK:
                WinDismissDlg(hwnd, TRUE);
                break;
           default:
                return(FALSE);
                break;
         }
    default:
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
  }
  return(FALSE);
}



// DIALOG PROCESSING FOR THE LOG FILE DIALOG...
MRESULT EXPENTRY LogFileDlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
  switch(msg)
  {
    case WM_INITDLG:
         // SAVE THE PREVIOUS FILE SPECIFICATION FOR POSSIBLE RESTORE...
         strncpy(szLogFileHold, szLogFileSpec, 255);

         //SETUP THE INITIAL FILE SPECIFICATION GOING INTO THE DIALOG...
         WinSendDlgItemMsg(hwnd,
                           IDM_WATCHLOGFILENAME,
                           EM_SETTEXTLIMIT,
                           MPFROMSHORT(254),
                           (MPARAM)NULL);
         WinSetDlgItemText(hwnd,
                           IDM_WATCHLOGFILENAME,
                           (PSZ)szLogFileSpec);
         break;
    case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
           case IDM_WATCHLOGFILE_OK:
                if (!OpenLogFile(hwnd))
                   WinMessageBox(HWND_DESKTOP,
                                 hwnd,
                                 (PCH)"DOS File Error encountered, File Not Opened......",
                                 (PCH)"Dos File Error!",
                                 NULL,
                                 MB_OK | MB_ICONEXCLAMATION);
                else
                   WinDismissDlg(hwnd, TRUE);
                break;

           // IF CANCEL IS SELECTED, RESTORE THE FILE NAME TO IT'S CONTENT
           // TO WHAT IS WAS BEFORE CHOOSING THE OPEN LOG FILE OPTION FROM
           // THE MENU AND RELEASE THE DIALOG...
           case IDM_WATCHLOGFILE_CANCEL:
                strncpy(szLogFileSpec, szLogFileHold, 255);
                WinDismissDlg(hwnd, TRUE);
                break;
         }
         break;
    default:
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
  }
  return FALSE;
}



// OPEN DOS LOGGING FILE...
BOOL OpenLogFile(HWND hwnd)
{
  MENUITEM miTemp;
  HWND     hwndMenu;
  int      iNumberOfListItems = 1;
  SHORT    sItemID;
  ULONG    ulEndOfFilePointer;
  ULONG    ulBegOfFilePointer;
  ULONG    ulRecords;
  ULONG    ulCurrentRecord;
  USHORT   usBytesRead;

  // GET THE LOG FILE NAME FROM THE DIALOG ID...
  WinQueryDlgItemText(hwnd,
                      IDM_WATCHLOGFILENAME,
                      (USHORT)254,
                      (PSZ)&szLogFileSpec);

  // ATTEMPT TO OPEN THE APPROPRIATE FILE...
  if (DosOpen((PSZ)szLogFileSpec,
              &pLogFile,
              &usFileAction,
              0L,
              0,
              0x11,
              0x42,
              0L))
      return FALSE;
  fLogFileOpen = TRUE;
  // WE ARE NOW SUCCESSFULLY OPEN...
  ClearMainList(hwndMainList);
  ClearSelector(szSelectorString);
  // IF FILE ALREADY EXISTED, READ THE CURRENT INFORMATION AND PLACE
  // INTO LIST BOX...
  DosChgFilePtr(pLogFile,
                0L,
                (USHORT)2,
                &ulEndOfFilePointer);
  if (ulEndOfFilePointer != 0)
     {
     ClearMainList(hwndMainList);
     DosChgFilePtr(pLogFile,
                   0L,
                   (USHORT)0,
                   &ulBegOfFilePointer);
     ulRecords = ulEndOfFilePointer / (ULONG)82;
     for (ulCurrentRecord = 1; ulCurrentRecord <= ulRecords; ulCurrentRecord++)
         {
         // READ A SINGLE MESSAGE...
         DosRead(pLogFile,
                 (char far *)szSelectorString,
                 (USHORT)80,
                 &usBytesRead);
         // ENSURE THE MESSAGE STRING IS NULL TERMINATED AND ADD THE 
         // MESSAGE STRING AS AN ITEM IN THE LIST BOX...
         szSelectorString[80] = '\0';
         WinSendMsg(hwndMainList,
                    LM_INSERTITEM,
                    (MPARAM)-1L,
                    (MPARAM)(PCH)szSelectorString);
         WinSendMsg(hwndMainList,
                    LM_SELECTITEM,
                    (MPARAM)(iNumberInList - 1),
                    (MPARAM)FALSE);
         WinSendMsg(hwndMainList,
                    LM_SELECTITEM,
                    (MPARAM)iNumberInList++,
                    (MPARAM)TRUE);
         WinSendMsg(hwndMainList,
                    LM_SETTOPINDEX,
                    (MPARAM)(iNumberInList - 1),
                    (MPARAM)TRUE);
         // READ THE CARRIAGE RETURN AND LINE FEED TO ESTABLISH PROPER
         // POSITION FOR NEXT MESSAGE...
         DosRead(pLogFile,
                 (char far *)szSelectorString,
                 (USHORT)2,
                 &usBytesRead);
         }
     }
  
  ClearSelector(szSelectorString);

  // ESTABLISH ADDRESSABILITY TO THE OPTIONS MENU SO IT CAN BE MODIFIED...
  hwndMenu = WinWindowFromID(hwndParentFrm, FID_MENU);
  WinSendMsg(hwndMenu,
             MM_QUERYITEM,
             MPFROM2SHORT(IDM_WATCHOPTIONS, FALSE),
             MPFROMP((PSZ)&miTemp));
  hwndMenu = miTemp.hwndSubMenu;
  sItemID  = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(1),
                               (MPARAM)NULL);

  // RESET THE TEXT OF THE OPEN LOG FILE MENU TO READ CLOSE INSTEAD...
  WinSendMsg(hwndMenu,
             MM_SETITEMTEXT,
             MPFROMSHORT(sItemID),
             (MPARAM)(PSZ)&szFileStrClose);

  // ESTABLISH ADDRESSABILITY AND RESET THE ATTRIBUTES OF THE TRUNCATE OPTION...
  sItemID  = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(2),
                               (MPARAM)NULL);
  WinSendMsg(hwndMenu,
             MM_SETITEMATTR,
             MPFROM2SHORT(sItemID, FALSE),
             MPFROM2SHORT(MIA_DISABLED, !MIA_DISABLED));

  return TRUE;
}


// WRITE THE LOG MESSAGE RECEIVED FROM THE CLIENT APPLICATION TO THE
// DOS LOGGING FILE...
VOID WriteLogFileEntry(PSZ szSelectorString)
{
  // ENSURE THE MESSAGE STRING IS NULL TERMINATED...
  szSelectorString[80] = '\0';

  // WRITE THE ACTUAL STRING TO THE FILE...
  DosWrite(pLogFile,
           (char far *)szSelectorString,
           (USHORT)80,
           &usBytesWritten);

  // ADD A CARRIAGE RETURN AND LINE FEED TO THE DATA WRITTEN...
  DosWrite(pLogFile,
           (char far *)"\r\n",
           (USHORT)2,
           &usBytesWritten);
  return;
}




// CLOSE DOS LOGGING FILE...
VOID CloseLogFile(HWND hwnd)
{
  MENUITEM miTemp;
  HWND     hwndMenu;
  SHORT    sItemID;

  // FLUSH THE FILE BUFFERS, CLOSE THE FILE, AND SET THE FLAG TO
  // INDICATE THAT NO LOGGING FILE IS CURRENTLY OPEN...
  DosBufReset(pLogFile);
  DosClose(pLogFile);
  fLogFileOpen = FALSE;

  // ESTABLISH ADDRESSABILITY TO THE OPTIONS MENU SO IT CAN BE MODIFIED...
  hwndMenu = WinWindowFromID(hwndParentFrm, FID_MENU);
  WinSendMsg(hwndMenu,
             MM_QUERYITEM,
             MPFROM2SHORT(IDM_WATCHOPTIONS, FALSE),
             MPFROMP((PSZ)&miTemp));
  hwndMenu = miTemp.hwndSubMenu;
  sItemID  = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(1),
                               (MPARAM)NULL);

  // RESET THE TEXT OF THE CLOSE LOG FILE MENU TO READ OPEN INSTEAD...
  WinSendMsg(hwndMenu,
             MM_SETITEMTEXT,
             MPFROMSHORT(sItemID),
             (MPARAM)(PSZ)&szFileStrOpen);

  // ESTABLISH ADDRESSABILITY AND RESET THE ATTRIBUTES OF THE TRUNCATE OPTION...
  sItemID  = (SHORT)WinSendMsg(hwndMenu,
                               MM_ITEMIDFROMPOSITION,
                               MPFROMSHORT(2),
                               (MPARAM)NULL);
  WinSendMsg(hwndMenu,
             MM_SETITEMATTR,
             MPFROM2SHORT(sItemID, FALSE),
             MPFROM2SHORT(MIA_DISABLED, MIA_DISABLED));

  return;
}


// SAVE THE CURRENT POSITION OF THE PARENT FRAME AND THE CURRENT LOG
// FILE NAME... 
VOID DosSaveConfiguration(HWND hwnd)
{
  USHORT usBytesWritten;

  WinQueryWindowPos(hwnd, &swp);
  DosOpen((PSZ)szCfgFileSpec,
          &pCfgFile,
          &usFileAction,
          0L,
          0,
          0x12,
          0x41,
          0L);
  DosWrite(pCfgFile,
           &swp.x,
           2,
           &usBytesWritten);
  DosWrite(pCfgFile,
           &swp.y,
           2,
           &usBytesWritten);
  DosWrite(pCfgFile,
           &szLogFileSpec,
           255,
           &usBytesWritten);
  DosClose(pCfgFile);
  return;
}


// INITIALIZE THE WINDOW POSITION AND THE FILE NAME LAST USED...
VOID DosRestoreConfiguration()
{
  USHORT usBytesRead;

  if (DosOpen((PSZ)szCfgFileSpec,
               &pCfgFile,
               &usFileAction,
               0L,
               0,
               0x01,
               0x40,
               0L))
     {
     swp.x = 10;
     swp.y = 10;
     return;
     }
  DosRead(pCfgFile,
          &swp.x,
          2,
          &usBytesRead);
  DosRead(pCfgFile,
          &swp.y,
          2,
          &usBytesRead);
  DosRead(pCfgFile,
          &szLogFileSpec,
          255,
          &usBytesRead);
  return;
}

// END OF WATCH.C

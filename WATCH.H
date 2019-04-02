#define IDM_WATCHMAIN                    1
#define IDM_WATCHLIST                    2

#define IDM_WATCHOPTIONS                 5

#define IDM_WATCHCLEARMSGAREA            6

#define IDM_WATCHLOGTOFILE               7
#define IDM_WATCHLOGFILEDLG              8
#define IDM_WATCHLOGHEAD                 9
#define IDM_WATCHLOGFILENAME             10
#define IDM_WATCHLOGFILE_OK              11
#define IDM_WATCHLOGFILE_CANCEL          12 
#define IDM_WATCHLOGFILE_HELP            13

#define IDM_WATCHTRUNCATEFILE            15

#define IDM_WATCHCHANGEFONT              16

#define IDM_WATCHEXITMENU                17
#define IDM_WATCHEXIT                    18
#define IDM_WATCHRESUME                  19

#define IDM_WATCHHELP                    20
#define IDM_WATCHHELPFORHELP             21
#define IDM_WATCHEXTENDEDHELP            22
#define IDM_WATCHKEYSHELP                23
#define IDM_WATCHKEYSHELP_ALT            24
#define IDM_WATCHHELPINDEX               25
#define IDM_WATCHABOUT                   26
#define IDM_WATCHABOUTDLG                27
#define IDM_WATCHABOUT_TITLE             28
#define IDM_WATCHABOUT_VERSION           29
#define IDM_WATCHABOUT_FRAME             30
#define IDM_WATCHABOUT_COPYRIGHT         31
#define IDM_WATCHABOUT_BY                32
#define IDM_WATCHABOUT_AUTHOR            33
#define IDM_WATCHABOUT_OK                34
#define IDM_WATCHABOUT_HELP              35
#define IDM_WATCHABOUT_STREET            36
#define IDM_WATCHABOUT_TOWN              37

#define IDM_CLIENTINSTALL                40
#define IDM_CLIENTINSTALL_ALT            41

#define IDM_WATCHHELPTABLE               50
#define IDM_WATCHMAINSUBTABLE            51
#define IDM_WATCHLOGFILESUBTABLE         52
#define IDM_WATCHHELPSUBTABLE            53
#define IDM_WATCHABOUTSUBTABLE           54

#define IDM_WATCHPRINT                   60

#define IDM_WATCHSELECTPRINTER           70

#define IDH_WATCHMAIN                    IDM_WATCHMAIN
#define IDH_WATCHLIST                    IDM_WATCHLIST

#define IDH_WATCHOPTIONS                 IDM_WATCHOPTIONS
#define IDH_WATCHCLEARMSGAREA            IDM_WATCHCLEARMSGAREA

#define IDH_WATCHLOGTOFILE               IDM_WATCHLOGTOFILE
#define IDH_WATCHLOGFILEDLG              IDM_WATCHFILEDLG
#define IDH_WATCHLOGHEAD                 IDM_WATCHLOGHEAD
#define IDH_WATCHLOGFILENAME             IDM_WATCHLOGFILENAME
#define IDH_WATCHLOGFILE_OK              IDM_WATCHLOGFILE_OK
#define IDH_WATCHLOGFILE_CANCEL          IDM_WATCHLOGFILE_CANCEL
#define IDH_WATCHLOGFILE_HELP            IDM_WATCHLOGFILE_HELP

#define IDH_WATCHTRUNCATEFILE            IDM_WATCHTRUNCATEFILE

#define IDH_WATCHEXITMENU                IDM_WATCHEXITMENU
#define IDH_WATCHEXIT                    IDM_WATCHEXIT
#define IDH_WATCHRESUME                  IDM_WATCHRESUME

#define IDH_WATCHHELP                    IDM_WATCHHELP
#define IDH_WATCHHELPFORHELP             IDM_WATCHHELPFORHELP
#define IDH_WATCHEXTENDEDHELP            IDM_WATCHEXTENDEDHELP
#define IDH_WATCHKEYSHELP                IDM_WATCHKEYSHELP
#define IDH_WATCHKEYSHELP_ALT            IDM_WATCHKEYSHELP_ALT
#define IDH_WATCHHELPINDEX               IDM_WATCHHELPINDEX
#define IDH_WATCHABOUT                   IDM_WATCHABOUT
#define IDH_WATCHABOUTDLG                IDM_WATCHABOUTDLG
#define IDH_WATCHABOUT_TITLE             IDM_WATCHABOUT_TITLE
#define IDH_WATCHABOUT_VERSION           IDM_WATCHABOUT_VERSION
#define IDH_WATCHABOUT_FRAME             IDM_WATCHABOUT_FRAME
#define IDH_WATCHABOUT_COPYRIGHT         IDM_WATCHABOUT_COPYRIGHT
#define IDH_WATCHABOUT_BY                IDM_WATCHABOUT_BY
#define IDH_WATCHABOUT_AUTHOR            IDM_WATCHABOUT_AUTHOR
#define IDH_WATCHABOUT_OK                IDM_WATCHABOUT_OK
#define IDH_WATCHABOUT_HELP              IDM_WATCHABOUT_HELP

#define IDH_CLIENTINSTALL                IDM_CLIENTINSTALL
#define IDH_CLIENTINSTALL_ALT            IDM_CLIENTINSTALL_ALT

// SETUP USER DEFINED COMMAND MESSAGES...
#define WATCH_REQUEST_HANDLE        WM_USER+501
#define WATCH_RECEIVE_HANDLE        WM_USER+502
#define WATCH_REQUEST_ACTION        WM_USER+503
#define WATCH_PREPARE_SHUTDOWN      WM_USER+504

#define WATCH_SEGMENT               "\\SHAREMEM\\WATCH.SEG"
#define WATCH_SEMAPHORE             "\\SEM\\WATCH.SEM"

// DEFINE INCLUDES FOR THE APPLICATION BEING DEBUGGED...
#define WATCHVARIABLES                    \
unsigned short     sWatchSelector;        \
HSYSSEM            hWatchSysSem;          \
BOOL               fWatchConnected;       \
char far *         szSelectorString;      \
HWND               hwndWatchWnd;

#define WATCHHELLO                                 \
WinBroadcastMsg(hwnd,                              \
                WATCH_REQUEST_HANDLE,              \
                MPFROMHWND(hwnd),                  \
                0L,                                \
                BMSG_FRAMEONLY | BMSG_POSTQUEUE);

#define WATCHATTACH                                      \
case WATCH_RECEIVE_HANDLE:                               \
     if (fWatchConnected)                                \
         break;                                          \
     hwndWatchWnd = HWNDFROMMP(mp1);                     \
     fWatchConnected = 1;                                \
     if (DosGetShrSeg(WATCH_SEGMENT, &sWatchSelector))   \
         fWatchConnected = 0;                            \
     if (DosOpenSem(&hWatchSysSem, WATCH_SEMAPHORE))     \
         fWatchConnected = 0;                            \
     break;


#define WATCHPOST(s)                                                          \
if (fWatchConnected)                                                       \
   {                                                                       \
     DosSemRequest(hWatchSysSem, -1L);                                     \
     szSelectorString = (char far *)((unsigned long)sWatchSelector << 16); \
     strncpy((char far *)szSelectorString, (char far *)s, 80);             \
     szSelectorString[80] = '\0';                                          \
     WinSendMsg(hwndWatchWnd, WATCH_REQUEST_ACTION, 0L, 0L);               \
     DosSemClear(hWatchSysSem);                                            \
   } 



#define EXTERNWATCHVARIABLES                      \
extern unsigned short      sWatchSelector;        \
extern HSYSSEM             hWatchSysSem;          \
extern BOOL                fWatchConnected;       \
extern char far *          szSelectorString;      \
extern HWND                hwndWatchWnd;

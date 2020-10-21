#include "input.h"

int last_ch;

FrameInfo input(FrameInfo last_frame) {
    last_ch = getch();
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
    if ((last_ch >= '0' && last_ch <= '9') ||
            (last_ch >= KEY_DOWN && last_ch <= KEY_RIGHT) ||
            last_ch == 'g')
        return {kAction, last_frame.input_context};
    if (last_ch == '>') return {kFloorDown, last_frame.input_context};
    if (last_ch == '<') return {kFloorUp, last_frame.input_context};
    if (last_ch == 'i') return {kMenuOpen, kMenu};
    return {kNone, last_frame.input_context};
}

int GetLastCh() {
    return last_ch;
}

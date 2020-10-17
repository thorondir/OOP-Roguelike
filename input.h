#ifndef INPUT_H_
#define INPUT_H_

#include <ncurses.h>

enum InputType {
    kNone,
    kAction,
    kMenuOpen,
};

enum InputContext {
    kMain,
    kMenu,
    kSelection,
    kAbort
};

struct FrameInfo {
    InputType input_type;
    InputContext input_context;
};

extern FrameInfo input(FrameInfo);
extern int GetLastCh();

#endif

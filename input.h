#ifndef INPUT_H_
#define INPUT_H_

#include <ncurses.h>

// struct for the types of possible inputs
enum InputType {
    kNone,
    kAction,
    kFloorDown,
    kFloorUp,
    kMenuOpen,
};

// struct containing the possible places where input can happen
enum InputContext {
    kMain,
    kMenu,
    kSelection,
    kAbort
};

// struct containing a context and input type
struct FrameInfo {
    InputType input_type;
    InputContext input_context;
};

extern FrameInfo input(FrameInfo);
extern int GetLastCh();

#endif

# Switch focus between editor and integrated terminal in Visual Studio Code
https://stackoverflow.com/questions/42796887/switch-focus-between-editor-and-integrated-terminal-in-visual-studio-code

CMD-SHIFT-P -> Preferences: Open Keyboard Shortcuts File and add these entries:
```json
// Toggle between terminal and editor focus
{ "key": "ctrl+`", "command": "workbench.action.terminal.focus"},
{ "key": "ctrl+`", "command": "workbench.action.focusActiveEditorGroup", "when": "terminalFocus"}
```
# Integers
```cpp
short // -37767..32767
signed char // -127..127
unsigned short // 0..65356
unsigned char // 0..255
```

# Vector<T> API
```cpp
v.back(); // return last element
v.pop_back(); // remove last element and return void
v.clear(); // removes all elements from the vector
```

# Multi-Cursor Editing in Visual Studio Code
## Basic selections
* CTRL-ALT-{UP,DOWN}:      Select next/previous line
* ALT-CLICK:               Create cursors
* CTRL-U:                  Undo last cursor operation
* CTRL-SHIFT-L:            Select current match
* CTRL-F2:                 Select current word
* SHIFT-ALT-{RIGHT, LEFT}: Expand/shrink selection

## Rectangular Selections
* SHIFT-ALT-Drag:        Create rectangular selection **by mouse**
* SHIFT-ALT-CTRL-Arrows: Create rectangular selection **by keyboard**

## Other shortcuts
* CTRL-L: Select entire line
* CTRL-{RIGHT, LEFT} : Select to word boundary
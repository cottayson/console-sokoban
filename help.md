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
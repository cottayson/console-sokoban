# Cmake
https://stackoverflow.com/questions/43413717/compile-cmake-based-project-with-mingw
* get list of generators
$ cmake -G

* select generator
$ cmake -G "MinGW Makefiles"

# using NMake
...

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
signed char // -127..127      (1 byte)
unsigned char // 0..2^8 - 1   (1 byte)
short // -37767..32767        (2 bytes)
unsigned short // 0..2^16 - 1 (2 bytes)
```

# Vector<T> API
```cpp
v.back(); // return last element
v.pop_back(); // remove last element and return void
v.clear(); // removes all elements from the vector
```
## Deque
```cpp
  deque<short> q;
  q.push_back(1);
  q.push_back(2);
  q.push_back(3);
  cout << q.size() << endl; // 3
  deque<short>::iterator it = q.begin(); // q.end() == q.begin() + q.size()
  q.insert(it, 100); // <=> q.insert(it, amount=1, value=100); , it += amount
  // 100 1 2 3
  for (short elem : q) {
    cout << elem << " ";
  }
  cout << endl;
  it--;
  q.insert(it, 5, 3);
  // 3 3 3 3 3 100 1 2 3
  for (deque<short>::iterator it = q.begin(); it != q.end(); ++it) {
    cout << *it << " ";
  } 
  cout << endl;
```

## Tuple
```cpp
  std::tuple<int, char> foo(100, 'h');
  std::cout << std::get<0>(foo); << std::endl; // 100
  std::cout << std::get<1>(foo); << std::endl; // h
  auto bar = std::make_tuple("test", 3.1, 14, 'y');
  std::get<2>(bar); // 14
  int ivalue; char cvalue;
  std::tie(ivalue, cvalue) = foo; // ivalue = 100, cvalue = 'h'
```

## String
```cpp
  // concat two strings
  string s1 = "hello";
  string s2 = " world";
  string s3 = "!!!";
  cout << s1 + s2 << endl; // hello world
  s1.insert(s1.size(), s2);
  cout << s1 << endl;      // hello world
  s1.insert(s1.end(), 3, (char)'.');
  cout << s1 << endl;      // hello world...
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
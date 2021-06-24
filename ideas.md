# Ideas how to effectively solve level:
## Divide and conquer
We know that only two ways exists for moving this block from that area:
```text
"....#2##"
"##### # "
"###   # "
"## $  # "
"1 $ $## "
"##   #  "
"######  "
```
This can be generalized:
Rewind until the condition is met (while condition)
Example condition: The block is in passage number N (at position (x, y))

# Ideas how to effectively generate human-like level:
* Given goals and wall but initial positions of blocks are unknown
  (Like in older software for generating levels of sokoban)
* Given blocks positions but walls are unknown

# Loading levels from file
```txt
  example of reading arbitrary list of levels:
     ###  -- begin of level 1
  #### ##
  #@$.  #
  # ### #
  ### ### -- end of level 1
  ### ## -- wrong level
    ##### ###
  ###   ### ###
  #           #
  ##  ####    #
   ####  ####  -- wrong level
    ##### ###  -- begin of level 2
  ###   ### ###
  #           #
  ##  ####    #
   ####  ###### -- end of level 2
```

## Properties of sokoban level representation:
1. number of empty goals == number of free blocks
2. have exactly one player character `@` or `+`
3. walls topologically bounded
  ```txt
  ####
  #    -- have hole => walls not bounded
  ####
  ```
4. have exactly one (*connected component*)[https://en.wikipedia.org/wiki/Component_(graph_theory)]
  examples of wrong level with two components (constructed by connecting not_walls):
  ```txt
  ###########
  #.$ # @$. # -- this level can't be solved
  ###########

  ###########
  # * # @$. # -- this level can be solved but have two components of not_walls
  ###########
  ```
5. level line contains >= 2 '#' symbols

## Testing ideas:
* ```cmd
  compile && build\main | more
  ```

* catch2 framework
* model states and actions:
  * verify state basically
  * verify state assiming that it created from another already verified state by sequence of actions

## State colors
`U` - utility function, `U(position)` corresponds to optimality of current position, `good` or `bad`
* Red state1 - wrong branch -> no way to complete level
* Orange state1 - U(s) <= U(state1), where s in set_of_neighbors(state1)
* Yellow state:
  1. Yellow state1 - exists such state s: U(s) > U(state1), where s in set_of_neighbors(state1)
  or another more simple variant
  2. Yellow state1 - exists some yellow neighbour state
* Green state1 - exists some green neighbour state

### Colored interface + modes
* In free mode: User can mark states with colors and this helps to memorize some bad states. 
* In strict proof mode: User must prove that some branches are have red color.

# TODO
```cpp
  levels[3].movePlayerByDiff(1, 0);
  levels[3].movePlayerByDiff(0, 1);
  std::cout << levels[3].toString() << std::endl;

  gameLoop(levels[3]);
  
   blocks ordered from left to right, up to down like letters
  "  ####  "
  "  #++#  "
  " ##@+## "
  " #@@1.# "
  "##@2  ##"
  "#@@#34@#"
  "#@@@@@@#"
  "########"; @ - indicates player position class (if cost of move = 0)
  numberOfDistinctPushes = {
    block 1: [R, D]  -- 2
    block 2: [R]     -- 1
    block 3: [U]     -- 1
    block 4: [U]     -- 1
  } => all_possible_pushes.size() == 5
  

  // TODO: calculate number of possible pushes in current player position class
  // number of pushes in this start position = 

  gameLoop(f, startString);
```
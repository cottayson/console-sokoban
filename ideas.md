# Ideas how to effectively solve level:
## Divide and conquer
We know that only two ways exists for moving this block from that area:
```cpp
"....#2##"
"##### # "
"###   # "
"## $  # "
"1 $ $## "
"##   #  "
"######  "
```
Это можно обобщить:
Перемотка до выполнения условия (while условие)
Пример условия: ящик находится в проходе номер N (в позиции (x, y))

# Ideas how to effectively generate human-like level:
* Given goals and wall but initial positions of blocks are unknown
  (Like in older software for genering levels of sokoban)
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
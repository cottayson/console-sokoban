void createPointerOfBoardClass() {
  Board<ushort> f(9, 9);
  std::string startString = 
  "#####    "
  "#   #    "
  "# $@# ###"
  "# $$# #.#"
  "### ###.#"
  " ##    .#"
  " #   #  #"
  " #   ####"
  " #####   ";

  Board<ushort>* g; // create a pointer to Board class
  g = &f; // set g to link of f
  vector<Board<ushort>*> stack;
  stack.push_back(g);
  g->loadFromString(startString);
  cout << g->toString() << endl;
  cout << stack[0]->toString() << endl;
}
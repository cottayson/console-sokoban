#ifndef OTHER
#define OTHER

// https://stackoverflow.com/questions/2732978/c-how-to-declare-a-struct-in-a-header-file
struct Point {
  int x = 0;
  int y = 0;
};
// to avoid error undefined reference to `void show<int>(int const&)'
// I include this template in header
// see: https://stackoverflow.com/questions/10632251/undefined-reference-to-template-function
// https://docs.microsoft.com/en-us/cpp/cpp/source-code-organization-cpp-templates?view=msvc-160#the-inclusion-model
template<typename T>
void show(T const& x) {
  std::cout << x << std::endl;
}

/* hello
 * 
 *
 */
void showPoint(Point&);
double getLength(Point&);

#endif
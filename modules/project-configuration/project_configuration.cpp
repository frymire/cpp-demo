
#include <iostream>

/*
    The Visual Studio Solution Explorer view uses filters by default. To see the actual file
    structure, click the "Show All Files" button. Note that this button is set separately for
    each project. You can also click the "Solutions and Folders" buttons to toggle to the file
    structure, but this does not give access to the solution and project properties when you right
    click them.

    Visual Studio outputs intermediate files to $(ProjectDirectory)\$(Configuration). To change this,
    you might do something like this:
      Project Properties -> General -> Output Directory -> "$(SolutionDir)bin\$(Configuration)\"
      Project Properties -> General -> Intermediate Directory -> "$(SolutionDir)bin\intermediates\$(Configuration)\$(ProjectName)\"
    Note that $(SolutionDir) includes a backslash at the end, since it's a directory, so there's no extra '\' before bin.
    You might also include $(Platform) in the path, if you're doing x64 and x32.
 */
int main() {
  std::cout << "Hello cruel world. :\\\n";
}

# renesas_assignment

Project Requirements:

Create a Qt application to render digital signals satisfying the following:
-Functional requirements:
-Provide the following basic feature set:
-Import data files formatted as described below.
-Render the data on a widget. Please use the attached UI prototype for reference.
-[Optional feature, desirable] Provide a zoom feature for the rendering widget.
-Dataset size: 300k points or more. Please note that such an amount of data is tricky to repaint each time, so please consider
a more effective solution.

Input File Format:
TIMESTEP;100; // time delta
UNITS;ns; // time units
... // arbitrary amount of lines with additional info
DATA; // a keyword that marks the start of a dataset
1; // signal value at 0 nanoseconds
1; // signal value at 100 nanoseconds
0; // signal value at 200 nanoseconds


Non-functional requirements:
-Version control requirements:
	Use git repository.
	Publish the code and share the link with us.
-Development environment and build requirements:
	Use CMake as a build automation tool.
Testing requirements:
	[Optional] Integrate Google test library into the project.
	[Optional] Add a few tests for the most critical part of the application.
Other requirements:
	-Avoid using third-party libraries except for the Qt Framework and GoogleTest.
	-Spend at most 10 hours on the project	
	
![alt text](https://github.com/parisnikf/renesas_assignment/blob/main/renesas_assignment/application_gui.png?raw=true)	
	
Build:
Project has been implemented using QTCreator with Desktop Qt 6.5.1 MinGW 64-bit
CMakeLists.txt has been added.

Issues:
Horizontally scrolling needs improvement to work correctly.

Possible Improvements:
Also for the better performance for a fix size data structure we could use ring/circular buffer.
A progress bar that will show the progress of the file import while at the same time the application paints the current data.
That way the user will know when the import has finished.




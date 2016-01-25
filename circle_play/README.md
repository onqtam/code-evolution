circle play
=======

Given a starting point A and end point B find all paths between them which have K reflections from circles.





by default data/input.txt gets loaded.
	its format is:
	line #
		1: point A
		2: point B
		3: K (number of reflections)
		4: N (number of circles)
		5 - (4 + N): the N circles

- Project file is for Visual Studio 2015.
- Use config.h to enable/disable/tweak parts of the program compile time.
- Todo: kd tree for faster intersection with circles and parallelism (multi-threaded)

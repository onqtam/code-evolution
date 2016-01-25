circle play
=======

Given a starting point A and end point B find all paths between them which have K reflections from circles.




The program by default loads data/input.txt when started - it's format is:

- line 1: point A
- line 2: point B
- line 3: K (number of reflections)
- line 4: N (number of circles)
- line 5 to line 4 + N: the N circles

- Project file is for Visual Studio 2015 and the Release config works out of the box.
- Use config.h to enable/disable/tweak parts of the program compile time.
- Todo: kd tree for faster intersection with circles and parallelism (multi-threaded)

Controls:

- Up/Down - change


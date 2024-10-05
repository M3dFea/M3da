www.m3dfea.com for tutorials and some videos are on youtube.
m3d compiled in Visual Studio 2019. Originally started this in C++4 many years ago, before vector classes were added.
M3d is written with no add-ins or external modules so it can be deployed with no problems I would like it to stay this way. 
m3d has been used in many commercial aerospace projects and this has driven the development. Most of the structures are shell and beam models built by hand and with abstracted geometry.
M3d is driven ,mainly, from the command line with keywords invoking procedures. The menus and icons simply pass the command keyword to the command line.
Each function like "NDCR" node create has a menu class handler which goes into the a command stack to be implemented. All menu classes begin with a z. find the menu class for a particular command and you can trace it back through the code to see how it works.
The main class that embodies everything is the dBASE class. This holds all the objects, the next important object is the mesh object which  can hold every thing to do with a fem. the dBASE object can have many fem objects, you activate the current mesh to work on it or merge them. The base object also holds the geometry.




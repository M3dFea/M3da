fm3d compiled in Vis studio 2019. Originally started this in ç++4 many years ago, before vector classes were added.

m3d has been used in many commercial aerospace projects and this what has driven the development. most of are structure are shell and beam model built by hand and with abstracted geometry.

it was a very deliberate choice to drive the code from command line menu system. the allows basic txt scripts to be pasted in the command line. I did try exposing merhods by API functions but the engineers did not want to get involved with VBA programing.

each function like NDCR node create has a menu class handling to which goes in the command stack robe implemented. All menu classes begin with a z. find the menu for a particular command and you can trace it back through the code to see how it works.

the main class that embodies every thing is the dBASE class. this hold all the objects, the next important object is the mesh object which  can hold every thing to do with a fem. the dBASE object can have many fem objects, you activate the current mesh to work on or merge them. the base object also holds the geometry.

areas that need work
1 iges import.
the iges import was based on the autocad acis engine. this even supports shell and part data structures.

2 need to now stitch surfaces in m3d to create the shell and part data structure which already exist in m3d.

3 tet mesher need some work 

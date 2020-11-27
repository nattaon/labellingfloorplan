# labellingfloorplan
A program for labelling wall segments from a topview floorplan image (generated from [Multi-ply-manipulator](https://github.com/nattaon/Multi-ply-manipulator)).
<a href="url"><img src="https://github.com/nattaon/labellingfloorplan/blob/master/labellingfloorplan_ss.png"  width="500" ></a>

## What it does
- Draw a line label, automatic save .txt for each image.
- Straigh a line horizontal or vertical.
- Connect/Trim 2 lines at the intersection point.
- Generate a black-write label (Menu: Label > Generate label) for training in Unet segmentation.

## Instalation
I use Qt Creator 4.5.2 Based on Qt 5.9.5 (GCC 7.3.0, 64 bit) on Ubuntu 18.04.
Projects Settings:
- Shadow build: ☑
- Build directory: ./build
- Custom Process Step: cmake ..
- Make: make -j12 in /pathtofolder/build
-j12 is the number of cpu cores. We specify the number to increase the speed of the make process. You can check it by typing `nproc` in the command line

## Programing detail
- imageLabel(QLabel) is the main drawing area. I use QPixmap to read an image, QPainter and QPen to draw a line, then call setPixmap() to show the final image. It is nested in QScrollArea for enable image zooming.

Main Functions
- resizeEvent(): enlarge QScrollArea area to fit the program window whwn it changed. adjust QTreeWidget size and position to fill the window height.
- eventFilter(): detect mouse position move(TempMarkPixel(), TempDrawLine() 
and mouse down (SetStartLine(), SetEndLine()) to trigger a label drawing function.
- TempMarkPixel(): show a red dot at the position of mouse over the image area.
- TempDrawLine(): show a red line drawn from the previous click position, to the current (moving) mouse position.
- Once a line was drawn, Add_Line_to_TreeWidget() and Add_Line_to_Textfile() were triggered to keep the line poisiton.
- Add_Line_to_Textfile(): use QTextStream to write a text file contains x1,y1,x2,y2 positions
- Add_Line_to_TreeWidget(): add x1,y1,x2,y2 positions to the widget inorder to manipulate the line later.


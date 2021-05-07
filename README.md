# OpenGL_Teapot

OpenGL model drawing and viewing with Visual C++.  

## Tasks

+ You will create a scene by placing a “Utah Teapot” on a flat surface.
+ You can use *.smf file versions of the Utah Teapot.
+ Read the teapot model file in your code and place it on the surface.
+ You must implement the surface as a flat rectangular shape and place the teapot model on this surface.
  + Make the teapot model rotate in counter clockwise direction around its y-axis crossing across its
center of mass, continuously.
  + Pressing ‘+’ button on keyboard increases the rotation speed of the teapot.
  + Pressing ‘-’ button on keyboard decreases the rotation speed of the teapot
+ You do not need to implement any lighting (so the scene does not need to look as polished as in the figure). Just make sure that the user can distinctly see the teapot and the bunny placed over a surface and they are in different colors. 
+ Place your camera in the scene so that it sees the scene with a similar angle and distance as depicted in the figure above.
+ You will create a controllable camera.
  + Implement the keyboard input so that the user can navigate the camera:
    - “Up Arrow” button: camera moves forward (positive way) along the global z-axis direction.
    - “Down Arrow” button: camera moves backward (negative way) along the global z-axis direction
    - “Right Arrow” button: camera moves to the right (positive way) along the global x-axis direction
    - “Left Arrow” button: camera moves to the left (negative way) along the global x-axis direction
    - “Page Up” button: camera moves to the upward (positive way) along the global y-axis direction
    - “Page Down” button: camera moves to the left (negative way) along the global x-axis direction
  + Implement the mouse input so that the user can rotate the camera anyway s/he likes.
    - Vertical movement of the mouse rotates the camera around its sideways axis.
    - Horizontal movement of the mouse rotates the camera around its y-axis.
    - Also note that mouse cursor should be invisible inside the drawing window.
  + The camera should see the scene using Perspective (fovy, aspect, zNear, zFar) function defined in mat.h of Angel’s codes. 
  + The camera should adapt to resizing of the drawing window, so if the window is made smaller, the teapot and the rectangular surface should become smaller without getting distorted (and vice-versa)

    ![teapot drawing](https://github.com/iremozkal/OpenGL_Teapot/blob/main/Images/img1.PNG?raw=true)

**NOTE**: Implement your homework using OpenGL 3.1 version or higher. All programming assignments must use the shader-based functionality of OpenGL: 1) no immediate mode 2) at least one vertex shader and one fragment shader. Therefore, you should not use any of the deprecated features of the API, e.g. glBegin, glEnd, glVertex3f, glTranslate etc.  


## Solution
+ To read the teapot.smf file, I used Mesh.h. First I created a Mesh object called teapot, then with Load3DModel function, returned the vertex data of the mesh.
+ For surface, I draw a basic rectangle with vertices.  
+ I declare two object, one for teapot, one for surface. With the object info, it will split in two control in one vertex shader. In vertex shader, I have translation and rotation matrices for each object. And I also have scale matrix for teapot. Each one returns a different color. 
+ In initialization of the OpenGL, I loaded the teapot and surface data into vertex buffer object. And sent the uniforms to the program such as model view, projection, theta, and object information. 
+ I kept a rotation direction value for the counter clockwise rotation, and a speed that is initially started with a value.The theta for rotation is changed with the direction *speed. When the speed goes lower than 0, it stops. I tried + instead of *, then it changed the direction. 
+ It won’t change the direction when speed goes negative. And for that, if you want to change the direction of rotation, you can press the “t”button on keyboard.
+ For camera settings with perspective, I changed the “eye” points to be similar with the given figure’s camera location. And for the keyboard inputs, I add to “at” point, an x y value, to change the camera move with keyboard. Fovy is field of view in Y direction angle (inDegree) and aspect is viewport aspect ratio. For projection parameters, I used zNear and zFar.
+ For arrow buttons on the keyboard, I set a new keyboard2 function and used the
GLUT_KEY values.
+ Because of the camera should adapt to resizing of the window; there is a reshape
function that sets the view and calculates aspect with the window’s width and height.
+ And for mouse operations, vertical and horizontal movements of the mouse without a click should make the camera move. But all I can find is a drag and drop kinda mouse operation. So, it’s a missing part. 


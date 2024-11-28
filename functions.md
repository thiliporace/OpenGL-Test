### glfwSwapBuffers(window) <br>
Double buffer. When an application draws in a single buffer the resulting image may 
display flickering issues. This is because the resulting output image is not drawn in an 
instant, but drawn pixel by pixel and usually from left to right and top to bottom. Because 
this image is not displayed at an instant to the user while still being rendered to, the result 
may contain artifacts. To circumvent these issues, windowing applications apply a double
buffer for rendering. The front buffer contains the final output image that is shown at 
the screen, while all the rendering commands draw to the back buffer. As soon as all 
the rendering commands are finished we swap the back buffer to the front buffer so the
image can be displayed without still being rendered to, removing all the aforementioned
artifacts. <br>

### glGenBuffers(1, &VBO) <br>
Vertex buffer objects (VBO) store a large number of vertices in the GPU’s memory. 
The advantage of using those buffer objects is that we can send large batches of data all at once to the graphics 
card, and keep it there if there’s enough memory left, without having to send data one vertex at a time. 
Sending data to the graphics card from the CPU is relatively slow, so wherever we can we try to 
send as much data as possible at once. Once the data is in the graphics card’s memory the vertex shader 
has almost instant access to the vertices making it extremely fast. <br>

### glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW) <br>
glBufferData is a function specifically targeted to copy user-defined data into the currently
bound buffer. Its first argument is the type of the buffer we want to copy data into: the vertex buffer
object currently bound to the GL_ARRAY_BUFFER target. The second argument specifies the size
of the data (in bytes) we want to pass to the buffer; a simple sizeof of the vertex data suffices.
The third parameter is the actual data we want to send.
The fourth parameter specifies how we want the graphics card to manage the given data. This
can take 3 forms: <br>
• GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times. <br>
• GL_STATIC_DRAW: the data is set only once and used many times. <br>
• GL_DYNAMIC_DRAW: the data is changed a lot and used many times. <br>

### shaderProgram = glCreateProgram() <br>
A shader program object is the final linked version of multiple shaders combined. To use the recently
compiled shaders we have to link them to a shader program object and then activate this shader
program when rendering objects. The activated shader program’s shaders will be used when we
issue render calls.
When linking the shaders into a program it links the outputs of each shader to the inputs of the
next shader. This is also where you’ll get linking errors if your outputs and inputs do not match. <br>

### glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0) <br>
• The first parameter specifies which vertex attribute we want to configure. Remember that we
specified the location of the position vertex attribute in the vertex shader with layout
(location = 0). This sets the location of the vertex attribute to 0 and since we want to
pass data to this vertex attribute, we pass in 0. <br>
• The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so
it is composed of 3 values. <br>
• The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL
consists of floating point values). <br>
• The next argument specifies if we want the data to be normalized. If we’re inputting integer
data types (int, byte) and we’ve set this to GL_TRUE, the integer data is normalized to 0 (or
-1 for signed data) and 1 when converted to float. This is not relevant for us so we’ll leave
this at GL_FALSE. <br>
• The fifth argument is known as the stride and tells us the space between consecutive vertex
attributes. Since the next set of position data is located exactly 3 times the size of a float
away we specify that value as the stride. Note that since we know that the array is tightly
packed (there is no space between the next vertex attribute value) we could’ve also specified
the stride as 0 to let OpenGL determine the stride (this only works when values are tightly
packed). Whenever we have more vertex attributes we have to carefully define the spacing
between each vertex attribute but we’ll get to see more examples of that later on. <br>
• The last parameter is of type void* and thus requires that weird cast. This is the offset of
where the position data begins in the buffer. Since the position data is at the start of the data
array this value is just 0. We will explore this parameter in more detail later on. <br>

### glGenVertexArrays(1, &VAO) <br>
A vertex array object (also known as VAO) can be bound just like a vertex buffer object and any
subsequent vertex attribute calls from that point on will be stored inside the VAO. This has the
advantage that when configuring vertex attribute pointers you only have to make those calls once
and whenever we want to draw the object, we can just bind the corresponding VAO. This makes
switching between different vertex data and attribute configurations as easy as binding a different
VAO. All the state we just set is stored inside the VAO. <br>
A vertex array object stores the following:<br>
• Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.<br>
• Vertex attribute configurations via glVertexAttribPointer.<br>
• Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.<br>
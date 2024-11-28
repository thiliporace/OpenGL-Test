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

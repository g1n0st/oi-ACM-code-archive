# -*- coding: utf-8 -*-
import glfw
import OpenGL.GL as gl

import cv2
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import numpy as np
import sys

import imgui
from imgui.integrations.glfw import GlfwRenderer

global capture
capture = None

def matToTexture(mat, minFilter, magFilter, wrapFilter):
    textureID = GLuint()
    glGenTextures(1, textureID)

    # Bind to our texture handle
    glBindTexture(GL_TEXTURE_2D, textureID)


    # Catch silly-mistake texture interpolation method for magnification
    glPixelStoref(GL_UNPACK_ALIGNMENT, 1)
    #Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter)


    # Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter)


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)


    #Set incoming texture format to:
    #GL_BGR       for CV_CAP_OPENNI_BGR_IMAGE,
    #GL_LUMINANCE for CV_CAP_OPENNI_DISPARITY_MAP,
    #Work out other mappings as required ( there's a list in comments in main() )
    #print(GL_RGB)
    inputColourFormat = GL_RGB
    #
    #if (mat.channels() == 1) {
    #   	inputColourFormat = GL_LUMINANCE;
    #}

    #Create the texture
    glTexImage2D(GL_TEXTURE_2D, # Type of texture
	    0, # Pyramid level (for mip-mapping) - 0 is the top level
	    GL_RGB, # Internal colour format to convert to
	    640, # Image width  i.e. 640 for Kinect in standard mode
	    480, # Image height i.e. 480 for Kinect in standard mode
	    0, # Border width in pixels (can either be 1 or 0)
	    inputColourFormat, # Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
	    GL_UNSIGNED_BYTE, # Image data type
	    mat.data); # The actual image data itself
    return textureID

def display():
    global capture
    _,image = capture.read()

    
    image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
    image = cv2.flip(image, 0)
    #you must convert the image to array for glTexImage2D to work
    #maybe there is a faster way that I don't know about yet...

    #print image_arr
    
    # Create Texture
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    glEnable(GL_TEXTURE_2D)

    imageTex = matToTexture(image, GL_LINEAR, GL_LINEAR, GL_CLAMP)
    
    glBindTexture(GL_TEXTURE_2D, imageTex);
    glBegin(GL_POLYGON)
    glTexCoord2f(0, 0)
    glVertex2f(-1, -1)
    glTexCoord2f(1, 0)
    glVertex2f(1, -1)
    glTexCoord2f(1, 1)
    glVertex2f(1, 1)
    glTexCoord2f(0, 1)
    glVertex2f(-1, 1)
    glEnd();

    #Free the texture memory
    glDeleteTextures(1, imageTex)


    glDisable(GL_TEXTURE_2D)
    
def main():
    window = impl_glfw_init()
    impl = GlfwRenderer(window)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        impl.process_inputs()

        
        imgui.new_frame()

        if imgui.begin_main_menu_bar():
            if imgui.begin_menu("File", True):

                clicked_quit, selected_quit = imgui.menu_item(
                    "Quit", 'Cmd+Q', False, True
                )

                if clicked_quit:
                    exit(1)

                imgui.end_menu()
            imgui.end_main_menu_bar()

        imgui.show_test_window()

        imgui.begin("Custom window", True)
        imgui.text("Bar")
        imgui.text_colored("Eggs", 0.2, 1., 0.)
        imgui.end()

        display()

        imgui.render()
        glfw.swap_buffers(window)

    impl.shutdown()
    imgui.shutdown()
    glfw.terminate()


def impl_glfw_init():
    width, height = 1280, 960
    window_name = "minimal ImGui/GLFW3 example"

    if not glfw.init():
        print("Could not initialize OpenGL context")
        exit(1)

    # OS X supports only forward-compatible core profiles from 3.2

    # Create a windowed mode window and its OpenGL context
    window = glfw.create_window(
        int(width), int(height), window_name, None, None
    )
    glfw.make_context_current(window)

    if not window:
        glfw.terminate()
        print("Could not initialize Window")
        exit(1)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    glfw.swap_interval(1)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 3)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 3)
    glfw.window_hint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE)

    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, gl.GL_TRUE)
    
    return window

if __name__ == "__main__":
    #start openCV capturefromCAM
    capture = cv2.VideoCapture(1)
    capture.set(3,640)
    capture.set(4,480)

    main()

#include <iostream>
#include <sstream> // stringstream
#include <chrono> // milliseconds()
#include <thread> // sleep_for()
#include <GLFW/glfw3.h>

using namespace std;

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define SEIZURE_WARNING 0

const char* szTitle = "RefreshRateMultitool, Version 0.20";
volatile bool running = true;
volatile bool toggleFullScreen = false;

void callback_error(int error, const char* description)
{
    cout << "GLFW ERROR: " << description << "\n";
}

/* Process keyboard input.
 * ENTER: toggle windowed / full screen modes.
 * ESCAPE: finish the program.
 *
 * [in] window The window that received the event.
 * [in] key The keyboard key that was pressed or released.
 * [in] scancode The system-specific scancode of the key.
 * [in] action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
 * [in] mods Bit field describing which modifier keys were held down.
 */
void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (GLFW_PRESS != action)
        return;

    switch (key) {
    case GLFW_KEY_ENTER:
        toggleFullScreen = true;
        break;
    case GLFW_KEY_ESCAPE:
        running = false;
        break;
    }
}

/* Update the GL viewport when the screen gets resized.
 *
 * [in] window The window that the user resized.
 * [in] width The new width, in screen coordinates, of the window.
 * [in] height The new height, in screen coordinates, of the window.
 */
void callback_resize(GLFWwindow* window, int width, int height)
{
    //printf("Window size set to %dx%d.\n", width, height);

    glViewport(0, 0, width, height);

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, static_cast<double>(nViewportWidth) / nViewportHeight, 0.1, 100);
    //glOrtho(-8, 8, -5, 5, 0, 100);
    glMatrixMode(GL_MODELVIEW);*/
}

GLFWwindow* createWindow(bool fullScreen = false)
{
    const GLFWvidmode* ptVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    GLFWwindow* window = 0;
    if (fullScreen) {
         window = glfwCreateWindow(ptVideoMode->width, ptVideoMode->height, szTitle, glfwGetPrimaryMonitor(), NULL);
    }
    else {
        window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, szTitle, NULL, NULL);
        glfwSetWindowPos(window, (ptVideoMode->width - DEFAULT_WIDTH) / 2, (ptVideoMode->height - DEFAULT_HEIGHT) / 2);
    }
    if (!window)
        return 0;

    glfwMakeContextCurrent(window);

    /* Using a swap interval of 0 can be useful for benchmarking purposes, when it is not desirable
     * to measure the time it takes to wait for the vertical retrace.
     * A swap interval of 1 lets you avoid tearing (enables "vsync"). */
    glfwSwapInterval(1); // Only for the current context

    //glfwSetWindowSizeCallback(window, callback_resize);
    glfwSetFramebufferSizeCallback(window, callback_resize);
    glfwSetKeyCallback(window, callback_key);

//    std::stringstream x;
//    x << "\nDesktop Mode: " << ptVideoMode->width << "x" << ptVideoMode->height
//      << " / " << (ptVideoMode->redBits + ptVideoMode->greenBits + ptVideoMode->blueBits) << "bpp"
//      << " @ " << glfwGetWindowAttrib(window, GLFW_REFRESH_RATE) << " Hz Vertical Refresh Rate.\n\n"
//      //<< "CPU Count: " << glfwGetNumberOfProcessors()
//      << "\nGL Renderer: " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << " v" << glGetString(GL_VERSION)
//      //<< "\nGLFW_ACCELERATED: " << glfwGetWindowParam(GLFW_ACCELERATED)
//      << "\nGLFW_RED_BITS: " << glfwGetWindowAttrib(window, GLFW_RED_BITS)
//      << "\nGLFW_GREEN_BITS: " << glfwGetWindowAttrib(window, GLFW_GREEN_BITS)
//      << "\nGLFW_BLUE_BITS: " << glfwGetWindowAttrib(window, GLFW_BLUE_BITS)
//      << "\nGLFW_ALPHA_BITS: " << glfwGetWindowAttrib(window, GLFW_ALPHA_BITS)
//      << "\nGLFW_DEPTH_BITS: " << glfwGetWindowAttrib(window, GLFW_DEPTH_BITS)
//      << "\nGLFW_STENCIL_BITS: " << glfwGetWindowAttrib(window, GLFW_STENCIL_BITS)
//      << "\nGLFW_REFRESH_RATE: " << glfwGetWindowAttrib(window, GLFW_REFRESH_RATE)
//      << "\nGLFW_SAMPLES: " << glfwGetWindowAttrib(window, GLFW_SAMPLES);
//    cout << x.str() << "\n\n";

    glfwShowWindow(window);

    // Setup some OpenGL properties
    glLineWidth(10.0f);
    glClearColor(0, 0, 0, 1);
    glColor3d(1, 1, 1);
    glTranslatef(-1, -1, 0);
    glScalef(2, 2, 1);

    return window;
}

int main(int argc, char * argv[])
{
    cout << szTitle << "\n";
    cout << "\n";
    cout << "Usage:\n";
    cout << "    RefreshRateTool [<columns> <rows> <refresh rate>]\n";
    cout << "\n";
    cout << "Control keys:\n";
    cout << "    ENTER: toggle between Windowed and Full Screen modes.\n";
    cout << "    ESCAPE: finish the program.\n";
    cout << "\n";
#if SEIZURE_WARNING
    cout << "WARNING: This application will produce FLASHING IMAGES to test your screen(s)!\n";
    cout << "\n";
    cout << "If getting a seizure is a risk for you, close this window and do not proceed.\n";
    cout << "If you take the responsibility upon yourself, enter the two words 'I agree' and\n";
    cout << "press enter.\n";
    cout << "\n";

    char userText[100];
    std::fgets(userText, 10, stdin);
#endif

    // Initialize GLFW while the user thinks about it
    glfwSetErrorCallback(callback_error);
    glfwInit();

#if SEIZURE_WARNING
    if (false == (strcmp(userText, "I agree\n")   == 0 || strcmp(userText, "i agree\n")   == 0
                  || strcmp(userText, "\'I agree\'") == 0 || strcmp(userText, "\'i agree\'") == 0
                  || strcmp(userText, "\"I agree\"") == 0 || strcmp(userText, "\"i agree\"") == 0))
    {
        printf("It appears you do not agree; exiting...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        glfwTerminate();
        return 0;
    }
#endif

    unsigned int counter = 0;
    int nRefreshRate = 60;
    int nColumns = 6;
    int nRows = 1;
    //int nRows = nRefreshRate / nColumns;
    if (argc >= 2)
        nColumns = std::atoi(argv[1]);
    if (argc >= 3)
        nRows = std::atoi(argv[2]);
    if (argc >= 4)
        nRefreshRate = std::atoi(argv[3]);

    const double dWidth = 1.0 / nColumns;
    const double dHeight = 1.0 / nRows;

    // Set default hints for OpenGL windows
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // Hidden until correctly created and placed
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);
    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    glfwWindowHint(GLFW_REFRESH_RATE, nRefreshRate); // Ignored in windowed mode

    // Start in windowed mode
    GLFWwindow* window = createWindow(false);
    if (!window){
        glfwTerminate();
        return 0;
    }

    double startup = 300;

    // Main loop
    while (running && !glfwWindowShouldClose(window))
    {
        // OpenGL rendering goes here...
        glClear(GL_COLOR_BUFFER_BIT);

        counter = (counter + 1) % (nColumns * nRows);

        glBegin(GL_LINES);
        for (int c = 0; c <= nColumns; ++c) {
            glVertex2d(double(c) / nColumns, 0);
            glVertex2d(double(c) / nColumns, 1);
        }
        for (int r = 0; r <= nRows; ++r) {
            glVertex2d(0, double(r) / nRows);
            glVertex2d(1, double(r) / nRows);
        }
        glEnd();

        glBegin(GL_QUADS);
        double x = double(counter % nColumns) / nColumns;
        double y = 1 - double(counter / nColumns) / nRows;
        glVertex2d(x, y);
        glVertex2d(x + dWidth, y);
        glVertex2d(x + dWidth, y - dHeight);
        glVertex2d(x, y - dHeight);
        glEnd();

        // Swap front and back rendering buffers
        glfwSwapBuffers(window);

        // Process pending events
        glfwPollEvents();

        // Toggle Full Screen if needed
        if (toggleFullScreen) {
            toggleFullScreen = false;
            bool isFullScreen = (NULL != glfwGetWindowMonitor(window));
            glfwDestroyWindow(window);
            window = createWindow(!isFullScreen);
        }

        // Program starts with a fancy drawing speedup
        if (startup >= 1.0) {
            std::this_thread::sleep_for(std::chrono::duration< double, std::ratio<1, 1000> >(startup));
            startup *= 0.8;
        }
    }

    // Close window and terminate GLFW
    glfwTerminate();
    return 0;
}

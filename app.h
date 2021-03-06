/*
------------------------------------------------------------------------------
          Licensing information can be found at the end of the file.
------------------------------------------------------------------------------

app.h - v0.4 - Small cross-platform base framework for graphical apps.

Do this:
    #define APP_IMPLEMENTATION
before you include this file in *one* C/C++ file to create the implementation.
*/


#ifndef app_h
#define app_h

#if !defined(APP_WINDOWS) && !defined(APP_MACOS) && !defined(APP_LINUX_X11) && !defined(APP_NULL)
#if defined WIN32
#define APP_WINDOWS
#elif defined __APPLE__
#define APP_MACOS
#elif defined __linux__
#define APP_LINUX_X11
#endif
#endif

#ifndef APP_S16
    #define APP_S16 short
#endif
#ifndef APP_U32
    #define APP_U32 unsigned int
#endif
#ifndef APP_U64
    #define APP_U64 unsigned long long
#endif


typedef struct app_t app_t;

int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx );

typedef enum app_state_t { APP_STATE_EXIT_REQUESTED, APP_STATE_NORMAL, } app_state_t;
app_state_t app_yield( app_t* app );
void app_cancel_exit( app_t* app );

void app_title( app_t* app, char const* title );
char const* app_cmdline( app_t* app );
char const* app_filename( app_t* app );
char const* app_userdata( app_t* app );
char const* app_appdata( app_t* app );

APP_U64 app_time_count( app_t* app );
APP_U64 app_time_freq( app_t* app );

typedef enum app_log_level_t { APP_LOG_LEVEL_INFO, APP_LOG_LEVEL_WARNING, APP_LOG_LEVEL_ERROR, } app_log_level_t;
void app_log( app_t* app, app_log_level_t level, char const* message );
void app_fatal_error( app_t* app, char const* message );

void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y );
void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y ); 

void app_pointer_pos( app_t* app, int x, int y );
int app_pointer_x( app_t* app );
int app_pointer_y( app_t* app );

void app_pointer_limit( app_t* app, int x, int y, int width, int height );
void app_pointer_limit_off( app_t* app );

typedef enum app_interpolation_t { APP_INTERPOLATION_NONE, APP_INTERPOLATION_LINEAR, } app_interpolation_t;
void app_interpolation( app_t* app, app_interpolation_t interpolation );

typedef enum app_screenmode_t { APP_SCREENMODE_WINDOW, APP_SCREENMODE_FULLSCREEN, } app_screenmode_t;
void app_screenmode( app_t* app, app_screenmode_t screenmode );

void app_window_size( app_t* app, int width, int height );
int app_window_width( app_t* app );
int app_window_height( app_t* app );

void app_window_pos( app_t* app, int x, int y );
int app_window_x( app_t* app );
int app_window_y( app_t* app );

typedef struct app_display_t 
    {
    char id[ 64 ];
    int x;
    int y;
    int width;
    int height;
    } app_display_t ;

typedef struct app_displays_t { app_display_t* displays; int count; } app_displays_t;
app_displays_t app_displays( app_t* app );

void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr );

void app_sound( app_t* app, int sample_pairs_count, 
    void (*sound_callback)( APP_S16* sample_pairs, int sample_pairs_count, void* user_data ), void* user_data );
void app_sound_volume( app_t* app, float volume );

typedef enum app_key_t { APP_KEY_INVALID, APP_KEY_LBUTTON, APP_KEY_RBUTTON, APP_KEY_CANCEL, APP_KEY_MBUTTON, 
    APP_KEY_XBUTTON1, APP_KEY_XBUTTON2, APP_KEY_BACK, APP_KEY_TAB, APP_KEY_CLEAR, APP_KEY_RETURN, APP_KEY_SHIFT, 
    APP_KEY_CONTROL, APP_KEY_MENU, APP_KEY_PAUSE, APP_KEY_CAPITAL, APP_KEY_KANA, APP_KEY_HANGUL = APP_KEY_KANA, 
    APP_KEY_JUNJA, APP_KEY_FINAL, APP_KEY_HANJA, APP_KEY_KANJI = APP_KEY_HANJA, APP_KEY_ESCAPE, APP_KEY_CONVERT, 
    APP_KEY_NONCONVERT, APP_KEY_ACCEPT, APP_KEY_MODECHANGE, APP_KEY_SPACE, APP_KEY_PRIOR, APP_KEY_NEXT, APP_KEY_END, 
    APP_KEY_HOME, APP_KEY_LEFT, APP_KEY_UP, APP_KEY_RIGHT, APP_KEY_DOWN, APP_KEY_SELECT, APP_KEY_PRINT, APP_KEY_EXEC, 
    APP_KEY_SNAPSHOT, APP_KEY_INSERT, APP_KEY_DELETE, APP_KEY_HELP, APP_KEY_0, APP_KEY_1, APP_KEY_2, APP_KEY_3, 
    APP_KEY_4, APP_KEY_5, APP_KEY_6, APP_KEY_7, APP_KEY_8, APP_KEY_9, APP_KEY_A, APP_KEY_B, APP_KEY_C, APP_KEY_D, 
    APP_KEY_E, APP_KEY_F, APP_KEY_G, APP_KEY_H, APP_KEY_I, APP_KEY_J, APP_KEY_K, APP_KEY_L, APP_KEY_M, APP_KEY_N, 
    APP_KEY_O, APP_KEY_P, APP_KEY_Q, APP_KEY_R, APP_KEY_S, APP_KEY_T, APP_KEY_U, APP_KEY_V, APP_KEY_W, APP_KEY_X, 
    APP_KEY_Y, APP_KEY_Z, APP_KEY_LWIN, APP_KEY_RWIN, APP_KEY_APPS, APP_KEY_SLEEP, APP_KEY_NUMPAD0, APP_KEY_NUMPAD1, 
    APP_KEY_NUMPAD2, APP_KEY_NUMPAD3, APP_KEY_NUMPAD4, APP_KEY_NUMPAD5, APP_KEY_NUMPAD6, APP_KEY_NUMPAD7, 
    APP_KEY_NUMPAD8, APP_KEY_NUMPAD9, APP_KEY_MULTIPLY, APP_KEY_ADD, APP_KEY_SEPARATOR, APP_KEY_SUBTRACT, 
    APP_KEY_DECIMAL, APP_KEY_DIVIDE, APP_KEY_F1, APP_KEY_F2, APP_KEY_F3, APP_KEY_F4, APP_KEY_F5, APP_KEY_F6, APP_KEY_F7, 
    APP_KEY_F8, APP_KEY_F9, APP_KEY_F10, APP_KEY_F11, APP_KEY_F12, APP_KEY_F13, APP_KEY_F14, APP_KEY_F15, APP_KEY_F16, 
    APP_KEY_F17, APP_KEY_F18, APP_KEY_F19, APP_KEY_F20, APP_KEY_F21, APP_KEY_F22, APP_KEY_F23, APP_KEY_F24, 
    APP_KEY_NUMLOCK, APP_KEY_SCROLL, APP_KEY_LSHIFT, APP_KEY_RSHIFT, APP_KEY_LCONTROL, APP_KEY_RCONTROL, APP_KEY_LMENU, 
    APP_KEY_RMENU, APP_KEY_BROWSER_BACK, APP_KEY_BROWSER_FORWARD, APP_KEY_BROWSER_REFRESH, APP_KEY_BROWSER_STOP, 
    APP_KEY_BROWSER_SEARCH, APP_KEY_BROWSER_FAVORITES, APP_KEY_BROWSER_HOME, APP_KEY_VOLUME_MUTE, APP_KEY_VOLUME_DOWN, 
    APP_KEY_VOLUME_UP, APP_KEY_MEDIA_NEXT_TRACK, APP_KEY_MEDIA_PREV_TRACK, APP_KEY_MEDIA_STOP, APP_KEY_MEDIA_PLAY_PAUSE, 
    APP_KEY_LAUNCH_MAIL, APP_KEY_LAUNCH_MEDIA_SELECT, APP_KEY_LAUNCH_APP1, APP_KEY_LAUNCH_APP2, APP_KEY_OEM_1, 
    APP_KEY_OEM_PLUS, APP_KEY_OEM_COMMA, APP_KEY_OEM_MINUS, APP_KEY_OEM_PERIOD, APP_KEY_OEM_2, APP_KEY_OEM_3, 
    APP_KEY_OEM_4, APP_KEY_OEM_5, APP_KEY_OEM_6, APP_KEY_OEM_7, APP_KEY_OEM_8, APP_KEY_OEM_102, APP_KEY_PROCESSKEY, 
    APP_KEY_ATTN, APP_KEY_CRSEL, APP_KEY_EXSEL, APP_KEY_EREOF, APP_KEY_PLAY, APP_KEY_ZOOM, APP_KEY_NONAME, APP_KEY_PA1, 
    APP_KEY_OEM_CLEAR, APP_KEYCOUNT } app_key_t;

typedef enum app_input_type_t { APP_INPUT_KEY_DOWN, APP_INPUT_KEY_UP, APP_INPUT_DOUBLE_CLICK, APP_INPUT_CHAR, 
    APP_INPUT_MOUSE_MOVE, APP_INPUT_MOUSE_DELTA, APP_INPUT_SCROLL_WHEEL, APP_INPUT_TABLET } app_input_type_t;

typedef enum app_pressed_t { APP_NOT_PRESSED, APP_PRESSED, } app_pressed_t;

typedef struct app_input_event_t 
    {
    app_input_type_t type;
    union data_t
        {
        app_key_t key;
        char char_code;
        struct { int x; int y; } mouse_pos;
        struct { float x; float y; } mouse_delta;
        float wheel_delta;
        struct { int x; int y; float pressure; app_pressed_t tip; app_pressed_t lower; app_pressed_t upper; } tablet;
        } data;
    } app_input_event_t;

typedef struct app_input_t { app_input_event_t* events; int count; } app_input_t;
app_input_t app_input( app_t* app );

void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y );
void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y );

#endif /* app_h */


/**

Example
=======

Here's a basic sample program which starts a windowed app and plots random pixels.

    #define  APP_IMPLEMENTATION
    #define  APP_WINDOWS
    #include "app.h"

    #include <stdlib.h> // for rand and __argc/__argv
    #include <string.h> // for memset

    int app_proc( app_t* app, void* user_data )
        {
        (void) user_data;
        APP_U32 canvas[ 320 * 200 ]; // a place for us to draw stuff
        memset( canvas, 0xC0, sizeof( canvas ) ); // clear to grey
        app_screenmode( app, APP_SCREENMODE_WINDOW );

        // keep running until the user close the window
        while( app_yield( app ) != APP_STATE_EXIT_REQUESTED )
            {
            // plot a random pixel on the canvas
            int x = rand() % 320;
            int y = rand() % 200;
            APP_U32 color = rand() | ( (APP_U32) rand() << 16 );
            canvas[ x + y * 320 ] = color;

            // display the canvas
            app_present( app, canvas, 320, 200, 0xffffff, 0x000000 );
            }
        return 0;
        }

    int main( int argc, char** argv )
        {
        (void) argc, argv;
        return app_run( app_proc, NULL, NULL, NULL, NULL );
        }

    // pass-through so the program will build with either /SUBSYSTEM:WINDOWS or /SUBSYSTEN:CONSOLE
    extern "C" int __stdcall WinMain( struct HINSTANCE__*, struct HINSTANCE__*, char*, int ) { return main( __argc, __argv ); }



API Documentation
=================

app.h is a single-header library, and does not need any .lib files or other binaries, or any build scripts. To use it,
you just include app.h to get the API declarations. To get the definitions, you must include app.h from *one* single
C or C++ file, and #define the symbol `APP_IMPLEMENTATION` before you do. 

As app.h is meant to be a cross platform library (even though only windows is supported right now), you must also 
define which platform you are running on, like this:

    #define APP_IMPLEMENTATION
    #define APP_WINDOWS
    #include "app.h"


Customization
-------------
There are a few different things in app.h which are configurable by #defines. Most of the API use the `int` data type,
for integer values where the exact size is not important. However, for some functions, it specifically makes use of 16, 
32 and 64 bit data types. These default to using `short`, `unsigned int` and `unsigned long long` by default, but can be
redefined by #defining APP_S16, APP_U32 and APP_U64 respectively, before including app.h. This is useful if you, for 
example, use the types from `<stdint.h>` in the rest of your program, and you want app.h to use compatible types. In 
this case, you would include app.h using the following code:

    #define APP_S16 int16_t
    #define APP_U32 uint32_t
    #define APP_U64 uint64_t
    #include "app.h"

Note that when customizing the data types, you need to use the same definition in every place where you include app.h, 
as they affect the declarations as well as the definitions.

The rest of the customizations only affect the implementation, so will only need to be defined in the file where you
have the #define APP_IMPLEMENTATION.


### Custom memory allocators

Even though app.h attempts to minimize the memory use and number of allocations, it still needs to make *some* use of
dynamic allocation by calling `malloc`. Programs might want to keep track of allocations done, or use custom defined
pools to allocate memory from. app.h allows for specifying custom memory allocation functions for `malloc` and `free`.
This is done with the following code:

    #define APP_IMPLEMENTATION
    #define APP_MALLOC( ctx, size ) ( my_custom_malloc( ctx, size ) )
    #define APP_FREE( ctx, ptr ) ( my_custom_free( ctx, ptr ) )
    #include "app.h"

where `my_custom_malloc` and `my_custom_free` are your own memory allocation/deallocation functions. The `ctx` parameter
is an optional parameter of type `void*`. When `app_run` is called, you can pass in a `memctx` parameter, which can be a
pointer to anything you like, and which will be passed through as the `ctx` parameter to every APP_MALLOC/APP_FREE call.
For example, if you are doing memory tracking, you can pass a pointer to your tracking data as `memctx`, and in your
custom allocation/deallocation function, you can cast the `ctx` param back to the right type, and access the tracking
data.

If no custom allocator is defined, app.h will default to `malloc` and `free` from the C runtime library.


### Custom logging function

There's a bunch of things being logged when app.h runs. It will log an informational entry with the date and time for 
when the app is started and stopped, it will log warnings when non-essential initialization fails, and it will log 
error messages when things go wrong. By default, logging is done by a simple printf to stdout. As some applications may
need a different behavior, such as writing out a log file, it is possible to override the default logging behavior 
through defines like this:

    #define APP_IMPLEMENTATION
    #define APP_LOG( ctx, level, message ) ( my_log_func( ctx, level, message ) )
    #include "app.h"

where `my_log_func` is your own logging function. Just like for the memory allocators, the `ctx` parameter is optional,
and is just a `void*` value which is passed through. But in the case of logging, it will be passed through as the value
off the `logctx` parameter passed into `app_run`. The `level` parameter specifies the severity level of the logging,
and can be used to direct different types of messages to different logging systems, or filter out messages of certain
severity level, e.g. supressing informational messages.


### Custom fatal error function

As the app.h library works on the lowest level of your program, interfacing directly with the operating system, there
might occur errors which it can not recover from. In these cases, a *fatal error* will be reported. By default, when a
fatal error happens, app.h will print a message to stdout, show a messagebox to the user, and force exit the program.

It is possible to change this behaviour using the following define:

    #define APP_IMPLEMENTATION
    #define APP_FATAL_ERROR( ctx, message ) ( my_custom_fatal_error_func( ctx, message ) )
    #include "app.h"

where `my_custom_fatal_error_func` is your own error reporting function. The `ctx` parameter fills the same purpose as
for the allocator and logging functions, but here it is the `fatalctx` parameter to `app_run` which is passed through.


app_run
-------

    int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx )

Creates a new app instance, calls the given app_proc and waits for it to return. Then it destroys the app instance.

* app_proc - function pointer to the user defined starting point of the app. The parameters to that function are:
    app_t* a pointer to the app instance. This is an opaque type, and it is passed to all other functions in the API.
    void* pointer to the user defined data that was passed as the `user_data` parameter to `app_run`.   
* user_data - pointer to user defined data which will be passed through to app_proc. May be NULL.
* memctx - pointer to user defined data which will be passed through to custom APP_MALLOC/APP_FREE calls. May be NULL.
* logctx - pointer to user defined data to be passed through to custom APP_LOG calls. May be NULL.
* fatalctx - pointer to user defined data to be passed through to custom APP_FATAL_ERROR calls. May be NULL.

When app_run is called, it will perform all the initialization needed by app.h, and create an `app_t*` instance. It will
then call the user-specified `app_proc`, and wait for it to return. The `app_t*` instance will be passed to `app_proc`,
and can be used to call other functions in the API. When returning from `app_proc`, a return value is specified, and 
`app_run` will perform termination and cleanup, and destroy the `app_t*` instance, and then return the same value it got
from the `app_proc`. After `app_run` returns, the `app_t*` value is no longer valid for use in any API calls.


app_yield
---------

    app_state_t app_yield( app_t* app )

Allows for app.h and the operating system to perform internal house keeping and updates. It should be called on each
iteration of your main loop.

The return value can be either `APP_STATE_NORMAL` or `APP_STATE_EXIT_REQUESTED`. `APP_STATE_EXIT_REQUESTED` means that
the user have requested the app to terminate, e.g. by pressing the *close* button on the window, and the user defined
`app_proc` needs to handle this, by either returning (to signal that the app should terminate) or by calling
`app_cancel_exit` to ignore the request. A typical pattern is to display a message to the user to confirm that the app
should exit. In the case of `APP_STATE_NORMAL`, there is no need to do anything.


app_cancel_exit
---------------

    void app_cancel_exit( app_t* app )

Used to reset the `APP_STATE_EXIT_REQUESTED` state. See `app_yield` for details.


app_title
---------

    void app_title( app_t* app, char const* title )

Sets the name of the application, which is displayed in the task switcher and in the title bar of the window.


app_cmdline
-----------

    char const* app_cmdline( app_t* app )

Returns the command line string used to launch the executable. This can be parsed to get command line arguments.


app_filename
------------

    char const* app_filename( app_t* app )

Returns the full filename and path of the executable. The first part of `app_cmdline` usually contains the name of the
executable, but not necessarily the full path, depending on how it was launched. `app_filename`, however, always returns
the full path.


app_userdata
------------
    
    char const* app_userdata( app_t* app )

Returns the full path to a directory where a users personal files can be stored. Depending on the access rights of the
user, it may or may not be possible to write data to the same location as the executable, and instead it must be stored
in a specific area designated by the operating system. `app_userdata` returns the path to the root if that directory.
A typical use for this is to store the users savegame files, by creating a subfolder corresponding to your app, and save
the data there.


app_appdata
-----------

    char const* app_appdata( app_t* app )

Returns the full path to a directory where application specific files can be stored. Similar to the location returned by
`app_userdata`, but suitable for application data shared between users. Typical use for this is to store the result of
cached calculations or temporary files.


app_time_count
--------------

    APP_U64 app_time_count( app_t* app )

Returns the current value of the high precision clock. The epoch is undefined, and the resolution can vary between 
systems. Use `app_time_freq` to convert to seconds. Typical use is to make two calls to `app_time_count` and calculate
the difference, to measure the time elapsed between the two calls.


app_time_freq
-------------

    APP_U64 app_time_freq( app_t* app )

Returns the number of clock ticks per second of the high precision clock. An example use case could be:

    APP_U64 current_count = app_time_count( app );
    APP_U64 delta_count = current_count - previous_count;
    double delta_time = ( (double) delta_count ) / ( (double) app_time_freq( app ) );
    previous_count = current_count;

to measure the time between two iterations through your main loop.


app_log
-------

    void app_log( app_t* app, app_log_level_t level, char const* message )

app.h will do logging on certain events, e.q when the app starts and ends or when something goes wrong. As the logging
can be customized (see section on customization), it might be desirable for the program to do its own logging the same
way as app.h does it. By calling `app_log`, logging will be done the same way as it is done inside app.h, whether custom
logging or default logging is being used.


app_fatal_error
---------------

    void app_fatal_error( app_t* app, char const* message )

Same as with app_log, but for reporting fatal errors, `app_fatal_error` will report an error the same way as is done
internally in app.h, whether custom or default fatal error reporting is being used.


app_pointer
-----------

    void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y )

Sets the appearence current mouse pointer. `app_pointer` is called with the following parameters:

* width, height - the horizontal and vertical dimensions of the mouse pointer bitmap.
* pixels_abgr - width x height number of pixels making up the pointer bitmap, each pixel being a 32-bit unsigned integer
    where the highest 8 bits are the alpha channel, and the following 8-bit groups are blue, green and red channels.
* hotspot_x, hotspot_y - offset into the bitmap of the pointer origin, the center point it will be drawn at.


app_pointer_default
-------------------

    void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y )

Retrieves the width, height, pixel data and hotspot for the default mouse pointer. Useful for restoring the default
pointer after using `app_pointer`, or for doing software rendered pointers. Called with the following parameters:

* width, height - pointers to integer values that are to receive the width and height of the pointer. May be NULL.  
* pixels_abgr - width x height number of pixels to receive the pointer bitmap. May be NULL
* hotspot_x, hotspot_y - pointers to integer values that are to receive the hotspot coordinates. May be NULL.    

A typical pattern for calling `app_pointer_default` is to first call it with `pixels_abgr` as NULL, to query the bitmaps 
dimensions, and then call it again after preparing a large enough memory area.


app_pointer_pos
---------------

    void app_pointer_pos( app_t* app, int x, int y )

Set the position of the mouse pointer, in window coordinates. The function `app_coordinates_bitmap_to_window` can be
used to convert between the coordinate system of the currently displayed bitmap and that of the window.


app_pointer_limit
-----------------

    void app_pointer_limit( app_t* app, int x, int y, int width, int height )

Locks the mouse pointer movements to stay within the specified area, in window coordinates. The function 
`app_coordinates_bitmap_to_window` can be used to convert between the coordinate system of the currently displayed 
bitmap and that of the window.


app_pointer_limit_off
---------------------

    void app_pointer_limit_off( app_t* app )

Turns of the mouse pointer movement restriction, allowing the pointer to be moved freely again.


app_interpolation
-----------------

    void app_interpolation( app_t* app, app_interpolation_t interpolation )

app.h supports two different modes of displaying a bitmap. When using `APP_INTERPOLATION_LINEAR`, the bitmap will be 
drawn with bilinear interpolations, stretching it to fill the window (maintaining aspect ratio), giving it a smooth, if
somwhat blurry, look. With `APP_INTERPOLATION_NONE`, scaling will only be done on whole pixel ratios, using no 
interpolation, which is particularly suitable to maintain the clean, precise look of pixel art.
`APP_INTERPOLATION_LINEAR` is the default setting.


app_screenmode
--------------

    void app_screenmode( app_t* app, app_screenmode_t screenmode )

Switch between windowed mode and fullscreen mode. `APP_SCREENMODE_WINDOW` is used to select windowed mode, and
`APP_SCREENMODE_FULLSCREEN` is used to switch to fullscreen mode. `APP_SCREENMODE_FULLSCREEN` is the default. Note that
the app.h fullscreenmode is of the "borderless windowed" type, meaning that fullscreen mode just means that the window
is set to cover the entire screen, and its borders are hidden. It does not imply any exclusive locking of GPU resources.
When switching from windowed to fullscreen mode on a multi-display system, the app will go fullscreen on the display
that the window is currently on.


app_window_size
---------------

    void app_window_size( app_t* app, int width, int height )

Sets the size of the window. If currently in `APP_SCREENMODE_FULLSCREEN` screen mode, the setting will not take effect
until switching to `APP_SCREENMODE_WINDOW`. `width` and `height` specifies the size of the windows client area, not
counting borders, title bar or decorations.


app_window_width/app_window_height
----------------------------------

    int app_window_width( app_t* app )
    int app_window_height( app_t* app )

Returns the current dimensions of the window (which might have been resized by the user). Regardless of whether the app
is currently in fullscreen or windowed mode, `app_window_width` and `app_window_height` returns the dimension the window
*would* have in windowed mode. Width and height specifies the size of the windows client area, not counting borders, 
title bar or decorations.


app_window_pos
--------------

    void app_window_pos( app_t* app, int x, int y )

Sets the position of the top left corner of the window. If currently in `APP_SCREENMODE_FULLSCREEN` screen mode, the 
setting will not take effect until switching to `APP_SCREENMODE_WINDOW`. 


app_window_x/app_window_y
-------------------------

    int app_window_x( app_t* app )
    int app_window_y( app_t* app )

Returns the current position of the windows top left corner. Regardless of whether the app is currently in fullscreen or 
windowed mode, `app_window_x` and `app_window_y` returns the position the window *would* have in windowed mode. 


app_displays
------------

    app_displays_t app_displays( app_t* app )

Returns a list of all displays connected to the system. For each display, the following fields are reported:
* id - a platform specific string used to identify the display. Useful for saving which display was in use.
* x, y - position of the top left corner of the display, relative to the primary dispay which is always at 0,0.
* width, height - size of the display, in pixels.


app_present
-----------
    
    void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr )

app.h provides a very minimal API for drawing - the only thing you can really do, is provide it with a bitmap for it to
display on the screen. It is then up to the rest of your program to implement code for drawing shapes or sprites onto 
that bitmap. When all your drawing is done, you call `app_present` passing it the bitmap, and it will be displayed on 
the screen. `app_present` takes the following parameters:
* pixels_xbgr - width x height number of pixels making up the bitmap to be presented, each pixel being a 32-bit unsigned 
    integer where the highest 8 bits are not used, and the following 8-bit groups are blue, green and red channels. This
    parameter may be NULL, in which case no bitmap is drawn, to allow for custom rendering. See below for details.
* width, height - the horizontal and vertical dimensions of the bitmap
* mod_xbgr - an rgb color value which will be automatically multiplied with each pixel, component by component, before
    it is displayed. Can be used to for example fade the bitmap to/from black. Set to 0xffffff for no effect.
* border_xbgr - an rgb color value to be used as *border color*. The borders are the areas outside of the bitmap, which
    are visible when the window aspect ratio does not match that of the bitmap, so you get bars above or below it.

Since app.h uses opengl, you can also opt to not pass a bitmap to `app_present`, by passing NULL as the `pixels_xbgr`
parameter (in which case the rest of the parameters are ignored). When doing this, it is up to your program to perform 
drawing using opengl calls. In this case `app_present` will work as a call to SwapBuffers only. Note that glSetViewPort 
will be automatically called whenever the window is resized.


app_sound_buffer_size
---------------------

    void app_sound_buffer_size( app_t* app, int sample_pairs_count )

The api for playing sound samples is just as minimal as that for drawing. app.h provides a single, looping sound stream,
and it is up to your program to handle sound formats, voices and mixing. By calling `app_sound_buffer_size`, a sound
stream of the specified size is initialized, and playback is started. If a `sample_pairs_count` of 0 is given, sound
playback will be stopped.

The sound buffer is in 44100hz, signed 16-bit stereo format, and the `sample_pairs_count` specified how many left/right
pairs of 16-bit samples the buffer will contain. As an example, to specify a 1 second stream buffer, you would give the
value 44100 for the `sample_pairs_count` parameter, which would internally create a sound buffer of 176,400 bytes, from
44100 samples x 2 channels x 2 bytes per sample. However, since the bits per sample and number of channels are fixed,
the exact byte size of the sound buffer is not important in the app.h API.


app_sound_position
------------------

    int app_sound_position( app_t* app )

Returns the current playback position of the sound stream, given in the number of sample pairs from the start of the
buffer. Typical use of a streaming sound buffer is to fill the buffer with data, wait for the playback position to get
passed the mid point of the buffer, and then write the next bit of data over the part that has already been played, and 
so on.


app_sound_write
---------------

    void app_sound_write( app_t* app, int sample_pairs_offset, int sample_pairs_count, APP_S16 const* sample_pairs )

Writes sample data to the sound buffer. It takes the following parameters:

* sample_pairs_offset - the offset into the buffer of where to start writing, in number of sample pairs from the start.
* sample_pairs_count - the number of sample pairs to write. Must be less than the buffer size.
* sample_pairs - an array of sound samples, as signed 16-bit integers. Must be at least `sample_pairs_count` in length.

The `sample_pairs` parameter can be NULL, in which case the corresponding part of the buffer is cleared.


app_sound_volume
----------------

    void app_sound_volume( app_t* app, float volume )

Sets the output volume level of the sound stream, as a normalized linear value in the range 0.0f to 1.0f, inclusive.


app_input
---------

    app_input_t app_input( app_t* app )

Returns a list of input events which occured since the last call to `app_input`. Each input event can be of one of a 
list of types, and the `type` field of the `app_input_event_t` struct specifies which type the event is. The `data`
struct is a union of fields, where only one of them is valid, depending on the value of `type`:
* APP_INPUT_KEY_DOWN, APP_INPUT_KEY_UP, APP_INPUT_DOUBLE_CLICK - use the `key` field of the `data` union, which contains
    one of the keyboard key identifiers from the `app_key_t` enumeration. `APP_INPUT_KEY_DOWN` means a key was pressed,
    or that it was held long enough for the key repeat to kick in. `APP_INPUT_KEY_UP` means a key was released, and is
    not sent on key repeats. For both these events, a `key` may also mean a mouse button, as those are listed in the 
    `app_key_t` enum. `APP_INPUT_DOUBLE_CLICK` means a mouse button have been double clicked, and is not sent for 
    keyboard keys.
* APP_INPUT_CHAR - use the `char_code` field of the `data` union, which contains the ASCII value of the key that was
    pressed. This is used to read text input, and will handle things like upper/lower case, and characters which 
    requires multiple keys to be pressed in sequence to generate one input. This means that generally, when a key is 
    pressed, you will get both an `APP_INPUT_KEY_DOWN` event and an `APP_INPUT_CHAR` event - just use the one you are
    interested in, and ignore the other.
* APP_INPUT_MOUSE_MOVE - use the `mouse_pos` field of the `data` union, which contains the x and y position of the
    mouse pointer, in window coordinates. The function `app_coordinates_window_to_bitmap` can be used to convert between 
    the coordinate system of the window and that of the currently displayed bitmap. The `APP_INPUT_MOUSE_MOVE` event is
    sent whenever the user moves the mouse, as long as the window has focus and the pointer is inside its client area.
* APP_INPUT_MOUSE_DELTA - use the `mouse_delta` field of the `data` union, which contains the horizontal and vertical
    offset which the mouse has been moved by. Ideally, these values should be in normalized -1.0f to 1.0f range, but as
    there is no standardisation on the hardware and os level for this, it is not possible to do, so instead the value
    have been scaled to give roughly normalized -1.0f to 1.0f values on a typical setup. For serious use, sensitivity
    settings and/or user calibration is recommended. The `APP_INPUT_MOUSE_DELTA` event is sent whenever the user moves
    the mouse, regardless of whether the window has focus or whether the pointer is inside the window or not. The
    `APP_INPUT_MOUSE_DELTA` event is a better option for reading relative mouse movements than using the
    `APP_INPUT_MOUSE_MOVE` event together with `app_pointer_pos` to re-center the pointer on every update.
* APP_INPUT_SCROLL_WHEEL - use the `wheel_delta` field of the `data` union, which contains the number of clicks by which
    the scroll wheel on the mouse was turned, where positive values indicate that the wheel have been rotated away from
    the user, and negative values means it has turned towards the user. The `APP_INPUT_SCROLL_WHEEL` is sent every time
    the user turns the scroll wheel, as long as the window has focus.
* APP_INPUT_TABLET - use the `tablet` field of the `data` union, which contains details about the pen used with a 
    graphical tablet, if connected and installed. The `x` and `y` fields are the horizontal and vertical positions of 
    the pen on the tablet, scaled to the coordinate system of the window. The function `app_coordinates_window_to_bitmap` 
    can be used to convert between the coordinate system of the window and that of the currently displayed bitmap. The
    `pressure` field is the current pressure of the pen against the tablet, in normalized 0.0f to 1.0f range, inclusive,
    where 0.0f means no pressure and 1.0f means full pressure. The `tip` field is set to `APP_PRESSED` if the tip of the
    pen is touching the tablet at all, and to `APP_NOT_PRESSED` otherwise. The `upper` and `lower` fields indicate the
    current state of the buttons on the side of the pen. The "eraser" part of the pen is not currently supported.


app_coordinates_window_to_bitmap
--------------------------------

    void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y )

Functions in the `app.h` API expects and returns coordinates in the windows coordinate system, where 0, 0 is the top
left corner of the windows client area (the area inside of the window borders, excluding title bar and decorations), and
width, height is the dimension, in pixels, of the client area. It is often desirable to translate a position given in
window coordinates into a position on the bitmap that is being displayed - taking into account whether the window is in
fullscreen or windowed mode, and how the bitmap is stretched or padded depending on which interpolation mode is being
used: `APP_INTERPOLATION_NONE` or `APP_INTERPOLATION_LINEAR`. `app_coordinates_window_to_bitmap` performs this
translation, and is called with the following parameters:
* width, height - dimensions of the bitmap being presented, the same as the ones passed to `app_present`.
* x, y - pointers to integer values containing the coordinate, in the coordinate system of the window, to be translated. 
    When the function returns, their values will have been updated with the corresponding position in the coordinate 
    system of the bitmap.


app_coordinates_bitmap_to_window
--------------------------------

    void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y )

This performs the opposite translation to `app_coordinates_window_to_bitmap` - it converts a position given in the 
coordinate system of the bitmap into the coordinate system of the window. See `app_coordinates_window_to_bitmap` for
details.

**/



/*
----------------------
    IMPLEMENTATION
----------------------
*/
#ifdef APP_IMPLEMENTATION
#undef APP_IMPLEMENTATION


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    OPENGL CODE - Shared between platform implementations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef APP_NULL

#if defined( APP_WINDOWS )
    #define _CRT_NONSTDC_NO_DEPRECATE 
    #define _CRT_SECURE_NO_WARNINGS
    #include <stddef.h>
    #define APP_GLCALLTYPE __stdcall
    typedef unsigned int APP_GLuint;
    typedef int APP_GLsizei;
    typedef unsigned int APP_GLenum;
    typedef int APP_GLint;
    typedef float APP_GLfloat;
    typedef char APP_GLchar;
    typedef unsigned char APP_GLboolean;
    typedef size_t APP_GLsizeiptr;
    typedef unsigned int APP_GLbitfield;
#elif defined( APP_MACOS )
    #define _CRT_NONSTDC_NO_DEPRECATE
    #define _CRT_SECURE_NO_WARNINGS
    #include <stddef.h>
    #include <string.h>
    #include <OpenGL/gl3.h>
    #define APP_GLCALLTYPE
    typedef GLuint APP_GLuint;
    typedef GLsizei APP_GLsizei;
    typedef GLenum APP_GLenum;
    typedef GLint APP_GLint;
    typedef GLfloat APP_GLfloat;
    typedef GLchar APP_GLchar;
    typedef GLboolean APP_GLboolean;
    typedef GLsizeiptr APP_GLsizeiptr;
    typedef GLbitfield APP_GLbitfield;
#elif defined( APP_LINUX_X11 )
    #define _CRT_NONSTDC_NO_DEPRECATE
    #define _CRT_SECURE_NO_WARNINGS
    #include <stddef.h>
    #include <string.h>
    #include <GL/gl.h>
    #define APP_GLCALLTYPE
    typedef GLuint APP_GLuint;
    typedef GLsizei APP_GLsizei;
    typedef GLenum APP_GLenum;
    typedef GLint APP_GLint;
    typedef GLfloat APP_GLfloat;
    typedef GLchar APP_GLchar;
    typedef GLboolean APP_GLboolean;
    typedef GLsizeiptr APP_GLsizeiptr;
    typedef GLbitfield APP_GLbitfield;
#else
    #error Undefined platform. Define APP_WINDOWS, APP_MACOS, APP_LINUX_X11 or APP_NULL.
    #define APP_GLCALLTYPE
    typedef int APP_GLuint;
    typedef int APP_GLsizei;
    typedef int APP_GLenum;
    typedef int APP_GLint;
    typedef int APP_GLfloat;
    typedef int APP_GLchar;
    typedef int APP_GLboolean;
    typedef int APP_GLsizeiptr;
    typedef int APP_GLbitfield;
#endif

#define APP_GL_FLOAT 0x1406
#define APP_GL_FALSE 0
#define APP_GL_FRAGMENT_SHADER 0x8b30
#define APP_GL_VERTEX_SHADER 0x8b31
#define APP_GL_COMPILE_STATUS 0x8b81
#define APP_GL_LINK_STATUS 0x8b82
#define APP_GL_INFO_LOG_LENGTH 0x8b84
#define APP_GL_ARRAY_BUFFER 0x8892
#define APP_GL_TEXTURE_2D 0x0de1
#define APP_GL_TEXTURE0 0x84c0
#define APP_GL_TEXTURE_MIN_FILTER 0x2801
#define APP_GL_TEXTURE_MAG_FILTER 0x2800
#define APP_GL_NEAREST 0x2600
#define APP_GL_LINEAR 0x2601
#define APP_GL_STATIC_DRAW 0x88e4
#define APP_GL_RGBA 0x1908
#define APP_GL_UNSIGNED_BYTE 0x1401
#define APP_GL_COLOR_BUFFER_BIT 0x00004000
#define APP_GL_TRIANGLE_FAN 0x0006

struct app_internal_opengl_t
    {
    APP_GLuint (APP_GLCALLTYPE* glCreateShader) (APP_GLenum type);
    void (APP_GLCALLTYPE* glShaderSource) (APP_GLuint shader, APP_GLsizei count, APP_GLchar const* const* string, APP_GLint const* length);
    void (APP_GLCALLTYPE* glCompileShader) (APP_GLuint shader);
    void (APP_GLCALLTYPE* glGetShaderiv) (APP_GLuint shader, APP_GLenum pname, APP_GLint *params);
    APP_GLuint (APP_GLCALLTYPE* glCreateProgram) (void);
    void (APP_GLCALLTYPE* glAttachShader) (APP_GLuint program, APP_GLuint shader);
    void (APP_GLCALLTYPE* glBindAttribLocation) (APP_GLuint program, APP_GLuint index, APP_GLchar const* name);
    void (APP_GLCALLTYPE* glLinkProgram) (APP_GLuint program);
    void (APP_GLCALLTYPE* glGetProgramiv) (APP_GLuint program, APP_GLenum pname, APP_GLint *params);
    void (APP_GLCALLTYPE* glGenBuffers) (APP_GLsizei n, APP_GLuint *buffers);
    void (APP_GLCALLTYPE* glBindBuffer) (APP_GLenum target, APP_GLuint buffer);
    void (APP_GLCALLTYPE* glEnableVertexAttribArray) (APP_GLuint index);
    void (APP_GLCALLTYPE* glVertexAttribPointer) (APP_GLuint index, APP_GLint size, APP_GLenum type, APP_GLboolean normalized, APP_GLsizei stride, void const* pointer);
    void (APP_GLCALLTYPE* glGenVertexArrays) (APP_GLsizei n, APP_GLuint* arrays);
    void (APP_GLCALLTYPE* glBindVertexArray) (APP_GLuint array);
    void (APP_GLCALLTYPE* glGenTextures) (APP_GLsizei n, APP_GLuint* textures);
    void (APP_GLCALLTYPE* glEnable) (APP_GLenum cap);
    void (APP_GLCALLTYPE* glActiveTexture) (APP_GLenum texture);
    void (APP_GLCALLTYPE* glBindTexture) (APP_GLenum target, APP_GLuint texture);
    void (APP_GLCALLTYPE* glTexParameteri) (APP_GLenum target, APP_GLenum pname, APP_GLint param);
    void (APP_GLCALLTYPE* glDeleteBuffers) (APP_GLsizei n, APP_GLuint const* buffers);
    void (APP_GLCALLTYPE* glDeleteTextures) (APP_GLsizei n, APP_GLuint const* textures);
    void (APP_GLCALLTYPE* glBufferData) (APP_GLenum target, APP_GLsizeiptr size, void const *data, APP_GLenum usage);
    void (APP_GLCALLTYPE* glUseProgram) (APP_GLuint program);
    void (APP_GLCALLTYPE* glUniform1i) (APP_GLint location, APP_GLint v0);
    void (APP_GLCALLTYPE* glUniform3f) (APP_GLint location, APP_GLfloat v0, APP_GLfloat v1, APP_GLfloat v2);
    APP_GLint (APP_GLCALLTYPE* glGetUniformLocation) (APP_GLuint program, APP_GLchar const* name);
    void (APP_GLCALLTYPE* glTexImage2D) (APP_GLenum target, APP_GLint level, APP_GLint internalformat, APP_GLsizei width, APP_GLsizei height, APP_GLint border, APP_GLenum format, APP_GLenum type, void const* pixels);
    void (APP_GLCALLTYPE* glClearColor) (APP_GLfloat red, APP_GLfloat green, APP_GLfloat blue, APP_GLfloat alpha);
    void (APP_GLCALLTYPE* glClear) (APP_GLbitfield mask);
    void (APP_GLCALLTYPE* glDrawArrays) (APP_GLenum mode, APP_GLint first, APP_GLsizei count);
    void (APP_GLCALLTYPE* glViewport) (APP_GLint x, APP_GLint y, APP_GLsizei width, APP_GLsizei height);
    void (APP_GLCALLTYPE* glDeleteShader) (APP_GLuint shader);
    void (APP_GLCALLTYPE* glDeleteProgram) (APP_GLuint program);
    #ifdef APP_REPORT_SHADER_ERRORS
        void (APP_GLCALLTYPE* glGetShaderInfoLog) (APP_GLuint shader, APP_GLsizei bufSize, APP_GLsizei *length, APP_GLchar *infoLog);
    #endif

    app_interpolation_t interpolation;
    int window_width;
    int window_height;

    APP_GLuint vertexbuffer;
    APP_GLuint vertexarray;
    APP_GLuint texture;
    APP_GLuint shader;
};


static int app_internal_opengl_init( app_t* app, struct app_internal_opengl_t* gl, app_interpolation_t interpolation,
    int window_width, int window_height )
    {
    (void) app;
    gl->interpolation = interpolation;
    gl->window_width = window_width;
    gl->window_height = window_height;
    
    char const* vs_source_gl3 =
        "#version 150\n           \
        in vec4 pos;     \
        out vec2 uv;        \
                                \
        void main( void )       \
        {                       \
            gl_Position = vec4( pos.xy, 0.0, 1.0 ); \
            uv = pos.zw;          \
    }";
    
    char const* vs_source_gl2 =
        "#version 110\n         \
        attribute vec4 pos;     \
        varying vec2 uv;        \
                                \
        void main( void )       \
            {                   \
            gl_Position = vec4( pos.xy, 0.0, 1.0 ); \
            uv = pos.zw;        \
    }";

    char const* fs_source_gl3 =
        "#version 150\n                 \
         in vec2 uv;                    \
         out vec4 fragColor;            \
                                        \
         uniform sampler2D tex;         \
         uniform vec3 modulate;         \
                                        \
         void main(void)                \
         {                              \
            fragColor = texture( tex, uv ) * vec4( modulate, 1.0 );  \
        }";

    char const* fs_source_gl2 =
        "#version 110\n                 \
         varying vec2 uv;               \
                                        \
         uniform sampler2D tex;         \
         uniform vec3 modulate;         \
                                        \
         void main(void)                \
         {                              \
            gl_FragColor = texture2D( tex, uv ) * vec4( modulate, 1.0 );  \
        }";

    // choose which shaders to use based on gl major version.
    char const* vs_source;
    char const* fs_source;
    const GLubyte* versionStr = glGetString(GL_VERSION);
    switch(versionStr[0])
    {
        case '2':
            vs_source = vs_source_gl2;
            fs_source = fs_source_gl2;
            break;
        case '3':
        case '4':
            vs_source = vs_source_gl3;
            fs_source = fs_source_gl3;
            break;
        default:
            app_fatal_error( app, "Unsupported OpenGL Version\n" );
            break;
    }


    
    #ifdef APP_REPORT_SHADER_ERRORS
        char error_message[ 1024 ]; 
    #endif

    APP_GLuint vs = gl->glCreateShader( APP_GL_VERTEX_SHADER );
    gl->glShaderSource( vs, 1, (char const**) &vs_source, NULL );
    gl->glCompileShader( vs );
    APP_GLint vs_compiled;
    gl->glGetShaderiv( vs, APP_GL_COMPILE_STATUS, &vs_compiled );
    if( !vs_compiled )
        {
        #ifdef APP_REPORT_SHADER_ERRORS     
            char const* prefix = "Vertex Shader Error: ";
            strcpy( error_message, prefix );
            int len = 0, written = 0;
            gl->glGetShaderiv( vs, APP_GL_INFO_LOG_LENGTH, &len );
            gl->glGetShaderInfoLog( vs, (APP_GLsizei)( sizeof( error_message ) - strlen( prefix ) ), &written, 
                error_message + strlen( prefix ) );     
            app_fatal_error( app, error_message );
        #endif
        return 0;
        }
    
    APP_GLuint fs = gl->glCreateShader( APP_GL_FRAGMENT_SHADER );
    gl->glShaderSource( fs, 1, (char const**) &fs_source, NULL );
    gl->glCompileShader( fs );
    APP_GLint fs_compiled;
    gl->glGetShaderiv( fs, APP_GL_COMPILE_STATUS, &fs_compiled );
    if( !fs_compiled )
        {
        #ifdef APP_REPORT_SHADER_ERRORS     
            char const* prefix = "Fragment Shader Error: ";
            strcpy( error_message, prefix );
            int len = 0, written = 0;
            gl->glGetShaderiv( vs, APP_GL_INFO_LOG_LENGTH, &len );
            gl->glGetShaderInfoLog( fs, (APP_GLsizei)( sizeof( error_message ) - strlen( prefix ) ), &written, 
                error_message + strlen( prefix ) );     
            app_fatal_error( app, error_message );
        #endif
        return 0;
        }


    APP_GLuint prg = gl->glCreateProgram();
    gl->glAttachShader( prg, fs );
    gl->glAttachShader( prg, vs );
    gl->glBindAttribLocation( prg, 0, "pos" );
    gl->glLinkProgram( prg );

    APP_GLint linked;
    gl->glGetProgramiv( prg, APP_GL_LINK_STATUS, &linked );
    if( !linked )
        {
        #ifdef APP_REPORT_SHADER_ERRORS
            char const* prefix = "Shader Link Error: ";
            strcpy( error_message, prefix );
            int len = 0, written = 0;
            gl->glGetShaderiv( vs, APP_GL_INFO_LOG_LENGTH, &len );
            gl->glGetShaderInfoLog( prg, (APP_GLsizei)( sizeof( error_message ) - strlen( prefix ) ), &written, 
                error_message + strlen( prefix ) );     
            app_fatal_error( app, error_message );
        #endif
        return 0;
        }

    gl->shader = prg;
    gl->glDeleteShader( fs );
    gl->glDeleteShader( vs );

    gl->glGenBuffers( 1, &gl->vertexbuffer );
    gl->glGenVertexArrays( 1, &gl->vertexarray );
    gl->glBindVertexArray( gl->vertexarray );
    gl->glBindBuffer( APP_GL_ARRAY_BUFFER, gl->vertexbuffer );
    gl->glEnableVertexAttribArray( 0 );
    gl->glVertexAttribPointer( 0, 4, APP_GL_FLOAT, APP_GL_FALSE, 4 * sizeof( APP_GLfloat ), 0 );

    gl->glGenTextures( 1, &gl->texture ); 
    gl->glEnable( APP_GL_TEXTURE_2D ); 
    gl->glActiveTexture( APP_GL_TEXTURE0 );
    gl->glBindTexture( APP_GL_TEXTURE_2D, gl->texture );
    gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MIN_FILTER, APP_GL_NEAREST );
    gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MAG_FILTER, APP_GL_NEAREST );

    return 1;
    }


static int app_internal_opengl_term( struct app_internal_opengl_t* gl )
    {
    gl->glDeleteProgram( gl->shader );
    gl->glDeleteBuffers( 1, &gl->vertexbuffer); 
    gl->glDeleteTextures( 1, &gl->texture ); 
    return 1;
    }


static int app_internal_opengl_present( struct app_internal_opengl_t* gl, APP_U32 const* pixels_xbgr, int width, 
    int height, APP_U32 mod_xbgr, APP_U32 border_xbgr )
    {
    float x1 = 0.0f, y1 = 0.0f, x2 = (float) gl->window_width, y2 = (float) gl->window_height;

    if( gl->interpolation == APP_INTERPOLATION_LINEAR )
        {
        float hscale = gl->window_width / (float) width;
        float vscale = gl->window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;

        float hborder = ( gl->window_width - pixel_scale * width ) / 2.0f;
        float vborder = ( gl->window_height - pixel_scale * height ) / 2.0f;
        x1 = hborder;
        y1 = vborder;
        x2 = x1 + pixel_scale * width;
        y2 = y1 + pixel_scale * height;
        }
    else
        {
        int hscale = gl->window_width / width;
        int vscale = gl->window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;

        int hborder = ( gl->window_width - pixel_scale * width ) / 2;
        int vborder = ( gl->window_height - pixel_scale * height ) / 2;
        x1 = (float) hborder;
        y1 = (float) vborder;
        x2 = x1 + (float) ( pixel_scale * width );
        y2 = y1 + (float) ( pixel_scale * height );
        }

    x1 = ( x1 / gl->window_width ) * 2.0f - 1.0f;
    x2 = ( x2 / gl->window_width ) * 2.0f - 1.0f;
    y1 = ( y1 / gl->window_height ) * 2.0f - 1.0f;
    y2 = ( y2 / gl->window_height ) * 2.0f - 1.0f;

    APP_GLfloat vertices[ 16 ]; 
    vertices[  0 ] = x1;
    vertices[  1 ] = y1;
    vertices[  2 ] = 0.0f;
    vertices[  3 ] = 1.0f;

    vertices[  4 ] = x2;
    vertices[  5 ] = y1;
    vertices[  6 ] = 1.0f;
    vertices[  7 ] = 1.0f;

    vertices[  8 ] = x2;
    vertices[  9 ] = y2;
    vertices[ 10 ] = 1.0f;
    vertices[ 11 ] = 0.0f;

    vertices[ 12 ] = x1;
    vertices[ 13 ] = y2;
    vertices[ 14 ] = 0.0f;
    vertices[ 15 ] = 0.0f;
  
    gl->glBindVertexArray(gl->vertexarray);
    gl->glBufferData( APP_GL_ARRAY_BUFFER, 4 * 4 * sizeof( APP_GLfloat ), vertices, APP_GL_STATIC_DRAW );
    gl->glVertexAttribPointer( 0, 4, APP_GL_FLOAT, APP_GL_FALSE, 4 * sizeof( APP_GLfloat ), 0 );

    float mod_r = ( ( mod_xbgr >> 16 ) & 0xff ) / 255.0f;
    float mod_g = ( ( mod_xbgr >> 8  ) & 0xff ) / 255.0f;
    float mod_b = ( ( mod_xbgr       ) & 0xff ) / 255.0f;

    gl->glUseProgram( gl->shader );
    gl->glUniform1i( gl->glGetUniformLocation( gl->shader, "tex" ), 0 );
    gl->glUniform3f( gl->glGetUniformLocation( gl->shader, "modulate" ), mod_r, mod_g, mod_b );

    gl->glActiveTexture( APP_GL_TEXTURE0 );
    gl->glBindTexture( APP_GL_TEXTURE_2D, gl->texture );
    gl->glTexImage2D( APP_GL_TEXTURE_2D, 0, APP_GL_RGBA, width, height, 0, APP_GL_RGBA, APP_GL_UNSIGNED_BYTE, pixels_xbgr ); 
    
    if( gl->interpolation == APP_INTERPOLATION_LINEAR )
        {
        gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MIN_FILTER, APP_GL_LINEAR );
        gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MAG_FILTER, APP_GL_LINEAR );
        }
    else
        {
        gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MIN_FILTER, APP_GL_NEAREST );
        gl->glTexParameteri( APP_GL_TEXTURE_2D, APP_GL_TEXTURE_MAG_FILTER, APP_GL_NEAREST );
        }

    float r = ( ( border_xbgr >> 16 ) & 0xff ) / 255.0f;
    float g = ( ( border_xbgr >> 8  ) & 0xff ) / 255.0f;
    float b = ( ( border_xbgr       ) & 0xff ) / 255.0f;
    gl->glClearColor( r, g, b, 1.0f );
    gl->glClear( APP_GL_COLOR_BUFFER_BIT );
    gl->glDrawArrays( APP_GL_TRIANGLE_FAN, 0, 4 );

    return 1;
    }


static void app_internal_opengl_resize( struct app_internal_opengl_t* gl, int width, int height )
    {
    gl->glViewport( 0, 0, width, height );    
    gl->window_width = width;
    gl->window_height = height;
    }


static void app_internal_opengl_interpolation( struct app_internal_opengl_t* gl, app_interpolation_t interpolation )
    {
    gl->interpolation = interpolation;
    }


#endif // #ifndef APP_NULL


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    NULL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined( APP_NULL )


struct app_t { };
int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx ) 
    { app_t app; return app_proc( &app, user_data ); }
app_state_t app_yield( app_t* app ) { return APP_STATE_EXIT_REQUESTED; }
void app_cancel_exit( app_t* app ) { }
void app_title( app_t* app, char const* title ) { }
char const* app_cmdline( app_t* app ) { return 0; }
char const* app_filename( app_t* app ) { return 0; }
char const* app_userdata( app_t* app ) { return 0; }
char const* app_appdata( app_t* app ) { return 0; }
APP_U64 app_time_count( app_t* app ) { return 0; }
APP_U64 app_time_freq( app_t* app ) { return 0; }
void app_log( app_t* app, app_log_level_t level, char const* message ) { }
void app_fatal_error( app_t* app, char const* message ) { }
void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y ) { }
void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y ) { }
void app_pointer_pos( app_t* app, int x, int y ) { }
void app_pointer_limit( app_t* app, int x, int y, int width, int height ) { }
void app_pointer_limit_off( app_t* app ) { }
void app_interpolation( app_t* app, app_interpolation_t interpolation ) { }
void app_screenmode( app_t* app, app_screenmode_t screenmode ) { }
void app_window_size( app_t* app, int width, int height ) { }
int app_window_width( app_t* app ) { return 0; }
int app_window_height( app_t* app ) { return 0; }
void app_window_pos( app_t* app, int x, int y ) { }
int app_window_x( app_t* app ) { return 0; }
int app_window_y( app_t* app ) { return 0; }
app_displays_t app_displays( app_t* app ) { app_displays_t x = { 0 }; return x; }
void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr ) { }
void app_sound( app_t* app, int sample_pairs_count, void (*sound_callback)( APP_S16* sample_pairs, int sample_pairs_count, void* user_data ), void* user_data ) { }
void app_sound_volume( app_t* app, float volume ) { }
app_input_t app_input( app_t* app ) { app_input_t x = { 0 }; return x; }
void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y ) { }
void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y ) { }



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    WINDOWS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#elif defined( APP_WINDOWS )

#define _CRT_NONSTDC_NO_DEPRECATE 
#define _CRT_SECURE_NO_WARNINGS

#if !defined( _WIN32_WINNT ) || _WIN32_WINNT < 0x0501 
    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x501// requires Windows XP minimum
#endif
// 0x0400=Windows NT 4.0, 0x0500=Windows 2000, 0x0501=Windows XP, 0x0502=Windows Server 2003, 0x0600=Windows Vista, 
// 0x0601=Windows 7, 0x0602=Windows 8, 0x0603=Windows 8.1, 0x0A00=Windows 10, 
#define _WINSOCKAPI_
#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#pragma warning( disable: 4255 ) // 'function' : no function prototype given: converting '()' to '(void)'
#pragma warning( disable: 4917 ) // 'declarator' : a GUID can only be associated with a class, interface or namespace
#include <windows.h>
#include <shlobj.h>
#pragma warning( pop )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "shell32.lib" )
#define DIRECTSOUND_VERSION 0x0800
#include <dsound.h>
#include <time.h>
#include <stdio.h>

#pragma warning( push )
#pragma warning( disable: 4668 ) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
#include <math.h>
#pragma warning( pop )

#ifndef APP_MALLOC
    #include <stdlib.h>
    #if defined(__cplusplus)
        #define APP_MALLOC( ctx, size ) ( ::malloc( size ) )
        #define APP_FREE( ctx, ptr ) ( ::free( ptr ) )
    #else
        #define APP_MALLOC( ctx, size ) ( malloc( size ) )
        #define APP_FREE( ctx, ptr ) ( free( ptr ) )
    #endif
#endif

#ifndef APP_LOG
    #if defined(__cplusplus)
        #define APP_LOG( ctx, level, message ) ::printf( "%s\n", message )
    #else
        #define APP_LOG( ctx, level, message ) printf( "%s\n", message )
    #endif
#endif

#ifndef APP_FATAL_ERROR
    #if defined(__cplusplus)
        #define APP_FATAL_ERROR( ctx, message ) { ::printf( "FATAL ERROR: %s\n", message ); \
            ::MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); ::_flushall(); ::_exit( 0xff ); }
    #else
        #define APP_FATAL_ERROR( ctx, message ) { printf( "FATAL ERROR: %s\n", message ); \
            MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); _flushall(); _exit( 0xff ); }
    #endif
#endif

typedef struct APP_LOGCONTEXTA 
    {
    char lcName[ 40 ]; UINT lcOptions; UINT lcStatus; UINT lcLocks; UINT lcMsgBase; UINT lcDevice; UINT lcPktRate;
    DWORD lcPktData; DWORD lcPktMode; DWORD lcMoveMask; DWORD lcBtnDnMask; DWORD lcBtnUpMask; LONG lcInOrgX; 
    LONG lcInOrgY; LONG lcInOrgZ; LONG lcInExtX; LONG lcInExtY; LONG lcInExtZ; LONG lcOutOrgX; LONG lcOutOrgY;
    LONG lcOutOrgZ; LONG lcOutExtX; LONG lcOutExtY; LONG lcOutExtZ; DWORD lcSensX; DWORD lcSensY; DWORD lcSensZ;
    BOOL lcSysMode; int lcSysOrgX; int lcSysOrgY; int lcSysExtX; int lcSysExtY; DWORD lcSysSensX; DWORD lcSysSensY;
    } APP_LOGCONTEXTA;
typedef struct APP_AXIS { LONG axMin; LONG axMax; UINT axUnits; DWORD axResolution; } APP_AXIS;
typedef struct APP_PACKET { DWORD pkButtons; LONG pkX; LONG pkY; UINT pkNormalPressure; } APP_PACKET;
DECLARE_HANDLE( APP_HMGR );
DECLARE_HANDLE( APP_HCTX );
#define APP_WTI_DEVICES 100
#define APP_WTI_DDCTXS 400 /* 1.1 */
#define APP_CXO_MESSAGES 0x0004
#define APP_DVC_NPRESSURE 15
#define APP_PK_BUTTONS 0x0040 // button information
#define APP_PK_X 0x0080 // x axis
#define APP_PK_Y 0x0100 // y axis
#define APP_PK_NORMAL_PRESSURE 0x0400 // normal or tip pressure
#define APP_PACKETDATA APP_PK_X | APP_PK_Y | APP_PK_BUTTONS | APP_PK_NORMAL_PRESSURE
#define APP_PACKETMODE 0
#define APP_WT_PACKET 0x7FF0

struct app_t
    {
    void* memctx;
    void* logctx;
    void* fatalctx;
    app_interpolation_t interpolation;
    app_screenmode_t screenmode;

    BOOL initialized;
    BOOL closed;

    char exe_path[ 260 ];
    char userdata_path[ 260 ];
    char appdata_path[ 260 ];
    char const* cmdline;

    HINSTANCE hinstance;
    HWND hwnd;
    HDC hdc;
    HICON icon;
    BOOL has_focus;
    BOOL is_minimized;

    struct app_internal_opengl_t gl;
    HMODULE gl_dll;
    HGLRC gl_context; 
    PROC (APP_GLCALLTYPE* wglGetProcAddress) (LPCSTR);
    HGLRC (APP_GLCALLTYPE* wglCreateContext) (HDC);
    BOOL (APP_GLCALLTYPE* wglDeleteContext) (HGLRC);
    BOOL (APP_GLCALLTYPE* wglMakeCurrent) (HDC, HGLRC);
    BOOL (APP_GLCALLTYPE* wglSwapIntervalEXT) (int);

    HANDLE sound_notifications[ 2 ];
    HMODULE dsound_dll;
    IDirectSound8* dsound;
    IDirectSoundBuffer8* dsoundbuf; 
    HANDLE sound_thread_handle;
    volatile LONG exit_sound_thread;
    int sample_pairs_count;
    int sound_level;
    void (*sound_callback)( APP_S16* sample_pairs, int sample_pairs_count, void* user_data );
    void* sound_user_data;

    HCURSOR current_pointer;

    BOOL clip_cursor;
    RECT clip_rect;

    app_input_event_t input_events[ 1024 ];
    int input_count;

    int windowed_x;
    int windowed_y;
    int windowed_h;
    int windowed_w;
    int fullscreen_width;
    int fullscreen_height;

    int display_count;
    app_display_t displays[ 16 ];
    HMONITOR displays_hmonitor[ 16 ];

    struct  
        {
        HMODULE wintab_dll;
        APP_HCTX context;
        int max_pressure;

        UINT (WINAPI *WTInfo)( UINT, UINT, LPVOID );
        APP_HCTX (WINAPI *WTOpen)( HWND, APP_LOGCONTEXTA*, BOOL );
        BOOL (WINAPI *WTClose)( APP_HCTX );
        BOOL (WINAPI *WTEnable)( APP_HCTX, BOOL );
        BOOL (WINAPI *WTPacket)( APP_HCTX, UINT, LPVOID );
        } tablet;
    };


static app_key_t app_internal_vkcode_to_appkey( app_t* app, int vkcode )
    {
    int map[ 256 * 2 ] = { APP_KEY_INVALID, 0x00, APP_KEY_LBUTTON, 0x01, APP_KEY_RBUTTON, 0x02, APP_KEY_CANCEL, 0x03, APP_KEY_MBUTTON, 0x04, 
        APP_KEY_XBUTTON1, 0x05, APP_KEY_XBUTTON2, 0x06, -1, 0x07, APP_KEY_BACK, 0x08, APP_KEY_TAB, 0x09, -1, 0x0A, -1, 0x0B, APP_KEY_CLEAR, 0x0C, 
        APP_KEY_RETURN, 0x0D, -1, 0x0E, -1, 0x0F, APP_KEY_SHIFT, 0x10, APP_KEY_CONTROL, 0x11, APP_KEY_MENU, 0x12, APP_KEY_PAUSE, 0x13, 
        APP_KEY_CAPITAL, 0x14, APP_KEY_KANA, 0x15, -1, 0x16, APP_KEY_JUNJA, 0x17, APP_KEY_FINAL, 0x18, APP_KEY_HANJA, 0x19, -1, 0x1A, 
        APP_KEY_ESCAPE, 0x1B, APP_KEY_CONVERT, 0x1C, APP_KEY_NONCONVERT, 0x1D, APP_KEY_ACCEPT, 0x1E, APP_KEY_MODECHANGE, 0x1F, APP_KEY_SPACE, 0x20, 
        APP_KEY_PRIOR, 0x21, APP_KEY_NEXT, 0x22, APP_KEY_END, 0x23, APP_KEY_HOME, 0x24, APP_KEY_LEFT, 0x25, APP_KEY_UP, 0x26, APP_KEY_RIGHT, 0x27, 
        APP_KEY_DOWN, 0x28, APP_KEY_SELECT, 0x29, APP_KEY_PRINT, 0x2A, APP_KEY_EXEC, 0x2B, APP_KEY_SNAPSHOT, 0x2C, APP_KEY_INSERT, 0x2D, 
        APP_KEY_DELETE, 0x2E, APP_KEY_HELP, 0x2F, APP_KEY_0, 0x30, APP_KEY_1, 0x31, APP_KEY_2, 0x32, APP_KEY_3, 0x33, APP_KEY_4, 0x34, 
        APP_KEY_5, 0x35, APP_KEY_6, 0x36, APP_KEY_7, 0x37, APP_KEY_8, 0x38, APP_KEY_9, 0x39, -1, 0x3A, -1, 0x3B, -1, 0x3C, -1, 0x3D, -1, 0x3E, 
        -1, 0x3F, -1, 0x40, APP_KEY_A, 0x41, APP_KEY_B, 0x42, APP_KEY_C, 0x43, APP_KEY_D, 0x44, APP_KEY_E, 0x45, APP_KEY_F, 0x46, APP_KEY_G, 0x47, 
        APP_KEY_H, 0x48, APP_KEY_I, 0x49, APP_KEY_J, 0x4A, APP_KEY_K, 0x4B, APP_KEY_L, 0x4C, APP_KEY_M, 0x4D, APP_KEY_N, 0x4E, APP_KEY_O, 0x4F, 
        APP_KEY_P, 0x50, APP_KEY_Q, 0x51, APP_KEY_R, 0x52, APP_KEY_S, 0x53, APP_KEY_T, 0x54, APP_KEY_U, 0x55, APP_KEY_V, 0x56, APP_KEY_W, 0x57, 
        APP_KEY_X, 0x58, APP_KEY_Y, 0x59, APP_KEY_Z, 0x5A, APP_KEY_LWIN, 0x5B, APP_KEY_RWIN, 0x5C, APP_KEY_APPS, 0x5D, -1, 0x5E, APP_KEY_SLEEP, 0x5F, 
        APP_KEY_NUMPAD0, 0x60, APP_KEY_NUMPAD1, 0x61, APP_KEY_NUMPAD2, 0x62, APP_KEY_NUMPAD3, 0x63, APP_KEY_NUMPAD4, 0x64, APP_KEY_NUMPAD5, 0x65, 
        APP_KEY_NUMPAD6, 0x66, APP_KEY_NUMPAD7, 0x67, APP_KEY_NUMPAD8, 0x68, APP_KEY_NUMPAD9, 0x69, APP_KEY_MULTIPLY, 0x6A, APP_KEY_ADD, 0x6B, 
        APP_KEY_SEPARATOR, 0x6C, APP_KEY_SUBTRACT, 0x6D, APP_KEY_DECIMAL, 0x6E, APP_KEY_DIVIDE, 0x6F, APP_KEY_F1, 0x70, APP_KEY_F2, 0x71, 
        APP_KEY_F3, 0x72, APP_KEY_F4, 0x73, APP_KEY_F5, 0x74, APP_KEY_F6, 0x75, APP_KEY_F7, 0x76, APP_KEY_F8, 0x77, APP_KEY_F9, 0x78, 
        APP_KEY_F10, 0x79, APP_KEY_F11, 0x7A, APP_KEY_F12, 0x7B, APP_KEY_F13, 0x7C, APP_KEY_F14, 0x7D, APP_KEY_F15, 0x7E, APP_KEY_F16, 0x7F, 
        APP_KEY_F17, 0x80, APP_KEY_F18, 0x81, APP_KEY_F19, 0x82, APP_KEY_F20, 0x83, APP_KEY_F21, 0x84, APP_KEY_F22, 0x85, APP_KEY_F23, 0x86, 
        APP_KEY_F24, 0x87, -1, 0x88, -1, 0x89, -1, 0x8A, -1, 0x8B, -1, 0x8C, -1, 0x8D, -1, 0x8E, -1, 0x8F, APP_KEY_NUMLOCK, 0x90, 
        APP_KEY_SCROLL, 0x91, -1, 0x92, -1, 0x93, -1, 0x94, -1, 0x95, -1, 0x96, -1, 0x97, -1, 0x98, -1, 0x99, -1, 0x9A, -1, 0x9B, -1, 0x9C, -1, 0x9D,
        -1, 0x9E, -1, 0x9F, APP_KEY_LSHIFT, 0xA0, APP_KEY_RSHIFT, 0xA1, APP_KEY_LCONTROL, 0xA2, APP_KEY_RCONTROL, 0xA3, APP_KEY_LMENU, 0xA4,
        APP_KEY_RMENU, 0xA5, APP_KEY_BROWSER_BACK, 0xA6, APP_KEY_BROWSER_FORWARD, 0xA7, APP_KEY_BROWSER_REFRESH, 0xA8, APP_KEY_BROWSER_STOP, 0xA9, 
        APP_KEY_BROWSER_SEARCH, 0xAA, APP_KEY_BROWSER_FAVORITES, 0xAB, APP_KEY_BROWSER_HOME, 0xAC, APP_KEY_VOLUME_MUTE, 0xAD, 
        APP_KEY_VOLUME_DOWN, 0xAE, APP_KEY_VOLUME_UP, 0xAF, APP_KEY_MEDIA_NEXT_TRACK, 0xB0, APP_KEY_MEDIA_PREV_TRACK, 0xB1, APP_KEY_MEDIA_STOP, 0xB2,
        APP_KEY_MEDIA_PLAY_PAUSE, 0xB3, APP_KEY_LAUNCH_MAIL, 0xB4, APP_KEY_LAUNCH_MEDIA_SELECT, 0xB5, APP_KEY_LAUNCH_APP1, 0xB6, 
        APP_KEY_LAUNCH_APP2, 0xB7, -1, 0xB8, -1, 0xB9, APP_KEY_OEM_1, 0xBA, APP_KEY_OEM_PLUS, 0xBB, APP_KEY_OEM_COMMA, 0xBC, APP_KEY_OEM_MINUS, 0xBD, 
        APP_KEY_OEM_PERIOD, 0xBE, APP_KEY_OEM_2, 0xBF, APP_KEY_OEM_3, 0xC0, -1, 0xC1, -1, 0xC2, -1, 0xC3, -1, 0xC4, -1, 0xC5, -1, 0xC6, -1, 0xC7,
        -1, 0xC8, -1, 0xC9, -1, 0xCA, -1, 0xCB, -1, 0xCC, -1, 0xCD, -1, 0xCE, -1, 0xCF, -1, 0xD0, -1, 0xD1, -1, 0xD2, -1, 0xD3, -1, 0xD4, -1, 0xD5,
        -1, 0xD6, -1, 0xD7, -1, 0xD8, -1, 0xD9, -1, 0xDA, APP_KEY_OEM_4, 0xDB, APP_KEY_OEM_5, 0xDC, APP_KEY_OEM_6, 0xDD, APP_KEY_OEM_7, 0xDE,
        APP_KEY_OEM_8, 0xDF, -1, 0xE0, -1, 0xE1, APP_KEY_OEM_102, 0xE2, -1, 0xE3, -1, 0xE4, APP_KEY_PROCESSKEY, 0xE5, -1, 0xE6, -1, 0xE7, -1, 0xE8, 
        -1, 0xE9, -1, 0xEA, -1, 0xEB, -1, 0xEC, -1, 0xED, -1, 0xEE, -1, 0xEF, -1, 0xF0, -1, 0xF1, -1, 0xF2, -1, 0xF3, -1, 0xF4, -1, 0xF5,
        APP_KEY_ATTN, 0xF6, APP_KEY_CRSEL, 0xF7, APP_KEY_EXSEL, 0xF8, APP_KEY_EREOF, 0xF9, APP_KEY_PLAY, 0xFA, APP_KEY_ZOOM, 0xFB, 
        APP_KEY_NONAME, 0xFC, APP_KEY_PA1, 0xFD, APP_KEY_OEM_CLEAR, 0xFE, -1, 0xFF, };
    if( vkcode < 0 || vkcode >= sizeof( map ) / ( 2 * sizeof( *map ) ) ) return APP_KEY_INVALID;
    if( map[ vkcode * 2 + 1 ] != vkcode )
        {
        app_log( app, APP_LOG_LEVEL_ERROR, "Keymap definition error" );
        return APP_KEY_INVALID;
        }
    return (app_key_t) map[ vkcode * 2 ];
    }


static void app_internal_add_input_event( app_t* app, app_input_event_t* event )
    {
    if( app->has_focus )
        {
        if( app->input_count < sizeof( app->input_events ) / sizeof( *app->input_events ) )
            app->input_events[ app->input_count++ ] = *event;
        }
    }


static RECT app_internal_rect( int left, int top, int right, int bottom )
    {
    RECT r; r.left = left; r.top = top; r.right = right; r.bottom = bottom; return r;
    }


static BOOL app_internal_tablet_init( app_t* app )
    {
    app->tablet.wintab_dll = LoadLibraryA( "Wintab32.dll" );
    if( !app->tablet.wintab_dll ) return FALSE;

    app->tablet.WTInfo = ( UINT (WINAPI*)( UINT, UINT, LPVOID ) ) 
        (uintptr_t ) GetProcAddress( app->tablet.wintab_dll, "WTInfoA" );
    app->tablet.WTOpen = ( APP_HCTX (WINAPI*)( HWND, APP_LOGCONTEXTA*, BOOL ) )
        (uintptr_t ) GetProcAddress( app->tablet.wintab_dll, "WTOpenA" );
    app->tablet.WTClose = ( BOOL (WINAPI*)( APP_HCTX ) )
        (uintptr_t ) GetProcAddress( app->tablet.wintab_dll, "WTClose" );
    app->tablet.WTEnable = ( BOOL (WINAPI*)( APP_HCTX, BOOL ) )
        (uintptr_t ) GetProcAddress( app->tablet.wintab_dll, "WTEnable" );
    app->tablet.WTPacket = ( BOOL (WINAPI*)( APP_HCTX, UINT, LPVOID ) )
        (uintptr_t ) GetProcAddress( app->tablet.wintab_dll, "WTPacket" );

    if( !app->tablet.WTInfo( 0 ,0, NULL ) ) return FALSE; // checks if tablet is present
                                                      
    APP_LOGCONTEXTA log_context; 
    memset( &log_context, 0, sizeof( log_context ) );
    app->tablet.WTInfo( APP_WTI_DDCTXS, 0, &log_context );

    APP_AXIS pressure; 
    memset( &pressure, 0, sizeof( pressure ) );
    app->tablet.WTInfo( APP_WTI_DEVICES, APP_DVC_NPRESSURE, &pressure );
    app->tablet.max_pressure = pressure.axMax;

    log_context.lcPktData = APP_PACKETDATA;
    log_context.lcOptions |= APP_CXO_MESSAGES;
    log_context.lcPktMode = APP_PACKETMODE;
    log_context.lcMoveMask = APP_PACKETDATA;
    log_context.lcBtnUpMask = log_context.lcBtnDnMask;
    log_context.lcOutOrgX = 0;
    log_context.lcOutOrgY = 0;
    log_context.lcOutExtX = GetSystemMetrics( SM_CXSCREEN) ;
    log_context.lcOutExtY = -GetSystemMetrics( SM_CYSCREEN );

    app->tablet.context = app->tablet.WTOpen( app->hwnd, &log_context, FALSE );
    if( !app->tablet.context ) return FALSE;
    return TRUE;
}


static BOOL app_internal_tablet_term( app_t* app )
    {
    if( app->tablet.context ) app->tablet.WTClose( app->tablet.context );
    if( app->tablet.wintab_dll ) FreeLibrary( app->tablet.wintab_dll );
    return TRUE;
    }



static LRESULT CALLBACK app_internal_wndproc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
    app_t* app = (app_t*)(uintptr_t) GetWindowLongPtr( hwnd, GWLP_USERDATA );
    if( !app ) return DefWindowProc( hwnd, message, wparam, lparam);

    app_input_event_t input_event;

    switch( message )
        {
        case WM_CHAR: 
            input_event.type = APP_INPUT_CHAR; input_event.data.char_code = (char) wparam; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_LBUTTONDOWN: 
            input_event.type = APP_INPUT_KEY_DOWN; input_event.data.key = APP_KEY_LBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_LBUTTONUP: 
            input_event.type = APP_INPUT_KEY_UP; input_event.data.key = APP_KEY_LBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_LBUTTONDBLCLK: 
            input_event.type = APP_INPUT_DOUBLE_CLICK; input_event.data.key = APP_KEY_LBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_RBUTTONDOWN: 
            input_event.type = APP_INPUT_KEY_DOWN; input_event.data.key = APP_KEY_RBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_RBUTTONUP: 
            input_event.type = APP_INPUT_KEY_UP; input_event.data.key = APP_KEY_RBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_RBUTTONDBLCLK: 
            input_event.type = APP_INPUT_DOUBLE_CLICK; input_event.data.key = APP_KEY_RBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_MBUTTONDOWN: 
            input_event.type = APP_INPUT_KEY_DOWN; input_event.data.key = APP_KEY_MBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_MBUTTONUP: 
            input_event.type = APP_INPUT_KEY_UP; input_event.data.key = APP_KEY_MBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_MBUTTONDBLCLK: 
            input_event.type = APP_INPUT_DOUBLE_CLICK; input_event.data.key = APP_KEY_MBUTTON; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_XBUTTONDOWN: 
            input_event.type = APP_INPUT_KEY_DOWN; input_event.data.key = HIWORD( wparam ) == 1 ? APP_KEY_XBUTTON1 :APP_KEY_XBUTTON2; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_XBUTTONUP: 
            input_event.type = APP_INPUT_KEY_UP; input_event.data.key = HIWORD( wparam ) == 1 ? APP_KEY_XBUTTON1 :APP_KEY_XBUTTON2; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_XBUTTONDBLCLK: 
            input_event.type = APP_INPUT_DOUBLE_CLICK; input_event.data.key = HIWORD( wparam ) == 1 ? APP_KEY_XBUTTON1 :APP_KEY_XBUTTON2; 
            app_internal_add_input_event( app, &input_event ); 
            break;
        case WM_SYSKEYDOWN: 
        case WM_KEYDOWN: 
            {
            input_event.type = APP_INPUT_KEY_DOWN; 
            WPARAM vkcode = wparam;
            UINT scancode = (UINT)( ( lparam & 0x00ff0000 ) >> 16 );
            int extended  = ( lparam & 0x01000000 ) != 0;
            UINT const maptype = 3; //MAPVK_VSC_TO_VK_EX
            switch( vkcode ) 
                {
                case VK_SHIFT:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) MapVirtualKey( scancode, maptype ) ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                case VK_CONTROL:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, extended ? VK_RCONTROL : VK_LCONTROL ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                case VK_MENU:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, extended ? VK_RMENU : VK_LMENU ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                default:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;    
                }
            } break;
        case WM_SYSKEYUP: 
        case WM_KEYUP: 
            {
            input_event.type = APP_INPUT_KEY_UP; 
            WPARAM vkcode = wparam;
            UINT scancode = (UINT)( ( lparam & 0x00ff0000 ) >> 16 );
            int extended  = ( lparam & 0x01000000 ) != 0;
            UINT const maptype = 3; //MAPVK_VSC_TO_VK_EX
            switch( vkcode ) 
                {
                case VK_SHIFT:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) MapVirtualKey( scancode, maptype ) ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                case VK_CONTROL:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, extended ? VK_RCONTROL : VK_LCONTROL ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                case VK_MENU:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 

                    input_event.data.key = app_internal_vkcode_to_appkey( app, extended ? VK_RMENU : VK_LMENU ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;
                default:
                    input_event.data.key = app_internal_vkcode_to_appkey( app, (int) wparam ); 
                    app_internal_add_input_event( app, &input_event ); 
                    break;    
                }
            } break;

        case WM_MOUSEWHEEL: input_event.type = APP_INPUT_KEY_DOWN; input_event.data.key = APP_KEY_LBUTTON;
            if( app->has_focus )
                {
                float const microsoft_mouse_wheel_constant = 120.0f;
                float wheel_delta = ( (float) GET_WHEEL_DELTA_WPARAM( wparam ) ) / microsoft_mouse_wheel_constant;
                if( app->input_count > 0 && app->input_events[ app->input_count - 1 ].type == APP_INPUT_SCROLL_WHEEL )
                    {
                    app_input_event_t* event = &app->input_events[ app->input_count - 1 ];
                    event->data.wheel_delta += wheel_delta;                 
                    }
                else
                    {
                    input_event.type = APP_INPUT_SCROLL_WHEEL;
                    input_event.data.wheel_delta = wheel_delta;
                    app_internal_add_input_event( app, &input_event ); 
                    }
                }
            break;

        case WM_MOUSEMOVE:
            if( app->has_focus )
                {
                POINT p;
                GetCursorPos( &p ); 
                ScreenToClient( app->hwnd, &p );
                int mouse_x = p.x;
                int mouse_y = p.y;

                input_event.type = APP_INPUT_MOUSE_MOVE; 
                input_event.data.mouse_pos.x = mouse_x; 
                input_event.data.mouse_pos.y = mouse_y; 
                app_internal_add_input_event( app, &input_event ); 
                }
            break;

        case WM_INPUT: 
            {
            RAWINPUT raw;
            UINT size = sizeof( raw );
            GetRawInputData( (HRAWINPUT) lparam, RID_INPUT, &raw, &size, sizeof( RAWINPUTHEADER ) );    
            if( raw.header.dwType == RIM_TYPEMOUSE ) 
                {
                float dx = (float) raw.data.mouse.lLastX;
                float dy = (float) raw.data.mouse.lLastY;

                float const microsoft_mouse_dpi_constant = 400.0f; // Apparently, most mice are meant to run at 400 DPI. This might be wrong.
                dx /= microsoft_mouse_dpi_constant;
                dy /= microsoft_mouse_dpi_constant;

                if( app->input_count > 0 && app->input_events[ app->input_count - 1 ].type == APP_INPUT_MOUSE_DELTA )
                    {
                    app_input_event_t* event = &app->input_events[ app->input_count - 1 ];
                    event->data.mouse_delta.x += dx;                    
                    event->data.mouse_delta.y += dy;                    
                    }
                else
                    {
                    input_event.type = APP_INPUT_MOUSE_DELTA;
                    input_event.data.mouse_delta.x = dx;                    
                    input_event.data.mouse_delta.y = dy;                    
                    app_internal_add_input_event( app, &input_event ); 
                    }
                } 
            break;
            }

        case APP_WT_PACKET:
            {
            APP_PACKET packet;
            memset( &packet, 0, sizeof( packet ) );
            if( (APP_HCTX) lparam == app->tablet.context && 
                app->tablet.WTPacket( app->tablet.context, (UINT) wparam, &packet ) )
                {
                POINT p;
                p.x = packet.pkX;
                p.y = packet.pkY;
                ScreenToClient( app->hwnd, &p );
                int pen_x = p.x;
                int pen_y = p.y;

                input_event.type = APP_INPUT_TABLET;
                input_event.data.tablet.x = pen_x; 
                input_event.data.tablet.y = pen_y; 
                input_event.data.tablet.pressure = (float) packet.pkNormalPressure / (float) app->tablet.max_pressure;
                input_event.data.tablet.tip = ( packet.pkButtons & 1 ) ? APP_PRESSED : APP_NOT_PRESSED;
                input_event.data.tablet.lower = ( packet.pkButtons & 2 ) ? APP_PRESSED : APP_NOT_PRESSED;
                input_event.data.tablet.upper = ( packet.pkButtons & 4 ) ? APP_PRESSED : APP_NOT_PRESSED;
                app_internal_add_input_event( app, &input_event ); 
                }
            } break;

        case WM_SETCURSOR:
            if( LOWORD( lparam ) == HTCLIENT )
                {
                SetCursor( app->current_pointer );
                return 0;
                }
            break;


        case WM_WINDOWPOSCHANGED:
            {
            if( app->screenmode == APP_SCREENMODE_FULLSCREEN )
                {
                RECT wr, cr;
                GetWindowRect( app->hwnd, &wr );
                GetClientRect( app->hwnd, &cr );
                if( wr.right - wr.left == cr.right - cr.left && wr.bottom - wr.top == cr.bottom - cr.top )
                    {
                    if( cr.right - cr.left != app->fullscreen_width || cr.bottom - cr.top != app->fullscreen_height )
                        app_screenmode( app, APP_SCREENMODE_WINDOW );
                    }
                }

            if( app->clip_cursor ) 
                {
                RECT r = app->clip_rect;
                ClientToScreen( app->hwnd, (POINT*)&r );
                ClientToScreen( app->hwnd, ( (POINT*)&r ) + 1 );
                ClipCursor( &r );
                }

            } break;

        case WM_SIZE:
            {
            if( wparam == SIZE_MAXIMIZED )
                {
                WINDOWPLACEMENT placement;
                placement.length = sizeof( placement );
                GetWindowPlacement( app->hwnd, &placement );
                app->windowed_x = placement.rcNormalPosition.left;
                app->windowed_y = placement.rcNormalPosition.top;
                app->windowed_w = placement.rcNormalPosition.right - placement.rcNormalPosition.left;
                app->windowed_h = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top;
                }

            RECT r;
            GetClientRect( app->hwnd, &r );     
            app_internal_opengl_resize( &app->gl, r.right - r.left, r.bottom - r.top );
            } break;


        case WM_ACTIVATEAPP:
            app->has_focus = (BOOL) wparam;
            if( app->has_focus ) 
                {
                app->is_minimized = FALSE;
                if( app->clip_cursor ) 
                    {
                    RECT r = app->clip_rect;
                    ClientToScreen( app->hwnd, (POINT*)&r );
                    ClientToScreen( app->hwnd, ( (POINT*)&r ) + 1 );
                    ClipCursor( &r );
                    }
                }
            else
                {
                ClipCursor( NULL );
                }
            
            break;
            
        case WM_SYSCOMMAND:
            if( ( wparam & 0xFFF0 ) == SC_MINIMIZE ) app->is_minimized = TRUE;
            break;

        case WM_CLOSE:
            app->closed = TRUE;
            return 0;
            break;
        }

    return DefWindowProc( hwnd, message, wparam, lparam);
    }

    
static BOOL CALLBACK app_internal_monitorenumproc( HMONITOR hmonitor, HDC dc, LPRECT rect, LPARAM data )
    {
    (void) dc;
    app_t* app = (app_t*) data;

    if( app->display_count >= sizeof( app->displays ) / sizeof( *app->displays ) ) return FALSE;
    app->displays_hmonitor[ app->display_count ] = hmonitor;
    app_display_t* display = &app->displays[ app->display_count++ ];
    
    display->x = rect->left;
    display->y = rect->top;
    display->width = rect->right - rect->left;
    display->height = rect->bottom - rect->top;

    #ifdef __cplusplus
        MONITORINFOEXA mi;
        mi.cbSize = sizeof( mi );
        BOOL res = GetMonitorInfoA( hmonitor, &mi );
        if( res && strlen( mi.szDevice ) >= sizeof( display->id ) ) res = FALSE;
        strcpy( display->id, res ? mi.szDevice : "" ) ;
    #else
        MONITORINFOEXA mi;
        mi.cbSize = sizeof( mi );
        BOOL res = GetMonitorInfoA( hmonitor, (LPMONITORINFO)&mi );
        if( res && strlen( mi.szDevice ) >= sizeof( display->id ) ) res = FALSE;
        strcpy( display->id, res ? mi.szDevice : "" ) ;
    #endif

    return TRUE;
    }


static void app_internal_app_default_cursor( app_t* app )
    {
    APP_U32 pointer_pixels[ 256 * 256 ];
    int pointer_width, pointer_height, pointer_hotspot_x, pointer_hotspot_y; 
    app_pointer_default( app, &pointer_width, &pointer_height, pointer_pixels, &pointer_hotspot_x, &pointer_hotspot_y );
    app_pointer( app, pointer_width, pointer_height, pointer_pixels, pointer_hotspot_x, pointer_hotspot_y );
    }


#pragma warning( push )
#pragma warning( disable: 4533 ) // initialization of 'wc' is skipped by 'goto init_failed'

int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx )
    {
    int result = 0xff;

    // Init app instance
    app_t* app = (app_t*) APP_MALLOC( memctx, sizeof( app_t ) );
    memset( app, 0, sizeof( *app ) );
    app->memctx = memctx;
    app->logctx = logctx;
    app->fatalctx = fatalctx;
    app->interpolation = APP_INTERPOLATION_LINEAR;
    app->screenmode = APP_SCREENMODE_FULLSCREEN;

    // Log start message
    char msg[ 64 ];
    time_t t = time( NULL );
    struct tm* start = localtime( &t );
    sprintf( msg, "Application started %02d:%02d:%02d %04d-%02d-%02d.", 
        start->tm_hour, start->tm_min, start->tm_sec, start->tm_year + 1900, start->tm_mon + 1, start->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );

    // Increase timing precision
    TIMECAPS tc;
    if( timeGetDevCaps( &tc, sizeof( TIMECAPS ) ) == TIMERR_NOERROR ) 
        timeBeginPeriod( tc.wPeriodMin );

    // Get instance handle
    app->hinstance = GetModuleHandle( NULL );

    // Retrieve the path of our executable
    GetModuleFileNameA( 0, app->exe_path, sizeof( app->exe_path ) );

    // Retrieve user data path
    SHGetFolderPathA( NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, app->userdata_path ); 

    // Retrieve app data path
    SHGetFolderPathA( NULL, CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, app->appdata_path ); 

    // Get command line string
    app->cmdline = GetCommandLineA();

    // Load a default Arrow cursor     
    app_internal_app_default_cursor( app );

    // Load first icon in the exe and use as app icon
    app->icon = LoadIconA( app->hinstance , MAKEINTRESOURCEA( 1 ) );

    // List all displays
    app->display_count = 0;
    EnumDisplayMonitors( NULL, NULL, app_internal_monitorenumproc, (LPARAM) app );
    if( app->display_count <= 0 ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to get display info" ); goto init_failed;  }

    // Setup the main application window
    app->windowed_w = app->displays[ 0 ].width - app->displays[ 0 ].width / 6;
    app->windowed_h = app->displays[ 0 ].height - app->displays[ 0 ].height / 6; 
    app->windowed_x = ( app->displays[ 0 ].width - app->windowed_w ) /  2;
    app->windowed_y = ( app->displays[ 0 ].height - app->windowed_h ) / 2;

    app->fullscreen_width = app->displays[ 0 ].width;
    app->fullscreen_height = app->displays[ 0 ].height;

    RECT winrect = app_internal_rect( app->windowed_x, app->windowed_y, 
        app->windowed_x + app->windowed_w, app->windowed_y + app->windowed_h );
    AdjustWindowRect( &winrect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE );

    WNDCLASSEX wc = { sizeof( WNDCLASSEX ), CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,  
        (WNDPROC) app_internal_wndproc, 0, 0, 0, 0, 0, 0, 0, TEXT( "app_wc" ), 0 };
    wc.hInstance = app->hinstance; wc.hIcon = app->icon; wc.hCursor = app->current_pointer; 
    wc.hbrBackground = (HBRUSH) GetStockObject( BLACK_BRUSH ); wc.hIconSm = app->icon;
    RegisterClassEx( &wc );
    app->hwnd = CreateWindowEx( 0, wc.lpszClassName, 0, WS_OVERLAPPEDWINDOW, app->windowed_x, app->windowed_y, 
        winrect.right - winrect.left, winrect.bottom - winrect.top, (HWND) 0, (HMENU) 0, app->hinstance, 0 );
    if( !app->hwnd ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to create window." ); goto init_failed; }
    ShowWindow( app->hwnd, SW_HIDE );
    app->hdc = GetDC( app->hwnd );
    app->has_focus = TRUE;
    app->is_minimized = FALSE;

    // Store app pointer with window
    #pragma warning( push )
    #pragma warning( disable: 4244 ) // conversion from 'LONG_PTR' to 'LONG', possible loss of data
    SetWindowLongPtr( app->hwnd, GWLP_USERDATA, (LONG_PTR) app );
    #pragma warning( pop )

    // Windows specific OpenGL initialization
    app->gl_dll = LoadLibraryA( "opengl32.dll" );
    if( !app->gl_dll ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to load opengl32.dll" ); goto init_failed; }
    app->wglGetProcAddress = (PROC(APP_GLCALLTYPE*)(LPCSTR)) (uintptr_t) GetProcAddress( app->gl_dll, "wglGetProcAddress" );
    if( !app->wglGetProcAddress ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to find wglGetProcAddress" ); goto init_failed; }
    app->wglCreateContext = (HGLRC(APP_GLCALLTYPE*)(HDC)) (uintptr_t) GetProcAddress( app->gl_dll, "wglCreateContext" );
    if( !app->wglCreateContext ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to find wglCreateContext" ); goto init_failed; }
    app->wglDeleteContext = (BOOL(APP_GLCALLTYPE*)(HGLRC)) (uintptr_t) GetProcAddress( app->gl_dll, "wglDeleteContext" );
    if( !app->wglDeleteContext ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to find wglDeleteContext" ); goto init_failed; }
    app->wglMakeCurrent = (BOOL(APP_GLCALLTYPE*)(HDC, HGLRC)) (uintptr_t) GetProcAddress( app->gl_dll, "wglMakeCurrent" );
    if( !app->wglMakeCurrent ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to find wglMakeCurrent" ); goto init_failed; }
    
    PIXELFORMATDESCRIPTOR pfd;
    memset( &pfd, 0, sizeof( pfd ) );
    pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    BOOL res = SetPixelFormat( app->hdc, ChoosePixelFormat( app->hdc, &pfd ), &pfd );
    if( !res ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to set pixel format" ); goto init_failed; }

    app->gl_context = app->wglCreateContext( app->hdc ); 
    if( !app->gl_context ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to create OpenGL context" ); goto init_failed; }
    res = app->wglMakeCurrent( app->hdc, app->gl_context );
    if( !res ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to activate OpenGl Context" ); goto init_failed; }

    app->wglSwapIntervalEXT = (BOOL (APP_GLCALLTYPE*)(int)) (uintptr_t) app->wglGetProcAddress( "wglSwapIntervalEXT" );
    if( app->wglSwapIntervalEXT ) app->wglSwapIntervalEXT( 1 );

    // Attempt to bind opengl functions using GetProcAddress
    app->gl.glCreateShader = ( APP_GLuint (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) GetProcAddress( app->gl_dll, "glCreateShader" );
    app->gl.glShaderSource = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLchar const* const*, APP_GLint const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glShaderSource" );
    app->gl.glCompileShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glCompileShader" );
    app->gl.glGetShaderiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGetShaderiv" );
    app->gl.glCreateProgram = ( APP_GLuint (APP_GLCALLTYPE*) (void) ) (uintptr_t) GetProcAddress( app->gl_dll, "glCreateProgram" );
    app->gl.glAttachShader = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glAttachShader" );
    app->gl.glBindAttribLocation = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint, APP_GLchar const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glBindAttribLocation" );
    app->gl.glLinkProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glLinkProgram" );
    app->gl.glGetProgramiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGetProgramiv" );
    app->gl.glGenBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGenBuffers" );
    app->gl.glBindBuffer = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glBindBuffer" );
    app->gl.glEnableVertexAttribArray = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glEnableVertexAttribArray" );
    app->gl.glVertexAttribPointer = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLint, APP_GLenum, APP_GLboolean, APP_GLsizei, void const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glVertexAttribPointer" );
    app->gl.glGenVertexArrays = (void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGenVertexArrays" );
    app->gl.glBindVertexArray = (void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glBindVertexArray" );
    app->gl.glGenTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGenTextures" );
    app->gl.glEnable = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) GetProcAddress( app->gl_dll, "glEnable" );
    app->gl.glActiveTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) GetProcAddress( app->gl_dll, "glActiveTexture" );
    app->gl.glBindTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glBindTexture" );
    app->gl.glTexParameteri = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLenum, APP_GLint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glTexParameteri" );
    app->gl.glDeleteBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glDeleteBuffers" );
    app->gl.glDeleteTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glDeleteTextures" );
    app->gl.glBufferData = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLsizeiptr, void const *, APP_GLenum) ) (uintptr_t) GetProcAddress( app->gl_dll, "glBufferData" );
    app->gl.glUseProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glUseProgram" );
    app->gl.glUniform1i = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glUniform1i" );
    app->gl.glUniform3f = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) GetProcAddress( app->gl_dll, "glUniform3f" );
    app->gl.glGetUniformLocation = ( APP_GLint (APP_GLCALLTYPE*) (APP_GLuint, APP_GLchar const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGetUniformLocation" );
    app->gl.glTexImage2D = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei, APP_GLint, APP_GLenum, APP_GLenum, void const*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glTexImage2D" );
    app->gl.glClearColor = ( void (APP_GLCALLTYPE*) (APP_GLfloat, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) GetProcAddress( app->gl_dll, "glClearColor" );
    app->gl.glClear = ( void (APP_GLCALLTYPE*) (APP_GLbitfield) ) (uintptr_t) GetProcAddress( app->gl_dll, "glClear" );
    app->gl.glDrawArrays = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLsizei) ) (uintptr_t) GetProcAddress( app->gl_dll, "glDrawArrays" );
    app->gl.glViewport = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei) ) (uintptr_t) GetProcAddress( app->gl_dll, "glViewport" );
    app->gl.glDeleteShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glDeleteShader" );
    app->gl.glDeleteProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) GetProcAddress( app->gl_dll, "glDeleteProgram" );
    #ifdef APP_REPORT_SHADER_ERRORS
        app->gl.glGetShaderInfoLog = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLsizei*, APP_GLchar*) ) (uintptr_t) GetProcAddress( app->gl_dll, "glGetShaderInfoLog" );
    #endif

    // Any opengl functions which didn't bind, try binding them using wglGetProcAddrss
    if( !app->gl.glCreateShader ) app->gl.glCreateShader = ( APP_GLuint (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) app->wglGetProcAddress( "glCreateShader" );
    if( !app->gl.glShaderSource ) app->gl.glShaderSource = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLchar const* const*, APP_GLint const*) ) (uintptr_t) app->wglGetProcAddress( "glShaderSource" );
    if( !app->gl.glCompileShader ) app->gl.glCompileShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glCompileShader" );
    if( !app->gl.glGetShaderiv ) app->gl.glGetShaderiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) app->wglGetProcAddress( "glGetShaderiv" );
    if( !app->gl.glCreateProgram ) app->gl.glCreateProgram = ( APP_GLuint (APP_GLCALLTYPE*) (void) ) (uintptr_t) app->wglGetProcAddress( "glCreateProgram" );
    if( !app->gl.glAttachShader ) app->gl.glAttachShader = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glAttachShader" );
    if( !app->gl.glBindAttribLocation ) app->gl.glBindAttribLocation = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint, APP_GLchar const*) ) (uintptr_t) app->wglGetProcAddress( "glBindAttribLocation" );
    if( !app->gl.glLinkProgram ) app->gl.glLinkProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glLinkProgram" );
    if( !app->gl.glGetProgramiv ) app->gl.glGetProgramiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) app->wglGetProcAddress( "glGetProgramiv" );
    if( !app->gl.glGenBuffers ) app->gl.glGenBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) app->wglGetProcAddress( "glGenBuffers" );
    if( !app->gl.glBindBuffer ) app->gl.glBindBuffer = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glBindBuffer" );
    if( !app->gl.glEnableVertexAttribArray ) app->gl.glEnableVertexAttribArray = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glEnableVertexAttribArray" );
    if( !app->gl.glVertexAttribPointer ) app->gl.glVertexAttribPointer = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLint, APP_GLenum, APP_GLboolean, APP_GLsizei, void const*) ) (uintptr_t) app->wglGetProcAddress( "glVertexAttribPointer" );
    if( !app->gl.glGenVertexArrays ) app->gl.glGenVertexArrays = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) app->wglGetProcAddress( "glGenVertexArrays" );
    if( !app->gl.glBindVertexArray ) app->gl.glBindVertexArray = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glBindVertexArray" );
    if( !app->gl.glGenTextures ) app->gl.glGenTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) app->wglGetProcAddress( "glGenTextures" );
    if( !app->gl.glEnable ) app->gl.glEnable = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) app->wglGetProcAddress( "glEnable" );
    if( !app->gl.glActiveTexture ) app->gl.glActiveTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) app->wglGetProcAddress( "glActiveTexture" );
    if( !app->gl.glBindTexture ) app->gl.glBindTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glBindTexture" );
    if( !app->gl.glTexParameteri ) app->gl.glTexParameteri = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLenum, APP_GLint) ) (uintptr_t) app->wglGetProcAddress( "glTexParameteri" );
    if( !app->gl.glDeleteBuffers ) app->gl.glDeleteBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) app->wglGetProcAddress( "glDeleteBuffers" );
    if( !app->gl.glDeleteTextures ) app->gl.glDeleteTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) app->wglGetProcAddress( "glDeleteTextures" );
    if( !app->gl.glBufferData ) app->gl.glBufferData = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLsizeiptr, void const *, APP_GLenum) ) (uintptr_t) app->wglGetProcAddress( "glBufferData" );
    if( !app->gl.glUseProgram ) app->gl.glUseProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glUseProgram" );
    if( !app->gl.glUniform1i ) app->gl.glUniform1i = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint) ) (uintptr_t) app->wglGetProcAddress( "glUniform1i" );
    if( !app->gl.glUniform3f ) app->gl.glUniform3f = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) app->wglGetProcAddress( "glUniform3f" );
    if( !app->gl.glGetUniformLocation ) app->gl.glGetUniformLocation = ( APP_GLint (APP_GLCALLTYPE*) (APP_GLuint, APP_GLchar const*) ) (uintptr_t) app->wglGetProcAddress( "glGetUniformLocation" );
    if( !app->gl.glTexImage2D ) app->gl.glTexImage2D = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei, APP_GLint, APP_GLenum, APP_GLenum, void const*) ) (uintptr_t) app->wglGetProcAddress( "glTexImage2D" );
    if( !app->gl.glClearColor ) app->gl.glClearColor = ( void (APP_GLCALLTYPE*) (APP_GLfloat, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) app->wglGetProcAddress( "glClearColor" );
    if( !app->gl.glClear ) app->gl.glClear = ( void (APP_GLCALLTYPE*) (APP_GLbitfield) ) (uintptr_t) app->wglGetProcAddress( "glClear" );
    if( !app->gl.glDrawArrays ) app->gl.glDrawArrays = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLsizei) ) (uintptr_t) app->wglGetProcAddress( "glDrawArrays" );
    if( !app->gl.glViewport ) app->gl.glViewport = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei) ) (uintptr_t) app->wglGetProcAddress( "glViewport" );
    if( !app->gl.glDeleteShader ) app->gl.glDeleteShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glDeleteShader" );
    if( !app->gl.glDeleteProgram ) app->gl.glDeleteProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) app->wglGetProcAddress( "glDeleteProgram" );
    #ifdef APP_REPORT_SHADER_ERRORS
        if( !app->gl.glGetShaderInfoLog ) app->gl.glGetShaderInfoLog = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLsizei*, APP_GLchar*) ) (uintptr_t) app->wglGetProcAddress( "glGetShaderInfoLog" );
    #endif

    // Report error if any gl function was not found.
    if( !app->gl.glCreateShader ) { app_fatal_error( app, "Could not find function glCreateShader." ); goto init_failed; }
    if( !app->gl.glShaderSource ) { app_fatal_error( app, "Could not find function glShaderSource." ); goto init_failed; }
    if( !app->gl.glCompileShader ) { app_fatal_error( app, "Could not find function glCompileShader." ); goto init_failed; }
    if( !app->gl.glGetShaderiv ) { app_fatal_error( app, "Could not find function glGetShaderiv." ); goto init_failed; }
    if( !app->gl.glCreateProgram ) { app_fatal_error( app, "Could not find function glCreateProgram." ); goto init_failed; }
    if( !app->gl.glAttachShader ) { app_fatal_error( app, "Could not find function glAttachShader." ); goto init_failed; }
    if( !app->gl.glBindAttribLocation ) { app_fatal_error( app, "Could not find function glBindAttribLocation." ); goto init_failed; }
    if( !app->gl.glLinkProgram ) { app_fatal_error( app, "Could not find function glLinkProgram." ); goto init_failed; }
    if( !app->gl.glGetProgramiv ) { app_fatal_error( app, "Could not find function glGetProgramiv." ); goto init_failed; }
    if( !app->gl.glGenBuffers ) { app_fatal_error( app, "Could not find function glGenBuffers." ); goto init_failed; }
    if( !app->gl.glBindBuffer ) { app_fatal_error( app, "Could not find function glBindBuffer." ); goto init_failed; }
    if( !app->gl.glEnableVertexAttribArray ) { app_fatal_error( app, "Could not find function glEnableVertexAttribArray." ); goto init_failed; }
    if( !app->gl.glVertexAttribPointer ) { app_fatal_error( app, "Could not find function glVertexAttribPointer." ); goto init_failed; }
    if( !app->gl.glGenVertexArrays ) { app_fatal_error( app, "Could not find function glGenVertexArrays." ); goto init_failed; }
    if( !app->gl.glBindVertexArray ) { app_fatal_error( app, "Could not find function glBindVertexArray." ); goto init_failed; }
    if( !app->gl.glGenTextures ) { app_fatal_error( app, "Could not find function glGenTextures." ); goto init_failed; }
    if( !app->gl.glEnable ) { app_fatal_error( app, "Could not find function glEnable." ); goto init_failed; }
    if( !app->gl.glActiveTexture ) { app_fatal_error( app, "Could not find function glActiveTexture." ); goto init_failed; }
    if( !app->gl.glBindTexture ) { app_fatal_error( app, "Could not find function glBindTexture." ); goto init_failed; }
    if( !app->gl.glTexParameteri ) { app_fatal_error( app, "Could not find function glTexParameteri." ); goto init_failed; }
    if( !app->gl.glDeleteBuffers ) { app_fatal_error( app, "Could not find function glDeleteBuffers." ); goto init_failed; }
    if( !app->gl.glDeleteTextures ) { app_fatal_error( app, "Could not find function glDeleteTextures." ); goto init_failed; }
    if( !app->gl.glBufferData ) { app_fatal_error( app, "Could not find function glBufferData." ); goto init_failed; }
    if( !app->gl.glUseProgram ) { app_fatal_error( app, "Could not find function glUseProgram." ); goto init_failed; }
    if( !app->gl.glUniform1i ) { app_fatal_error( app, "Could not find function glUniform1i." ); goto init_failed; }
    if( !app->gl.glUniform3f ) { app_fatal_error( app, "Could not find function glUniform3f." ); goto init_failed; }
    if( !app->gl.glGetUniformLocation ) { app_fatal_error( app, "Could not find function glGetUniformLocation." ); goto init_failed; }
    if( !app->gl.glTexImage2D ) { app_fatal_error( app, "Could not find function glTexImage2D." ); goto init_failed; }
    if( !app->gl.glClearColor ) { app_fatal_error( app, "Could not find function glClearColor." ); goto init_failed; }
    if( !app->gl.glClear ) { app_fatal_error( app, "Could not find function glClear." ); goto init_failed; }
    if( !app->gl.glDrawArrays ) { app_fatal_error( app, "Could not find function glDrawArrays." ); goto init_failed; }
    if( !app->gl.glViewport ) { app_fatal_error( app, "Could not find function glViewport." ); goto init_failed; }
    if( !app->gl.glDeleteShader ) { app_fatal_error( app, "Could not find function glDeleteShader." ); goto init_failed; }
    if( !app->gl.glDeleteProgram ) { app_fatal_error( app, "Could not find function glDeleteProgram." ); goto init_failed; }
    #ifdef APP_REPORT_SHADER_ERRORS
        if( !app->gl.glGetShaderInfoLog ) { app_fatal_error( app, "Could not find function glGetShaderInfoLog." ); goto init_failed; }
    #endif

    // Platform independent OpenGL initialization
    int width = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_width : app->windowed_w;
    int height = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_height: app->windowed_h;
    if( !app_internal_opengl_init( app, &app->gl, app->interpolation, width, height ) )
        { 
        app_log( app, APP_LOG_LEVEL_ERROR, "Failed to initialize OpenGL" ); 
        goto init_failed; 
        }

    app->sound_notifications[ 0 ] = CreateEventA( NULL, FALSE, FALSE, NULL );
    app->sound_notifications[ 1 ] = CreateEventA( NULL, FALSE, FALSE, NULL );


    app->dsound_dll = LoadLibraryA( "dsound.dll" );
    if( !app->dsound_dll ) app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't load dsound.dll. Sound disabled." );

    if( app->dsound_dll )
        {
        HRESULT (WINAPI *DirectSoundCreate8)(LPCGUID,LPDIRECTSOUND8*,LPUNKNOWN) = ( HRESULT (WINAPI*)(LPCGUID,LPDIRECTSOUND8*,LPUNKNOWN) ) 
            (uintptr_t) GetProcAddress( (HMODULE) app->dsound_dll, "DirectSoundCreate8" ); 
        if( !DirectSoundCreate8 ) 
            { 
            app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't find DirectSoundCreate. Sound disabled." ); 
            FreeLibrary( app->dsound_dll );
            app->dsound_dll = 0;
            }
        if( DirectSoundCreate8 )
            {
            HRESULT hr = DirectSoundCreate8( NULL, &app->dsound, NULL );
            if( FAILED( hr ) || !app->dsound ) 
                { 
                app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't create DirectSound object. Sound disabled." ); 
                DirectSoundCreate8 = 0; 
                FreeLibrary( app->dsound_dll );
                app->dsound_dll = 0;
                }   
            else
                {
                hr = IDirectSound8_SetCooperativeLevel( app->dsound, app->hwnd, DSSCL_NORMAL);
                if( FAILED( hr ) ) 
                    { 
                    app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't set cooperative level for DirectSound object. Sound disabled." ); 
                    IDirectSound8_Release( app->dsound );
                    app->dsound = 0;
                    DirectSoundCreate8 = 0; 
                    FreeLibrary( app->dsound_dll );
                    app->dsound_dll = 0;
                    }
                }
            }
        }
    app->sound_thread_handle = INVALID_HANDLE_VALUE;

    USHORT const USAGE_PAGE_GENERIC = ((USHORT) 0x01);
    USHORT const USAGE_GENERIC_MOUSE = ((USHORT) 0x02);

    RAWINPUTDEVICE rid[ 1 ];
    rid[ 0 ].usUsagePage = USAGE_PAGE_GENERIC; 
    rid[ 0 ].usUsage = USAGE_GENERIC_MOUSE; 
    rid[ 0 ].dwFlags = RIDEV_INPUTSINK;   
    rid[ 0 ].hwndTarget = app->hwnd;
    RegisterRawInputDevices( rid, 1, sizeof( *rid ) );

    if( !app_internal_tablet_init( app ) ) app_log( app, APP_LOG_LEVEL_WARNING, "WinTab initialization failed - tablet not available" );

    result = app_proc( app, user_data );

init_failed:
    if( !app_internal_tablet_term( app ) ) app_log( app, APP_LOG_LEVEL_WARNING, "WinTab termination failed" );
    if( app->sound_thread_handle != INVALID_HANDLE_VALUE )
        {
        InterlockedExchange( &app->exit_sound_thread, 1 );
        WaitForSingleObject( app->sound_thread_handle, INFINITE );
        CloseHandle( app->sound_thread_handle );
        }
    if( app->dsoundbuf ) IDirectSoundBuffer8_Release( app->dsoundbuf );
    if( app->dsound ) IDirectSound8_Release( app->dsound );
    if( app->dsound_dll ) FreeLibrary( app->dsound_dll );
    if( app->sound_notifications[ 0 ] ) CloseHandle( app->sound_notifications[ 0 ] );
    if( app->sound_notifications[ 1 ] ) CloseHandle( app->sound_notifications[ 1 ] );
    if( !app_internal_opengl_term( &app->gl ) ) app_log( app, APP_LOG_LEVEL_WARNING, "Failed to terminate OpenGL" ); 
    if( app->gl_context ) app->wglMakeCurrent( 0, 0 );
    if( app->gl_context ) app->wglDeleteContext( app->gl_context );     
    if( app->gl_dll ) FreeLibrary( app->gl_dll );
    if( app->icon ) DestroyIcon( app->icon );
    if( app->current_pointer ) DestroyIcon( app->current_pointer );
    if( app->hdc ) ReleaseDC( app->hwnd, app->hdc );
    if( app->hwnd ) DestroyWindow( app->hwnd );
    UnregisterClass( TEXT( "app_wc" ), app->hinstance );

    if( timeGetDevCaps( &tc, sizeof( TIMECAPS ) ) == TIMERR_NOERROR ) 
        timeEndPeriod( tc.wPeriodMin );

    t = time( NULL );
    struct tm* end = localtime( &t );
    sprintf( msg, "Application terminated %02d:%02d:%02d %04d-%02d-%02d.", 
        end->tm_hour, end->tm_min, end->tm_sec, end->tm_year + 1900, end->tm_mon + 1, end->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );

    APP_FREE( memctx, app );
    return result;
    }

#pragma warning( pop )


app_state_t app_yield( app_t* app )
    {
    if( !app->initialized )
        {
        if( app->screenmode == APP_SCREENMODE_WINDOW ) 
        {
            app->screenmode = APP_SCREENMODE_FULLSCREEN;
            app_screenmode( app, APP_SCREENMODE_WINDOW );
        }
        else
        {
            app->screenmode = APP_SCREENMODE_WINDOW;
            app_screenmode( app, APP_SCREENMODE_FULLSCREEN );
        }
        ShowWindow( app->hwnd, SW_SHOWNORMAL );         
        SetActiveWindow( app->hwnd );
        BringWindowToTop( app->hwnd );
        SwitchToThisWindow( app->hwnd, TRUE );
        if( app->tablet.context ) app->tablet.WTEnable( app->tablet.context, TRUE );
        app->initialized = TRUE;
        }

    MSG msg;
    while( PeekMessage( &msg, app->hwnd, 0,0, PM_REMOVE ) )
        {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
        }

//  if( app->has_focus )
        SwitchToThread();   //  yield to any thread on same processor
    //else
    //  Sleep( 4 ); // Pause for a bit... we're not in a rush here
    
    return app->closed == TRUE ? APP_STATE_EXIT_REQUESTED : APP_STATE_NORMAL;
    }


void app_cancel_exit( app_t* app )
    {
    app->closed = FALSE;
    }


void app_title( app_t* app, char const* title )
    {
    #ifdef UNICODE
        int len = (int) strlen (title );
        if( len < 256 )
            {
            WCHAR unistring[ 256 ];
            MultiByteToWideChar( CP_ACP, 0, title, -1, unistring, len + 1 );
            SetWindowText( app->hwnd, unistring );
            }
    #else
        SetWindowText( app->hwnd, title );
    #endif
    }


char const* app_cmdline( app_t* app )
    {
    return app->cmdline;
    }


char const* app_filename( app_t* app )
    {
    return app->exe_path;
    }


char const* app_userdata( app_t* app )
    {
    return app->userdata_path;
    }


char const* app_appdata( app_t* app )
    {
    return app->appdata_path;
    }


APP_U64 app_time_count( app_t* app )
    {
    (void) app;
    LARGE_INTEGER c;
    QueryPerformanceCounter( &c );
    return (APP_U64) c.QuadPart;
    }


APP_U64 app_time_freq( app_t* app )
    {
    (void) app;
    LARGE_INTEGER f;
    QueryPerformanceFrequency( &f );
    return (APP_U64) f.QuadPart;
    }


void app_log( app_t* app, app_log_level_t level, char const* message )
    {
    (void) app, level, message;
    APP_LOG( app->logctx, level, message );
    }


void app_fatal_error( app_t* app, char const* message )
    {
    (void) app, message;
    APP_FATAL_ERROR( app->fatalctx, message );
    }


static HCURSOR app_internal_create_cursor( HWND hwnd, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y )
    {
    int size = width > height ? width : height;
    BITMAPV5HEADER header;
    memset( &header, 0, sizeof( BITMAPV5HEADER ) );
    header.bV5Size = sizeof( BITMAPV5HEADER );
    header.bV5Width = (LONG) size;
    header.bV5Height = -(LONG) size;
    header.bV5Planes = 1;
    header.bV5BitCount = 32;
    header.bV5Compression = BI_BITFIELDS;
    header.bV5RedMask   =  0x00FF0000;
    header.bV5GreenMask =  0x0000FF00;
    header.bV5BlueMask  =  0x000000FF;
    header.bV5AlphaMask =  0xFF000000; 

    HDC hdc = GetDC( hwnd );
    void* bits = NULL;
    HBITMAP bitmap = CreateDIBSection( hdc, (BITMAPINFO*)&header, DIB_RGB_COLORS,  (void**) &bits, NULL, (DWORD) 0);
    ReleaseDC( NULL, hdc );

    APP_U32* ptr = (APP_U32*) bits;
    for( int y = 0; y < height; ++y )
        {
        for( int x = 0; x < width; ++x )
        {
            APP_U32 c = pixels_abgr[ x + y * width ];
            APP_U32 a = ( c & 0xff000000 ) >> 24;
            APP_U32 b = ( c & 0x00ff0000 ) >> 16;
            APP_U32 g = ( c & 0x0000ff00 ) >> 8;
            APP_U32 r = ( c & 0x000000ff );
            ptr[ x + y * size ] = ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
            }
        }

    HBITMAP empty_mask = CreateBitmap( size, size, 1, 1, NULL );
    ICONINFO icon_info;
    icon_info.fIcon = FALSE; 
    icon_info.xHotspot = (DWORD) hotspot_x;
    icon_info.yHotspot = (DWORD) hotspot_y;
    icon_info.hbmMask = empty_mask;
    icon_info.hbmColor = bitmap;

    HCURSOR cursor = CreateIconIndirect( &icon_info );
    DeleteObject( bitmap );          
    DeleteObject( empty_mask ); 

    return cursor;    
    }


void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y )
    {
    if( app->current_pointer ) DestroyIcon( app->current_pointer );
    app->current_pointer = 0;
    
    if( pixels_abgr )
        app->current_pointer = app_internal_create_cursor( app->hwnd, width, height, 
            pixels_abgr, hotspot_x, hotspot_y );
    ShowCursor( FALSE );
    SetCursor( app->current_pointer );
    ShowCursor( TRUE );
    }


static BOOL app_internal_extract_default_windows_cursor( int* width, int* height, APP_U32* pixels_abgr, 
    int* hotspot_x, int* hotspot_y )
    {
    HCURSOR cursor = LoadCursor( NULL, IDC_ARROW );
    if( !cursor ) return FALSE;
    
    ICONINFO info;
    if( !GetIconInfo( cursor, &info ) ) { DestroyCursor( cursor ); return FALSE; }
    BOOL bw_cursor = ( info.hbmColor == NULL );

    BITMAP bmpinfo;
    memset( &bmpinfo, 0, sizeof( bmpinfo ) );
    if( bw_cursor && GetObject( info.hbmMask, sizeof( BITMAP ), &bmpinfo ) == 0 ) 
        { 
        DestroyCursor( cursor ); 
        DeleteObject( info.hbmColor );
        DeleteObject( info.hbmMask );
        return FALSE; 
        }
    if( !bw_cursor && GetObject( info.hbmColor, sizeof( BITMAP ), &bmpinfo ) == 0 )
        { 
        DestroyCursor( cursor ); 
        DeleteObject( info.hbmColor );
        DeleteObject( info.hbmMask );
        return FALSE; 
        }

    if( bmpinfo.bmWidth > 256 || bmpinfo.bmHeight > 256 )
        {
        DestroyCursor( cursor ); 
        DeleteObject( info.hbmColor );
        DeleteObject( info.hbmMask );
        return FALSE; 
        }
    int pointer_width = bmpinfo.bmWidth;
    int pointer_height = ( bmpinfo.bmHeight >= 0 ? bmpinfo.bmHeight : -bmpinfo.bmHeight ) / ( bw_cursor ? 2 : 1 );

    if( width ) *width = pointer_width;
    if( height ) *height = pointer_height;
    if( hotspot_x ) *hotspot_x = (int) info.xHotspot;
    if( hotspot_y ) *hotspot_y = (int) info.yHotspot;
    if( !pixels_abgr )
        {
        DestroyCursor( cursor ); 
        DeleteObject( info.hbmColor );
        DeleteObject( info.hbmMask );
        return TRUE;
        }
    
    BITMAPINFOHEADER bmi;
    bmi.biSize = sizeof( BITMAPINFOHEADER );
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = bmpinfo.bmWidth;
    bmi.biHeight = -bmpinfo.bmHeight;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;
    HDC hdc = GetDC( NULL );
    if( GetDIBits( hdc, bw_cursor ? info.hbmMask : info.hbmColor, 0, (UINT) bmpinfo.bmHeight, pixels_abgr, 
        (BITMAPINFO*) &bmi, DIB_RGB_COLORS ) != bmpinfo.bmHeight )
        {
        DestroyCursor( cursor ); 
        DeleteObject( info.hbmColor );
        DeleteObject( info.hbmMask );
        ReleaseDC( NULL, hdc );
        return FALSE;
        }
    ReleaseDC( NULL, hdc );

    if( bw_cursor )
        {
        for( int y = 0; y < pointer_height; ++y )
            {
            for( int x = 0; x < pointer_width; ++x )
                {
                APP_U32 c = pixels_abgr[ x + pointer_width * y ];
                APP_U32 m = pixels_abgr[ x + pointer_width * ( pointer_height + y ) ];
                APP_U32 a = 255 - ( c & 0xff );
                APP_U32 g = m & 0xff;
                pixels_abgr[ x + pointer_width * y ] = ( a << 24 ) | ( g << 16 ) | ( g << 8 ) | g;
                }
            }
        }
    else
        {
        for( int y = 0; y < pointer_height; ++y )
            {
            for( int x = 0; x < pointer_width; ++x )
                {
                APP_U32 c = pixels_abgr[ x + pointer_width * y ];
                APP_U32 a = ( c >> 24 ) & 0xff;
                APP_U32 r = ( c >> 16 ) & 0xff;
                APP_U32 g = ( c >>  8 ) & 0xff;
                APP_U32 b = ( c       ) & 0xff;
                pixels_abgr[ x + pointer_width * y ] = ( a << 24 ) | ( b << 16 ) | ( g << 8 ) | r;
                }
            }
        }

    DeleteObject( info.hbmColor );
    DeleteObject( info.hbmMask );
    DestroyCursor( cursor );
    return TRUE;
    }


void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y )
    {
    (void) app;

    APP_U32 default_pointer_data[ 11 * 16 ] = 
        {
        0xFF000000,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0xFF000000,0xFF000000,0xFF000000,0xFF000000,
        0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFFFFFFFF,0xFF000000,0x00000000,0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0xFF000000,0x00000000,0x00000000,0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,0x00000000,
        0xFF000000,0x00000000,0x00000000,0x00000000,0x00000000,0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xFF000000,0xFFFFFFFF,0xFFFFFFFF,0xFF000000,0x00000000,0x00000000,
        0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xFF000000,0xFF000000,0xFF000000,0x00000000,0x00000000,
        };

    if( !app_internal_extract_default_windows_cursor( width, height, pixels_abgr, hotspot_x, hotspot_y ) )
        {
        if( width ) *width = 11;
        if( height ) *height = 16;
        if( hotspot_x ) *hotspot_x = 0;
        if( hotspot_y ) *hotspot_y = 0;
        if( pixels_abgr ) memcpy( pixels_abgr, default_pointer_data, sizeof( APP_U32 ) * 11 * 16 );
        }
    }



void app_pointer_pos( app_t* app, int x, int y )
    {
    POINT p;
    p.x = x;
    p.y = y;
    ClientToScreen( app->hwnd, &p );
    SetCursorPos( p.x, p.y );     
    }


int app_pointer_x( app_t* app )
    {
    POINT p;
    GetCursorPos( &p ); 
    ScreenToClient( app->hwnd, &p );
    return (int) p.x;
    }


int app_pointer_y( app_t* app )
    {
    POINT p;
    GetCursorPos( &p ); 
    ScreenToClient( app->hwnd, &p );
    return (int) p.y;
    }


void app_pointer_limit( app_t* app, int x, int y, int width, int height )
    { 
    app->clip_cursor = TRUE;
    app->clip_rect.left= x;
    app->clip_rect.top = y;
    app->clip_rect.right = x + width;
    app->clip_rect.bottom = y + height;
    
    RECT r = app->clip_rect;
    ClientToScreen( app->hwnd, (POINT*)&r );
    ClientToScreen( app->hwnd, ( (POINT*)&r ) + 1 );
    ClipCursor( &r );
    }


void app_pointer_limit_off( app_t* app )
    {
    app->clip_cursor = FALSE;
    ClipCursor( 0 );
    }


void app_interpolation( app_t* app, app_interpolation_t interpolation )
    {
    if( interpolation == app->interpolation ) return;
    app->interpolation = interpolation;

    POINT p;
    GetCursorPos( &p ); 
    ScreenToClient( app->hwnd, &p );
    int mouse_x = p.x;
    int mouse_y = p.y;

    app_input_event_t input_event;
    input_event.type = APP_INPUT_MOUSE_MOVE; 
    input_event.data.mouse_pos.x = mouse_x; 
    input_event.data.mouse_pos.y = mouse_y; 
    app_internal_add_input_event( app, &input_event );

    app_internal_opengl_interpolation( &app->gl, interpolation );
    }


void app_screenmode( app_t* app, app_screenmode_t screenmode )
    {
    if( screenmode == app->screenmode ) return;
    app->screenmode = screenmode;
    BOOL visible = IsWindowVisible( app->hwnd );
    if( screenmode == APP_SCREENMODE_WINDOW ) 
        {
        SetWindowLong( app->hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | ( visible ? WS_VISIBLE : 0 ) );

        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );        
        GetWindowPlacement( app->hwnd, &placement );
        placement.showCmd = (UINT)( visible ? SW_SHOW : SW_HIDE );
        
        placement.rcNormalPosition.left = app->windowed_x;
        placement.rcNormalPosition.top = app->windowed_y;
        placement.rcNormalPosition.right = app->windowed_x + app->windowed_w;
        placement.rcNormalPosition.bottom = app->windowed_y + app->windowed_h;
        SetWindowPlacement( app->hwnd, &placement );
        }
    else
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );

        if( visible )
            {
            if( placement.showCmd != SW_SHOWMAXIMIZED )
                {
                app->windowed_x = placement.rcNormalPosition.left;
                app->windowed_y = placement.rcNormalPosition.top;
                app->windowed_w = placement.rcNormalPosition.right - placement.rcNormalPosition.left;
                app->windowed_h = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top;
                }
            else
                {
                ShowWindow( app->hwnd, SW_RESTORE );
                }
            }

        HMONITOR hmonitor = MonitorFromWindow( app->hwnd, MONITOR_DEFAULTTOPRIMARY );
        int display_index = 0;
        for( int i = 0; i < app->display_count; ++i )
            {
            if( app->displays_hmonitor[ i ] == hmonitor )
                {
                display_index = i;
                break;
                }
            }


        RECT r = app_internal_rect( app->displays[ display_index ].x, app->displays[ display_index ].y, 
            app->displays[ display_index ].x + app->displays[ display_index ].width, 
            app->displays[ display_index ].y + app->displays[ display_index ].height );
        app->fullscreen_width = r.right - r.left;
        app->fullscreen_height = r.bottom - r.top;
        SetWindowPos( app->hwnd, 0, r.left, r.top, app->fullscreen_width, app->fullscreen_height, 
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED );     

        SetWindowLong( app->hwnd, GWL_STYLE, ( visible ? WS_VISIBLE : 0 ) );        
        SetWindowPos( app->hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED );       
        }
    }


void app_window_size( app_t* app, int width, int height )
    {
    RECT r;
    r = app_internal_rect( 0, 0, width, height );
    AdjustWindowRect( &r, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE );
    
    width = r.right - r.left;
    height = r.bottom - r.top;
    app->windowed_w = width;
    app->windowed_h = height;

    if( app->screenmode == APP_SCREENMODE_WINDOW ) 
        SetWindowPos( app->hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED );
    }


int app_window_width( app_t* app )
    {
    int width = app->windowed_w;
    if( app->screenmode == APP_SCREENMODE_WINDOW )
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );
        width = placement.rcNormalPosition.right - placement.rcNormalPosition.left;
        }
    RECT r = app_internal_rect( 0, 0, 0, 0 );
    AdjustWindowRect( &r, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE );
    return width - ( r.right - r.left );
    }


int app_window_height( app_t* app )
    {
    int height = app->windowed_h;
    if( app->screenmode == APP_SCREENMODE_WINDOW )
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );
        height = placement.rcNormalPosition.bottom - placement.rcNormalPosition.top;
        }
    RECT r = app_internal_rect( 0, 0, 0, 0 );
    AdjustWindowRect( &r, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE );
    return height - ( r.bottom - r.top );
    }


void app_window_pos( app_t* app, int x, int y )
    {
    if( app->screenmode == APP_SCREENMODE_WINDOW ) 
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );
        placement.rcNormalPosition.right = x + ( placement.rcNormalPosition.right - placement.rcNormalPosition.left );
        placement.rcNormalPosition.bottom = y + ( placement.rcNormalPosition.bottom - placement.rcNormalPosition.top );
        placement.rcNormalPosition.left = x;
        placement.rcNormalPosition.top = y;
        SetWindowPlacement( app->hwnd, &placement );
        }

    app->windowed_x = x;
    app->windowed_y = y;
    }


int app_window_x( app_t* app )
    {
    if( app->screenmode == APP_SCREENMODE_WINDOW ) 
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );
        return placement.rcNormalPosition.left;
        }
    else
        {
        return app->windowed_x;
        }
    }


int app_window_y( app_t* app )
    {
    if( app->screenmode == APP_SCREENMODE_WINDOW ) 
        {
        WINDOWPLACEMENT placement;
        placement.length = sizeof( placement );
        GetWindowPlacement( app->hwnd, &placement );
        return placement.rcNormalPosition.top;
        }
    else
        {
        return app->windowed_y;
        }
    }


app_displays_t app_displays( app_t* app ) 
    { 
    app_displays_t displays; 
    displays.count = app->display_count;
    displays.displays = app->displays;
    return displays; 
    }


void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr )
    {
    if( app->is_minimized ) return;
    if( pixels_xbgr ) app_internal_opengl_present( &app->gl, pixels_xbgr, width, height, mod_xbgr, border_xbgr );  
    SwapBuffers( app->hdc );
    }


static void app_sound_write( app_t* app, int sample_pairs_offset, int sample_pairs_count ) 
    { 
    int offset = sample_pairs_offset * 2 * ( 16 / 8 );
    int length = sample_pairs_count * 2 * ( 16 / 8 );

    // Obtain memory address of write block. This will be in two parts if the block wraps around.
    LPVOID lpvPtr1; 
    DWORD dwBytes1; 
    LPVOID lpvPtr2; 
    DWORD dwBytes2; 
    HRESULT hr = IDirectSoundBuffer8_Lock( app->dsoundbuf, (DWORD) offset, (DWORD) length, &lpvPtr1, &dwBytes1, 
        &lpvPtr2, &dwBytes2, 0 ); 
 
    // If DSERR_BUFFERLOST is returned, restore and retry lock. 
    if( hr == DSERR_BUFFERLOST ) 
        { 
        IDirectSoundBuffer8_Restore( app->dsoundbuf ); 
        hr = IDirectSoundBuffer8_Lock( app->dsoundbuf, (DWORD) offset, (DWORD) length, &lpvPtr1, &dwBytes1, 
            &lpvPtr2, &dwBytes2, 0 ); 
        } 
    if( FAILED( hr) ) 
        { 
        app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't lock sound buffer" );
        IDirectSound8_Release( app->dsound );
        app->dsound = 0;
        return;
        }

    // Write to pointers.      
    app->sound_callback( (APP_S16*) lpvPtr1, (int) dwBytes1 / ( 2 * ( 16 / 8 ) ), app->sound_user_data );
    if( lpvPtr2 ) app->sound_callback( (APP_S16*) lpvPtr2, (int) dwBytes2 / ( 2 * ( 16 / 8 ) ), app->sound_user_data );

    // Release the data back to DirectSound. 
    hr = IDirectSoundBuffer8_Unlock( app->dsoundbuf, lpvPtr1, dwBytes1, lpvPtr2, dwBytes2 ); 
    if( FAILED( hr) ) 
        { 
        app_log( app, APP_LOG_LEVEL_WARNING, "Couldn't unlock sound buffer" );
        IDirectSound8_Release( app->dsound );
        app->dsound = 0;
        return;
        }
    }


static DWORD WINAPI app_sound_thread_proc( LPVOID lpThreadParameter )
    {
    app_t* app = (app_t*) lpThreadParameter;
    int mid_point = app->sample_pairs_count / 2;
    int half_size = mid_point;
    int prev_pos = 0;
    while( InterlockedCompareExchange( &app->exit_sound_thread, 0, 0 ) == 0 )
        {
        WaitForMultipleObjectsEx( 2, app->sound_notifications, FALSE, 100, FALSE );
        DWORD position = 0;
        IDirectSoundBuffer8_GetCurrentPosition( app->dsoundbuf, &position, 0 );
        int pos = ( (int) position )/( 2 * ( 16 / 8 ) );

        if( prev_pos >= mid_point && pos < mid_point )
            app_sound_write( app, mid_point, half_size );
        else if( prev_pos < mid_point && pos >= mid_point )
            app_sound_write( app, 0, half_size );

        prev_pos = pos; 
        }

    return 0;
    }


void app_sound( app_t* app, int sample_pairs_count, void (*sound_callback)( APP_S16* sample_pairs, int sample_pairs_count, void* user_data ), void* user_data )
    {
    if( !app->dsound ) return;

    if( !sound_callback || !sample_pairs_count )
        {
        if( app->sound_thread_handle != INVALID_HANDLE_VALUE )
            {
            InterlockedExchange( &app->exit_sound_thread, 1 );
            WaitForSingleObject( app->sound_thread_handle, INFINITE );
            CloseHandle( app->sound_thread_handle );
            app->sound_thread_handle = INVALID_HANDLE_VALUE;
            }
        if( app->dsoundbuf ) 
            {
            IDirectSoundBuffer8_Release( app->dsoundbuf );
            app->dsoundbuf = NULL;
            }
        app->sample_pairs_count = 0;
        app->sound_callback = NULL;
        app->sound_user_data = NULL;
        return;
        }

    if( app->sample_pairs_count != sample_pairs_count ) 
        {
        app->sample_pairs_count = sample_pairs_count;

        if( app->dsoundbuf ) 
            {
            IDirectSoundBuffer8_Release( app->dsoundbuf );
            app->dsoundbuf = 0;
            }

        if( sample_pairs_count > 0 )
            {
            int const channels = 2;
            int const frequency = 44100;
            int const bits_per_sample = 16;

            WAVEFORMATEX format; 
            memset( &format, 0, sizeof( WAVEFORMATEX ) ); 
            format.wFormatTag = WAVE_FORMAT_PCM; 
            format.nChannels = (WORD) channels; 
            format.nSamplesPerSec = (DWORD) frequency; 
            format.nBlockAlign = (WORD) ( ( channels * bits_per_sample ) / 8 ); 
            format.nAvgBytesPerSec = (DWORD) ( frequency * format.nBlockAlign ); 
            format.wBitsPerSample = (WORD) bits_per_sample; 
            format.cbSize = 0;

            DSBUFFERDESC dsbdesc; 
            memset( &dsbdesc, 0, sizeof( DSBUFFERDESC ) ); 
            dsbdesc.dwSize = sizeof( DSBUFFERDESC ); 
        
            dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY ; 
        
            int size = channels * ( bits_per_sample / 8 ) * sample_pairs_count;
            dsbdesc.dwBufferBytes = (DWORD) size; 
            dsbdesc.lpwfxFormat = &format; 
        
            IDirectSoundBuffer* soundbuf = NULL;    
            HRESULT hr = IDirectSound8_CreateSoundBuffer( app->dsound, &dsbdesc, &soundbuf, NULL ); 
            if( FAILED( hr ) || !soundbuf ) 
                {
                app_log( app, APP_LOG_LEVEL_WARNING, "Failed to create sound buffer" ); 
                IDirectSound8_Release( app->dsound );
                app->dsound = 0;
                app->sample_pairs_count = 0;
                app->sound_callback = NULL;
                app->sound_user_data = NULL;
                return;
                }

            GUID const GUID_IDirectSoundBuffer8 = { 0x6825a449, 0x7524, 0x4d82, { 0x92, 0x0f, 0x50, 0xe3, 0x6a, 0xb3, 0xab, 0x1e } };
            hr = IDirectSoundBuffer8_QueryInterface( soundbuf, GUID_IDirectSoundBuffer8, (void**) &app->dsoundbuf );
            IDirectSoundBuffer_Release( soundbuf );

            if( FAILED( hr ) || !app->dsoundbuf )
                { 
                app_log( app, APP_LOG_LEVEL_WARNING, "Failed to create sound buffer" ); 
                IDirectSound8_Release( app->dsound );
                app->dsound = 0;
                app->sample_pairs_count = 0;
                app->sound_callback = NULL;
                app->sound_user_data = NULL;
                return;
                }                    

            IDirectSoundNotify8* notify = NULL; 
            GUID const GUID_IDirectSoundNotify8 = { 0xb0210783, 0x89cd, 0x11d0, { 0xaf, 0x8, 0x0, 0xa0, 0xc9, 0x25, 0xcd, 0x16 } };
            hr = app->dsoundbuf->QueryInterface( GUID_IDirectSoundNotify8, (void**) &notify );
            if( FAILED( hr ) || !notify )
                { 
                app_log( app, APP_LOG_LEVEL_WARNING, "Failed to create sound buffer" ); 
                IDirectSoundBuffer_Release( app->dsoundbuf );
                IDirectSound8_Release( app->dsound );
                app->dsound = 0;
                app->dsoundbuf = 0;
                app->sample_pairs_count = 0;
                app->sound_callback = NULL;
                app->sound_user_data = NULL;
                return;
                }                    

            DSBPOSITIONNOTIFY notify_positions[ 2 ];
            notify_positions[ 0 ].dwOffset = 0;
            notify_positions[ 0 ].hEventNotify = app->sound_notifications[ 0 ];
            notify_positions[ 1 ].dwOffset = (DWORD)( size / 2 );
            notify_positions[ 1 ].hEventNotify = app->sound_notifications[ 1 ];

            IDirectSoundNotify_SetNotificationPositions( notify, 2, notify_positions );
            IDirectSoundNotify_Release( notify );

            app->sound_thread_handle = CreateThread( NULL, 0U, app_sound_thread_proc, app, 0, NULL );
            SetThreadPriority( app->sound_thread_handle, THREAD_PRIORITY_HIGHEST );

            IDirectSoundBuffer8_Play( app->dsoundbuf, 0, 0, DSBPLAY_LOOPING );
            }
        }

    app->sound_callback = sound_callback;
    app->sound_user_data = user_data;
    }


void app_sound_volume( app_t* app, float volume )
    {
    if( !app->dsound ) return;
    if( !app->dsoundbuf ) return;

    int level = volume < 0.000015f ? DSBVOLUME_MIN : (int) ( 2000.0f * log10f( volume ) );
    if( app->sound_level == level ) return; 
    app->sound_level = level;

    IDirectSoundBuffer8_SetVolume( app->dsoundbuf, level );
    }


app_input_t app_input( app_t* app )
    {
    app_input_t input; 
    input.events = app->input_events; 
    input.count = app->input_count;
    app->input_count = 0;
    return input;
    }


void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y )
    {
    if( width == 0 || height == 0 ) return;
    RECT r;
    GetClientRect( app->hwnd, &r );
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : r.right - r.left;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : r.bottom - r.top;


    if( app->interpolation == APP_INTERPOLATION_LINEAR )
        {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
            {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x -= (int)( hborder );
            *y -= (int)( vborder );
            *x = (int)( *x / pixel_scale );
            *y = (int)( *y / pixel_scale );
            }
        else 
            {
            *x = 0;
            *y = 0;
            }
        }
    else
        {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x -= (int)( hborder );
        *y -= (int)( vborder );
        *x = (int)( *x / pixel_scale );
        *y = (int)( *y / pixel_scale );
        }
    }


void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y )
    {
    RECT r;
    GetClientRect( app->hwnd, &r );
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : r.right - r.left;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : r.bottom - r.top;


    if( app->interpolation == APP_INTERPOLATION_LINEAR )
        {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
            {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x = (int)( *x * pixel_scale );
            *y = (int)( *y * pixel_scale );
            *x += (int)( hborder );
            *y += (int)( vborder );
            }
        else 
            {
            *x = 0;
            *y = 0;
            }
        }
    else
        {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x = (int)( *x * pixel_scale );
        *y = (int)( *y * pixel_scale );
        *x += (int)( hborder );
        *y += (int)( vborder );
        }
    }

#elif defined( APP_MACOS )

#include <AudioUnit/AudioUnit.h>
#include <stdbool.h>
#include <sys/time.h>
#include <mach/mach_time.h>

#include <objc/message.h>
#include <objc/runtime.h>
#include <CoreGraphics/CGGeometry.h>

#ifndef APP_MALLOC
#include <stdlib.h>
#if defined(__cplusplus)
#define APP_MALLOC( ctx, size ) ( ::malloc( size ) )
#define APP_FREE( ctx, ptr ) ( ::free( ptr ) )
#else
#define APP_MALLOC( ctx, size ) ( malloc( size ) )
#define APP_FREE( ctx, ptr ) ( free( ptr ) )
#endif
#endif

#ifndef APP_LOG
#if defined(__cplusplus)
#define APP_LOG( ctx, level, message ) ::printf( "%s\n", message )
#else
#define APP_LOG( ctx, level, message ) printf( "%s\n", message )
#endif
#endif

#ifndef APP_FATAL_ERROR
// todo: use a macos messagebox
#define APP_FATAL_ERROR( ctx, message ) { printf( "FATAL ERROR: %s\n", message ); }

/*
#if defined(__cplusplus)
#define APP_FATAL_ERROR( ctx, message ) { ::printf( "FATAL ERROR: %s\n", message ); \
::MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); ::_flushall(); ::_exit( 0xff ); }
#else
#define APP_FATAL_ERROR( ctx, message ) { printf( "FATAL ERROR: %s\n", message ); \
MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); _flushall(); _exit( 0xff ); }
#endif
 */
#endif

typedef id(*ObjcIdMessage)(id, SEL);
typedef void(*ObjcVoidMessage)(id, SEL);
typedef void(*ObjcVoidMessageId)(id, SEL, id);
typedef void(*ObjcVoidMessageBool)(id, SEL, bool);
typedef void(*ObjcVoidMessageInt)(id, SEL, int);
typedef void(*ObjcVoidMessagePoint)(id, SEL, CGPoint);
typedef void(*ObjcVoidMessageSize)(id, SEL, CGSize);
typedef void(*ObjcVoidMessageRect)(id, SEL, CGRect);
typedef void(*ObjcVoidMessageRectBool)(id, SEL, CGRect, bool);
typedef void(*ObjcVoidMessageVoidStarInt)(id, SEL, void*, int);
typedef bool(*ObjcBoolMessage)(id, SEL);
typedef int(*ObjcIntMessage)(id, SEL);
typedef double(*ObjcDoubleMessage)(id, SEL);
typedef const char*(*ObjcCharStarMessage)(id, SEL);
typedef CGPoint(*ObjcPointMessage)(id, SEL);
typedef CGPoint(*ObjcPointMessagePointId)(id, SEL, CGPoint, id);
typedef CGRect(*ObjcRectMessage)(id, SEL);
typedef id(*ObjcIdMessageInt)(id, SEL, int);
typedef id(*ObjcIdMessageRect)(id, SEL, CGRect);
typedef id(*ObjcIdMessageId)(id, SEL, id);
typedef id(*ObjcIdMessageVoidStar)(id, SEL, void*);
typedef id(*ObjcNextEventMessage)(id, SEL, unsigned long long, id, id, bool);
typedef id(*ObjcWindowInitMessage)(id, SEL, CGRect, int, int, bool);
typedef id(*ObjcViewInitMessage)(id, SEL, CGRect, id);
typedef id(*ObjcMenuItemInitMessage)(id, SEL, id, SEL, id);

ObjcIdMessage objc_id_msgSend = (ObjcIdMessage)objc_msgSend;
ObjcVoidMessage objc_void_msgSend     = (ObjcVoidMessage)objc_msgSend;
ObjcVoidMessageId objc_void_msgSend_id = (ObjcVoidMessageId)objc_msgSend;
ObjcVoidMessageBool objc_void_msgSend_bool = (ObjcVoidMessageBool)objc_msgSend;
ObjcVoidMessageInt objc_void_msgSend_int = (ObjcVoidMessageInt)objc_msgSend;
ObjcVoidMessagePoint objc_void_msgSend_point = (ObjcVoidMessagePoint)objc_msgSend;
ObjcVoidMessageSize objc_void_msgSend_size = (ObjcVoidMessageSize)objc_msgSend;
ObjcVoidMessageRect objc_void_msgSend_rect = (ObjcVoidMessageRect)objc_msgSend;
ObjcVoidMessageRectBool objc_void_msgSend_rect_bool = (ObjcVoidMessageRectBool)objc_msgSend;
ObjcVoidMessageVoidStarInt objc_void_msgSend_voidstar_int = (ObjcVoidMessageVoidStarInt)objc_msgSend;
ObjcBoolMessage objc_bool_msgSend = (ObjcBoolMessage)objc_msgSend;
ObjcDoubleMessage objc_double_msgSend = (ObjcDoubleMessage)objc_msgSend_fpret;
ObjcIntMessage objc_int_msgSend = (ObjcIntMessage)objc_msgSend;
ObjcCharStarMessage objc_charstar_msgSend = (ObjcCharStarMessage)objc_msgSend;
// note this uses objc_msgSend, not objc_msgSend_stret. It seems a CGPoint is small enough to pass in registers, but this is dependant on the architecture, so we may need to revisit this if not compmiling for x64.
ObjcPointMessage objc_point_msgSend = (ObjcPointMessage)objc_msgSend;
ObjcPointMessagePointId objc_point_msgSend_point_id = (ObjcPointMessagePointId)objc_msgSend;
ObjcRectMessage objc_rect_msgSend = (ObjcRectMessage)objc_msgSend_stret;
ObjcIdMessageInt objc_id_msgSend_int = (ObjcIdMessageInt)objc_msgSend;
ObjcIdMessageRect objc_id_msgSend_rect = (ObjcIdMessageRect)objc_msgSend;
ObjcIdMessageId objc_id_msgSend_id = (ObjcIdMessageId)objc_msgSend;
ObjcIdMessageVoidStar objc_id_msgSend_voidstar = (ObjcIdMessageVoidStar)objc_msgSend;
ObjcNextEventMessage objc_next_event_msgSend = (ObjcNextEventMessage)objc_msgSend;
ObjcWindowInitMessage objc_window_init_msgSend = (ObjcWindowInitMessage)objc_msgSend;
ObjcViewInitMessage objc_view_init_msgSend = (ObjcViewInitMessage)objc_msgSend;
ObjcMenuItemInitMessage objc_menuitem_init_msgSend = (ObjcMenuItemInitMessage)objc_msgSend;

// OSX keycodes for keys that are independent of keyboard layout
enum {
    OSX_KEY_Return                    = 0x24,
    OSX_KEY_Tab                       = 0x30,
    OSX_KEY_Space                     = 0x31,
    OSX_KEY_Delete                    = 0x33,
    OSX_KEY_Escape                    = 0x35,
    OSX_KEY_Command                   = 0x37,
    OSX_KEY_Shift                     = 0x38,
    OSX_KEY_CapsLock                  = 0x39,
    OSX_KEY_Option                    = 0x3A,
    OSX_KEY_Control                   = 0x3B,
    OSX_KEY_RightShift                = 0x3C,
    OSX_KEY_RightOption               = 0x3D,
    OSX_KEY_RightControl              = 0x3E,
    OSX_KEY_Function                  = 0x3F,
    OSX_KEY_F17                       = 0x40,
    OSX_KEY_VolumeUp                  = 0x48,
    OSX_KEY_VolumeDown                = 0x49,
    OSX_KEY_Mute                      = 0x4A,
    OSX_KEY_F18                       = 0x4F,
    OSX_KEY_F19                       = 0x50,
    OSX_KEY_F20                       = 0x5A,
    OSX_KEY_F5                        = 0x60,
    OSX_KEY_F6                        = 0x61,
    OSX_KEY_F7                        = 0x62,
    OSX_KEY_F3                        = 0x63,
    OSX_KEY_F8                        = 0x64,
    OSX_KEY_F9                        = 0x65,
    OSX_KEY_F11                       = 0x67,
    OSX_KEY_F13                       = 0x69,
    OSX_KEY_F16                       = 0x6A,
    OSX_KEY_F14                       = 0x6B,
    OSX_KEY_F10                       = 0x6D,
    OSX_KEY_F12                       = 0x6F,
    OSX_KEY_F15                       = 0x71,
    OSX_KEY_Help                      = 0x72,
    OSX_KEY_Home                      = 0x73,
    OSX_KEY_PageUp                    = 0x74,
    OSX_KEY_ForwardDelete             = 0x75,
    OSX_KEY_F4                        = 0x76,
    OSX_KEY_End                       = 0x77,
    OSX_KEY_F2                        = 0x78,
    OSX_KEY_PageDown                  = 0x79,
    OSX_KEY_F1                        = 0x7A,
    OSX_KEY_LeftArrow                 = 0x7B,
    OSX_KEY_RightArrow                = 0x7C,
    OSX_KEY_DownArrow                 = 0x7D,
    OSX_KEY_UpArrow                   = 0x7E
};

enum OSXWindowStyleMask
{
    OSXWindowStyleMaskBorderless        = 0,
    OSXWindowStyleMaskTitled            = 1 << 0,
    OSXWindowStyleMaskClosable          = 1 << 1,
    OSXWindowStyleMaskMiniaturizable    = 1 << 2,
    OSXWindowStyleMaskResizable         = 1 << 3,
    OSXWindowStyleMaskTexturedBackground = 1 << 8,
    /* Specifies a window whose titlebar and toolbar have a unified look - that is, a continuous background. Under the titlebar and toolbar a horizontal separator line will appear.
     */
    OSXWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
    /* When set, the window will appear full screen. This mask is automatically toggled when toggleFullScreen: is called.
     */
    OSXWindowStyleMaskFullScreen = 1 << 14,
};

enum {
    OSXOpenGLPFAAllRenderers       =   1,    /* choose from all available renderers          */
    OSXOpenGLPFATripleBuffer       =   3,    /* choose a triple buffered pixel format        */
    OSXOpenGLPFADoubleBuffer       =   5,    /* choose a double buffered pixel format        */
    OSXOpenGLPFAAuxBuffers         =   7,    /* number of aux buffers                        */
    OSXOpenGLPFAColorSize          =   8,    /* number of color buffer bits                  */
    OSXOpenGLPFAAlphaSize          =  11,    /* number of alpha component bits               */
    OSXOpenGLPFADepthSize          =  12,    /* number of depth buffer bits                  */
    OSXOpenGLPFAStencilSize        =  13,    /* number of stencil buffer bits                */
    OSXOpenGLPFAAccumSize          =  14,    /* number of accum buffer bits                  */
    OSXOpenGLPFAMinimumPolicy      =  51,    /* never choose smaller buffers than requested  */
    OSXOpenGLPFAMaximumPolicy      =  52,    /* choose largest buffers of type requested     */
    OSXOpenGLPFASampleBuffers      =  55,    /* number of multi sample buffers               */
    OSXOpenGLPFASamples            =  56,    /* number of samples per multi sample buffer    */
    OSXOpenGLPFAAuxDepthStencil    =  57,    /* each aux buffer has its own depth stencil    */
    OSXOpenGLPFAColorFloat         =  58,    /* color buffers store floating point pixels    */
    OSXOpenGLPFAMultisample        =  59,    /* choose multisampling                         */
    OSXOpenGLPFASupersample        =  60,    /* choose supersampling                         */
    OSXOpenGLPFASampleAlpha        =  61,    /* request alpha filtering                      */
    OSXOpenGLPFARendererID         =  70,    /* request renderer by ID                       */
    OSXOpenGLPFANoRecovery         =  72,    /* disable all failure recovery systems         */
    OSXOpenGLPFAAccelerated        =  73,    /* choose a hardware accelerated renderer       */
    OSXOpenGLPFAClosestPolicy      =  74,    /* choose the closest color buffer to request   */
    OSXOpenGLPFABackingStore       =  76,    /* back buffer contents are valid after swap    */
    OSXOpenGLPFAScreenMask         =  84,    /* bit mask of supported physical screens       */
    OSXOpenGLPFAAllowOfflineRenderers  = 96,  /* allow use of offline renderers               */
    OSXOpenGLPFAAcceleratedCompute =  97,    /* choose a hardware accelerated compute device */
    OSXOpenGLPFAVirtualScreenCount = 128,    /* number of virtual screens in this format     */
    OSXOpenGLPFAOpenGLProfile       =  99, /* specify an OpenGL Profile to use             */
    
};
typedef uint32_t OSXOpenGLPixelFormatAttribute;

enum {
    OSXOpenGLProfileVersionLegacy   = 0x1000,   /* choose a Legacy/Pre-OpenGL 3.0 Implementation */
    OSXOpenGLProfileVersion3_2Core  = 0x3200,   /* choose an OpenGL 3.2 Core Implementation      */
    OSXOpenGLProfileVersion4_1Core  = 0x4100    /* choose an OpenGL 4.1 Core Implementation      */
};

enum {
    OSXOpenGLContextParameterSwapInterval = 222, /* 1 param.  0 -> Don't sync, 1 -> Sync to vertical retrace     */
};

enum {
    OSXTerminateCancel = 0,
    OSXTerminateNow = 1,
    OSXTerminateLater = 2
};

enum {
    OSXEventTypeLeftMouseDown             = 1,
    OSXEventTypeLeftMouseUp               = 2,
    OSXEventTypeRightMouseDown            = 3,
    OSXEventTypeRightMouseUp              = 4,
    OSXEventTypeMouseMoved                = 5,
    OSXEventTypeLeftMouseDragged          = 6,
    OSXEventTypeRightMouseDragged         = 7,
    OSXEventTypeMouseEntered              = 8,
    OSXEventTypeMouseExited               = 9,
    OSXEventTypeKeyDown                   = 10,
    OSXEventTypeKeyUp                     = 11,
    OSXEventTypeFlagsChanged              = 12,
    OSXEventTypeAppKitDefined             = 13,
    OSXEventTypeSystemDefined             = 14,
    OSXEventTypeApplicationDefined        = 15,
    OSXEventTypePeriodic                  = 16,
    OSXEventTypeCursorUpdate              = 17,
    OSXEventTypeScrollWheel               = 22,
    OSXEventTypeTabletPoint               = 23,
    OSXEventTypeTabletProximity           = 24,
    OSXEventTypeOtherMouseDown            = 25,
    OSXEventTypeOtherMouseUp              = 26,
    OSXEventTypeOtherMouseDragged         = 27,
    /* The following event types are available on some hardware on 10.5.2 and later */
    OSXEventTypeGesture       = 29,
    OSXEventTypeMagnify       = 30,
    OSXEventTypeSwipe         = 31,
    OSXEventTypeRotate        = 18,
    OSXEventTypeBeginGesture   = 19,
    OSXEventTypeEndGesture    = 20,
    
#if __LP64__
    OSXEventTypeSmartMagnify  = 32,
#endif
    OSXEventTypeQuickLook  = 33,
    
#if __LP64__
    OSXEventTypePressure  = 34,
    OSXEventTypeDirectTouch  = 37,
#endif
};

const uint64_t OSXEventMaskAny                          = 0xffffffffffffffff;
const int OSXWindowCollectionBehaviorFullScreenPrimary  = 1 << 7;
const int OSXBackingStoreBuffered                       = 2;

struct app_t
{
    void* memctx;
    void* logctx;
    void* fatalctx;
    app_interpolation_t interpolation;
    app_screenmode_t screenmode;
    
    bool initialized;
    bool closed;
    bool has_focus;
    bool is_minimized;
    
    id window;
    
    int display_count;
    app_display_t displays[ 16 ];
    
    struct app_internal_opengl_t gl;
    
    app_input_event_t input_events[ 1024 ];
    int input_count;
    
    int windowed_x;
    int windowed_y;
    int windowed_h;
    int windowed_w;
    int fullscreen_width;
    int fullscreen_height;
    
    AudioComponentInstance audioUnit;
    APP_S16* audio_buffer;
    int audio_buffer_size;
    int audio_buffer_position;
    float sound_vol;
};

static app_key_t app_internal_osx_map_key(int keyCode, char keyChar)
{
    // OSX key-codes represent the position on a standard US keyboard where a particular key is,
    // if the user has a different layout, we won't know from the keycode what the actual key was.
    // So instead we use the keyChar to figure out the key if possible, then fall back to the key code.
    if(keyChar >= 'a' && keyChar <= 'z')
        return APP_KEY_A + (keyChar - 'a');
    if(keyChar >= 'A' && keyChar <= 'Z')
        return APP_KEY_A + (keyChar - 'A');
    if(keyChar >= '0' && keyChar <= '9')
        return APP_KEY_0 + (keyChar - '0');
    
    switch(keyChar)
    {
        case ',':
            return APP_KEY_OEM_COMMA;
        case '.':
            return APP_KEY_OEM_PERIOD;
        default:
            break;
    }
    
    switch(keyCode)
    {
        case OSX_KEY_F1:
            return APP_KEY_F1;
        case OSX_KEY_F2:
            return APP_KEY_F2;
        case OSX_KEY_F3:
            return APP_KEY_F3;
        case OSX_KEY_F4:
            return APP_KEY_F4;
        case OSX_KEY_F5:
            return APP_KEY_F5;
        case OSX_KEY_F6:
            return APP_KEY_F6;
        case OSX_KEY_F7:
            return APP_KEY_F7;
        case OSX_KEY_F8:
            return APP_KEY_F8;
        case OSX_KEY_F9:
            return APP_KEY_F9;
        case OSX_KEY_F10:
            return APP_KEY_F10;
        case OSX_KEY_F11:
            return APP_KEY_F11;
        case OSX_KEY_F12:
            return APP_KEY_F12;
        case OSX_KEY_F13:
            return APP_KEY_F13;
        case OSX_KEY_F14:
            return APP_KEY_F14;
        case OSX_KEY_F15:
            return APP_KEY_F15;
        case OSX_KEY_F16:
            return APP_KEY_F16;
        case OSX_KEY_F17:
            return APP_KEY_F17;
        case OSX_KEY_F18:
            return APP_KEY_F18;
        case OSX_KEY_F19:
            return APP_KEY_F19;
        case OSX_KEY_F20:
            return APP_KEY_F20;
        case OSX_KEY_Return:
            return APP_KEY_RETURN;
        case OSX_KEY_End:
            return APP_KEY_END;
        case OSX_KEY_Home:
            return APP_KEY_HOME;
        case OSX_KEY_LeftArrow:
            return APP_KEY_LEFT;
        case OSX_KEY_RightArrow:
            return APP_KEY_RIGHT;
        case OSX_KEY_UpArrow:
            return APP_KEY_UP;
        case OSX_KEY_DownArrow:
            return APP_KEY_DOWN;
        case OSX_KEY_Space:
            return APP_KEY_SPACE;
        case OSX_KEY_Tab:
            return APP_KEY_TAB;
        case OSX_KEY_Escape:
            return APP_KEY_ESCAPE;
        case OSX_KEY_Delete:
            return APP_KEY_DELETE;
        case OSX_KEY_Shift:
            return APP_KEY_SHIFT;
        case OSX_KEY_Control:
            return APP_KEY_CONTROL;
        case OSX_KEY_RightShift:
            return APP_KEY_RSHIFT;
        case OSX_KEY_RightControl:
            return APP_KEY_RCONTROL;
        default:
            break;
    }
    
    return APP_KEY_INVALID;
}

static void app_internal_add_input_event( app_t* app, app_input_event_t* event )
{
    if( app->has_focus )
    {
        if( app->input_count < sizeof( app->input_events ) / sizeof( *app->input_events ) )
            app->input_events[ app->input_count++ ] = *event;
    }
}

void app_internal_osx_add_key_event(app_t* app, int keyCode, char keyChar, bool isUp)
{
    app_input_event_t event;
    event.type = isUp ? APP_INPUT_KEY_UP : APP_INPUT_KEY_DOWN;
    event.data.key = app_internal_osx_map_key(keyCode, keyChar);
    app_internal_add_input_event(app, &event);
    
    if(!isUp)
    {
        event.type = APP_INPUT_CHAR;
        event.data.char_code = keyChar;
        app_internal_add_input_event(app, &event);
    }
}

void app_internal_osx_add_mouse_move_event(app_t* app, int mouse_x, int mouse_y)
{
    app_input_event_t event;
    event.type = APP_INPUT_MOUSE_MOVE;
    event.data.mouse_pos.x = mouse_x;
    event.data.mouse_pos.y = mouse_y;
    
    app_internal_add_input_event( app, &event );
}

void app_internal_osx_add_mouse_press_event(app_t* app, int button, bool isUp, bool isDoubleClick)
{
    if(button < 0 || button > 2)
        return;
    
    app_input_event_t event;
    event.type = isDoubleClick ? APP_INPUT_DOUBLE_CLICK : isUp ? APP_INPUT_KEY_UP : APP_INPUT_KEY_DOWN;
    event.data.key = button == 0 ? APP_KEY_LBUTTON : button == 1 ? APP_KEY_RBUTTON : APP_KEY_MBUTTON;
    
    app_internal_add_input_event( app, &event );
}

void app_internal_osx_add_scroll_event(app_t* app, float scrollY)
{
    app_input_event_t event;
    event.type = APP_INPUT_SCROLL_WHEEL;
    event.data.wheel_delta = scrollY;
    
    app_internal_add_input_event( app, &event );
}

// NSWindow and NSApplication delegate methods

void osx_window_keyDown(id self, SEL _cmd, id event)
{
    // empty function, but necessary to swallow the key event, so it isn't considered as unhandled.
}

void osx_applicationDidFinishLaunching(id self, SEL _cmd, id notification)
{
}

BOOL osx_applicationShouldTerminateAfterLastWindowClosed(id self, SEL _cmd, id sender)
{
    return YES;
}

int osx_applicationShouldTerminate(id self, SEL _cmd, id sender)
{
    app_t* app;
    object_getInstanceVariable(self, "app", (void*)&app);
    app->closed = true;
    
    // don't terminate immediately, just wait for the app to close.
    return OSXTerminateCancel;
}

void osx_windowWillClose(id self, SEL _cmd, id notification)
{
    app_t* app;
    object_getInstanceVariable(self, "app", (void*)&app);
    app->closed = true;
}

void osx_windowDidResize(id self, SEL _cmd, id notification)
{
    CGRect contentRect = objc_rect_msgSend(self, sel_getUid("contentLayoutRect"));
    id glView;
    object_getInstanceVariable(self, "glView", (void*)&glView);
    
    objc_void_msgSend_rect(glView, sel_getUid("setFrame:"), contentRect);
    
    app_t* app;
    object_getInstanceVariable(self, "app", (void*)&app);

    int width = (int)contentRect.size.width;
    int height = (int)contentRect.size.height;
    app->windowed_w = width;
    app->windowed_h = height;
    if(app->screenmode == APP_SCREENMODE_WINDOW)
    {
        app_internal_opengl_resize( &app->gl, width, height );
    }
}

void osx_windowDidMove(id self, SEL _cmd, id notification)
{
}

void osx_windowDidMiniaturize(id self, SEL _cmd, id notification)
{
}

void osx_windowDidDeminiaturize(id self, SEL _cmd, id notification)
{
}

void osx_windowDidEnterFullScreen(id self, SEL _cmd, id notification)
{
    id screen = objc_id_msgSend((id)objc_getClass("NSScreen"), sel_getUid("mainScreen"));
    CGRect screenFrame = objc_rect_msgSend(screen, sel_getUid("frame"));
    objc_void_msgSend_rect_bool(self, sel_getUid("setFrame:display:"), screenFrame, YES);
    
    app_t* app;
    object_getInstanceVariable(self, "app", (void*)&app);
    app_screenmode(app, APP_SCREENMODE_FULLSCREEN);
}

void osx_windowDidExitFullScreen(id self, SEL _cmd, id notification)
{
    app_t* app;
    object_getInstanceVariable(self, "app", (void*)&app);
    app_screenmode(app, APP_SCREENMODE_WINDOW);
}

//

int app_internal_osx_get_screen_count()
{
    id screens = objc_id_msgSend((id)objc_getClass("NSScreen"), sel_getUid("screens"));
    int screen_count = objc_int_msgSend(screens, sel_getUid("count"));
    return screen_count;
}

void app_internal_osx_get_screen_rect(int screen_idx, int* x, int* y, int* w, int* h)
{
    id screens = objc_id_msgSend((id)objc_getClass("NSScreen"), sel_getUid("screens"));
    int screen_count = objc_int_msgSend(screens, sel_getUid("count"));
    if(screen_idx < 0 || screen_idx >= screen_count)
        return;
    
    id screen = objc_id_msgSend_int(screens, sel_getUid("objectAtIndex:"), screen_idx);
    CGRect screenFrame = objc_rect_msgSend(screen, sel_getUid("frame"));
    
    if(x != NULL) *x = screenFrame.origin.x;
    if(y != NULL) *y = screenFrame.origin.y;
    if(w != NULL) *w = screenFrame.size.width;
    if(h != NULL) *h = screenFrame.size.height;
}

void app_internal_osx_get_window_position(id app_window, int* x, int* y)
{
    CGRect windowFrame = objc_rect_msgSend(app_window, sel_getUid("frame"));
    
    if(x != NULL) *x = windowFrame.origin.x;
    if(y != NULL) *y = windowFrame.origin.y;
}

void app_internal_osx_get_window_content_size(id app_window, int* w, int* h)
{
    CGRect contentFrame = objc_rect_msgSend(app_window, sel_getUid("contentLayoutRect"));
    
    if(w != NULL) *w = contentFrame.size.width;
    if(h != NULL) *h = contentFrame.size.height;
}

void app_internal_osx_set_window_position(id app_window, int x, int y)
{
    objc_void_msgSend_point(app_window, sel_getUid("setFrameOrigin:"), (CGPoint){x,y});
}

void app_internal_osx_set_window_content_size(id app_window, int w, int h)
{
    objc_void_msgSend_size(app_window, sel_getUid("setContentSize:"), (CGSize){w,h});
}

void app_internal_osx_set_window_title(id app_window, const char* title)
{
    id titleStr = objc_id_msgSend_voidstar((id)objc_getClass("NSString"), sel_getUid("stringWithUTF8String:"), (char*)title);
    objc_void_msgSend_id(app_window, sel_getUid("setTitle:"), titleStr);
}

void app_internal_osx_show_window(id app_window)
{
    objc_void_msgSend_id(app_window, sel_getUid("makeKeyAndOrderFront:"), app_window);
}

void app_internal_osx_set_fullscreen(id app_window, bool fullscreen)
{
    int styleMask = objc_int_msgSend(app_window, sel_getUid("styleMask"));
    bool isFS = ((styleMask & OSXWindowStyleMaskFullScreen) == OSXWindowStyleMaskFullScreen);
    
    if(isFS == fullscreen)
        return;
    
    if(fullscreen)
    {
        id mainScreen = objc_id_msgSend((id)objc_getClass("NSScreen"), sel_getUid("mainScreen"));
        CGRect screenFrame = objc_rect_msgSend(mainScreen, sel_getUid("frame"));
        objc_void_msgSend_rect_bool(app_window, sel_getUid("setFrame:display:"), screenFrame, YES);
        objc_void_msgSend_id(app_window, sel_getUid("toggleFullScreen:"), app_window);
    }
    else
    {
        objc_void_msgSend_id(app_window, sel_getUid("toggleFullScreen:"), app_window);
    }
}

void app_internal_osx_handle_events(id app_window)
{
    id autoReleasePool = objc_id_msgSend((id)objc_getClass("NSAutoreleasePool"), sel_getUid("alloc"));
    autoReleasePool = objc_id_msgSend(autoReleasePool, sel_getUid("init"));
    
    id nsapp = objc_id_msgSend((id)objc_getClass("NSApplication"), sel_getUid("sharedApplication"));
    id defaultRunLoopMode = objc_id_msgSend_voidstar((id)objc_getClass("NSString"), sel_getUid("stringWithUTF8String:"), "kCFRunLoopDefaultMode");
    
    app_t* app;
    object_getInstanceVariable(app_window, "app", (void*)&app);
    
    while(true)
    {
        id event = objc_next_event_msgSend(nsapp, sel_getUid("nextEventMatchingMask:untilDate:inMode:dequeue:"), OSXEventMaskAny, NULL, defaultRunLoopMode, YES);
        if(event == NULL)
            break;
        
        int type = objc_int_msgSend(event, sel_getUid("type"));
        
        switch(type)
        {
            case OSXEventTypeKeyDown:
            case OSXEventTypeKeyUp:
            {
                bool isUp = type == OSXEventTypeKeyUp;
                int keyCode = objc_int_msgSend(event, sel_getUid("keyCode"));
                id nsStr = objc_id_msgSend(event, sel_getUid("characters"));
                const char* charStr = objc_charstar_msgSend(nsStr, sel_getUid("UTF8String"));
                app_internal_osx_add_key_event(app, keyCode, charStr[0], isUp);
            }
                break;
            case OSXEventTypeMouseMoved:
            case OSXEventTypeLeftMouseDragged:
            case OSXEventTypeOtherMouseDragged:
            {
                CGPoint window_point = objc_point_msgSend(event, sel_getUid("locationInWindow"));
                
                id glView;
                object_getInstanceVariable(app_window, "glView", (void*)&glView);
                CGPoint local_point = objc_point_msgSend_point_id(glView, sel_getUid("convertPoint:fromView:"), window_point, NULL);
                CGRect viewBounds = objc_rect_msgSend(glView, sel_getUid("bounds"));
                
                int view_height = viewBounds.size.height;
                int x = (int)local_point.x;
                int y = (int)(view_height - local_point.y - 1);
                
                app_internal_osx_add_mouse_move_event(app, x,y);
            }
                break;
            case OSXEventTypeLeftMouseDown:
            case OSXEventTypeOtherMouseDown:
            {
                int clickCount = objc_int_msgSend(event, sel_getUid("clickCount"));
                bool doubleClick = (clickCount % 2) == 0;
                int buttonNum = objc_int_msgSend(event, sel_getUid("buttonNumber"));
                
                app_internal_osx_add_mouse_press_event(app, buttonNum, false, doubleClick);
            }
                break;
            case OSXEventTypeLeftMouseUp:
            case OSXEventTypeOtherMouseUp:
            {
                int buttonNum = objc_int_msgSend(event, sel_getUid("buttonNumber"));
                
                app_internal_osx_add_mouse_press_event(app, buttonNum, true, false);
            }
                break;
            case OSXEventTypeScrollWheel:
            {
                float deltaY = objc_double_msgSend(event, sel_getUid("deltaY"));
                app_internal_osx_add_scroll_event(app, deltaY);
            }
                break;
            default:
                break;
        }
        
        objc_void_msgSend_id(nsapp, sel_getUid("sendEvent:"), event);
    }
    
    objc_void_msgSend(autoReleasePool, sel_getUid("release"));
}

void app_internal_osx_present(id app_window)
{
    if(objc_bool_msgSend(app_window, sel_getUid("isVisible")))
    {
        id glView;
        object_getInstanceVariable(app_window, "glView", (void*)&glView);
        id glContext = objc_id_msgSend(glView, sel_getUid("openGLContext"));
        objc_void_msgSend(glContext, sel_getUid("flushBuffer"));
    }
}

id app_internal_osx_create_window(id title, int width, int height)
{
    id app_window = objc_id_msgSend((id)objc_getClass("AppWindow"), sel_getUid("alloc"));
    CGRect contentRect = (CGRect){0,0,width,height};
    
    app_window = objc_window_init_msgSend(app_window, sel_getUid("initWithContentRect:styleMask:backing:defer:"), contentRect, OSXWindowStyleMaskClosable | OSXWindowStyleMaskTitled | OSXWindowStyleMaskMiniaturizable | OSXWindowStyleMaskResizable, OSXBackingStoreBuffered, false);
    
    objc_void_msgSend_id(app_window, sel_getUid("setTitle:"), title);
    
    // get a OpenGL 3.2 context
    OSXOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
        OSXOpenGLPFAOpenGLProfile, OSXOpenGLProfileVersion3_2Core,
        OSXOpenGLPFAColorSize,   24,
        OSXOpenGLPFAAlphaSize,   8,
        OSXOpenGLPFADepthSize,   24,
        OSXOpenGLPFAStencilSize, 8,
        OSXOpenGLPFADoubleBuffer,
        OSXOpenGLPFAAccelerated,
        OSXOpenGLPFANoRecovery,
        0
    };
    
    id format = objc_id_msgSend((id)objc_getClass("NSOpenGLPixelFormat"), sel_getUid("alloc"));
    format = objc_id_msgSend_voidstar(format, sel_getUid("initWithAttributes:"), pixelFormatAttributes);
    
    id glView = objc_id_msgSend((id)objc_getClass("NSOpenGLView"), sel_getUid("alloc"));
    glView = objc_view_init_msgSend(glView, sel_getUid("initWithFrame:pixelFormat:"), contentRect, format);
    
    objc_void_msgSend(glView, sel_getUid("acceptsFirstResponder"));
    id glContext = objc_id_msgSend(glView, sel_getUid("openGLContext"));
    objc_void_msgSend(glContext, sel_getUid("makeCurrentContext"));
    GLint swapInt = 1;
    objc_void_msgSend_voidstar_int(glContext, sel_getUid("setValues:forParameter:"), &swapInt, OSXOpenGLContextParameterSwapInterval);
    objc_void_msgSend_id(app_window, sel_getUid("setContentView:"), glView);
    
    objc_void_msgSend(glView, sel_getUid("prepareOpenGL"));
    
    objc_void_msgSend_id(app_window, sel_getUid("setDelegate:"), app_window);
    objc_void_msgSend_bool(app_window, sel_getUid("setAcceptsMouseMovedEvents:"), YES);
    objc_void_msgSend_bool(app_window, sel_getUid("setOpaque:"), YES);
    
    object_setInstanceVariable(app_window, "glView", glView);
    
    objc_void_msgSend_int(app_window, sel_getUid("setCollectionBehavior:"), OSXWindowCollectionBehaviorFullScreenPrimary);
    
    return app_window;
}

id app_internal_osx_view_init(app_t* app, int width, int height)
{
    id nsapp = objc_id_msgSend((id)objc_getClass("NSApplication"), sel_getUid("sharedApplication"));
    
    Class AppWindow = objc_allocateClassPair((Class)objc_getClass("NSWindow"), "AppWindow", 0);
    class_addIvar(AppWindow, "glView", sizeof(id), 4, "@");
    class_addIvar(AppWindow, "app", sizeof(app_t*), 4, "^app_t=}");
    
    // add delegate methods for NSWindow and NSApplication
    class_addMethod(AppWindow, sel_getUid("keyDown:"), (IMP)osx_window_keyDown, "v@:@");
    class_addMethod(AppWindow, sel_getUid("applicationDidFinishLaunching:"), (IMP)osx_applicationDidFinishLaunching, "v@:@");
    class_addMethod(AppWindow, sel_getUid("applicationShouldTerminate:"), (IMP)osx_applicationShouldTerminate, "i@:@");
    class_addMethod(AppWindow, sel_getUid("windowWillClose:"), (IMP)osx_windowWillClose, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidResize:"), (IMP)osx_windowDidResize, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidMove:"), (IMP)osx_windowDidMove, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidMiniaturize:"), (IMP)osx_windowDidMiniaturize, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidDeminiaturize:"), (IMP)osx_windowDidDeminiaturize, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidEnterFullScreen:"), (IMP)osx_windowDidEnterFullScreen, "v@:@");
    class_addMethod(AppWindow, sel_getUid("windowDidExitFullScreen:"), (IMP)osx_windowDidExitFullScreen, "v@:@");
    class_addMethod(AppWindow, sel_getUid("applicationShouldTerminateAfterLastWindowClosed:"), (IMP)osx_applicationShouldTerminateAfterLastWindowClosed, "c@:@");
    
    // register our class
    objc_registerClassPair(AppWindow);
    
    int applicationActivationPolicyRegular = 0;
    int applicationPresentationDefault = 0;
    objc_void_msgSend_int(nsapp, sel_getUid("setActivationPolicy:"), applicationActivationPolicyRegular);
    objc_void_msgSend_int(nsapp, sel_getUid("setPresentationOptions:"), applicationPresentationDefault);
    
    id processInfo = objc_id_msgSend((id)objc_getClass("NSProcessInfo"), sel_getUid("processInfo"));
    id appName = objc_id_msgSend(processInfo, sel_getUid("processName"));
    
    // create the window
    id app_window = app_internal_osx_create_window(appName, width, height);
    object_setInstanceVariable(app_window, "app", app);
    
    // add a menubar with a quit option
    id menubar = objc_id_msgSend((id)objc_getClass("NSMenu"), sel_getUid("new"));
    id appMenuItem = objc_id_msgSend((id)objc_getClass("NSMenuItem"), sel_getUid("new"));
    objc_void_msgSend_id(menubar, sel_getUid("addItem:"), appMenuItem);
    objc_void_msgSend_id(nsapp, sel_getUid("setMainMenu:"), menubar);
    id appMenu = objc_id_msgSend((id)objc_getClass("NSMenu"), sel_getUid("new"));
    id quitTitle = objc_id_msgSend_voidstar((id)objc_getClass("NSString"), sel_getUid("stringWithUTF8String:"), "Quit ");
    id qKey = objc_id_msgSend_voidstar((id)objc_getClass("NSString"), sel_getUid("stringWithUTF8String:"), "q");
    quitTitle = objc_id_msgSend_id(quitTitle, sel_getUid("stringByAppendingString:"), appName);
    id quitMenuItem = objc_id_msgSend((id)objc_getClass("NSMenuItem"), sel_getUid("alloc"));
    quitMenuItem = objc_menuitem_init_msgSend(quitMenuItem, sel_getUid("initWithTitle:action:keyEquivalent:"), quitTitle, sel_getUid("terminate:"), qKey);
    objc_void_msgSend_id(appMenu, sel_getUid("addItem:"), quitMenuItem);
    objc_void_msgSend_id(appMenuItem, sel_getUid("setSubmenu:"), appMenu);
    
    objc_void_msgSend_id(nsapp, sel_getUid("setDelegate:"), app_window);
    objc_void_msgSend_bool(nsapp, sel_getUid("activateIgnoringOtherApps:"), YES);
    objc_void_msgSend(nsapp, sel_getUid("finishLaunching"));
    
    return app_window;
}

OSStatus app_internal_osx_audio_output_cb(
                    void *inRefCon,
                    AudioUnitRenderActionFlags     *ioActionFlags,
                    const AudioTimeStamp         *inTimeStamp,
                    UInt32                         inBusNumber,
                    UInt32                         inNumberFrames,
                    AudioBufferList             *ioData)
{
    app_t* app = (app_t*) inRefCon;
    if(app->audio_buffer == NULL)
        return noErr;
    
    short* inbuf = (short*)app->audio_buffer;
    short* outbuf = (short*)ioData->mBuffers[0].mData;
    
    int read_pos = app->audio_buffer_position;
    int buf_end = app->audio_buffer_size;
    float vol = app->sound_vol;
    for (UInt32 frame = 0; frame < inNumberFrames; frame++)
    {
        outbuf[frame*2] = (short)(vol * inbuf[read_pos*2]);
        outbuf[frame*2+1] = (short)(vol * inbuf[read_pos*2+1]);

        read_pos++;
        if(read_pos == buf_end)
            read_pos = 0;
    }
    app->audio_buffer_position = read_pos;
    
    return noErr;
}

void app_internal_osx_audio_init(app_t* app)
{
    AudioComponentDescription defaultOutputDescription;
    defaultOutputDescription.componentType = kAudioUnitType_Output;
    defaultOutputDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
    defaultOutputDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    defaultOutputDescription.componentFlags = 0;
    defaultOutputDescription.componentFlagsMask = 0;
    
    // Get the default playback output unit
    AudioComponent defaultOutput = AudioComponentFindNext(NULL, &defaultOutputDescription);
    //    NSAssert(defaultOutput, @"Can't find default output");
    
    // Create a new unit based on this that we'll use for output
    OSErr err = AudioComponentInstanceNew(defaultOutput, &app->audioUnit);
    //    NSAssert1(toneUnit, @"Error creating unit: %ld", err);
    
    // Set our audio output function on the unit
    AURenderCallbackStruct input;
    input.inputProc = app_internal_osx_audio_output_cb;
    input.inputProcRefCon = app;
    err = AudioUnitSetProperty(app->audioUnit,
                               kAudioUnitProperty_SetRenderCallback,
                               kAudioUnitScope_Input,
                               0,
                               &input,
                               sizeof(input));
    //    NSAssert1(err == noErr, @"Error setting callback: %ld", err);
    
    // Set the format to stereo, 16bit signed integer, linear PCM
    const int bytes_per_channel = sizeof(short);
    double sampleRate = 44100;
    int channels = 2;
    
    AudioStreamBasicDescription streamFormat = {0};
    streamFormat.mSampleRate = sampleRate;
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger;
    streamFormat.mBytesPerPacket = bytes_per_channel * channels;
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mBytesPerFrame = bytes_per_channel * channels;
    streamFormat.mChannelsPerFrame = channels;
    streamFormat.mBitsPerChannel = bytes_per_channel * 8;
    err = AudioUnitSetProperty (app->audioUnit,
                                kAudioUnitProperty_StreamFormat,
                                kAudioUnitScope_Input,
                                0,
                                &streamFormat,
                                sizeof(AudioStreamBasicDescription));
    //    NSAssert1(err == noErr, @"Error setting stream format: %ld", err);
    
    AudioUnitInitialize(app->audioUnit);
    app->audio_buffer = NULL;
    app->audio_buffer_size = 0;
    app->audio_buffer_position = 0;
    app->sound_vol = 1.0f;
}

int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx )
{
    int result = 0xff;
        
    id autoReleasePool = objc_id_msgSend((id)objc_getClass("NSAutoreleasePool"), sel_getUid("alloc"));
    autoReleasePool = objc_id_msgSend(autoReleasePool, sel_getUid("init"));
    
    // Init app instance
    app_t* app = (app_t*) APP_MALLOC( memctx, sizeof( app_t ) );
    memset( app, 0, sizeof( *app ) );
    app->memctx = memctx;
    app->logctx = logctx;
    app->fatalctx = fatalctx;
    app->interpolation = APP_INTERPOLATION_LINEAR;
    app->screenmode = APP_SCREENMODE_FULLSCREEN;
    
    // Log start message
    char msg[ 64 ];
    time_t t = time( NULL );
    struct tm* start = localtime( &t );
    sprintf( msg, "Application started %02d:%02d:%02d %04d-%02d-%02d.",
            start->tm_hour, start->tm_min, start->tm_sec, start->tm_year + 1900, start->tm_mon + 1, start->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );
    
    // Increase timing precision
/*    TIMECAPS tc;
    if( timeGetDevCaps( &tc, sizeof( TIMECAPS ) ) == TIMERR_NOERROR )
        timeBeginPeriod( tc.wPeriodMin );
    
    // Get instance handle
    app->hinstance = GetModuleHandle( NULL );
    
    // Retrieve the path of our executable
    GetModuleFileNameA( 0, app->exe_path, sizeof( app->exe_path ) );
    
    // Retrieve user data path
    SHGetFolderPathA( NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, app->userdata_path );
    
    // Retrieve app data path
    SHGetFolderPathA( NULL, CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, app->appdata_path );
    
    // Get command line string
    app->cmdline = GetCommandLineA();
    
    // Load a default Arrow cursor
    app_internal_app_default_cursor( app );
    
    // Load first icon in the exe and use as app icon
    app->icon = LoadIconA( app->hinstance , MAKEINTRESOURCEA( 1 ) );
*/

    app->display_count = app_internal_osx_get_screen_count();
    if( app->display_count <= 0 ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to get display info" ); goto init_failed;  }

    for(int i=0; i<app->display_count; ++i)
    {
        app_internal_osx_get_screen_rect(i, &app->displays[i].x, &app->displays[i].y, &app->displays[i].width, &app->displays[i].height);

        // not quite sure what to use as the id. for now just use the screen index.
        snprintf(app->displays[i].id, 16, "%d", i);
    }
    
    // Setup the main application window
    app->windowed_w = app->displays[ 0 ].width - app->displays[ 0 ].width / 6;
    app->windowed_h = app->displays[ 0 ].height - app->displays[ 0 ].height / 6;
    app->windowed_x = ( app->displays[ 0 ].width - app->windowed_w ) /  2;
    app->windowed_y = ( app->displays[ 0 ].height - app->windowed_h ) / 2;
    
    app->fullscreen_width = app->displays[ 0 ].width;
    app->fullscreen_height = app->displays[ 0 ].height;

    app->window = app_internal_osx_view_init(app, app->windowed_w, app->windowed_h);

    app->has_focus = TRUE;
    app->is_minimized = FALSE;
    app->initialized = FALSE;
   
    // Bind opengl functions
    app->gl.glCreateShader = glCreateShader;
    app->gl.glShaderSource = glShaderSource;
    app->gl.glCompileShader = glCompileShader;
    app->gl.glGetShaderiv = glGetShaderiv;
    app->gl.glCreateProgram = glCreateProgram;
    app->gl.glAttachShader = glAttachShader;
    app->gl.glBindAttribLocation = glBindAttribLocation;
    app->gl.glLinkProgram = glLinkProgram;
    app->gl.glGetProgramiv = glGetProgramiv;
    app->gl.glGenBuffers = glGenBuffers;
    app->gl.glBindBuffer = glBindBuffer;
    app->gl.glEnableVertexAttribArray = glEnableVertexAttribArray;
    app->gl.glVertexAttribPointer = glVertexAttribPointer;
    app->gl.glGenVertexArrays = glGenVertexArrays;
    app->gl.glBindVertexArray = glBindVertexArray;
    app->gl.glGenTextures = glGenTextures;
    app->gl.glEnable = glEnable;
    app->gl.glActiveTexture = glActiveTexture;
    app->gl.glBindTexture = glBindTexture;
    app->gl.glTexParameteri = glTexParameteri;
    app->gl.glDeleteBuffers = glDeleteBuffers;
    app->gl.glDeleteTextures = glDeleteTextures;
    app->gl.glBufferData = glBufferData;
    app->gl.glUseProgram = glUseProgram;
    app->gl.glUniform1i = glUniform1i;
    app->gl.glUniform3f = glUniform3f;
    app->gl.glGetUniformLocation = glGetUniformLocation;
    app->gl.glTexImage2D = glTexImage2D;
    app->gl.glClearColor = glClearColor;
    app->gl.glClear = glClear;
    app->gl.glDrawArrays = glDrawArrays;
    app->gl.glViewport = glViewport;
    app->gl.glDeleteShader = glDeleteShader;
    app->gl.glDeleteProgram = glDeleteProgram;
#ifdef APP_REPORT_SHADER_ERRORS
    app->gl.glGetShaderInfoLog = glGetShaderInfoLog;
#endif
    
    // Platform independent OpenGL initialization
    int width = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_width : app->windowed_w;
    int height = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_height: app->windowed_h;
    if( !app_internal_opengl_init( app, &app->gl, app->interpolation, width, height ) )
    {
        app_log( app, APP_LOG_LEVEL_ERROR, "Failed to initialize OpenGL" );
        goto init_failed;
    }
    
    app_internal_opengl_resize( &app->gl, width, height );
    app_internal_osx_audio_init(app);
    
/*
    USHORT const USAGE_PAGE_GENERIC = ((USHORT) 0x01);
    USHORT const USAGE_GENERIC_MOUSE = ((USHORT) 0x02);
    
    RAWINPUTDEVICE rid[ 1 ];
    rid[ 0 ].usUsagePage = USAGE_PAGE_GENERIC;
    rid[ 0 ].usUsage = USAGE_GENERIC_MOUSE;
    rid[ 0 ].dwFlags = RIDEV_INPUTSINK;
    rid[ 0 ].hwndTarget = app->hwnd;
    RegisterRawInputDevices( rid, 1, sizeof( *rid ) );
    
    if( !app_internal_tablet_init( app ) ) app_log( app, APP_LOG_LEVEL_WARNING, "WinTab initialization failed - tablet not available" );
    */
    result = app_proc( app, user_data );
    
init_failed:
    if( !app_internal_opengl_term( &app->gl ) ) app_log( app, APP_LOG_LEVEL_WARNING, "Failed to terminate OpenGL" );
    // shutdown audiounit??
    objc_void_msgSend(autoReleasePool, sel_getUid("release"));
    
    t = time( NULL );
    struct tm* end = localtime( &t );
    sprintf( msg, "Application terminated %02d:%02d:%02d %04d-%02d-%02d.",
            end->tm_hour, end->tm_min, end->tm_sec, end->tm_year + 1900, end->tm_mon + 1, end->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );
    
    APP_FREE( memctx, app );
    return result;

}
app_state_t app_yield( app_t* app )
{
    if( !app->initialized )
    {
        if( app->screenmode == APP_SCREENMODE_WINDOW )
        {
            app->screenmode = APP_SCREENMODE_FULLSCREEN;
            app_screenmode( app, APP_SCREENMODE_WINDOW );
        }
        else
        {
            app->screenmode = APP_SCREENMODE_WINDOW;
            app_screenmode( app, APP_SCREENMODE_FULLSCREEN );
        }
        app_internal_osx_show_window(app->window);
        app->initialized = TRUE;
    }
    
    app_internal_osx_handle_events(app->window);
    
    return app->closed ? APP_STATE_EXIT_REQUESTED : APP_STATE_NORMAL;
}

void app_cancel_exit( app_t* app )
{
    app->closed = false;
}

void app_title( app_t* app, char const* title )
{
    app_internal_osx_set_window_title(app->window, title);
}

char const* app_cmdline( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_cmdline not implemented for macos yet\n");
    return 0;
}

char const* app_filename( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_filename not implemented for macos yet\n");
    return 0;
}

char const* app_userdata( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_userdata not implemented for macos yet\n");
    return 0;
}

char const* app_appdata( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_appdata not implemented for macos yet\n");
    return 0;
}

APP_U64 app_time_count( app_t* app )
{
    return mach_absolute_time();
}

APP_U64 app_time_freq( app_t* app )
{
    static APP_U64 time_freq = 0;
    if(time_freq == 0)
    {
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        time_freq = (APP_U64)(1000000000 * ((double)info.numer / info.denom));
    }
    return time_freq;
}

void app_log( app_t* app, app_log_level_t level, char const* message )
{
    APP_LOG( app->logctx, level, message );
}

void app_fatal_error( app_t* app, char const* message )
{
    APP_FATAL_ERROR( app->fatalctx, message );
}

void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer not implemented for macos yet\n");
}

void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_default not implemented for macos yet\n");
}

void app_pointer_pos( app_t* app, int x, int y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_pos not implemented for macos yet\n");
}

void app_pointer_limit( app_t* app, int x, int y, int width, int height )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_limit not implemented for macos yet\n");
}

void app_pointer_limit_off( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_limit_off not implemented for macos yet\n");
}

void app_interpolation( app_t* app, app_interpolation_t interpolation )
{
    if( interpolation == app->interpolation ) return;
    app->interpolation = interpolation;
    
/*    POINT p;
    GetCursorPos( &p );
    ScreenToClient( app->hwnd, &p );
    int mouse_x = p.x;
    int mouse_y = p.y;
    
    app_input_event_t input_event;
    input_event.type = APP_INPUT_MOUSE_MOVE;
    input_event.data.mouse_pos.x = mouse_x;
    input_event.data.mouse_pos.y = mouse_y;
    app_internal_add_input_event( app, &input_event );
 */
    
    app_internal_opengl_interpolation( &app->gl, interpolation );
}

void app_screenmode( app_t* app, app_screenmode_t screenmode )
{
    if(app->screenmode == screenmode)
        return;

    app->screenmode = screenmode;
    if(screenmode == APP_SCREENMODE_WINDOW)
    {
        app_internal_osx_set_fullscreen(app->window, false);
        app_internal_osx_set_window_content_size(app->window, app->windowed_w, app->windowed_h);
        app_internal_opengl_resize( &app->gl, app->windowed_w, app->windowed_h );
    }
    else if(screenmode == APP_SCREENMODE_FULLSCREEN)
    {
        app_internal_osx_set_fullscreen(app->window, true);
        app_internal_opengl_resize( &app->gl, app->fullscreen_width, app->fullscreen_height );
    }
}

void app_window_size( app_t* app, int width, int height )
{
    app->windowed_w = width;
    app->windowed_h = height;
    if(app->screenmode == APP_SCREENMODE_WINDOW)
    {
        app_internal_osx_set_window_content_size(app->window, app->windowed_w, app->windowed_h);
        app_internal_opengl_resize( &app->gl, width, height );
    }
}

int app_window_width( app_t* app )
{
    return app->windowed_w;
}

int app_window_height( app_t* app )
{
    return app->windowed_h;
}

void app_window_pos( app_t* app, int x, int y )
{
    app->windowed_x = x;
    app->windowed_y = y;
    app_internal_osx_set_window_position(app->window, app->windowed_x, app->windowed_y);
}

int app_window_x( app_t* app )
{
    return app->windowed_x;
}

int app_window_y( app_t* app )
{
    return app->windowed_y;
}

app_displays_t app_displays( app_t* app )
{
    app_displays_t displays;
    displays.count = app->display_count;
    displays.displays = app->displays;
    return displays;
}

void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr )
{
    if( pixels_xbgr ) app_internal_opengl_present( &app->gl, pixels_xbgr, width, height, mod_xbgr, border_xbgr );
    app_internal_osx_present(app->window);
}

void app_sound_buffer_size( app_t* app, int sample_pairs_count )
{
    if(app->audio_buffer != NULL)
    {
        APP_FREE(app->memctx, app->audio_buffer);
    }

    if(sample_pairs_count > 0)
    {
        app->audio_buffer_size = sample_pairs_count;
        app->audio_buffer_position = 0;
        app->audio_buffer = APP_MALLOC(app->memctx, sample_pairs_count * 2 * sizeof(short));
        memset(app->audio_buffer, 0x00, sample_pairs_count * 2 * sizeof(short));
        
        AudioOutputUnitStart(app->audioUnit);
    }
    else
    {
        AudioOutputUnitStop(app->audioUnit);
        app->audio_buffer_size = 0;
        app->audio_buffer = NULL;
    }
}

int app_sound_position( app_t* app )
{
    return app->audio_buffer_position;
}

void app_sound_write( app_t* app, int sample_pairs_offset, int sample_pairs_count, APP_S16 const* sample_pairs )
{
    if(app->audio_buffer == NULL)
        return;
    
    APP_S16* buffer = &app->audio_buffer[sample_pairs_offset * 2];
    for(int i=0; i<sample_pairs_count * 2; ++i)
    {
        buffer[i] = sample_pairs[i];
    }
}

void app_sound_volume( app_t* app, float volume )
{
    if(volume > 1.0f) volume = 1.0f;
    if(volume < 0.0f) volume = 0.0f;
    app->sound_vol = volume;
}

app_input_t app_input( app_t* app )
{
    app_input_t input;
    input.events = app->input_events;
    input.count = app->input_count;
    app->input_count = 0;
    return input;
}

void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y )
{
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : app->windowed_w;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : app->windowed_h;

    if( app->interpolation == APP_INTERPOLATION_LINEAR )
    {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
        {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x -= (int)( hborder );
            *y -= (int)( vborder );
            *x = (int)( *x / pixel_scale );
            *y = (int)( *y / pixel_scale );
        }
        else
        {
            *x = 0;
            *y = 0;
        }
    }
    else
    {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x -= (int)( hborder );
        *y -= (int)( vborder );
        *x = (int)( *x / pixel_scale );
        *y = (int)( *y / pixel_scale );
    }
}


void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y )
{
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : app->windowed_w;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : app->windowed_h;

    if( app->interpolation == APP_INTERPOLATION_LINEAR )
    {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
        {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x = (int)( *x * pixel_scale );
            *y = (int)( *y * pixel_scale );
            *x += (int)( hborder );
            *y += (int)( vborder );
        }
        else
        {
            *x = 0;
            *y = 0;
        }
    }
    else
    {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x = (int)( *x * pixel_scale );
        *y = (int)( *y * pixel_scale );
        *x += (int)( hborder );
        *y += (int)( vborder );
    }
}

#elif defined( APP_LINUX_X11 )

#include <stdbool.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <alsa/asoundlib.h>

#ifndef APP_MALLOC
#include <stdlib.h>
#if defined(__cplusplus)
#define APP_MALLOC( ctx, size ) ( ::malloc( size ) )
#define APP_FREE( ctx, ptr ) ( ::free( ptr ) )
#else
#define APP_MALLOC( ctx, size ) ( malloc( size ) )
#define APP_FREE( ctx, ptr ) ( free( ptr ) )
#endif
#endif

#ifndef APP_LOG
#if defined(__cplusplus)
#define APP_LOG( ctx, level, message ) ::printf( "%s\n", message )
#else
#define APP_LOG( ctx, level, message ) printf( "%s\n", message )
#endif
#endif

#ifndef APP_FATAL_ERROR
// todo: use a linux messagebox??
#define APP_FATAL_ERROR( ctx, message ) { printf( "FATAL ERROR: %s\n", message ); _exit( 0xff ); }
/*
#if defined(__cplusplus)
#define APP_FATAL_ERROR( ctx, message ) { ::printf( "FATAL ERROR: %s\n", message ); \
::MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); ::_flushall(); ::_exit( 0xff ); }
#else
#define APP_FATAL_ERROR( ctx, message ) { printf( "FATAL ERROR: %s\n", message ); \
MessageBoxA( 0, message, "Fatal Error!", MB_OK | MB_ICONSTOP ); _flushall(); _exit( 0xff ); }
#endif
 */
#endif

struct app_t 
{
    void* memctx;
    void* logctx;
    void* fatalctx;
    app_interpolation_t interpolation;
    app_screenmode_t screenmode;

    bool initialized;
    bool closed;
    bool has_focus;
    bool is_minimized;

    Display* display;
    Window window;
    GLXContext glContext;
    Colormap colMap;

    int display_count;
    app_display_t displays[ 16 ];
    
    struct app_internal_opengl_t gl;
    
    app_input_event_t input_events[ 1024 ];
    int input_count;
    
    int windowed_x;
    int windowed_y;
    int windowed_h;
    int windowed_w;
    int fullscreen_width;
    int fullscreen_height;    

    snd_pcm_t* alsa_handle;
    snd_pcm_hw_params_t* alsa_hw_params;

    APP_S16* audio_buffer;
    int audio_buffer_size;
    int audio_buffer_position;
    float sound_vol;
};

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef void(*glXSwapIntervalProc)(unsigned int);

static app_key_t app_internal_x11_map_key(KeySym keyCode, char keyChar)
{
    if(keyCode >= XK_0 && keyCode <= XK_9)
        return APP_KEY_0 + (keyCode - XK_0);
    if(keyCode >= XK_KP_0 && keyCode <= XK_KP_9)
        return APP_KEY_NUMPAD0 + (keyCode - XK_KP_0);
    if(keyCode >= XK_a && keyCode <= XK_z)
        return APP_KEY_A + (keyCode - XK_a);
    if(keyCode >= XK_A && keyCode <= XK_Z)
        return APP_KEY_A + (keyCode - XK_A);
    if(keyCode >= XK_F1 && keyCode <= XK_F24)
        return APP_KEY_F1 + (keyCode - XK_F1);

    switch(keyCode)
    {
        case XK_BackSpace:
            return APP_KEY_BACK;
        case XK_Tab:
            return APP_KEY_TAB;
        case XK_Clear:
            return APP_KEY_CLEAR;
        case XK_Return:
            return APP_KEY_RETURN;
        case XK_Shift_L:
        case XK_Shift_R:
            return APP_KEY_SHIFT;
        case XK_Control_L:
        case XK_Control_R:
            return APP_KEY_CONTROL;
        case XK_Escape:
            return APP_KEY_ESCAPE;
        case XK_space:
        case XK_KP_Space:
            return APP_KEY_SPACE;
        case XK_End:
            return APP_KEY_END;
        case XK_Home:
            return APP_KEY_HOME;
        case XK_Left:
            return APP_KEY_LEFT;
        case XK_Right:
            return APP_KEY_RIGHT;
        case XK_Up:
            return APP_KEY_UP;
        case XK_Down:
            return APP_KEY_DOWN;
        case XK_Insert:
            return APP_KEY_INSERT;
        case XK_Delete:
            return APP_KEY_DELETE;
        case XK_Help:
            return APP_KEY_HELP;
        default:
            break;
    }
    
    return APP_KEY_INVALID;
}

static void app_internal_add_input_event( app_t* app, app_input_event_t* event )
{
    if( app->has_focus )
    {
        if( app->input_count < sizeof( app->input_events ) / sizeof( *app->input_events ) )
            app->input_events[ app->input_count++ ] = *event;
    }
}

void app_internal_x11_add_key_event(app_t* app, KeySym keyCode, char keyChar, bool isUp)
{
    app_input_event_t event;
    event.type = isUp ? APP_INPUT_KEY_UP : APP_INPUT_KEY_DOWN;
    event.data.key = app_internal_x11_map_key(keyCode, keyChar);
    app_internal_add_input_event(app, &event);
    
    if(!isUp)
    {
        event.type = APP_INPUT_CHAR;
        event.data.char_code = keyChar;
        app_internal_add_input_event(app, &event);
    }
}

void app_internal_x11_add_mouse_move_event(app_t* app, int mouse_x, int mouse_y)
{
    app_input_event_t event;
    event.type = APP_INPUT_MOUSE_MOVE;
    event.data.mouse_pos.x = mouse_x;
    event.data.mouse_pos.y = mouse_y;
    
    app_internal_add_input_event( app, &event );
}

void app_internal_x11_add_mouse_press_event(app_t* app, int button, bool isUp, bool isDoubleClick)
{
    if(button < 0 || button > 2)
        return;
    
    app_input_event_t event;
    event.type = isDoubleClick ? APP_INPUT_DOUBLE_CLICK : isUp ? APP_INPUT_KEY_UP : APP_INPUT_KEY_DOWN;
    event.data.key = button == 0 ? APP_KEY_LBUTTON : button == 1 ? APP_KEY_RBUTTON : APP_KEY_MBUTTON;
    
    app_internal_add_input_event( app, &event );
}

void app_internal_x11_add_scroll_event(app_t* app, float scrollY)
{
    app_input_event_t event;
    event.type = APP_INPUT_SCROLL_WHEEL;
    event.data.wheel_delta = scrollY;
    
    app_internal_add_input_event( app, &event );
}


// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension)
{
  const char *start;
  const char *where, *terminator;
  
  // Extension names should not have spaces.
  where = strchr(extension, ' ');
  if (where || *extension == '\0')
    return false;

  // It takes a bit of care to be fool-proof about parsing the
  //   OpenGL extensions string. Don't be fooled by sub-strings, etc.
  for (start=extList;;) {
    where = strstr(start, extension);

    if (!where)
      break;

    terminator = where + strlen(extension);

    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return true;

    start = terminator;
  }

  return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}

extern char *__progname;
void app_internal_x11_view_init(app_t* app, int width, int height)
{
    Display *display = XOpenDisplay(NULL);

    if (!display)
    {
        app_fatal_error(app, "Failed to open X display\n");
    }

    // Get a matching FB config
    static int visual_attribs[] =
    {
      GLX_X_RENDERABLE    , True,
      GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
      GLX_RENDER_TYPE     , GLX_RGBA_BIT,
      GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
      GLX_RED_SIZE        , 8,
      GLX_GREEN_SIZE      , 8,
      GLX_BLUE_SIZE       , 8,
      GLX_ALPHA_SIZE      , 8,
      GLX_DEPTH_SIZE      , 24,
      GLX_STENCIL_SIZE    , 8,
      GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
    };

    int glx_major, glx_minor;
 
    // FBConfigs were added in GLX version 1.3.
    if ( !glXQueryVersion( display, &glx_major, &glx_minor ) || 
        ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
    {
        app_fatal_error (app, "Invalid GLX version\n");
    }

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fbcount);
    if (!fbc)
    {
        app_fatal_error( app, "Failed to retrieve a framebuffer config\n" );
    }

    // Pick the FB config/visual with the most samples per pixel
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
    for (int i=0; i<fbcount; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
        if ( vi )
        {
        int samp_buf, samples;
        glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
        glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES       , &samples  );
        
        if ( best_fbc < 0 || samp_buf && samples > best_num_samp )
            best_fbc = i, best_num_samp = samples;
        if ( worst_fbc < 0 || !samp_buf || samples < worst_num_samp )
            worst_fbc = i, worst_num_samp = samples;
        }
        XFree( vi );
    }

    GLXFBConfig bestFbc = fbc[ best_fbc ];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree( fbc );

    // Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig( display, bestFbc );

    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap( display,
                                            RootWindow( display, vi->screen ), 
                                            vi->visual, AllocNone );
    swa.background_pixmap = None ;
    swa.border_pixel      = 0;
    swa.event_mask        = StructureNotifyMask;

    Window win = XCreateWindow( display, RootWindow( display, vi->screen ), 
                                0, 0, width, height, 0, vi->depth, InputOutput, 
                                vi->visual, 
                                CWBorderPixel|CWColormap|CWEventMask, &swa );
    if ( !win )
    {
        app_fatal_error( app, "Failed to create window.\n" );
    }

    // Done with the visual info data
    XFree( vi );

    XStoreName( display, win, __progname );

    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString( display,
                                                    DefaultScreen( display ) );
    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
            glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

    GLXContext ctx = 0;

    // Install an X error handler so the application won't exit if GL 3.0
    // context allocation fails.
    //
    // Note this error handler is global.  All display connections in all threads
    // of a process use the same error handler, so be sure to guard against other
    // threads issuing X commands while this code is running.
    ctxErrorOccurred = false;
    int (*oldHandler)(Display*, XErrorEvent*) =
        XSetErrorHandler(&ctxErrorHandler);

    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
        !glXCreateContextAttribsARB )
    {
     //   printf( "glXCreateContextAttribsARB() not found ... using old-style GLX context\n" );
        ctx = glXCreateNewContext( display, bestFbc, GLX_RGBA_TYPE, 0, True );
    }

    // If it does, try to get a GL 3.0 context!
    else
    {
        int context_attribs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 2,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            None
        };

        ctx = glXCreateContextAttribsARB( display, bestFbc, 0,
                                        True, context_attribs );

        // Sync to ensure any errors generated are processed.
        XSync( display, False );
        if ( ctxErrorOccurred || ctx == NULL )
        {
            // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
            // When a context version below 3.0 is requested, implementations will
            // return the newest context version compatible with OpenGL versions less
            // than version 3.0.
            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

        //    printf( "Failed to create GL 3.0 context ... using old-style GLX context\n" );
            ctx = glXCreateContextAttribsARB( display, bestFbc, 0, 
                                                True, context_attribs );
        }
    }

    // Sync to ensure any errors generated are processed.
    XSync( display, False );

    // attempt to enable vsync
    glXSwapIntervalProc glXSwapInterval = NULL;
    if(isExtensionSupported(glxExts, "GLX_EXT_swap_control"))
    {
        glXSwapInterval = (glXSwapIntervalProc)glXGetProcAddressARB("glXSwapIntervalEXT");
    }
    else if(isExtensionSupported(glxExts, "GLX_MESA_swap_control"))
    {
        glXSwapInterval = (glXSwapIntervalProc)glXGetProcAddressARB("glXSwapIntervalMESA");
    }

    if(glXSwapInterval != NULL)
    {
        glXSwapInterval(1);
    }


    // Restore the original error handler
    XSetErrorHandler( oldHandler );

    if ( ctxErrorOccurred || !ctx )
    {
        app_fatal_error( app, "Failed to create an OpenGL context\n" );
    }

    glXMakeCurrent( display, win, ctx );

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, win, &wmDeleteMessage, 1); 

    XSelectInput(display, win,  ButtonPressMask | ButtonReleaseMask |
                                KeyPressMask | KeyReleaseMask |
                                ButtonMotionMask | PointerMotionMask |
                                StructureNotifyMask );

    app->display = display;
    app->window = win;
    app->glContext = ctx;
    app->colMap = cmap;
}

void app_internal_x11_handle_events(app_t* app)
{
    Atom wmDeleteMessage = XInternAtom(app->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(app->display, app->window, &wmDeleteMessage, 1);

    while(XPending(app->display))
    {
        XEvent event;
        XNextEvent(app->display, &event);
        
        switch(event.type)
        {
            case KeyPress:
            case KeyRelease:
                {
                    XKeyEvent ev = event.xkey;
                    bool isUp = ev.type == KeyRelease;
                    char key_str[4];
                    KeySym key_sym;
                    XLookupString(&ev, key_str, 4, &key_sym, NULL);
                    app_internal_x11_add_key_event(app, key_sym, key_str[0], isUp);
                }
                break;
            case MotionNotify:
                {
                    int x = event.xmotion.x;
                    int y = event.xmotion.y;

                    app_internal_x11_add_mouse_move_event(app, x,y);
                }
                break;
            case ButtonPress:
                {
                    int button = event.xbutton.button;
                    app_internal_x11_add_mouse_press_event(app, button-1, false, false);
                }
                break;
            case ButtonRelease:
                {
                    int button = event.xbutton.button;
                    app_internal_x11_add_mouse_press_event(app, button-1, true, false);
                }
                break;
            case ConfigureNotify:
                {                   
                    if(app->screenmode == APP_SCREENMODE_WINDOW)
                    {
                        XConfigureEvent ev = event.xconfigure;
                        app->windowed_w = ev.width;
                        app->windowed_h = ev.height;
                        app->windowed_x = ev.x;
                        app->windowed_y = ev.y;
                        app_internal_opengl_resize( &app->gl, app->windowed_w, app->windowed_h );
                    }
                }
                break;
            case ClientMessage:
                {
                    if(event.xclient.data.l[0] == wmDeleteMessage)
                    { 
                        app->closed = true;
                    }
                }
                break;
            default:
                break;
        }
    }
}

static void app_internal_linux_audio_output_cb(snd_async_handler_t *ahandler)
{
    snd_pcm_t *alsa_handle = snd_async_handler_get_pcm(ahandler);
    app_t* app = snd_async_handler_get_callback_private(ahandler);

    short* buffer = (short*)app->audio_buffer;
    int read_pos = app->audio_buffer_position;
    int buf_end = app->audio_buffer_size;

    snd_pcm_sframes_t avail;
    int err;
    
    avail = snd_pcm_avail_update(alsa_handle);

//    printf("Audio: %llu\n", avail);

//    while(avail > (app->audio_buffer_size / 4))
    {
        snd_pcm_sframes_t num_frames = buf_end - read_pos;
        if(num_frames > avail)
            num_frames = avail;

        err = snd_pcm_writei(alsa_handle, &buffer[read_pos*2], num_frames);
        if (err < 0) 
        {
            printf("Write error: %s\n", snd_strerror(err));
            return;
        }
        if (err != num_frames) {
            printf("Write error: written %i expected %li\n", err, num_frames);
            return;
        }

        read_pos += num_frames;
        if(read_pos == buf_end)
            read_pos = 0;

        avail = snd_pcm_avail_update(alsa_handle);
    }

    app->audio_buffer_position = read_pos;
}

int app_internal_linux_audio_init(app_t* app)
{
    (void)app;

    int err = 0;
    const char* pcm_name = "plughw:0,0";

    snd_pcm_t* alsa_handle;
    snd_pcm_hw_params_t *hw_params;

    if ((err = snd_pcm_open (&alsa_handle, pcm_name, SND_PCM_STREAM_PLAYBACK, 0)) < 0) 
    {
        app_log(app, APP_LOG_LEVEL_ERROR, snd_strerror (err));
        app_fatal_error(app, "Error opening audio device\n");
        return err;
	}

    unsigned int sample_rate = 44100;
    snd_pcm_hw_params_malloc (&hw_params);
    snd_pcm_hw_params_any (alsa_handle, hw_params);
    snd_pcm_hw_params_set_access (alsa_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format (alsa_handle, hw_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_rate_near (alsa_handle, hw_params, &sample_rate, 0);
    snd_pcm_hw_params_set_channels (alsa_handle, hw_params, 2);

/*    if ((err = snd_pcm_hw_params_set_buffer_size (alsa_handle, hw_params, 4096)) < 0) {
        app_log(app, snd_strerror (err));
        app_fatal_error(app, "Error settting audio buffer\n");
        return err;
    } */

    if ((err = snd_pcm_hw_params (alsa_handle, hw_params)) < 0) {
        app_log(app, APP_LOG_LEVEL_ERROR, snd_strerror (err));
        app_fatal_error(app, "Error setting audio parameters\n");
        return err;
    }

    snd_async_handler_t *ahandler;
    snd_async_add_pcm_handler(&ahandler, alsa_handle, app_internal_linux_audio_output_cb, app);

    if ((err = snd_pcm_prepare (alsa_handle)) < 0) {
        app_log(app, APP_LOG_LEVEL_ERROR, snd_strerror (err));
        app_fatal_error(app, "Error preparing audio interface\n");
        return err;
    }

    app->alsa_handle = alsa_handle;
    app->alsa_hw_params = hw_params;

    return err;
}

void app_internal_linux_audio_shutdown(app_t* app)
{
    snd_pcm_hw_params_free( app->alsa_hw_params );

    snd_pcm_close (app->alsa_handle);
}

int app_run( int (*app_proc)( app_t*, void* ), void* user_data, void* memctx, void* logctx, void* fatalctx )
{ 
    int result = 0xff;

    app_t* app = (app_t*) APP_MALLOC( memctx, sizeof( app_t ) );
    memset( app, 0, sizeof( *app ) );
    app->memctx = memctx;
    app->logctx = logctx;
    app->fatalctx = fatalctx;
    app->interpolation = APP_INTERPOLATION_LINEAR;
    app->screenmode = APP_SCREENMODE_FULLSCREEN;

    // Log start message
    char msg[ 64 ];
    time_t t = time( NULL );
    struct tm* start = localtime( &t );
    sprintf( msg, "Application started %02d:%02d:%02d %04d-%02d-%02d.",
            start->tm_hour, start->tm_min, start->tm_sec, start->tm_year + 1900, start->tm_mon + 1, start->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );

    Display *display = XOpenDisplay(NULL);
    app->display_count = ScreenCount(display);
    if( app->display_count <= 0 ) { app_log( app, APP_LOG_LEVEL_ERROR, "Failed to get display info" ); goto init_failed;  }

    for(int i=0; i<app->display_count; ++i)
    {
        app->displays[i].x = app->displays[i].y = 0;
        app->displays[i].width = XDisplayWidth(display, i);
        app->displays[i].height = XDisplayHeight(display, i);

        // not quite sure what to use as the id. for now just use the screen index.
        snprintf(app->displays[i].id, 16, "%d", i);
    }
    
    // Setup the main application window
    int default_display = XDefaultScreen(display);
    app->windowed_w = app->displays[ default_display ].width - app->displays[ default_display ].width / 6;
    app->windowed_h = app->displays[ default_display ].height - app->displays[ default_display ].height / 6;
    app->windowed_x = ( app->displays[ default_display ].width - app->windowed_w ) /  2;
    app->windowed_y = ( app->displays[ default_display ].height - app->windowed_h ) / 2;
    
    app->fullscreen_width = app->displays[ default_display ].width;
    app->fullscreen_height = app->displays[ default_display ].height;

    app_internal_x11_view_init(app, app->windowed_w, app->windowed_h);

    app->has_focus = true;
    app->is_minimized = false;
    app->initialized = false;
   
    // Bind opengl functions
    app->gl.glCreateShader = ( APP_GLuint (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) glXGetProcAddressARB( "glCreateShader" );
    app->gl.glShaderSource = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLchar const* const*, APP_GLint const*) ) (uintptr_t) glXGetProcAddressARB( "glShaderSource" );
    app->gl.glCompileShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glCompileShader" );
    app->gl.glGetShaderiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) glXGetProcAddressARB( "glGetShaderiv" );
    app->gl.glCreateProgram = ( APP_GLuint (APP_GLCALLTYPE*) (void) ) (uintptr_t) glXGetProcAddressARB( "glCreateProgram" );
    app->gl.glAttachShader = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glAttachShader" );
    app->gl.glBindAttribLocation = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLuint, APP_GLchar const*) ) (uintptr_t) glXGetProcAddressARB( "glBindAttribLocation" );
    app->gl.glLinkProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glLinkProgram" );
    app->gl.glGetProgramiv = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLenum, APP_GLint*) ) (uintptr_t) glXGetProcAddressARB( "glGetProgramiv" );
    app->gl.glGenBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) glXGetProcAddressARB( "glGenBuffers" );
    app->gl.glBindBuffer = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glBindBuffer" );
    app->gl.glEnableVertexAttribArray = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glEnableVertexAttribArray" );
    app->gl.glVertexAttribPointer = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLint, APP_GLenum, APP_GLboolean, APP_GLsizei, void const*) ) (uintptr_t) glXGetProcAddressARB( "glVertexAttribPointer" );
    app->gl.glGenVertexArrays = (void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) glXGetProcAddressARB( "glGenVertexArrays" );
    app->gl.glBindVertexArray = (void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glBindVertexArray" );
    app->gl.glGenTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint*) ) (uintptr_t) glXGetProcAddressARB( "glGenTextures" );
    app->gl.glEnable = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) glXGetProcAddressARB( "glEnable" );
    app->gl.glActiveTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum) ) (uintptr_t) glXGetProcAddressARB( "glActiveTexture" );
    app->gl.glBindTexture = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glBindTexture" );
    app->gl.glTexParameteri = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLenum, APP_GLint) ) (uintptr_t) glXGetProcAddressARB( "glTexParameteri" );
    app->gl.glDeleteBuffers = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) glXGetProcAddressARB( "glDeleteBuffers" );
    app->gl.glDeleteTextures = ( void (APP_GLCALLTYPE*) (APP_GLsizei, APP_GLuint const*) ) (uintptr_t) glXGetProcAddressARB( "glDeleteTextures" );
    app->gl.glBufferData = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLsizeiptr, void const *, APP_GLenum) ) (uintptr_t) glXGetProcAddressARB( "glBufferData" );
    app->gl.glUseProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glUseProgram" );
    app->gl.glUniform1i = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint) ) (uintptr_t) glXGetProcAddressARB( "glUniform1i" );
    app->gl.glUniform3f = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) glXGetProcAddressARB( "glUniform3f" );
    app->gl.glGetUniformLocation = ( APP_GLint (APP_GLCALLTYPE*) (APP_GLuint, APP_GLchar const*) ) (uintptr_t) glXGetProcAddressARB( "glGetUniformLocation" );
    app->gl.glTexImage2D = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei, APP_GLint, APP_GLenum, APP_GLenum, void const*) ) (uintptr_t) glXGetProcAddressARB( "glTexImage2D" );
    app->gl.glClearColor = ( void (APP_GLCALLTYPE*) (APP_GLfloat, APP_GLfloat, APP_GLfloat, APP_GLfloat) ) (uintptr_t) glXGetProcAddressARB( "glClearColor" );
    app->gl.glClear = ( void (APP_GLCALLTYPE*) (APP_GLbitfield) ) (uintptr_t) glXGetProcAddressARB( "glClear" );
    app->gl.glDrawArrays = ( void (APP_GLCALLTYPE*) (APP_GLenum, APP_GLint, APP_GLsizei) ) (uintptr_t) glXGetProcAddressARB( "glDrawArrays" );
    app->gl.glViewport = ( void (APP_GLCALLTYPE*) (APP_GLint, APP_GLint, APP_GLsizei, APP_GLsizei) ) (uintptr_t) glXGetProcAddressARB( "glViewport" );
    app->gl.glDeleteShader = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glDeleteShader" );
    app->gl.glDeleteProgram = ( void (APP_GLCALLTYPE*) (APP_GLuint) ) (uintptr_t) glXGetProcAddressARB( "glDeleteProgram" );
#ifdef APP_REPORT_SHADER_ERRORS
    app->gl.glGetShaderInfoLog = ( void (APP_GLCALLTYPE*) (APP_GLuint, APP_GLsizei, APP_GLsizei*, APP_GLchar*) ) (uintptr_t) glXGetProcAddressARB( "glGetShaderInfoLog" );
#endif

    // Platform independent OpenGL initialization
    int width = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_width : app->windowed_w;
    int height = app->screenmode == APP_SCREENMODE_FULLSCREEN ? app->fullscreen_height: app->windowed_h;
    if( !app_internal_opengl_init( app, &app->gl, app->interpolation, width, height ) )
    {
        app_log( app, APP_LOG_LEVEL_ERROR, "Failed to initialize OpenGL" );
        goto init_failed;
    }
    
    app_internal_opengl_resize( &app->gl, width, height );
    app_internal_linux_audio_init(app);
    
    result = app_proc( app, user_data ); 

init_failed:
    if( !app_internal_opengl_term( &app->gl ) ) app_log( app, APP_LOG_LEVEL_WARNING, "Failed to terminate OpenGL" );
    app_internal_linux_audio_shutdown(app);

    t = time( NULL );
    struct tm* end = localtime( &t );
    sprintf( msg, "Application terminated %02d:%02d:%02d %04d-%02d-%02d.",
            end->tm_hour, end->tm_min, end->tm_sec, end->tm_year + 1900, end->tm_mon + 1, end->tm_mday );
    app_log( app, APP_LOG_LEVEL_INFO, msg );
    
    APP_FREE( memctx, app );
    return result;
}

app_state_t app_yield( app_t* app ) 
{
    if( !app->initialized )
    {
        if( app->screenmode == APP_SCREENMODE_WINDOW )
        {
            app->screenmode = APP_SCREENMODE_FULLSCREEN;
            app_screenmode( app, APP_SCREENMODE_WINDOW );
        }
        else
        {
            app->screenmode = APP_SCREENMODE_WINDOW;
            app_screenmode( app, APP_SCREENMODE_FULLSCREEN );
        }

        XMapWindow( app->display, app->window );

        app->initialized = true;
    }
    
    app_internal_x11_handle_events(app);
    
    return app->closed ? APP_STATE_EXIT_REQUESTED : APP_STATE_NORMAL;
}

void app_cancel_exit( app_t* app ) 
{
    app->closed = false;
}

void app_title( app_t* app, char const* title ) 
{
    XStoreName( app->display, app->window, title );
}

char const* app_cmdline( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_cmdline not implemented for linux yet\n");
    return 0;
}

char const* app_filename( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_filename not implemented for linux yet\n");
    return 0;
}

char const* app_userdata( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_userdata not implemented for linux yet\n");
    return 0;
}

char const* app_appdata( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_appdata not implemented for linux yet\n");
    return 0;
}

APP_U64 app_time_count( app_t* app )
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000000 + ts.tv_nsec;
}

APP_U64 app_time_freq( app_t* app ) 
{ 
    // time count is in nanoseconds.
    return 1000000000;
}

void app_log( app_t* app, app_log_level_t level, char const* message )
{
    APP_LOG( app->logctx, level, message );
}

void app_fatal_error( app_t* app, char const* message )
{
    APP_FATAL_ERROR( app->fatalctx, message );
}

void app_pointer( app_t* app, int width, int height, APP_U32* pixels_abgr, int hotspot_x, int hotspot_y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer not implemented for linux yet\n");
}

void app_pointer_default( app_t* app, int* width, int* height, APP_U32* pixels_abgr, int* hotspot_x, int* hotspot_y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_default not implemented for linux yet\n");
}

void app_pointer_pos( app_t* app, int x, int y )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_pos not implemented for linux yet\n");
}

void app_pointer_limit( app_t* app, int x, int y, int width, int height )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_limit not implemented for linux yet\n");
}

void app_pointer_limit_off( app_t* app )
{
    APP_LOG(app, APP_LOG_LEVEL_INFO, "app_pointer_limit_off not implemented for linux yet\n");
}

void app_interpolation( app_t* app, app_interpolation_t interpolation )
{
    if( interpolation == app->interpolation ) return;
    app->interpolation = interpolation;
    
/*    POINT p;
    GetCursorPos( &p );
    ScreenToClient( app->hwnd, &p );
    int mouse_x = p.x;
    int mouse_y = p.y;
    
    app_input_event_t input_event;
    input_event.type = APP_INPUT_MOUSE_MOVE;
    input_event.data.mouse_pos.x = mouse_x;
    input_event.data.mouse_pos.y = mouse_y;
    app_internal_add_input_event( app, &input_event );
 */
    
    app_internal_opengl_interpolation( &app->gl, interpolation );
}

void app_internal_x11_set_fullscreen(app_t* app, bool fullscreen)
{
    XEvent event = (XEvent) {0};
    event.type = ClientMessage;
    event.xclient.window = app->window;
    event.xclient.format = 32; // Data is 32-bit longs
    event.xclient.message_type = XInternAtom(app->display, "_NET_WM_STATE", False);
    event.xclient.data.l[0] = fullscreen ? 1 : 0;
    event.xclient.data.l[1] = XInternAtom(app->display, "_NET_WM_STATE_FULLSCREEN", False);
    event.xclient.data.l[2] = 0; // No secondary property
    event.xclient.data.l[3] = 1; // Sender is a normal application

    XSendEvent(app->display,
               XDefaultRootWindow(app->display),
               False,
               SubstructureNotifyMask | SubstructureRedirectMask,
               &event);
}

void app_screenmode( app_t* app, app_screenmode_t screenmode )
{
    if(app->screenmode == screenmode)
        return;

    app->screenmode = screenmode;
    if(screenmode == APP_SCREENMODE_WINDOW)
    {
        app_internal_x11_set_fullscreen(app, false);
        XResizeWindow(app->display, app->window, app->windowed_w, app->windowed_h);
        app_internal_opengl_resize( &app->gl, app->windowed_w, app->windowed_h );
    }
    else if(screenmode == APP_SCREENMODE_FULLSCREEN)
    {
        app_internal_x11_set_fullscreen(app, true);
        app_internal_opengl_resize( &app->gl, app->fullscreen_width, app->fullscreen_height );
    }
}

void app_window_size( app_t* app, int width, int height )
{
    app->windowed_w = width;
    app->windowed_h = height;
    if(app->screenmode == APP_SCREENMODE_WINDOW)
    {
        XResizeWindow(app->display, app->window, width, height);
        app_internal_opengl_resize( &app->gl, width, height );
    }
}

int app_window_width( app_t* app )
{
    return app->windowed_w;
}

int app_window_height( app_t* app )
{
    return app->windowed_h;
}

void app_window_pos( app_t* app, int x, int y )
{
    app->windowed_x = x;
    app->windowed_y = y;
    XMoveWindow(app->display, app->window, x,y);
}

int app_window_x( app_t* app )
{
    return app->windowed_x;
}

int app_window_y( app_t* app )
{
    return app->windowed_y;
}

app_displays_t app_displays( app_t* app )
{
    app_displays_t displays;
    displays.count = app->display_count;
    displays.displays = app->displays;
    return displays;
}

void app_present( app_t* app, APP_U32 const* pixels_xbgr, int width, int height, APP_U32 mod_xbgr, APP_U32 border_xbgr ) 
{ 
    if( pixels_xbgr != NULL ) 
        app_internal_opengl_present( &app->gl, pixels_xbgr, width, height, mod_xbgr, border_xbgr );
    glXSwapBuffers ( app->display, app->window );
}

void app_sound_buffer_size( app_t* app, int sample_pairs_count ) 
{
    if(app->audio_buffer != NULL)
    {
        APP_FREE(app->memctx, app->audio_buffer);
    }

    if(sample_pairs_count > 0)
    {
        app->audio_buffer_size = sample_pairs_count;
        app->audio_buffer_position = 0;
        app->audio_buffer = APP_MALLOC(app->memctx, sample_pairs_count * 2 * sizeof(short));
        memset(app->audio_buffer, 0x00, sample_pairs_count * 2 * sizeof(short));
        
        snd_pcm_prepare (app->alsa_handle);
        
        unsigned int avail = snd_pcm_avail_update(app->alsa_handle);
        if(avail > sample_pairs_count)
            avail = sample_pairs_count;
        snd_pcm_writei(app->alsa_handle, app->audio_buffer, avail);
    }
    else
    {
        snd_pcm_drop(app->alsa_handle);
        app->audio_buffer_size = 0;
        app->audio_buffer = NULL;
    }
}

int app_sound_position( app_t* app ) 
{
    return app->audio_buffer_position;
}

void app_sound_write( app_t* app, int sample_pairs_offset, int sample_pairs_count, APP_S16 const* sample_pairs ) 
{
    if(app->audio_buffer == NULL)
        return;
    
    snd_pcm_state_t alsa_state = snd_pcm_state(app->alsa_handle);
    if(alsa_state != SND_PCM_STATE_PREPARED && alsa_state != SND_PCM_STATE_RUNNING)
        snd_pcm_prepare (app->alsa_handle);

    APP_S16* buffer = &app->audio_buffer[sample_pairs_offset * 2];
    for(int i=0; i<sample_pairs_count * 2; ++i)
    {
        buffer[i] = sample_pairs[i];
    }
}

void app_sound_volume( app_t* app, float volume ) 
{
    if(volume > 1.0f) volume = 1.0f;
    if(volume < 0.0f) volume = 0.0f;
    app->sound_vol = volume;
}

app_input_t app_input( app_t* app )
{
    app_input_t input;
    input.events = app->input_events;
    input.count = app->input_count;
    app->input_count = 0;
    return input;
}

void app_coordinates_window_to_bitmap( app_t* app, int width, int height, int* x, int* y )
{
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : app->windowed_w;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : app->windowed_h;

    if( app->interpolation == APP_INTERPOLATION_LINEAR )
    {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
        {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x -= (int)( hborder );
            *y -= (int)( vborder );
            *x = (int)( *x / pixel_scale );
            *y = (int)( *y / pixel_scale );
        }
        else
        {
            *x = 0;
            *y = 0;
        }
    }
    else
    {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x -= (int)( hborder );
        *y -= (int)( vborder );
        *x = (int)( *x / pixel_scale );
        *y = (int)( *y / pixel_scale );
    }
}


void app_coordinates_bitmap_to_window( app_t* app, int width, int height, int* x, int* y )
{
    int window_width = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_width : app->windowed_w;
    int window_height = ( app->screenmode == APP_SCREENMODE_FULLSCREEN ) ? app->fullscreen_height : app->windowed_h;

    if( app->interpolation == APP_INTERPOLATION_LINEAR )
    {
        float hscale = window_width / (float) width;
        float vscale = window_height / (float) height;
        float pixel_scale = hscale < vscale ? hscale : vscale;
        if( pixel_scale > 0.0f )
        {
            float hborder = ( window_width - pixel_scale * width ) / 2.0f;
            float vborder = ( window_height - pixel_scale * height ) / 2.0f;
            *x = (int)( *x * pixel_scale );
            *y = (int)( *y * pixel_scale );
            *x += (int)( hborder );
            *y += (int)( vborder );
        }
        else
        {
            *x = 0;
            *y = 0;
        }
    }
    else
    {
        int hscale = window_width / width;
        int vscale = window_height / height;
        int pixel_scale = pixel_scale = hscale < vscale ? hscale : vscale;
        pixel_scale = pixel_scale < 1 ? 1 : pixel_scale;
        int hborder = ( window_width - pixel_scale * width ) / 2;
        int vborder = ( window_height - pixel_scale * height ) / 2;
        *x = (int)( *x * pixel_scale );
        *y = (int)( *y * pixel_scale );
        *x += (int)( hborder );
        *y += (int)( vborder );
    }
}

#else
#error Undefined platform. Define APP_WINDOWS, APP_MACOS, APP_LINUX_X11 or APP_NULL.
#endif


#endif /* APP_IMPLEMENTATION */

/*
 revision history:
    0.4     pointer x/y, callback for sound, modifier keys fix, gl binding fix, cursor fix
    0.3        added API documentation
    0.2        first publicly released version
 */

/*
 ------------------------------------------------------------------------------
 
 This software is available under 2 licenses - you may choose the one you like.
 
 ------------------------------------------------------------------------------
 
 ALTERNATIVE A - MIT License
 
 Copyright (c) 2016 Mattias Gustavsson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 ------------------------------------------------------------------------------
 
 ALTERNATIVE B - Public Domain (www.unlicense.org)
 
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
 software, either in source code form or as a compiled binary, for any purpose,
 commercial or non-commercial, and by any means.
 
 In jurisdictions that recognize copyright laws, the author or authors of this
 software dedicate any and all copyright interest in the software to the public
 domain. We make this dedication for the benefit of the public at large and to
 the detriment of our heirs and successors. We intend this dedication to be an
 overt act of relinquishment in perpetuity of all present and future rights to
 this software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 ------------------------------------------------------------------------------
 */

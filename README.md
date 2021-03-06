RefreshRateMultitool
====================

RefreshRateMultitool displays a sequence of easily distinguishable images at the rate of your monitor's refresh rate.

This is a forked version of the original project found [here](https://github.com/shurcooL/RefreshRateMultitool). Main differences are:

- Add ability to toggle between Windowed and Full Screen modes.
- Ported to GLFW v3; reorganized code.
- Add ".pro" Project File in order to compile with Qt's QMake tool.
- Add Linux binary (Ubuntu Precise 12.04).

![RefreshRateMultitool in action, except the real thing runs much faster](https://dl.dropbox.com/u/8554242/dmitri/projects/RefreshRateMultitool/images/RefreshRateMultitool.gif)

    Usage:
        RefreshRateMultitool [<columns> <rows> <refresh rate>]
        <columns> - [optional] sets the number of columns. Default: 6
        <rows>    - [optional] sets the number of rows. Default: 1
        <refresh rate> - [optional] specify the screen refresh rate. Default: 60

This can be useful for a number of things:

- Finding out the input lag of a monitor more precisely
- Finding out if your monitor is actually dropping some of the input frames (e.g. monitor running in a 85 hz mode, but only displaying 60 frames/second, while dropping the other 25 every second)
- Finding out the black-to-white and white-to-black pixel response times

See more advanced use cases and discussion of the tool [here](http://hardforum.com/showthread.php?t=1423433).

****** WARNING ******
=====================

This application will produce FLASHING IMAGES to test your screen(s)!
If getting a seizure is a risk for you, please don't use it.

Also, according to PixPerAn,
"Some TFT-Displays tend to show "ghost pictures" after
displaying flickering contents for a long time.
RefreshRateMultitool contains such flickering contents. (In the
main menu as well as in the flicker-fullscreen)
We advise not run these program parts for long periods.
(Though, usually those "ghost pictures" will disappear after
some time. It seems to be very likely that this will happen with
most TFT's. But of course we cannot guarantee this!)"

RefreshRateMultitool comes with ABSOLUTELY NO WARRANTY.
You may use RefreshRateMultitool solely AT YOUR OWN RISK.

---

You should follow me on Twitter: [@shurcooL](http://twitter.com/shurcooL)

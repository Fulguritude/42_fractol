# 42_fractol
Keeping files on multiple machines for fractol

# Usage
First argument is the dwell type, if another argument is given, it should lead
to a file with one single line of floats, which will be interpreted as a complex
polynomial. The leftmost two floats correspond to the coef of degree zero.

# Dwell types
Four are available: julia, mandelbrot, newton (not exactly the newton fractal,
a simpler version that took some inspiration from the standard newton 'root'
method of generating an escape-time fractal), and burningship. Each dwell type
can work with every polynomial you could come up with, up to degree 255 (not
necessarily fast though, especially if the display is dynamic). Not all
polynomials give interesting results though.

# Settings inside software
Escape closes the software.

LCtrl toggles debug.
RCtrl toggles render mode (mariani-silver by default, or pixel-by-pixel, or
'none' which allows you to edit the value of your polynomial without the lag of
the real time render).
Space toggles staticity of display (when dynamic, mouse hover updates a
parameter of the fractal and calls the render function).
NumpadHome offers a slower, step-by-step rendering of Mariani-Silver (this gives
an idea of the algorithm's process and is useful for debugging).

Left-click recenters the fractol's anchor on the click's position.
Arrows recenter the anchor in an inversed fashion.

PageDown zooms in.
PageUp zooms out.
Scroll-up zooms in.
Scroll-down zooms out.

Numpad 0 to 9 correspond to 10 default palettes chosen, the default being
Numpad_8.

Numpad_+ and Numpad_- change the monomial the coefficient of which is being
updated by mouse_hover. Numpad_Enter sets the degree of the polynomial so that
the current monomial being edited becomes the term of highest degree.

# Saving
NumpadEnd prints the current polynomial to terminal: first line is human-
readable format, second line is machine readable format (you can copy that line
in a file and save a polynomial you liked in 'cpolys' for later use).

# Code macros
MAX_DWELL and WIN_H and WIN_W are macros if you want to edit them. MAX_DWELL
should be a power of 2 and COLOR_OFFSETs should be changed accordingly for the
palettes to keep working.
You can edit the definition of t_float in libft_shorthands.h for a speedup.

# Other comments
I tried to make the call to render dependent on the speed of mouse movement and
got pretty good results. The same cannot be really said for the scrolling: it's
more comfortable to use PageUp and PageDown.

# CSci-4611 Assignment 3:  Earthquake

Earthquake size : based on magnitude within range of magnitudes. A higher magnitude is a larger sphere.

Earthquake color : Range from red to yellow. The more orange/yellow a quake sphere is, the lower the magnitude. The most red quakes are the highest in magnitude.

When switching to a sphere, globe starts rotating. Doesn't begin rotating until transformation is complete,
    and stops rotating when transforming back to a flat view.

There are two values set up in the init of quake_app.cc, size_intensity_ and rotation_speed_.
    size_intensity_ changes the base size of the smallest earthquake (and the scale changes appropriately.)
    rotation_speed_ changes the speed that the globe rotates when in spherical form.

Special key interactions:

ESC - acts as a quick exit to the simulation.

SPACE - copies the Globe button.

ENTER - copies the debug button.

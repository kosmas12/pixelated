# Pixelated

Pixelated is an image viewer written in C. It aims
to be compatible with Linux, Windows, Mac and 
the original Xbox (using
[nxdk](https://github.com/XboxDev/nxdk)),
and aims to support as many formats as possible while 
also being as snappy and lightweight as possible.

Currently this program uses the SDL2 libraries
(SDL2, SDL2_ttf and SDL2_image).

# Notes

If your aim is to use Pixelated on Xbox, you need
to use a branch that isn't in the upstream nxdk
(which is what is linked above). This branch can be 
found [here](https://github.com/fgsfdsfgs/nxdk/tree/dev)
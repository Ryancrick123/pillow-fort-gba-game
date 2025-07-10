# An untitled album tie-in GBA game

A rhythm game exclusively for Game Boy Advance, developed in C++ using the Butano engine, with additional tools written in Python.

## Building

### Prerequisites

- Python 3.10+ (For chart generation)
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) - instructions specifically for Butano are [here](https://gvaliente.github.io/butano/getting_started.html)

### Steps

1. Ensure all requirements are installed and working correctly.
2. Clone this repo.
3. Run <code>make -jx</code> in the repo, where <code>x</code> is the number of cores your CPU has.
4. The ROM will be generated in the repo as <code>pf_lp.gba</code>.

## Adding custom songs

Custom songs can be added and a chart generated when building. The steps are as below:
1. Create a song using tracker. Use instrument 1 to dictate the notes intended to be added to a chart (any effects are ignored, only the notes and times are used). Instrument 1 can be silent if it doesn't match the music exactly (I did this for most songs), or it can have sound (I did this for Joan).
    - I used MilkyTracker, but I'm sure alternatives would be fine.
2. Export as a .xm file.
3. Add the .xm file to this_repo/audio.
4. Build the ROM.
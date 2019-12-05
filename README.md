Noisemaker is a digital audio synthesizer library. Using this library, the user can design a sound and that sound can be written to a wav file.

# Installation

**Disclaimer**: Installation instructions are given for Windows and MacOS but serious bugs exist on the Windows build and the Mac build is untested.

For starters, you'll need a C++ compiler and the C++ standard library.
Instructions for installing a compiler can be found [here](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler)
The project must be compiled with C++11 or higher.

**For Windows Users:** Note that if you use MinGW (as is recommended) on Windows, you'll have to make sure you install the `mingw32-gcc-g++-bin` and `mingw32-make-bin` packages and add them to your path. Otherwise you'll have to use a different generator for CMake and you're on your own.

## Other requisite software

You need to install `cmake`.

On Linux, you can simply run

```
apt install cmake
```
Or on MacOS, run
```
brew install cmake
```
For Windows systems, you can find the latest version of CMake [here](https://cmake.org/download/). Make sure you add cmake to your path.


## Libraries required for building the documentation 

You need to have [Python 3](https://www.python.org/downloads/) installed no matter what operating system you're using. On Windows, make sure that you add python and pip3 to your path.

Linux:
```
apt install doxygen
pip3 install sphinx sphinx_rtd_theme breathe
```
MacOS:
```
brew install doxygen
pip3 install sphinx sphinx_rtd_theme breathe
```
Windows:

Doxygen can be downloaded [here](http://www.doxygen.nl/download.html).
Then you can run:
```
pip3 install sphinx sphinx_rtd_theme breathe
```

## Install instructions

To start, make a build directory in the project:

```
mkdir build
cd build
```
Then run, on MacOS or Linux, run
```
cmake ..
```
Or, to build the documentation too, run

```
cmake -DBUILD_DOCS=ON ..
```
On Windows, you should run
```
cmake .. -G "MinGW Makefiles"
```
Again, to build the documentation, you'll need to run

```
cmake -DBUILD_DOCS=ON -G "MinGW Makefiles" ..
```

If it works, it should look something like this:

```
jack@the-machine:/mnt/c/Users/99jac/Documents/noisemaker/build$ cmake ..
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/c/Users/99jac/Documents/noisemaker/build
```

The next step is to do:

```
cmake --build .
```

Now you can do several things:

* *Read the docs* : If you build the documentation and all goes as planned, among other things you 
  should now find a file called `build/docs/sphinx/index.html` and if you point a browser
  at it, you can read the documentation.
* Run one of the already written main programs that makes some sound.
  ```
  cd tests
  ./NoisemakerTests
  ```

  That creates an output file called `test.wav` which you can play
  in Audacity, or your favorite media player.

  The the other one is:

  ```
  ./Megalovania
  ```

  The source for each of these is in: $ROOT/tests/*.cpp
  
# Building on Linux without sudo privilages

To build this on Linux without sudo privilages, you will need to do:

```
pip3 install --user sphinx
export PATH=${HOME}/.local/bin:${PATH}
mkdir build
cd build
cmake ..
cmake --build .
```


# Usage

The basic workflow in Noisemaker is as follows:
1. Create a custom instrument using Noisemaker classes
2. Read the samples of that instrument into an array
3. Write those samples into a wav file

Below is an exaple of how to create a 440hz sine wave:

    #include "noisemaker.h"
    #include "oscillator.h"
    #include "premadeSignals.h"
    #include "filefuncs.h"
    
    writableSample samples[100000];
    Oscillator o = formSineWave(440);
    
    for (int i = 0; i < numSamples; i++) {
     samples[i] = (writableSample) o.step();
    }
    
    writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

`writableSample` is the type that noisemaker uses to store samples. Right now it should be `int_16_t`.

`Oscillator` is a subclass of the `Signal` class. All `Signal`s have a `step()` function that returns the next sample that the 
`Signal` has generated. Here we use the premade `Oscillator` returned by the `sineWave` function.
It returns samples that make a sine wave at the specified frequency.

In the following `for` loop, we write `Oscillator`'s `step()` values to an array. We cast them from `sample` to `writableSample`, because that is the data type that writeWavFile expects.

Finally we pass that array to the `writeWavFile` function. Its parameters are self-explanatory.

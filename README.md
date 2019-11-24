Noisemaker is a digital audio synthesizer library. Right now, the user designs a sound and that sound can be written to a wav file.

# Installation

The only software required for this library is a C++ compiler and the C++ standard library.
Instructions for installing a compiler can be found [here](https://www.cs.odu.edu/~zeil/cs250PreTest/latest/Public/installingACompiler)
The project must be compiled with c++11 or higher.

## Mac OS preliminaries

You need to install `cmake`.  Instructions are [here](http://macappstore.org/cmake/)

If you already have `brew` installed, you should be able to do:

```
brew install cmake
```

You also need these to install the documentation.   The cmake may error out if you don't have these installed:

```
brew install sphinx doxygen 
```

Finally, you need something called `breathe` which is Python software installed
with `pip` (or `pip3`, depending on your Python install) If you don't already have `pip` installed, that's another rabbit hole (left as an exercise
to the reader.)




## Install instructions

To start, make a build directory:

```
mkdir build
cd build
cmake ..
```

If it works, it should look something like this:

```
169-231-158-36:build pconrad$ cmake ..
-- The C compiler identification is AppleClang 10.0.0.10001145
-- The CXX compiler identification is AppleClang 10.0.0.10001145
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Doxygen: /usr/local/bin/doxygen (found version "1.8.16") found components:  doxygen missing components:  dot
-- Found Sphinx: /Library/Frameworks/Python.framework/Versions/3.6/bin/sphinx-build  
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/pconrad/github/ccs-1l-f19/noisemaker/build
169-231-158-36:build pconrad$ 
```

The next step is to do:

```
cmake --build .
```

Now you can do several things:

* *Read the docs* : If all goes as planned, among other things you 
  should now find
  a file called `build/docs/sphinx/index.html` and if you point a browser
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

The basic workflow in noisemaker is as follows:
1. Create a custom instrument using Noisemaker classes
2. Read the samples of that instrument into an array
3. Write those samples into a wav file

Below is an exaple of how to create a 440hz sine wave:

    sample samples[100000];
    Constant c(noisemaker::maxSample*.5);
    Oscillator o = Oscillator::sineWave(440);
    
    for (int i = 0; i < numSamples; i++) {
     samples[i] = o.step();
    }
    writeWavFile(fopen("test.wav", "w"), samples, numSamples, noisemaker::sampleRate);

`sample` is the type that noisemaker uses to store samples. Right now it should be int16_t.

`Constant` is a subclass of the `Signal` class. All `Signal`s have a `step()` function that returns the next sample that the 
`Signal` has generated. For some `Signal`s this will vary from call to call, but for a `Constant`, `step()`'s return value
is unsurprisingly constant.

`Oscillator` is another `Signal`. Here we use the premade `Oscillator` returned by the `sineWave` function.
It returns samples that make a sine wave at the specified frequency.

In the following `for` loop, we write `Oscillator`'s `step()` values to an array

Finally we pass that array to the `writeWavFile` function. Its parameters are self-explanatory.

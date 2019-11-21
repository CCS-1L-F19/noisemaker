add_library (Noisemaker "noisemaker.cpp" "signal.cpp" "constant.cpp" "oscillator.cpp" "adder.cpp" "multiplier.cpp" "premadeSignals.cpp" "fileFuncs.cpp")

target_include_directories(Noisemaker PUBLIC .)

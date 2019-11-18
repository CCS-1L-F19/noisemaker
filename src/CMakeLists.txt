add_library (Noisemaker "noisemaker.cpp" "constant.cpp" "oscillator.cpp" "adder.cpp" "multiplier.cpp" "premadeSignals.cpp")

target_include_directories(Noisemaker PUBLIC .)

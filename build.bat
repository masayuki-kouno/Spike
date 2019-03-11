mkdir build
cd build
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\WDExpress\VC\Auxiliary\Build\vcvarsall.bat" x86_x64
cmake -G "NMake Makefiles" ..
nmake
cd src
sml_spike_test --gtest_output=xml:test_result.xml

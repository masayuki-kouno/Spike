mkdir build
cd build
cmake ..
make -j4
cd src
./sml_spike_test --gtest_output=xml:test_result.xml

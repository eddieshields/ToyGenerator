echo -en 'travis_fold:start:script.build\\r'
echo "Building..."
echo "Building under OS: $TRAVIS_OS_NAME"

mkdir -p build
cd build
echo "CMake-ing, CXX = $CXX"
cmake .. -DCMAKE_CXX_COMPILER=clang
echo "Building ..."
cmake --build . -- -j2 
cd ..
echo "Running test job ..."
./build/ToyGenerator
# cscshell
## Build instructions
Building requires cmake. To install cmake:
```
sudo apt-install cmake
```
Google test is required to compile tests. To install GTest:
```
sudo apt-get install libgtest-dev
```
The following commands will build and run cscshell
```
mkdir build
cd build
cmake ..
make
./cscsshell
```
## Commands to try in cscshell
```
help
url
text
history
set prompt <%h>
set histlen 50
quit
```

## To Run Tests
Once you have compiled the source code, you can execute the unit tests
```
make test
```
To see the results of each test indivudually
```
./runUnitTests
```

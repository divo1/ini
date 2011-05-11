rm -r *.o *.a *.exe
g++ -pipe -c CIni.cpp
ar rcs libCIni.a CIni.o
g++ -pipe main.cpp -L. -lCIni -o CIniTest
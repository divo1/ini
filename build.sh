echo Remove...
rm -r *.o *.a *.exe
echo Build...
echo -----------------
g++ -pipe -c CIni.cpp
ar rcs libCIni.a CIni.o
g++ -pipe main.cpp -L. -lCIni -o CIniTest
echo -----------------
echo End...
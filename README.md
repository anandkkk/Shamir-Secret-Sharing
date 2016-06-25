Steps/Commands for running JNI in scapi:-

1. Copy .java file in /home/../scapi/src/java/edu/biu/scapi/primitives/dlog
2. Compile .java file 
Ex. javac Polynomial.java CryptoPpDlogGF.java 
3. Generate header file 
javah edu.biu.scapi.primitives.dlog.class_name
4. Copy header file and .cpp file to /home/../scapi/src/jni/CryptoPPJavaInterface
5. Do changes in MAKEFILE
Go to  /home/../scapi/src/jni/CryptoPPJavaInterface/makefile
in SOURCES= (here add the cpp file name)
---If changes in Scapi Java files are present---
6. sudo make clean-scapi
7. sudo make compile-scapi
8. Copy Scapi-2.4.jar from /home/../scapi/build/scapi to /usr/lib/scapi

//If changes in JNI files are present
9. sudo make clean-jni-cryptopp
10. sudo make prefix=/usr
11. sudo make install prefix=/usr
12. Copy libCryptoPPJavaInterface.so from /home/../scapi/src/jni/CryptoPPJavaInterface
to /usr/lib/scapi

13. Run Test files with scapic and scapi commands

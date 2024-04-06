all : clean gen32 gen64 dieharder_test32 dieharder_test64
.PHONY : all

.PHONY: clean    
clean: 
	-rm gen32;
	-rm gen64

gen32 : gen32.cpp ../out/libdiceforge.a ../include/diceforge.h
	g++ gen32.cpp -o gen32 -L../out/ -ldiceforge
	
gen64 : gen64.cpp ../out/libdiceforge.a ../include/diceforge.h
	g++ gen64.cpp -o gen64 -L../out/ -ldiceforge

dieharder_test32 : dieharder_test32.cpp 
	g++ dieharder_test32.cpp -o dieharder_test32
	
dieharder_test64 : dieharder_test64.cpp 
	g++ dieharder_test64.cpp -o dieharder_test64

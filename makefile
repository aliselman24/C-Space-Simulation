all: compile run

compile:
	@if not exist lib mkdir lib
	@if not exist bin mkdir bin
	gcc -I ./include/ -o ./lib/Arac.o -c ./src/Arac.c
	gcc -I ./include/ -o ./lib/DosyaOkuyucu.o -c ./src/DosyaOkuyucu.c
	gcc -I ./include/ -o ./lib/Gezegen.o -c ./src/Gezegen.c
	gcc -I ./include/ -o ./lib/KayacGezegen.o -c ./src/KayacGezegen.c
	gcc -I ./include/ -o ./lib/GazDeviGezegen.o -c ./src/GazDeviGezegen.c
	gcc -I ./include/ -o ./lib/BuzDeviGezegen.o -c ./src/BuzDeviGezegen.c
	gcc -I ./include/ -o ./lib/CuceGezegen.o -c ./src/CuceGezegen.c
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c
	gcc -I ./include/ -o ./lib/ZamanHesaplayici.o -c ./src/ZamanHesaplayici.c
	gcc -I ./include/ -o ./lib/uzay_simulasyonu.o -c ./src/uzay_simulasyonu.c
	gcc -I ./include/ -o ./bin/simülasyon ./lib/*.o

run:
	./bin/simülasyon

clean:
	rm -rf lib/*.o bin/simülasyon
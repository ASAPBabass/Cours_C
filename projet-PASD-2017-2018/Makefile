## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb
# Règle de compilation

kruskal : union_find.o kruskal.o test_kruskal.o
	$(CC) $(CFLAGS) -o $@ $^

segmentation : pgm_img.o union_find.o segmentation.o test_segmentation.o
	$(CC) $(CFLAGS) -o $@ $^

coloration : union_find.o liste_simplement_chainee.o coloration.o test_coloration.o
	$(CC) $(CFLAGS) -o $@ $^

test_kruskal : kruskal
	./kruskal; diff -s arbres/output/A_10_SOMMETS arbres/A_10_SOMMETS
	./kruskal; diff -s arbres/output/A_200_SOMMETS arbres/A_200_SOMMETS
	./kruskal; diff -s arbres/output/A_1000_SOMMETS arbres/A_1000_SOMMETS
	./kruskal; diff -s arbres/output/A_2500_SOMMETS arbres/A_2500_SOMMETS

memoire_kruskal : kruskal	
	valgrind --leak-check=full ./kruskal

memoire_segmentation : segmentation
	valgrind --leak-check=full ./segmentation

memoire_coloration : coloration
	valgrind --leak-check=full ./coloration

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm *.o

doc:
	doxygen Doxyfile

TGZ_FILES :=  *.c *.h Makefile cr.pdf
TP_DIR := projet-PASD-2017-2018

rendu :
	[ -e cr.pdf ] || echo > cr.pdf
	cd .. ; tar czf $(TP_DIR)/rendu.tgz $(TGZ_FILES:%=$(TP_DIR)/%)


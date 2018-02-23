## Compilation automatique de source C
# Compilteur
CC := gcc
#options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb
# Règle de compilation

kruskal : union_find.o liste_simplement_chainee.o kruskal.o test_kruskal.o
	$(CC) $(CFLAGS) -o $@ $^

segmentation : pgm_img.o union_find.o liste_simplement_chainee.o kruskal.o segmentation.o test_segmentation.o
	$(CC) $(CFLAGS) -o $@ $^

coloration : union_find.o liste_simplement_chainee.o kruskal.o coloration.o test_coloration.o
	$(CC) $(CFLAGS) -o $@ $^

test_kruskal : kruskal
	./kruskal arbres/A_10_SOMMETS graphes/G_10_SOMMETS; diff -s arbres/output/A_10_SOMMETS arbres/A_10_SOMMETS
	./kruskal arbres/A_200_SOMMETS graphes/G_200_SOMMETS; diff -s arbres/output/A_200_SOMMETS arbres/A_200_SOMMETS
	./kruskal arbres/A_1000_SOMMETS graphes/G_1000_SOMMETS; diff -s arbres/output/A_1000_SOMMETS arbres/A_1000_SOMMETS
	./kruskal arbres/A_2500_SOMMETS graphes/G_2500_SOMMETS; diff -s arbres/output/A_2500_SOMMETS arbres/A_2500_SOMMETS

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


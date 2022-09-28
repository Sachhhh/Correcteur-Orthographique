all:
	cd arbre_prefix1 && make 
	cd arbre_prefix2 && make 
	cd hashtable && make 
	cd arbre_radix && make 

clean:
	cd arbre_prefix1 && make clean
	cd arbre_prefix2 && make clean
	cd hashtable && make clean
	cd arbre_radix && make clean



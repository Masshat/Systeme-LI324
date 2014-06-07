LI324 TME 10-11
===============

Participants : 1
----------------

> Bielle Benjamin 2900825     

Fichiers inclus
---------------

> include/fat.h    
> Definitions des variables globales, structures de donnees et des fonctions    
			
> src/func_FS_FAT.c    
> Implementation des fonctions    
						
> src/test_append2_file.c    
> Implementation du test de append2 file    

> src/test_append_file.c    
> Implementation du test de append file    

> src/test_cat.c    
> Implementation du test de cat    
			
> src/test_create_file.c    
> Implementation du test de create file    
		
> src/test_del_file.c    
> Implementation du test de del file    
		
> src/test_dir.c    
> Implementation du test de dir    
			
> src/test_list_FAT.c    
> Implementation du test de list FAT    
		
> src/test_mv_file.c    
> Implementation du test de mv file    
		
> src/test_read_dir.c    
> Implementation du test de read dir    
		
Directives de 'Makefile'
------------------------

> all    
> Compil tous les fichiers     

> proper     
> Suppression de tous les fichiers temporaires    
  
> clean     
> Suppression de tous les binaires, de tous les fichiers objet    
  
> cleanall     
> Suppression des repertoires bin et obj    

> zero     
> Remise a zéro de l'état de la mémoire        

> complet     
> Benchmark complet du programme        

Etat d'avancement
-----------------

> include/fat.h            - OK    
> src/func_FS_FAT.c        - OK    
> src/test_append2_file.c  - OK    
> src/test_append_file.c   - OK    
> src/test_cat.c           - OK    
> src/test_create_file.c   - OK    
> src/test_del_file.c      - OK     
> src/test_dir.c           - OK    
> src/test_list_FAT.c      - OK    
> src/test_mv_file.c       - OK    
> src/test_read_dir.c      - OK    

TEST
----

> Pour tester le programme, executer simplement le script bench.sh     

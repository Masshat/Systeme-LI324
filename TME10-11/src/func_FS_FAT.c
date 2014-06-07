#include "fat.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define dbg printf("%s : %d\n",__FILE__,__LINE__)


int file_found (char * file ) 
{
  int i;
  struct ent_dir * pt = pt_DIR;
  
  for (i=0; i< NB_DIR; i++) 
    {
      if ((pt->del_flag) && (!strcmp (pt->name, file))) 
	return 0;
      pt++;
    }
  
  /* fichier n'existe pas */
  return 1;
}


void list_fat () 
{
  int i;
  short *pt = pt_FAT;
  for (i=0; i < NB_ENT_FAT; i++) 
    {
      if (*pt)
	printf ("%d ",i);
      pt++;
    }
  printf ("\n");
}


void list_dir () 
{
  /* A COMPLETER */
  struct ent_dir * pt = pt_DIR;
  short * ptf = pt_FAT;
  short tmp;
  int i = 0;
  int nbfile= 0;
  
  while(i!=NB_DIR)
    {
      if(pt->del_flag)
	{
	  printf("nom : %s, taille : %d bloc : ",pt->name,pt->size);
	  printf("%d ",pt->first_bloc);
	  tmp=pt->first_bloc;
	  
	  while(ptf[tmp]!=-1)
	    {
	      printf("%d ",ptf[tmp]);
	      tmp=ptf[tmp];
	    }
	  printf("\n");
	  nbfile++;
	}
      i++;
      pt++;
    }
  printf("nombre de fichiers : %d\n",nbfile);
}

int cat_file (char* file) 
{
  /* A COMPLETER */
  struct ent_dir * pt = pt_DIR;
  short * ptf = pt_FAT;
  short size;
  short tmp;
  int i = 0;
  char * buffer=(char *)malloc(sizeof(char)*128);
  
  if (buffer == NULL)
    {
      perror("cat_file");
      exit (1);
    }
  
  /*
  printf("pt->name : %s\n",pt->name);
  printf("file     : %s\n",file);*/

  while(i!=NB_DIR)
    {
      if ( (pt->del_flag))
	{
	  if (!strcmp(pt->name,file))
	    {
	      size=pt->size;
	      tmp=pt->first_bloc;
	      read_sector(tmp,buffer);
	      size-=128;
	      printf("%s\n",buffer);
	      tmp=ptf[tmp];
	  
	      while((size-128)>0)
		{
		  read_sector(tmp,buffer);
		  size-=128;
		  printf("%s\n",buffer);
		  tmp=ptf[tmp]; 
		}
	      read_sector(tmp,buffer);
	      buffer[size]='\0';
	      printf("%s\n",buffer);
	       
	    }
	}
      i++;
      pt++;
    } 
  return EXIT_SUCCESS;
}

int mv_file (char*file1, char *file2) 
{
  /* A COMPLETER */
  struct ent_dir * pt = pt_DIR;
  int i = 0;
  
  while(i!=NB_DIR)
    {
      if((pt->del_flag) && (!strcmp(pt->name,file1)))
	{
	  if(strlen(file2)<=8)
	    {
	      strcpy(pt->name,file2);
	      write_DIR_FAT_sectors();
	      return 0;
	    }
	}
      i++;
      pt++;
    } 
  return -1;
}

int delete_file (char* file)
{
  /* A COMPLETER */  
  int i;
  struct ent_dir * pt = pt_DIR;
  short * ptf= pt_FAT;
  short tmp;
  short ptmp;
  
  for (i=0; i< NB_DIR; i++) 
    {
      if ((pt->del_flag) && (!strcmp (pt->name, file)))
	{
	  pt->del_flag=0;
	  tmp=pt->first_bloc;
	  
	  while(ptf[tmp]!=-1)
	    {
	      printf("%d\n",tmp);
	      ptmp=ptf[tmp];
	      ptf[tmp]=0;
	      tmp=ptmp;
	      
	    }
	  ptf[tmp]=0;
	  ptf[pt->first_bloc]=0;
	  write_DIR_FAT_sectors();
	  
	  return 0;
	}
      pt++;
    }
  
  return -1;
}

int create_file (char *file) 
{
  /* A COMPLETER */  
  int i=0;
  
  struct ent_dir * pt = pt_DIR;
  
  while(i<NB_DIR)
    {
      if(!(pt->del_flag))
	{
	  strcpy(pt->name,file);
	  pt->size=0;
	  pt->del_flag=1;
	  pt->first_bloc=FIN_FICHIER;
	  pt->last_bloc=FIN_FICHIER;
	  write_DIR_FAT_sectors();
	  
	  return 0;
	}
      i++;
      pt++;
    }
  return -1;
}


short alloc_bloc () 
{ 
  /* A COMPLETER */ 
  int i;
  struct ent_dir *pt = pt_DIR;
  short *ptf = pt_FAT;
  
  for (i=0; i < NB_ENT_FAT; i++) 
    {
      if (*ptf == 0)
	{
	  ptf[pt->first_bloc] = FIN_FICHIER;
	  ptf[pt->last_bloc] = FIN_FICHIER;
	  return i;
	}
      ptf++;
      pt++;
    }
  return -1;
}


short ajoute_bloc (int indice)
{
  short adr=alloc_bloc();
  
  if (adr == -1) return -1;
  
  if (pt_DIR[indice].first_bloc == FIN_FICHIER)
    {
      pt_DIR[indice].first_bloc = adr;
      pt_DIR[indice].last_bloc = adr; 
    }
  else 
    {
      pt_FAT[pt_DIR[indice].last_bloc] = adr;
      pt_DIR[indice].last_bloc = adr;
    }
  
  return adr;
}


/*copie i char de buff1 dans buff2
 */
void buffcpy(char* buff1, char* buff2, int i)
{
  while (i>0)
    {
      *buff2 = *buff1;
      buff1++;
      buff2++;
      i--;
    }
}

int append_file  (char*file, char *buffer, short size) 
{ 
  int indice = file_index(file);
  int offset_bloc;
  int cpt=0;
  int taille_cpy;
  char* sectbuff = (char*)malloc(SIZE_SECTOR * sizeof(char));
  
  if (indice == -1) return -1;

  offset_bloc = pt_DIR[indice].size % SIZE_SECTOR;
  
  /*complétion du dernier bloc utilisé*/
  if (offset_bloc != 0)
    {
      read_sector(pt_DIR[indice].last_bloc, sectbuff);
      
      taille_cpy = ((SIZE_SECTOR - offset_bloc)<size)?(SIZE_SECTOR - offset_bloc):size;
      buffcpy(buffer,sectbuff + offset_bloc, taille_cpy);
      
      write_sector(pt_DIR[indice].last_bloc, sectbuff);
      
      cpt=taille_cpy;
    }
  
  /* à ce point, le dernier bloc est plein et il y a encore quelque chose à copier*/
  while (cpt < size)
    {
      taille_cpy = (SIZE_SECTOR<size-cpt)?SIZE_SECTOR:size-cpt;
      buffcpy(buffer + cpt,sectbuff, taille_cpy);
      
      write_sector(ajoute_bloc(indice), sectbuff);
      
      cpt+=taille_cpy;
    }
  pt_DIR[indice].size+=size;
  write_DIR_FAT_sectors();
  
  return 0;
}


struct ent_dir*  read_dir (struct ent_dir *pt_ent ) 
{
  /* A COMPLETER */  
  
}



int file_index (char * file )
{
  int i;
  struct ent_dir * pt = pt_DIR;
  
  for (i=0; i< NB_DIR; i++) 
    {
      if ((pt->del_flag) && (!strcmp (pt->name, file))) 
	return i;
      pt++;
    }
  
  /* fichier n'existe pas */
  return -1;
}

int free_file_index () 
{
  int i=0;
  struct ent_dir * pt = pt_DIR;
  
  for (i=0; i< NB_DIR; i++) 
    {
      if (pt->del_flag ==0) 
	return i;
      pt++;
    }
  return -1;
}

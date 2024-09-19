#include <assert.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Compile in a linux terminal with
// $ gcc tp1-skeleton.c -o tp1.out
//
// then run the program
// $ ./tp1.out

struct fs_header {
  char identifier[8];
  uint32_t full_size;
  uint32_t checksum;
  char volume_name[];
} __attribute__((packed));

struct file_header {
  // A COMPLETER - Question 7
  uint32_t next_file_hdr;
  uint32_t infos;
  uint32_t checksum;
  char file_name_and_data[];
} __attribute__((packed));

uint32_t read32(unsigned char ptr[4]) {
  // A COMPLETER - Question 4
  // Création des différents octets
  uint8_t byte1 = (uint8_t)ptr[0];  // Most significant byte
  uint8_t byte2 = (uint8_t)ptr[1];
  uint8_t byte3 = (uint8_t)ptr[2];
  uint8_t byte4 = (uint8_t)ptr[3];  // Least significant byte

  // Création de la valeur de retour
  // Opérateur << x : décale la valeur de x bits, ex : 0001 << 2 donne 0100
  // Opérateur Ox1100 | Ox0089 "ajoute" les deux valeurs, cela donne Ox1189
  uint64_t value_read = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
  return value_read;
}

// aligns the address to the next 16-bytes boundary
long ceil_16(long x) {
  // A COMPLETER - Question 5
  if(x%16 == 0){
    return x;
  }
  int number_to_add = 16-x%16;
  return x+number_to_add;
}

// lists the files in a directory on stdout.
void ls(struct fs_header *fs, struct file_header *dir) {
  // A COMPLETER - Question 8
}

// pretty prints a file to stdout (name, type, size, but not content).
void pp_file(struct file_header *file) {
  // A COMPLETER - Question 8
  printf("... \n");
}

// find the first file with the specified name. Does not follow links. Returns
// NULL if no file matches.
struct file_header *find(struct fs_header *fs, struct file_header *root,
                         char *name) {
  // A COMPLETER - Question 9
}

void decode(struct fs_header *fs, size_t size) {
  // check that this file is really a romfs
  // A COMPLETER - Question 3
  if(strncmp(fs->identifier, "-rom1fs-", 8) != 0){  // On compare que les 8 premiers octets car on a pas de 0 en fin de char : il faut donner la taille de l'identifier
    printf("File system is not -rom1fs-\n");
    return;
  }
  printf("File system is -rom1fs-\n");

  // check that the claimed size makes sense.
  // A COMPLETER - Question 4
  unsigned char* full_size_char = (unsigned char*)&fs->full_size;

  if(size < read32(full_size_char)){          // Pas vraiment compris à quoi correspondaient size et full_size
    printf("Claimed size makes no sense\n");
    return;
  }
  printf("Claimed size makes sense\n");

  // Get the root file offset
  // A COMPLETER - Question 6
  // Il faut récupérer la taille du fs_header
  int i = 0;
  int size_volume_name = 0;
  while(fs->volume_name[i] != 0){
    size_volume_name++;
  }
  int padded_size_volume_name = ceil_16(size_volume_name);
  struct file_header *root = (struct file_header *)(&fs->volume_name[padded_size_volume_name]);

  // Question 8
  printf("Root directory: ");
  pp_file(root);
  printf("------\n");
  ls(fs, root);
  printf("------\n");

  // Question 9
  printf("Looking for message.txt\n");
  struct file_header *message = find(fs, root, "message.txt");
  // A COMPLETER - Question 9 - Afficher le contenu du fichier
}

int main(void) {
  int fd = open("fs.romfs", O_RDONLY);
  assert(fd != -1);
  off_t fsize;
  fsize = lseek(fd, 0, SEEK_END);

  //  printf("size is %d", fsize);
  void *addr = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
  assert(addr != MAP_FAILED);
  decode(addr, fsize);

  return 0;
}

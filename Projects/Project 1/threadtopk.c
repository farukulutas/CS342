#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/wait.h>

#include <fcntl.h>

#include <sys/mman.h>

#include <sys/stat.h>

#include <ctype.h>

#define MAX_N 10
#define MAX_WORD_SIZE 64
#define MAX_K 1000

char * infiles[MAX_N];
char * shm_name = "/shared_memory";

typedef struct {
  char word[MAX_WORD_SIZE];
  int count;
}
WordCount;

void process_file(const char * filename, WordCount * result, int K);
void convert_to_uppercase(char * word);

int main(int argc, char * argv[]) {
  int K, N;
  char * outfile;

  if (argc < 4) {
    return 1;
  }

  K = atoi(argv[1]);
  outfile = argv[2];
  N = atoi(argv[3]);

  for (int i = 0; i < N; i++) {
    infiles[i] = argv[i + 4];
  }

  int shm_size = N * K * sizeof(WordCount);
  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    return 1;
  }

  if (ftruncate(shm_fd, shm_size) == -1) {
    return 1;
  }

  WordCount * shm_data = (WordCount * ) mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_data == MAP_FAILED) {
    return 1;
  }

  pid_t pid;
  for (int i = 0; i < N; i++) {
    pid = fork();
    if (pid == 0) {
      process_file(infiles[i], shm_data + i * K, K);
      exit(0);
    } else if (pid == -1) {
      return 1;
    }
  }

  for (int i = 0; i < N; i++) {
    wait(NULL);
  }

  // Combine and sort results
  WordCount final_result[MAX_K * N];
  memcpy(final_result, shm_data, K * N * sizeof(WordCount));

  for (int i = 0; i < K * N; i++) {
    for (int j = i + 1; j < K * N; j++) {
      if (strcmp(final_result[i].word, final_result[j].word) == 0) {
        final_result[i].count += final_result[j].count;
        final_result[j].count = 0;
      }
    }
  }

  // Sort the results by count in descending order
  for (int i = 0; i < K * N; i++) {
    for (int j = i + 1; j < K * N; j++) {
      if (final_result[i].count < final_result[j].count) {
        WordCount temp = final_result[i];
        final_result[i] = final_result[j];
        final_result[j] = temp;
      }
    }
  }

  // Open output file
  FILE * out_file = fopen(outfile, "w");
  if (!out_file) {
    return 1;
  }

  // Write top K results to the output file
  for (int i = 0; i < K && final_result[i].count > 0; i++) {
    fprintf(out_file, "%s %d\n", final_result[i].word, final_result[i].count);
  }

  fclose(out_file);

  if (munmap(shm_data, shm_size) == -1) {
    return 1;
  }

  if (shm_unlink(shm_name) == -1) {
    return 1;
  }

  return 0;
}

void process_file(const char * filename, WordCount * result, int K) {
  FILE * file = fopen(filename, "r");
  if (!file) {
    exit(1);
  }
  // Initialize the result array
  for (int i = 0; i < K; i++) {
    result[i].count = 0;
    result[i].word[0] = '\0';
  }

  char word[MAX_WORD_SIZE];

  while (fscanf(file, " %63s", word) == 1) {
    convert_to_uppercase(word);

    int index = -1;
    for (int i = 0; i < K; i++) {
      if (strcmp(result[i].word, word) == 0) {
        index = i;
        break;
      }
    }

    if (index != -1) {
      result[index].count++;
    } else {
      int min_count = result[0].count;
      int min_index = 0;
      for (int i = 1; i < K; i++) {
        if (result[i].count < min_count) {
          min_count = result[i].count;
          min_index = i;
        }
      }

      if (min_count == 0) {
        strncpy(result[min_index].word, word, MAX_WORD_SIZE);
        result[min_index].count = 1;
      }
    }
  }

  fclose(file);
}

void convert_to_uppercase(char * word) {
  for (int i = 0; word[i]; i++) {
    word[i] = toupper((unsigned char) word[i]);
  }
}

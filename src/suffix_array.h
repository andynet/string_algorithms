#ifndef STRING_ALGORITHMS_SUFFIX_ARRAY_H
#define STRING_ALGORITHMS_SUFFIX_ARRAY_H

char *read_file(char *filename);
char *concat(char *str1, char *str2);
char **create_suffixes(char *str);
size_t *construct_SA(const char *text, char **suffixes);
void print_example(char *text, char **suffixes, size_t *suffix_array);
void save_SA(char *file, size_t *SA, size_t n);

#endif //STRING_ALGORITHMS_SUFFIX_ARRAY_H

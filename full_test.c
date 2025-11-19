#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

// =============================================================================
// =========================== UTILS DE TEST ===================================
// =============================================================================

typedef struct s_test_list
{
	int	passed;
	int	total;
	const char	*suite_name;
}	 t_test_list;

void	print_suite_header(const char *name)
{
	printf("\n\n"
		"===================================================================\n"
		"                        TESTS POUR %s\n"
		"===================================================================\n\n", name);
}

void	print_test_result(int success, const char *name, t_test_list *test_list)
{
	test_list->total++;
	if (success)
	{
		test_list->passed++;
		printf("[  \033[32mOK\033[0m  ] %s\n", name);
	}
	else
	{
		printf("[ \033[31mFAIL\033[0m ] %s\n", name);
	}
}

void	print_suite_summary(t_test_list *test_list)
{
	printf("\n-------------------------------------------------------------------\n");
	printf("RÉSUMÉ POUR %s : %d / %d tests passés.\n", test_list->suite_name, test_list->passed, test_list->total);
	printf("-------------------------------------------------------------------\n");
}


// =============================================================================
// =========================== PARTIE 1: LIBC ==================================
// =============================================================================

void	test_is_functions(t_test_list *test_list)
{
	print_suite_header("IS_FUNCTIONS");
	int success = 1;
	for (int i = -2; i < 260; i++)
	{
		if (!!ft_isalpha(i) != !!isalpha(i)) success = 0;
		if (!!ft_isdigit(i) != !!isdigit(i)) success = 0;
		if (!!ft_isalnum(i) != !!isalnum(i)) success = 0;
		if (!!ft_isascii(i) != !!isascii(i)) success = 0;
		if (!!ft_isprint(i) != !!isprint(i)) success = 0;
	}
	print_test_result(success, "ft_is...(alpha, digit, alnum, ascii, print)", test_list);

	success = 1;
	for (int i = -2; i < 260; i++)
	{
		if (ft_toupper(i) != toupper(i)) success = 0;
		if (ft_tolower(i) != tolower(i)) success = 0;
	}
	print_test_result(success, "ft_toupper / ft_tolower", test_list);
}

void	test_memory_functions(t_test_list *test_list)
{
	print_suite_header("MEMORY_FUNCTIONS");
	char mem1[50];
	char mem2[50];

	// ft_memset / ft_bzero
	ft_memset(mem1, 'A', 20);
	memset(mem2, 'A', 20);
	print_test_result(memcmp(mem1, mem2, 20) == 0, "ft_memset", test_list);
	ft_bzero(mem1, 10);
	print_test_result(mem1[0] == 0 && mem1[9] == 0 && mem1[10] == 'A', "ft_bzero", test_list);

	// ft_memcpy
	char src[] = "Ceci est un test.";
	ft_memcpy(mem1, src, strlen(src) + 1);
	print_test_result(strcmp(mem1, src) == 0, "ft_memcpy", test_list);

	// ft_memmove
	char memmove_src[] = "abcdefghijklmnopqrstuvwxyz";
	char *dest1 = memmove_src + 5;
	ft_memmove(dest1, memmove_src, 10);
	print_test_result(strncmp(dest1, "abcdefghij", 10) == 0, "ft_memmove (overlapping)", test_list);

	// ft_memchr
	char *haystack = "une phrase de test";
	print_test_result(ft_memchr(haystack, 'd', 10) == memchr(haystack, 'd', 10), "ft_memchr (found)", test_list);
	print_test_result(ft_memchr(haystack, 'z', 19) == memchr(haystack, 'z', 19), "ft_memchr (not found)", test_list);

	// ft_memcmp
	char s1[] = "atest", s2[] = "btest", s3[] = "atest";
	print_test_result((ft_memcmp(s1, s2, 5) < 0) && (memcmp(s1, s2, 5) < 0), "ft_memcmp (s1 < s2)", test_list);
	print_test_result((ft_memcmp(s2, s1, 5) > 0) && (memcmp(s2, s1, 5) > 0), "ft_memcmp (s2 > s1)", test_list);
	print_test_result(ft_memcmp(s1, s3, 5) == memcmp(s1, s3, 5), "ft_memcmp (s1 == s3)", test_list);

	// ft_calloc
	size_t count = 10, size = sizeof(int);
	int *arr = ft_calloc(count, size);
	int success = 1;
	if (!arr) success = 0;
	else {
		for (size_t i = 0; i < count; i++) if (arr[i] != 0) success = 0;
	}
	free(arr);
	print_test_result(success, "ft_calloc", test_list);

}

void	test_string_functions(t_test_list *test_list)
{
	print_suite_header("STRING_FUNCTIONS");
    char dest[50];

	// ft_strlen
	print_test_result(ft_strlen("test") == 4 && ft_strlen("") == 0, "ft_strlen", test_list);

	// ft_strlcpy
	memset(dest, 'A', 20);
	ft_strlcpy(dest, "abc", 4);
	print_test_result(strcmp(dest, "abc") == 0, "ft_strlcpy (full copy)", test_list);
	ft_strlcpy(dest, "longue chaine", 5);
	print_test_result(strcmp(dest, "long") == 0, "ft_strlcpy (truncated)", test_list);

	// ft_strlcat
	strcpy(dest, "abc");
	ft_strlcat(dest, "def", 10);
	print_test_result(strcmp(dest, "abcdef") == 0, "ft_strlcat", test_list);

	// ft_strchr / ft_strrchr
	char *str = "le test est le test";
	print_test_result(ft_strchr(str, 'e') == str + 1, "ft_strchr", test_list);
	print_test_result(ft_strrchr(str, 'e') == str + 15, "ft_strrchr", test_list);
	print_test_result(ft_strchr(str, 'z') == NULL, "ft_strchr (not found)", test_list);

	// ft_strncmp
	print_test_result(ft_strncmp("abc", "abd", 3) < 0, "ft_strncmp (s1 < s2)", test_list);
	print_test_result(ft_strncmp("abc", "abc", 5) == 0, "ft_strncmp (s1 == s2)", test_list);

	// ft_strnstr
	print_test_result(ft_strnstr("un test de strnstr", "str", 20) != NULL, "ft_strnstr (found)", test_list);
	print_test_result(ft_strnstr("un test de strnstr", "str", 10) == NULL, "ft_strnstr (not found in n)", test_list);

	// ft_strdup
	char *dup = ft_strdup(str);
	print_test_result(dup && strcmp(dup, str) == 0, "ft_strdup", test_list);
	free(dup);
}

void	test_conversion_functions(t_test_list *test_list)
{
	print_suite_header("CONVERSION_FUNCTIONS");

	// ft_atoi
	print_test_result(ft_atoi("  +42 a") == 42, "ft_atoi (positive)", test_list);
	print_test_result(ft_atoi("\t-1234") == -1234, "ft_atoi (negative)", test_list);
	print_test_result(ft_atoi("0") == 0, "ft_atoi (zero)", test_list);
	print_test_result(ft_atoi(NULL) == 0, "ft_atoi (null)", test_list);

	// ft_itoa
	char *res_itoa;
	res_itoa = ft_itoa(123); print_test_result(strcmp(res_itoa, "123") == 0, "ft_itoa (positive)", test_list); free(res_itoa);
	res_itoa = ft_itoa(-456); print_test_result(strcmp(res_itoa, "-456") == 0, "ft_itoa (negative)", test_list); free(res_itoa);
	res_itoa = ft_itoa(0); print_test_result(strcmp(res_itoa, "0") == 0, "ft_itoa (zero)", test_list); free(res_itoa);
	res_itoa = ft_itoa(INT_MAX); print_test_result(strcmp(res_itoa, "2147483647") == 0, "ft_itoa (INT_MAX)", test_list); free(res_itoa);
	res_itoa = ft_itoa(INT_MIN); print_test_result(strcmp(res_itoa, "-2147483648") == 0, "ft_itoa (INT_MIN)", test_list); free(res_itoa);
}


// =============================================================================
// ==================== PARTIE 2: FONCTIONS ADDITIONNELLES =====================
// =============================================================================

void	test_additional_string_functions(t_test_list *test_list)
{
	print_suite_header("ADDITIONAL_STRING_FUNCTIONS");
	char *res;

	// ft_substr
	res = ft_substr("abcdef", 1, 3); print_test_result(strcmp(res, "bcd") == 0, "ft_substr", test_list); free(res);

	// ft_strjoin
	res = ft_strjoin("abc", "def"); print_test_result(strcmp(res, "abcdef") == 0, "ft_strjoin", test_list); free(res);

	// ft_strtrim
	res = ft_strtrim("  abc  ", " "); print_test_result(strcmp(res, "abc") == 0, "ft_strtrim", test_list); free(res);
	res = ft_strtrim("xyabczyx", "xy"); print_test_result(strcmp(res, "abc") == 0, "ft_strtrim (multiple chars)", test_list); free(res);

	// ft_split
	char **split_res = ft_split("lorem ipsum dolor", ' ');
	int success = strcmp(split_res[0], "lorem") == 0 && strcmp(split_res[1], "ipsum") == 0 && strcmp(split_res[2], "dolor") == 0 && split_res[3] == NULL;
	for(int i=0; split_res[i]; i++) free(split_res[i]);
	free(split_res);
	print_test_result(success, "ft_split", test_list);

	// ft_strmapi / ft_striteri
	char to_iter[] = "abc";
	void iter_func(unsigned int i, char *c) { if (i < 2) *c = *c + 1; }
	ft_striteri(to_iter, iter_func);
	print_test_result(strcmp(to_iter, "bbc") == 0, "ft_striteri", test_list);

	char map_func(unsigned int i, char c) { return (c + i); }
	res = ft_strmapi("012", map_func);
	print_test_result(strcmp(res, "024") == 0, "ft_strmapi", test_list); free(res);
}

void test_output_functions(t_test_list *test_list)
{
	print_suite_header("OUTPUT_FUNCTIONS");
    int pipe_fd[2];
    char buf[100] = {0};
	int saved_stdout = dup(STDOUT_FILENO);

    // Redirect stdout to pipe
    pipe(pipe_fd);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);

	// ft_putchar_fd
    ft_putchar_fd('A', STDOUT_FILENO);
	fflush(stdout);
    read(pipe_fd[0], buf, 1);
    print_test_result(buf[0] == 'A', "ft_putchar_fd", test_list);

	// ft_putstr_fd
	memset(buf, 0, 100);
	ft_putstr_fd("BC", STDOUT_FILENO);
	fflush(stdout);
	read(pipe_fd[0], buf, 2);
    print_test_result(strcmp(buf, "BC") == 0, "ft_putstr_fd", test_list);

	// ft_putendl_fd
	memset(buf, 0, 100);
	ft_putendl_fd("DE", STDOUT_FILENO);
	fflush(stdout);
	read(pipe_fd[0], buf, 3);
    print_test_result(strcmp(buf, "DE\n") == 0, "ft_putendl_fd", test_list);

	// ft_putnbr_fd
	memset(buf, 0, 100);
	ft_putnbr_fd(-123, STDOUT_FILENO);
	fflush(stdout);
	read(pipe_fd[0], buf, 4);
    print_test_result(strcmp(buf, "-123") == 0, "ft_putnbr_fd", test_list);

	// Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
	close(pipe_fd[0]);
}


// =============================================================================
// ==================== PARTIE 3: LISTES (BONUS) ===============================
// =============================================================================

void del_content(void *content) { free(content); }
void *map_content(void *content) {
	int *new_content = malloc(sizeof(int));
	if(new_content) *new_content = *(int*)content + 1;
	return new_content;
}
void iter_content(void *content) { *(int*)content += 1; }

void test_list_functions(t_test_list *test_list)
{
	print_suite_header("LIST_FUNCTIONS (BONUS)");
	int *c1 = malloc(sizeof(int)); *c1 = 1;
	int *c2 = malloc(sizeof(int)); *c2 = 2;
	int *c3 = malloc(sizeof(int)); *c3 = 3;

	t_list *elem1 = ft_lstnew(c1);
	print_test_result(elem1 && elem1->content == c1 && elem1->next == NULL, "ft_lstnew", test_list);

	t_list *list = NULL;
	ft_lstadd_front(&list, elem1);
	print_test_result(list == elem1, "ft_lstadd_front", test_list);

	print_test_result(ft_lstsize(list) == 1, "ft_lstsize (1)", test_list);

	t_list *elem2 = ft_lstnew(c2);
	ft_lstadd_back(&list, elem2);
	print_test_result(list->next == elem2, "ft_lstadd_back", test_list);

	print_test_result(ft_lstlast(list) == elem2, "ft_lstlast", test_list);
	print_test_result(ft_lstsize(list) == 2, "ft_lstsize (2)", test_list);

	t_list *elem3 = ft_lstnew(c3);
	ft_lstadd_front(&list, elem3);
	print_test_result(list == elem3 && list->next == elem1, "ft_lstadd_front (2)", test_list);

	ft_lstdelone(elem1, del_content); // c1 is freed
	list->next = elem2; // Relink manually

	ft_lstiter(list, iter_content);
	print_test_result(*(int*)list->content == 4 && *(int*)list->next->content == 3, "ft_lstiter", test_list);

	t_list *mapped_list = ft_lstmap(list, map_content, del_content);
	print_test_result(mapped_list && *(int*)mapped_list->content == 5 && *(int*)mapped_list->next->content == 4, "ft_lstmap", test_list);

	ft_lstclear(&list, del_content);
	print_test_result(list == NULL, "ft_lstclear", test_list);
	ft_lstclear(&mapped_list, del_content);
}


// =============================================================================
// ============================= MAIN ==========================================
// =============================================================================

int	main(void)
{
	t_test_list is_suite = {0, 0, "IS_FUNCTIONS"};
	test_is_functions(&is_suite);
	print_suite_summary(&is_suite);

	t_test_list mem_suite = {0, 0, "MEMORY_FUNCTIONS"};
	test_memory_functions(&mem_suite);
	print_suite_summary(&mem_suite);

t_test_list str_suite = {0, 0, "STRING_FUNCTIONS"};
	test_string_functions(&str_suite);
	print_suite_summary(&str_suite);

t_test_list conv_suite = {0, 0, "CONVERSION_FUNCTIONS"};
	test_conversion_functions(&conv_suite);
	print_suite_summary(&conv_suite);

	t_test_list add_str_suite = {0, 0, "ADDITIONAL_STRING_FUNCTIONS"};
	test_additional_string_functions(&add_str_suite);
	print_suite_summary(&add_str_suite);

t_test_list output_suite = {0, 0, "OUTPUT_FUNCTIONS"};
	test_output_functions(&output_suite);
	print_suite_summary(&output_suite);

t_test_list list_suite = {0, 0, "LIST_FUNCTIONS (BONUS)"};
	test_list_functions(&list_suite);
	print_suite_summary(&list_suite);

	return (0);
}

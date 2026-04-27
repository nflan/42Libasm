#include "libasm.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	test_strlen(void)
{
	const char	*s = "libasm";

	printf("strlen:   ft=%zu libc=%zu\n", ft_strlen(s), strlen(s));
}

static void	test_strcpy(void)
{
	char	dst_ft[32];
	char	dst_libc[32];

	ft_strcpy(dst_ft, "hello beautiful corrector");
	strcpy(dst_libc, "hello beautiful corrector");
	printf("strcpy:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
	ft_strcpy(dst_ft, "");
	strcpy(dst_libc, "");
	printf("strcpy:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
	// strcpy(dst_libc, NULL);
	// ft_strcpy(dst_ft, NULL);
	// printf("strcpy:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
}

static void	test_strcmp(void)
{
	printf("strcmp A: ft=%d libc=%d\n", ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
	printf("strcmp B: ft=%d libc=%d\n", ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
	printf("strcmp C: ft=%d libc=%d\n", ft_strcmp("abz", "abc"), strcmp("abz", "abc"));
}

static void	test_write_read(void)
{
	char	buffer[32];
	ssize_t	ret;

	ret = ft_write(1, "write test\n", 11);
	printf("write:    ret=%zd errno=%d\n", ret, errno);
	errno = 0;
	ret = ft_write(-1, "x", 1);
	printf("write err: ret=%zd errno=%d\n", ret, errno);
	printf("Type something then press Enter: ");
	fflush(stdout);
	errno = 0;
	ret = ft_read(0, buffer, sizeof(buffer) - 1);
	if (ret >= 0)
		buffer[ret] = '\0';
	printf("read:     ret=%zd errno=%d content=\"%s\"\n", ret, errno, (ret >= 0) ? buffer : "");
}

static void	test_strdup(void)
{
	char	*s;

	s = ft_strdup("duplicate me");
	if (s == NULL)
	{
		perror("ft_strdup");
		return;
	}
	printf("strdup:   \"%s\"\n", s);
	free(s);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write_read();
	test_strdup();
	return (0);
}

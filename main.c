#include "libasm.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

const char *EMPTYSTRING = "";
const char *LONGSTRING = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nisl mauris, suscipit eget augue nec, mattis auctor purus. Curabitur ullamcorper massa facilisis, viverra purus ac, finibus orci. Ut quis tincidunt nulla. Nulla facilisi. Morbi suscipit ligula tortor, et eleifend urna molestie ac. Suspendisse feugiat lacus ut nibh viverra, at gravida magna commodo. Quisque venenatis gravida magna, vel maximus tellus pulvinar sit amet. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis eu rhoncus dolor. Maecenas pellentesque id quam at ultricies. Quisque vel quam vitae nisl venenatis egestas. Maecenas eu imperdiet odio. Sed id aliquet enim, nec consequat ligula. Fusce consectetur mauris a ornare blandit. In interdum, dui dignissim interdum aliquet, ante urna feugiat lectus, eu facilisis mauris metus a arcu. Proin eget felis id purus dictum porta. Ut consequat molestie sagittis.";

static void	test_strlen(void)
{
	const char	*s = "libasm";

	printf("STRLEN\n");

	printf("strlen:   ft=%zu libc=%zu\n", ft_strlen(s), strlen(s));
	printf("strlen with empty string:   ft=%zu libc=%zu\n", ft_strlen(EMPTYSTRING), strlen(EMPTYSTRING));
	printf("strlen with very long string   ft=%zu libc=%zu\n", ft_strlen(LONGSTRING), strlen(LONGSTRING));

	printf("END STRLEN\n\n");
}

static void	test_strcpy(void)
{
	char	dst_ft[1530];
	char	dst_libc[1530];

	printf("STRCPY\n");

	ft_strcpy(dst_ft, "hello beautiful corrector");
	strcpy(dst_libc, "hello beautiful corrector");
	printf("strcpy:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
	ft_strcpy(dst_ft, "");
	strcpy(dst_libc, "");
	printf("strcpy:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
	
	ft_strcpy(dst_ft, EMPTYSTRING);
	strcpy(dst_libc, EMPTYSTRING);
	printf("strcpy with empty string:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);

	ft_strcpy(dst_ft, LONGSTRING);
	strcpy(dst_libc, LONGSTRING);
	printf("strcpy with long string:   ft=\"%s\" libc=\"%s\"\n", dst_ft, dst_libc);
	printf("END STRCPY\n\n");
}

static void	test_strcmp(void)
{
	printf("STRCMP\n");
	printf("strcmp with 2 empty string: ft=%d libc=%d\n", ft_strcmp(EMPTYSTRING, EMPTYSTRING), strcmp(EMPTYSTRING, EMPTYSTRING));
	printf("strcmp with first string empty: ft=%d libc=%d\n", ft_strcmp(EMPTYSTRING, "Coucou"), strcmp(EMPTYSTRING, "Coucou"));
	printf("strcmp with second string empty: ft=%d libc%d\n", ft_strcmp("Coucou", EMPTYSTRING), strcmp("Coucou", EMPTYSTRING));

	printf("strcmp A: ft=%d libc=%d\n", ft_strcmp("abc", "abc"), strcmp("abc", "abc"));
	printf("strcmp B: ft=%d libc=%d\n", ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
	printf("strcmp C: ft=%d libc=%d\n", ft_strcmp("abz", "abc"), strcmp("abz", "abc"));
	printf("END STRCMP\n\n");
}

static void	test_write_read(void)
{
	char	buffer[32];
	ssize_t	ret;

	int fdo = open("coucou", O_RDWR);

	ft_write(1, "WRITE / READ\n", ft_strlen("WRITE / READ\n"));

	ret = ft_write(1, "write test\n", 11);
	printf("write:    ret=%zd errno=%d\n", ret, errno);
	errno = 0;
	ret = ft_write(-1, "x", 1);
	printf("write err: ret=%zd errno=%d\n", ret, errno);
	ret = ft_write(fdo, "C'est toi coucou", ft_strlen("C'est toi coucou"));
	printf("write err: ret=%zd errno=%d\n", ret, errno);

	printf("Type something then press Enter: ");
	fflush(stdout);
	errno = 0;
	ret = ft_read(0, buffer, sizeof(buffer) - 1);
	if (ret >= 0)
		buffer[ret] = '\0';
	printf("read:     ret=%zd errno=%d content=\"%s\"\n", ret, errno, (ret >= 0) ? buffer : "");

	lseek(fdo, 0, 0); // put the head of read at the beginning of the file.
	ret = ft_read(fdo, buffer, sizeof(buffer) - 1);
	if (ret >= 0)
		buffer[ret] = '\0';
	printf("read in coucou:     ret=%zd errno=%d content=\"%s\"\n", ret, errno, (ret >= 0) ? buffer : "");

	ret = ft_read(-1, buffer, sizeof(buffer) - 1);
	if (ret >= 0)
		buffer[ret] = '\0';
	printf("read with bad fd:     ret=%zd errno=%d content=\"%s\"\n", ret, errno, (ret >= 0) ? buffer : "");

	printf("END WRITE / READ\n\n");
}



static void	test_strdup(void)
{
	char	*s;
	char	*ls;

	printf("STRDUP\n");

	s = ft_strdup(EMPTYSTRING);
	if (s == NULL)
	{
		perror("ft_strdup");
		return;
	}
	printf("strdup with empty string: \"%s\"\n", s);
	free(s);

	ls = ft_strdup(LONGSTRING);
	if (ls == NULL)
	{
		perror("ft_strdup");
		return;
	}
	printf("strdup with long string: \"%s\"\n", ls);
	free(ls);

	printf("END STRDUP\n\n");
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

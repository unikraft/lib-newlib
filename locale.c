#include <string.h>
#include <stddef.h>

int strcoll_l(const char *s1, const char *s2,
				locale_t locale)
{
	return 0;
}

size_t strxfrm_l(char *restrict s1, const char *restrict s2,
				size_t n, locale_t locale)
{
	return 0;
}

int wcscoll_l(const wchar_t *ws1, const wchar_t *ws2,
				locale_t locale)
{
	return 0;
}

size_t wcsxfrm_l(wchar_t *restrict ws1, const wchar_t *restrict ws2,
				size_t n, locale_t locale)
{
	return 0;
}

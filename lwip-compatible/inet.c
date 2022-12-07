/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Bogdan Lascu <lascu.bogdan96@gmail.com>
 *
 * Copyright (c) 2019, University Politehnica of Bucharest. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

char *inet_ntoa(struct in_addr in)
{
	static char buf[16];
	unsigned char *a = (void *)&in;

	snprintf(buf, sizeof(buf), "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);

	return buf;
}

int inet_aton(const char *s0, struct in_addr *dest)
{
	const char *s = s0;
	unsigned char *d = (void *)dest;
	unsigned long a[4] = { 0 };
	char *z;
	int i;

	for (i = 0; i < 4; i++) {
		a[i] = strtoul(s, &z, 0);
		if (z == s || (*z && *z != '.') || !isdigit(*s))
			return 0;
		if (!*z)
			break;
		s = z + 1;
	}
	if (i == 4)
		return 0;
	switch (i) {
	case 0:
		a[1] = a[0] & 0xffffff;
		a[0] >>= 24;
	case 1:
		a[2] = a[1] & 0xffff;
		a[1] >>= 16;
	case 2:
		a[3] = a[2] & 0xff;
		a[2] >>= 8;
	}
	for (i = 0; i < 4; i++) {
		if (a[i] > 255)
			return 0;
		d[i] = a[i];
	}
	return 1;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
	return lwip_inet_ntop(af, src, dst, size);
}

int inet_pton(int af, const char *src, void *dst)
{
	return lwip_inet_pton(af, src, dst);
}

#if LWIP_DNS && LWIP_SOCKET && !(LWIP_COMPAT_SOCKETS)
int getaddrinfo(const char *node, const char *service,
		const struct addrinfo *hints,
		struct addrinfo **res)
{
	int rc;

	rc = lwip_getaddrinfo(node, service, hints, res);
	if (!rc) {
		/* Set the precise size of sockaddr */
		struct addrinfo *ai = *res;

		ai->ai_addrlen = ai->ai_family == AF_INET
				? sizeof(struct sockaddr_in)
				: sizeof(struct sockaddr_in6);
	}

	return rc;
}

void freeaddrinfo(struct addrinfo *res)
{
	return lwip_freeaddrinfo(res);
}
#endif /* LWIP_DNS && LWIP_SOCKET && !(LWIP_COMPAT_SOCKETS) */

/* Note: lwip implementation of getaddrinfo does not return all the errors
 * codes mentioned in its man page.
 */
const char *gai_strerror(int errcode)
{
	switch (errcode) {
#if LWIP_DNS_API_DEFINE_ERRORS
	case EAI_NONAME:
		return "The node or service is not known; or both node and service are NULL.";
	case EAI_SERVICE:
		return "The requested service is not available for the requested socket type.";
	case EAI_FAIL:
		return "The name server returned a permanent failure indication.";
	case EAI_MEMORY:
		return "Out of memory.";
	case EAI_FAMILY:
		return "The requested address family is not supported.";
	case EAI_OVERFLOW:
		return "The buffer pointed to by host or serv was too small.";
#endif /* LWIP_DNS_API_DEFINE_ERRORS */
	default:
		return "Error on getaddrinfo.";
	}
}

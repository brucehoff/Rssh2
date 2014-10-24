#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

struct sockaddr_in get_addr_for_host_name(char *hostname) {
    struct hostent *hent;
	char *host_address;
	int i;
	struct sockaddr_in server;

	hent = gethostbyname(hostname);

    /*
     * copy the network address part of the structure to the
     * sockaddr_in structure which is passed to connect()
     * taken from this example: http://shoe.bocks.com/net/#gethostbyname
     */
      memcpy(&server.sin_addr, hent->h_addr_list[0], hent->h_length);
      server.sin_family = AF_INET;
      server.sin_port = htons(22);

      /* lisbbh2 sftp upload/download examples do this:
       * server.sin_addr.s_addr = hostaddr;
       *
       */

      return server;
}

/*
 * Sample showing how to do SFTP transfers.
 *
 */

/* TODO do I need this??  #include "libssh2_config.h"*/
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <fcntl.h>

#ifdef HAVE_WINSOCK2_H
# include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
# ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>


const char *keyfile1="~/.ssh/id_rsa.pub";
const char *keyfile2="~/.ssh/id_rsa";
const char *username="username";
const char *password="password";
const char *sftppath="/tmp/TEST";


static void kbd_callback(const char *name, int name_len, 
             const char *instruction, int instruction_len, int num_prompts,
             const LIBSSH2_USERAUTH_KBDINT_PROMPT *prompts,
             LIBSSH2_USERAUTH_KBDINT_RESPONSE *responses,
             void **abstract)
{
    int i;
    size_t n;
    char buf[1024];
    (void)abstract;

    fprintf(stderr, "Performing keyboard-interactive authentication.\n");

    fprintf(stderr, "Authentication name: '");
    fwrite(name, 1, name_len, stderr);
    fprintf(stderr, "'\n");

    fprintf(stderr, "Authentication instruction: '");
    fwrite(instruction, 1, instruction_len, stderr);
    fprintf(stderr, "'\n");

    fprintf(stderr, "Number of prompts: %d\n\n", num_prompts);

    for (i = 0; i < num_prompts; i++) {
        fprintf(stderr, "Prompt %d from server: '", i);
        fwrite(prompts[i].text, 1, prompts[i].length, stderr);
        fprintf(stderr, "'\n");

        fprintf(stderr, "Please type response: ");
        fgets(buf, sizeof(buf), stdin);
        n = strlen(buf);
        while (n > 0 && strchr("\r\n", buf[n - 1]))
          n--;
        buf[n] = 0;

        responses[i].text = strdup(buf);
        responses[i].length = n;

        fprintf(stderr, "Response %d from user is '", i);
        fwrite(responses[i].text, 1, responses[i].length, stderr);
        fprintf(stderr, "'\n\n");
    }

    fprintf(stderr,
        "Done. Sending keyboard-interactive responses to server now.\n");
}

/**
 * Download a file from an sftp server.   Note this code is taken from example/sftp.c
 */
int sftp_download(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg)
{
    unsigned long hostaddr;
    int sock, i, auth_pw = 0;
    struct sockaddr_in sin;
    const char *fingerprint;
    char *userauthlist;
    LIBSSH2_SESSION *session;
    int rc;
    LIBSSH2_SFTP *sftp_session;
    LIBSSH2_SFTP_HANDLE *sftp_handle;
    char *hostname;
    char *authmode;
    char *localpath;
    int local_file_handle;

#ifdef WIN32
    WSADATA wsadata;

    WSAStartup(MAKEWORD(2,0), &wsadata);
#endif

    hostname = *hostname_arg;
    if (hostname != 0) {
        hostaddr = inet_addr(hostname);
    } else {
        hostaddr = htonl(0x7F000001);
    }

    username = *username_arg;
    password = *password_arg;
    sftppath = *sftppath_arg;
    /* This code supports different authentication methods, but at this time we use only password authentication */
    authmode = "-p";
    localpath = *localpath_arg;


    rc = libssh2_init (0);
    if (rc != 0) {
        fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
        return 1;
    }

    /*
     * The application code is responsible for creating the socket
     * and establishing the connection
     */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = hostaddr;
    rc = connect(sock, (struct sockaddr*)(&sin),sizeof(struct sockaddr_in));
    if (rc != 0) {
        fprintf(stderr, "error in 'sftp_download': failed to connect! host %s, hostaddr %lu, rc %d\n", hostname, hostaddr, rc);
        return -1;
    }

    /* Create a session instance
     */
    session = libssh2_session_init();
    if(!session)
        return -1;

    /* Since we have set non-blocking, tell libssh2 we are blocking */
    libssh2_session_set_blocking(session, 1);

    /* ... start it up. This will trade welcome banners, exchange keys,
     * and setup crypto, compression, and MAC layers
     */
    rc = libssh2_session_handshake(session, sock);
    if(rc) {
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
        return -1;
    }

    /* At this point we havn't yet authenticated.  The first thing to do
     * is check the hostkey's fingerprint against our known hosts Your app
     * may have it hard coded, may go to a file, may present it to the
     * user, that's your call
     */
    fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
    fprintf(stderr, "Fingerprint: ");
    for(i = 0; i < 20; i++) {
        fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
    }
    fprintf(stderr, "\n");

    /* check what authentication methods are available */
    userauthlist = libssh2_userauth_list(session, username, strlen(username));
    fprintf(stderr, "Authentication methods: %s\n", userauthlist);
    if (strstr(userauthlist, "password") != NULL) {
        auth_pw |= 1;
    }
    if (strstr(userauthlist, "keyboard-interactive") != NULL) {
        auth_pw |= 2;
    }
    if (strstr(userauthlist, "publickey") != NULL) {
        auth_pw |= 4;
    }

    /* if we got an 4. argument we set this option if supported */ 
    if(authmode != 0) {
        if ((auth_pw & 1) && !strcasecmp(authmode, "-p")) {
            auth_pw = 1;
        }
        if ((auth_pw & 2) && !strcasecmp(authmode, "-i")) {
            auth_pw = 2;
        }
        if ((auth_pw & 4) && !strcasecmp(authmode, "-k")) {
            auth_pw = 4;
        }
    }

    if (auth_pw & 1) {
        /* We could authenticate via password */
        if (libssh2_userauth_password(session, username, password)) {
            fprintf(stderr, "Authentication by password failed.\n");
            goto shutdown;
        }
    } else if (auth_pw & 2) {
        /* Or via keyboard-interactive */
        if (libssh2_userauth_keyboard_interactive(session, username, &kbd_callback) ) {
            fprintf(stderr,
                "\tAuthentication by keyboard-interactive failed!\n");
            goto shutdown;
        } else {
            fprintf(stderr,
                "\tAuthentication by keyboard-interactive succeeded.\n");
        }
    } else if (auth_pw & 4) {
        /* Or by public key */
        if (libssh2_userauth_publickey_fromfile(session, username, keyfile1, keyfile2, password)) {
            fprintf(stderr, "\tAuthentication by public key failed!\n");
            goto shutdown;
        } else {
            fprintf(stderr, "\tAuthentication by public key succeeded.\n");
        }
    } else {
        fprintf(stderr, "No supported authentication methods found!\n");
        goto shutdown;
    }

    fprintf(stderr, "libssh2_sftp_init()!\n");
    sftp_session = libssh2_sftp_init(session);

    if (!sftp_session) {
        fprintf(stderr, "Unable to init SFTP session\n");
        goto shutdown;
    }

    /* open local file path */
    local_file_handle = open(localpath, O_WRONLY, S_IWRITE);
    if (local_file_handle<0) {
        fprintf(stderr, "Unable to create local file: %s\n",
                localpath);
        goto shutdown;
    }

    fprintf(stderr, "libssh2_sftp_open()!\n");
    /* Request a file via SFTP */
    sftp_handle =
        libssh2_sftp_open(sftp_session, sftppath, LIBSSH2_FXF_READ, 0);

    if (!sftp_handle) {
        fprintf(stderr, "Unable to open file with SFTP: %ld\n",
                libssh2_sftp_last_error(sftp_session));
        goto shutdown;
    }
    fprintf(stderr, "libssh2_sftp_open() is done, now receive data!\n");
    do {
        char mem[1024];

        /* loop until we fail */
        fprintf(stderr, "libssh2_sftp_read()!\n");
        rc = libssh2_sftp_read(sftp_handle, mem, sizeof(mem));
        if (rc > 0) {
            write(local_file_handle, mem, rc);
        } else {
            break;
        }
    } while (1);

    close(local_file_handle)
    libssh2_sftp_close(sftp_handle);
    libssh2_sftp_shutdown(sftp_session);

  shutdown:

    libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");
    libssh2_session_free(session);

#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    fprintf(stderr, "all done\n");

    libssh2_exit();

    return 0;
}

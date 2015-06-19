#include <config.h>
#include <osdept.h>
#include <cmnhdr.h>
#include <udp.h>

#define MAX_TYPE 128

#define DEFAULT_UDP_PORT 4567

#define ENABLE_REGISTER_AFTER_STARTED

#define MAX_UDP_BUFFER 0x10000

struct
{
		udp_func_f func;
		void *data;
} udp_service[MAX_TYPE];

#ifdef ENABLE_REGISTER_AFTER_STARTED
static DECLARE_MUTEX(listen_mutex);
#endif

static DECLARE_THREAD(daemon);

int running; /* when udp is started, running is true */

#ifdef WIN32
static SOCKET udp_socket;
#else
static int udp_socket;
#endif

int udp_init (void)
{
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData );
	assert(err == 0);
#endif
		memset(udp_service, 0, sizeof(udp_service));
#ifdef ENABLE_REGISTER_AFTER_STARTED
		MUTEX_CREATE(listen_mutex);
#endif
		udp_socket = -1;		
		running = FALSE;
		return 0;
}

int udp_cleanup (void)
{
		assert(!running);
#ifdef ENABLE_REGISTER_AFTER_STARTED
		MUTEX_DESTROY(listen_mutex);
#endif
		return 0;
}

int udp_register (int type, udp_func_f func, void *data)
{
		if (type < 0 || type >= MAX_TYPE) return -1;
		if (udp_service[type].func != NULL) return -1;
#ifdef ENABLE_REGISTER_AFTER_STARTED
		MUTEX_LOCK(listen_mutex);
		udp_service[type].func = func;
		udp_service[type].data = data;
		MUTEX_UNLOCK(listen_mutex);
#else
		if (running) return -1;
		udp_service[type].func = func;
		udp_service[type].data = data;
#endif
		return 0;
}

int udp_deregister (int type)
{
		if (type < 0 || type >= MAX_TYPE) return -1;
		if (udp_service[type].func == NULL) return -1;
#ifdef ENABLE_REGISTER_AFTER_STARTED
		MUTEX_LOCK(listen_mutex);
		udp_service[type].func = NULL;
		udp_service[type].data = NULL;
		MUTEX_UNLOCK(listen_mutex);
#else
		if (running) return -1;
		udp_service[type].func = NULL;
		udp_service[type].data = NULL;
#endif
		return 0;
}

void udp_daemon (void *p)
{
		int s;
		static struct
		{
				int size;
				struct sockaddr addr;
				package_t *next;
				/* content of the package */
				int type;
				char data[MAX_UDP_BUFFER - sizeof (int)];
		} package;
		int type;
		for (;;)
		{
			int ret;
			s = sizeof(package.addr);
			ret = recvfrom(udp_socket, (char *)&package.type, MAX_UDP_BUFFER, 0,
						&package.addr, &s);
#ifdef ENABLE_REGISTER_AFTER_STARTED
			MUTEX_LOCK(listen_mutex);
#endif
			if (ret < 0) continue;
			type = package.type;
			info("Package of type %d\n", type);
			if (type < 0 || type >= MAX_TYPE) type = 0;
			else if (udp_service[type].func == NULL) type = 0;
			if (udp_service[type].func)
			{
					udp_service[type].func(udp_service[type].data,
									(package_t *)&package);
			}
#ifdef ENABLE_REGISTER_AFTER_STARTED
			MUTEX_UNLOCK(listen_mutex);
#endif
		}
}

int udp_start (short int port)
{
		struct sockaddr_in serv;
		int ret;
		udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
		assert(udp_socket != -1);
/*		bzero(&serv, sizeof(serv));*/
		memset(&serv, 0, sizeof(serv));
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = htonl(INADDR_ANY);
		serv.sin_port = htons(port);
		ret = bind(udp_socket, (struct sockaddr *)&serv, sizeof(serv));
		assert(ret == 0);
		THREAD_CREATE(daemon, udp_daemon, NULL);
		running = TRUE;
		return 0;
}

int udp_send (package_t *package)
{
		assert(package != NULL);
		assert(running);
		sendto(udp_socket, (char *)&package->type,
			package->size + sizeof(int),
		   	0, (struct sockaddr *)&package->addr,
			sizeof(package->addr));
		return 0;
}

int udp_stop (void)
{
		if (!running) return -1;
		THREAD_DESTROY(daemon);
		closesocket(udp_socket);
		running = 0;
		return 0;
}
extern package_t *reflect_table_package (int id);


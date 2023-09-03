/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Lilach 	  			*
*	Date      : 02/03/2023			*
************************************/

#include <string.h> 		/* strncpy, memcmp  */
#include <unistd.h> 		/* getpid  			*/
#include <arpa/inet.h>		/* to get ip		*/
#include <sys/socket.h>		/* to get ip 		*/
#include <ifaddrs.h>		/* to get ip 		*/

#include "uid.h"	

#define FAILURE (1)
#define SUCCESS (0)
#define TRUE  	(1)
#define FALSE 	(0)

static size_t count = 0;

/************************************************/

uid_t UIDCreate()
{
	uid_t new_uid = {0};
	
	struct ifaddrs *ifadress_struct = NULL;
	struct ifaddrs *ifa_runner = NULL;
	void *tmp_address_ptr = NULL;
	char tmp_address_buffer[INET_ADDRSTRLEN] = {0};

	new_uid.time_stamp = time(NULL);
	new_uid.counter = ++count;
	new_uid.pid = getpid();
	
	if (SUCCESS != getifaddrs(&ifadress_struct))
	{
		return UIDGetBad();
	}
	
	for (ifa_runner = ifadress_struct; NULL != ifa_runner; ifa_runner = ifa_runner->ifa_next)
	{
		if (AF_INET == ifa_runner->ifa_addr->sa_family)
		{
			tmp_address_ptr = &((struct sockaddr_in *)ifa_runner->ifa_addr)->sin_addr;
			inet_ntop(AF_INET, tmp_address_ptr, tmp_address_buffer, INET_ADDRSTRLEN);
			
			if (SUCCESS != strcmp(ifa_runner->ifa_name, "lo")) /* exclude loopback interface*/
			{ 
			    strcpy((char *)new_uid.ip, tmp_address_buffer);
			}
		}
	}
	freeifaddrs(ifadress_struct);
	
	return new_uid;
}

int UIDIsSame(uid_t lhs, uid_t rhs)
{
	int check = TRUE;
	
	if (0 != difftime(lhs.time_stamp, rhs.time_stamp))
	{
		check = FALSE;
	}
	
	if (0 != check)	
	{
		check = (lhs.counter == rhs.counter);
	}
	
	if (0 != check)
	{
		check = (lhs.pid == rhs.pid);
	}
	
	if (0 != check)
	{
		check = (SUCCESS == memcmp(lhs.ip, rhs.ip, LINUX_IP_SIZE));		
	}
	
	return check;

}

uid_t UIDGetBad()
{
	uid_t bad_uid = {0};
	
	return bad_uid;
}

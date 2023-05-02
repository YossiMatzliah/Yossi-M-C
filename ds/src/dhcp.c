/************************************
*	Developer :	Yossi Matzliah      *
*	Reviewer  :	Yotam S				*
*	Date      : 01/05/2023			*
************************************/

#include <stdio.h>	/* perror, printf */
#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */

#include "dhcp.h"
#include "trie.h"

#define MINIMUM_FREE_BITS (2)
#define UINT_BITS (32)
#define NETWORK ((unsigned int)0)
#define BROADCAST(bits_in_subnet) (((unsigned int)(0xFFFFFFFF)) >> (UINT_BITS - bits_in_subnet))
#define SERVER(bits_in_subnet) (((unsigned int)0xFFFFFFFE) & BROADCAST(bits_in_subnet))

struct dhcp_s
{
    unsigned int subnet_ip;     
    unsigned int network_mask;  
    size_t bits_in_subnet;      /* bits of host-net(available IPs) */
    void *trie;
};

/******************************** Static Functions *********************************/

static dhcp_status_t InitFixedAdresses(dhcp_t *dhcp);
static dhcp_status_t CheckValidIp(dhcp_t *dhcp, unsigned int requested_ip);
static dhcp_status_t CheckInvalidFree(dhcp_t *dhcp, unsigned int ip_to_free);
static void ConvertUCharToUInt(unsigned int *dest, unsigned char *src);
static void ConvertUIntToUChar(unsigned char *dest, unsigned int *src);

/********************************** API Functions **********************************/

dhcp_t *DHCPCreate(unsigned char *subnet_ip, size_t bits_in_subnet)
{
    dhcp_t *new_dhcp = NULL;
    dhcp_status_t status = SUCCESS;

    assert(NULL != subnet_ip);
    assert(MINIMUM_FREE_BITS < bits_in_subnet);

    new_dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    
    if (NULL == new_dhcp)
    {
        perror("Alocation Error");
        return NULL;
    }
    
    ConvertUCharToUInt(&new_dhcp->subnet_ip, subnet_ip);
    new_dhcp->network_mask = new_dhcp->subnet_ip;
    new_dhcp->network_mask >>= bits_in_subnet;
    new_dhcp->network_mask <<= bits_in_subnet;
    new_dhcp->bits_in_subnet = bits_in_subnet;    
    new_dhcp->trie = TrieCreate((unsigned int)bits_in_subnet);
    
    if (NULL == new_dhcp->trie)
    {
        perror("Alocation Error");
        free(new_dhcp);
        return NULL;
    }
    
    status = InitFixedAdresses(new_dhcp);
    
    return ((SUCCESS == status) ? new_dhcp : NULL);
}

void DHCPDestroy(dhcp_t *dhcp)
{
    TrieDestroy(dhcp->trie);
    free(dhcp);
}

dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, unsigned char *requested_ip, unsigned char *result_ip)
{
    unsigned int uint_requested_ip = 0;
    unsigned int uint_result_ip = 0;
    dhcp_status_t status = SUCCESS;
    
    assert(NULL != dhcp);
    assert(NULL != requested_ip);
    assert(NULL != result_ip);

    ConvertUCharToUInt(&uint_requested_ip, requested_ip);
    ConvertUCharToUInt(&uint_result_ip, result_ip);

    if (FAILURE == CheckValidIp(dhcp, uint_requested_ip))
    {
        uint_requested_ip = 0;
    }

    status = TrieInsert(dhcp->trie, uint_requested_ip, &uint_result_ip);
    uint_result_ip |= dhcp->network_mask;
    ConvertUIntToUChar(result_ip, &uint_result_ip);

    return status;
}

dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, unsigned char *ip_to_free)
{
    dhcp_status_t status = SUCCESS;
    unsigned int uint_ip_to_free = 0;

    assert(NULL != dhcp);
    assert(NULL != ip_to_free);

    ConvertUCharToUInt(&uint_ip_to_free, ip_to_free);

    status = CheckValidIp(dhcp, uint_ip_to_free);
    status += CheckInvalidFree(dhcp, uint_ip_to_free);

    if (SUCCESS != status)
    {
        return INVALID_FREE;
    }

    return TrieFree(dhcp->trie, uint_ip_to_free);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return TrieCountFree(dhcp->trie);
}

/******************************** Static Functions *********************************/

static dhcp_status_t InitFixedAdresses(dhcp_t *dhcp)
{
    dhcp_status_t status = SUCCESS;
    unsigned int network_address = NETWORK;
    unsigned int broadcast_address = BROADCAST(dhcp->bits_in_subnet);
    unsigned int server_address = SERVER(dhcp->bits_in_subnet);

    status = TrieInsert(dhcp->trie, network_address, &network_address);      
    status += TrieInsert(dhcp->trie, broadcast_address, &broadcast_address);    
    status += TrieInsert(dhcp->trie, server_address, &server_address);

    return ((SUCCESS == status) ? SUCCESS : DS_FAILURE);
}

static dhcp_status_t CheckValidIp(dhcp_t *dhcp, unsigned int requested_ip)
{
    assert(NULL != dhcp);

    requested_ip >>= dhcp->bits_in_subnet;
    requested_ip <<= dhcp->bits_in_subnet;

    return ((dhcp->network_mask != requested_ip) ? FAILURE : SUCCESS);
}

static dhcp_status_t CheckInvalidFree(dhcp_t *dhcp, unsigned int ip_to_free)
{
    ip_to_free <<= (UINT_BITS - dhcp->bits_in_subnet);
    ip_to_free >>= (UINT_BITS - dhcp->bits_in_subnet);

    if (ip_to_free == NETWORK || ip_to_free == BROADCAST(dhcp->bits_in_subnet) || ip_to_free == SERVER(dhcp->bits_in_subnet))
    {
        return INVALID_FREE;
    }

    return SUCCESS;
}

static void ConvertUCharToUInt(unsigned int *dest, unsigned char *src)
{
    *dest = (unsigned int)src[0] << 24 |
            (unsigned int)src[1] << 16 |
            (unsigned int)src[2] << 8  |
            (unsigned int)src[3];
}

static void ConvertUIntToUChar(unsigned char *dest, unsigned int *src)
{
    dest[0] = (*src >> 24) & 0xFF;
    dest[1] = (*src >> 16) & 0xFF;
    dest[2] = (*src >> 8) & 0xFF;
    dest[3] = *src & 0xFF;
}

void PrintCharPtr(unsigned char *ptr)
{
    int i = 0;

    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        if (i == BYTES_IN_IP - 1)
        {
            printf("%d", (int)ptr[i]);
        }

        else
        {
            printf("%d.", (int)ptr[i]);
        }
    }

    printf("\n");
}
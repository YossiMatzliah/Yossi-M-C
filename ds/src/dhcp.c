/************************************
 *	Developer :	Yossi Matzliah      *
 *	Reviewer  :					*
 *	Date      : /04/2023			*
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

typedef struct trie trie_node_t;

struct dhcp_s
{
    unsigned char subnet_mask[BYTES_IN_IP];  /* max is 255.255.255.255 - [8 BITS] [8 BITS] [8 BITS] [8 BITS] */     /* 10.10.0.5/8 -> 255.255.255.0*/
    size_t bits_in_subnet;  /* bits of host-net(available IPs) */
    void *trie;
};

/******************************** Static Functions *********************************/

static void BitsInSubnetToMask(size_t bits_in_subnet, unsigned char *subnet_mask);

/********************************** API Functions **********************************/

dhcp_t *DHCPCreate(unsigned char *subnet_ip, size_t bits_in_subnet)
{
    dhcp_t *new_dhcp = NULL;
    
    assert(NULL != subnet_ip);
    
    if (MINIMUM_FREE_BITS > bits_in_subnet)
    {
        return NULL;
    }

    new_dhcp = malloc(sizeof(dhcp_t));
    
    if (NULL == new_dhcp)
    {
        perror("Alocation Error");
        return NULL;
    }
    
    BitsInSubnetToMask(bits_in_subnet, new_dhcp->subnet_mask);
    new_dhcp->bits_in_subnet = bits_in_subnet;
    
    new_dhcp->trie = TrieCreate((unsigned int)bits_in_subnet);
    if (NULL == new_dhcp->trie)
    {
        perror("Alocation Error");
        free(new_dhcp);
        return NULL;
    }
    
    assert(NETWORK == TrieInsert(new_dhcp->trie, NETWORK));
    assert(BROADCAST(bits_in_subnet) == TrieInsert(new_dhcp->trie, BROADCAST(bits_in_subnet)));
    assert(SERVER(bits_in_subnet) == TrieInsert(new_dhcp->trie, SERVER(bits_in_subnet)));
    
    return new_dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    TrieDestroy(dhcp->trie);
    free(dhcp);
}

dhcp_status_t DHCPAllocateIp(dhcp_t *dhcp, unsigned char *requested_ip, unsigned char *result_ip)
{
    assert(NULL != dhcp);
    /* Add function to change ip_to_free from unsigned char * to unsigned int */
    return SUCCESS;
}

dhcp_status_t DHCPFreeIp(dhcp_t *dhcp, unsigned char *ip_to_free)
{
    assert(NULL != dhcp);
    /* Add function to change ip_to_free from unsigned char * to unsigned int */
    return TrieFree(dhcp->trie, ip_to_free);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    
    return TrieCountFree(dhcp->trie);
}

/******************************** Static Functions *********************************/

static void BitsInSubnetToMask(size_t bits_in_subnet, unsigned char *subnet_mask)
{
    size_t mask = 0xffffffffUL;
    mask = mask << (UINT_BITS - bits_in_subnet);
    subnet_mask[0] = (mask >> 24) & 0xff;           
    subnet_mask[1] = (mask >> 16) & 0xff;          
    subnet_mask[2] = (mask >> 8) & 0xff;
    subnet_mask[3] = mask & 0xff;
}


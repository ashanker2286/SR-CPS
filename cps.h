#ifndef CPS_H
#define CPS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <opx/cps_api_key.h>
#include <opx/dell-interface.h>
#include <opx/dell-base-if-vlan.h>
#include <opx/iana-if-type.h>
#include <opx/dell-base-if.h>
#include <opx/dell-base-if-phy.h>
#include <opx/cps_class_map.h>
#include <opx/cps_api_object_key.h>
#include <opx/dell-base-ip.h>
#include <opx/dell-base-routing.h>

typedef struct portCfg_s {
    char PortName[IF_NAMESIZE];
    uint32_t PortSpeed;
    uint8_t breakOutMode;
} PortCfg_t;

typedef struct cps_vlan_prop_s {
	uint32_t	ifIdx;
	uint32_t	vlanId;
	char		vlanName[256];
	uint32_t	operStatus;
	uint32_t	untagPorts[256];
	uint32_t 	tagPorts[256];
} cps_vlan_prop_t;

int getIfIdxFromIntfRef(char *intfRef);
cps_api_return_code_t delete_vlan(uint32_t vlanId);
cps_api_return_code_t create_vlan(uint32_t vlanId, uint32_t numOfTagPorts, char **tagPorts, uint32_t numOfUntagPorts, char **untagPorts);
//Not Working
void get_all_vlan_prop(int *count, cps_vlan_prop_t *vlanPropList);
cps_api_return_code_t create_ipv4_addr(char *intfRef, char *ipAddr, uint32_t prefix);
cps_api_return_code_t delete_ipv4_addr(char *intfRef, char *ipAddr, uint32_t prefix);
//Not Working
cps_api_return_code_t update_ipv4_addr(char *intfRef, char *ipAddr, uint32_t prefix);
cps_api_return_code_t create_ipv4_route(char *destNw, uint32_t prefix, char *nhIp);
cps_api_return_code_t delete_ipv4_route(char *destNw, uint32_t prefix, char *nhIp);

cps_api_return_code_t create_ipv4_neighbor(char *nbrIp, char *intf, uint8_t macAddr[6]);
cps_api_return_code_t delete_ipv4_neighbor(char *nbrIp, char *intf, uint8_t macAddr[6]);
cps_api_return_code_t get_port_cfg(PortCfg_t *portCfg, uint8_t *count);

#endif /* CPS_H */

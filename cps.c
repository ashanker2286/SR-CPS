#include <cps.h>
/*
 * Wrote using 
 * https://github.com/open-switch/opx-nas-interface/blob/master/src/unit_test/nas_int_vlan_unittest.cpp
 * TEST(std_vlan_test, create_vlan)
 */

int main(int argc, char *argv[]) {
	int ifIdx = -1;
	char *intfRef = "e101-001-0";

	int idx = 0;
	char **tagPortName;
	char **untagPortName;
	int val = 0;
	int count = 0;
        PortCfg_t *portCfg = NULL;
	cps_vlan_prop_t vlanPropList[10];
	uint8_t macAddr[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

	tagPortName = (char **)malloc(2 * sizeof(char *));
	for (idx = 0; idx < 2; idx++) {
		tagPortName[idx] = (char *)malloc(256 * sizeof(char));
		memset(tagPortName[idx], 0, 256);
	}

	untagPortName = (char **)malloc(2 * sizeof(char *));
	for (idx = 0; idx < 2; idx++) {
		untagPortName[idx] = (char *)malloc(256 * sizeof(char));
		memset(untagPortName[idx], 0, 256);
	}

	sprintf(tagPortName[0], "%s", "e101-001-0");
	sprintf(tagPortName[1], "%s", "e101-002-0");
	sprintf(untagPortName[0], "%s", "e101-003-0");
	sprintf(untagPortName[1], "%s", "e101-004-0");

        cps_api_return_code_t retVal = cps_api_ret_code_OK;

	while(1) {
		printf("Menu\n");
		printf("1. Create Vlan\n");
		printf("2. Delete Vlan\n");
		printf("3. Get IfIndex\n");
		printf("4. Get All Vlan Property\n");
		printf("5. Create IP Address on Vlan Interface\n");
		printf("6. Delete IP Address on Vlan Interface\n");
		printf("7. Update IP Address on Vlan Interface\n");
		printf("8. Create IPv4 Route\n");
		printf("9. Delete IPv4 Route\n");
		printf("10. Create IPv4 Neighbor\n");
		printf("11. Delete IPv4 Neighbor\n");
                printf("12. Get port config\n");
		printf("0. Exit\n");
		printf("Submit you option:");
		scanf("%d", &val);
		switch(val) {
		case 1:
			retVal = create_vlan(1000, 2, tagPortName, 2, untagPortName);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to create Vlan: %d\n", retVal);
				continue;
			}
			break;
		case 2:
			retVal = delete_vlan(1000);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to delete Vlan: %d\n", retVal);
				continue;
			}
			break;
		case 3:
			ifIdx = getIfIdxFromIntfRef(intfRef);
			if (ifIdx < 0) {
				printf("Failed to get ifIndex: %d\n", ifIdx);
				continue;
			}
			printf("IfIdx of %s is %d\n", intfRef, ifIdx);
			break;
		case 4:
			memset(vlanPropList, 0, 10 * sizeof(cps_vlan_prop_t));
			get_all_vlan_prop(&count, vlanPropList);
			for (idx = 0; idx < count; idx++) {
				printf("Vlan ifIdx: %d vlanId %d, vlanName: %s, operStatus: %d\n", vlanPropList[idx].ifIdx, vlanPropList[idx].vlanId, vlanPropList[idx].vlanName, vlanPropList[idx].operStatus);
			}
			break;
		case 5:
			retVal = create_ipv4_addr("br1000", "21.1.10.2", 24);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to create IPv4 Intf: %d\n", retVal);
				continue;
			}
			printf("Success: Creating IPv4Interface");
			break;
		case 6:
			retVal = delete_ipv4_addr("br1000", "21.1.10.2", 24);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to delete IPv4 Intf: %d\n", retVal);
				continue;
			}
			printf("Success: Deleting IPv4Interface");
			break;
		case 7:
			retVal = update_ipv4_addr("br1000", "31.1.10.2", 24);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to update IPv4 Intf: %d\n", retVal);
				continue;
			}
			printf("Success: Updating IPv4Interface");
			break;
		case 8:
			retVal = create_ipv4_route("41.1.10.0", 24, "21.1.10.1");
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to create IPv4 Route: %d\n", retVal);
				continue;
			}
			printf("Success: Creating IPv4 Route");
			break;
		case 9:
			retVal = delete_ipv4_route("41.1.10.0", 24, "21.1.10.1");
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to delete IPv4 Route: %d\n", retVal);
				continue;
			}
			printf("Success: Deleting IPv4 Route");
			break;
		case 10:
			retVal = create_ipv4_neighbor("21.1.10.3", "e101-001-0", macAddr);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to create IPv4 Neighbor: %d\n", retVal);
				continue;
			}
			printf("Success: Creating IPv4 Neighbor");
			break;
		case 11:
			retVal = delete_ipv4_neighbor("21.1.10.3", "e101-001-0", macAddr);
			if (retVal != cps_api_ret_code_OK) {
				printf("Failed to delete IPv4 Neighbor: %d\n", retVal);
				continue;
			}
			printf("Success: Deleting IPv4 Neighbor");
			break;
                case 12:
                        retVal = get_port_cfg(NULL, &count);
                        if (count <= 0 ) {
                           printf("No ports found\n");
                           break;
                        } 
                        printf("Found %d ports\n", count);
                        portCfg = (PortCfg_t *)malloc(sizeof (*portCfg) * count); 
                        count = 0;
                        retVal = get_port_cfg(portCfg, &count);
                        for (idx = 0 ; idx < count; idx++) {
                             printf("Port:%d name:%s speed:%u breakOutMode:%u\n", idx, (char *)portCfg[idx].PortName, portCfg[idx].PortSpeed,
                                    portCfg[idx].breakOutMode); 
                        }
                        break;
		case 0:
			return 0;
		default:
			printf("Invalid option\n");
		}
	}

	return 0;
}

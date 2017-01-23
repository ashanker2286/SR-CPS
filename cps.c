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
	cps_vlan_prop_t vlanPropList[10];

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
		printf("5. Set IP Address on Vlan Interface\n");
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
		case 0:
			return 0;
		default:
			printf("Invalid option\n");
		}
	}

	return 0;
}

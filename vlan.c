#include <cps.h>

/*
 * Wrote using 
 * https://github.com/open-switch/opx-nas-interface/blob/master/src/unit_test/nas_int_vlan_unittest.cpp
 * TEST(std_vlan_test, create_vlan)
 */

cps_api_return_code_t _add_ports_to_vlan(char *vlanName, int numOfTagPorts, char **tagPortNameList, int numOfUntagPorts, char **untagPortNameList) {
	cps_api_return_code_t retVal = cps_api_ret_code_OK;
	cps_api_object_t obj = cps_api_object_create();
	int idx = 0;

	cps_api_key_from_attr_with_qual(cps_api_object_key(obj), DELL_BASE_IF_CMN_IF_INTERFACES_INTERFACE_OBJ, cps_api_qualifier_TARGET);

	cps_api_object_attr_add(obj,IF_INTERFACES_INTERFACE_TYPE, (const char *)IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN, sizeof(IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN));
	cps_api_object_attr_add(obj, IF_INTERFACES_INTERFACE_NAME, vlanName, strlen(vlanName)+1);
	for (idx = 0; idx < numOfTagPorts; idx++) {
		printf("Vlan %s Tag Port %s\n", vlanName, tagPortNameList[idx]);
		cps_api_object_attr_add(obj, DELL_IF_IF_INTERFACES_INTERFACE_TAGGED_PORTS, tagPortNameList[idx], strlen(tagPortNameList[idx])+1);
	}

	for (idx = 0; idx < numOfUntagPorts; idx++) {
		printf("Vlan %s Untag Port %s\n", vlanName, untagPortNameList[idx]);
		cps_api_object_attr_add(obj, DELL_IF_IF_INTERFACES_INTERFACE_UNTAGGED_PORTS, untagPortNameList[idx], strlen(untagPortNameList[idx])+1);
	}

	cps_api_transaction_params_t tr;
	retVal = cps_api_transaction_init(&tr);
	if (retVal != cps_api_ret_code_OK) {
		printf("Failed cps_api_transaction_init() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_set(&tr, obj);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_set() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_commit(&tr);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_commit() retVal: %d\n", retVal);
		return retVal;
	}

	cps_api_transaction_close(&tr);
	
	return retVal;
}


cps_api_return_code_t _create_vlan(uint32_t vlanId) {
	cps_api_object_t obj = cps_api_object_create();
	cps_api_return_code_t retVal = cps_api_ret_code_OK;

	cps_api_key_from_attr_with_qual(cps_api_object_key(obj), DELL_BASE_IF_CMN_IF_INTERFACES_INTERFACE_OBJ, cps_api_qualifier_TARGET);

	cps_api_object_attr_add(obj,IF_INTERFACES_INTERFACE_TYPE, (const char *)IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN, sizeof(IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN));
	cps_api_object_attr_add_u32(obj,BASE_IF_VLAN_IF_INTERFACES_INTERFACE_ID, vlanId);

	cps_api_transaction_params_t tr;
	retVal = cps_api_transaction_init(&tr);
	if (retVal != cps_api_ret_code_OK) {
		printf("Failed cps_api_transaction_init() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_create(&tr, obj);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_create() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_commit(&tr);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_commit() retVal: %d\n", retVal);
		return retVal;
	}

	cps_api_transaction_close(&tr);
	return retVal;
}

cps_api_return_code_t delete_vlan(uint32_t vlanId) {
	cps_api_object_t obj = cps_api_object_create();
	cps_api_return_code_t retVal = cps_api_ret_code_OK;

	cps_api_key_from_attr_with_qual(cps_api_object_key(obj), DELL_BASE_IF_CMN_IF_INTERFACES_INTERFACE_OBJ, cps_api_qualifier_TARGET);

	cps_api_object_attr_add(obj,IF_INTERFACES_INTERFACE_TYPE, (const char *)IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN, sizeof(IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN));
	// Ashutosh: It doesnt work with vlanId
	//cps_api_object_attr_add_u32(obj,BASE_IF_VLAN_IF_INTERFACES_INTERFACE_ID, vlanId);

	const char *br_name = "br1000";
	cps_api_set_key_data(obj, IF_INTERFACES_INTERFACE_NAME, cps_api_object_ATTR_T_BIN,
                             br_name, strlen(br_name) + 1 );

	cps_api_transaction_params_t tr;
	retVal = cps_api_transaction_init(&tr);
	if (retVal != cps_api_ret_code_OK) {
		printf("Failed cps_api_transaction_init() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_delete(&tr, obj);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_delete() retVal: %d\n", retVal);
		return retVal;
	}

	retVal = cps_api_commit(&tr);
	if (retVal != cps_api_ret_code_OK) {
		cps_api_transaction_close(&tr);
		printf("Failed cps_api_commit() retVal: %d\n", retVal);
		return retVal;
	}

	cps_api_transaction_close(&tr);
	return retVal;
}

cps_api_return_code_t create_vlan(uint32_t vlanId, uint32_t numOfTagPorts, char **tagPorts, uint32_t numOfUntagPorts, char **untagPorts) {
	cps_api_return_code_t retVal = cps_api_ret_code_OK;
	char vlanName[256] = {0};

	retVal = _create_vlan(vlanId);
	if (retVal != cps_api_ret_code_OK) {
		printf("Failed _create_vlan() retVal: %d\n", retVal);
		return retVal;
	}

	sprintf(vlanName, "br%u", vlanId);
	retVal = _add_ports_to_vlan(vlanName, numOfTagPorts, tagPorts, numOfUntagPorts, untagPorts);
	if (retVal != cps_api_ret_code_OK) {
		printf("Failed _add_ports_to_vlan() retVal: %d\n", retVal);
		return retVal;
	}

	return retVal;
}

void get_vlan_prop_from_obj(cps_api_object_t obj, cps_vlan_prop_t *vlanProp){
	cps_api_object_it_t it;
	cps_api_object_it_begin(obj,&it);

	for ( ; cps_api_object_it_valid(&it) ; cps_api_object_it_next(&it) ) {
		int id = (int) cps_api_object_attr_id(it.attr);
		switch(id) {
		case DELL_BASE_IF_CMN_IF_INTERFACES_INTERFACE_IF_INDEX:
		    //std::cout<<"VLAN INDEX "<<cps_api_object_attr_data_u32(it.attr)<<std::endl;
			vlanProp->ifIdx = cps_api_object_attr_data_u32(it.attr);
			break;
		case BASE_IF_VLAN_IF_INTERFACES_INTERFACE_ID:
		    //std::cout<<"VLAN ID "<<cps_api_object_attr_data_u32(it.attr)<<std::endl;
			vlanProp->vlanId = cps_api_object_attr_data_u32(it.attr);
			break;
		case IF_INTERFACES_INTERFACE_NAME:
		    sprintf(vlanProp->vlanName, "%s", (char *)cps_api_object_attr_data_bin(it.attr));
		    break;
		case DELL_IF_IF_INTERFACES_INTERFACE_TAGGED_PORTS:
		    //std::cout<<"Tagged Port "<<cps_api_object_attr_data_u32(it.attr)<<std::endl;
		    break;
		case DELL_IF_IF_INTERFACES_INTERFACE_UNTAGGED_PORTS:
		    //std::cout<<"Untagged Port "<<cps_api_object_attr_data_u32(it.attr)<<std::endl;
		    break;
		case DELL_IF_IF_INTERFACES_INTERFACE_PHYS_ADDRESS:
		    //printf("MAC Address %s \n", (char *)cps_api_object_attr_data_bin(it.attr));
		    break;
		case IF_INTERFACES_INTERFACE_ENABLED:
		    //std::cout<<"Admin Status "<< cps_api_object_attr_data_u32(it.attr)<<std::endl;
			vlanProp->operStatus = cps_api_object_attr_data_u32(it.attr);
			break;
		case DELL_IF_IF_INTERFACES_INTERFACE_LEARNING_MODE:
		    //std::cout<<"Learning mode "<<cps_api_object_attr_data_u32(it.attr)<<std::endl;
		    break;

		default :
		    break;

		}
	}
}


void get_all_vlan_prop(int *count, cps_vlan_prop_t *vlanPropList) {
	cps_api_get_params_t gp;
	cps_api_get_request_init(&gp);
	cps_api_key_t *key;
	size_t mx, ix;

	cps_api_object_t obj = cps_api_object_list_create_obj_and_append(gp.filters);
	key = cps_api_object_key(obj);
	cps_api_key_from_attr_with_qual(key, DELL_BASE_IF_CMN_IF_INTERFACES_INTERFACE_OBJ,
				    cps_api_qualifier_TARGET);

	cps_api_object_attr_add(obj,IF_INTERFACES_INTERFACE_TYPE,
		(const char *)IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN,
		sizeof(IF_INTERFACE_TYPE_IANAIFT_IANA_INTERFACE_TYPE_IANAIFT_L2VLAN));

	gp.key_count = 1;
	gp.keys = key;

	if (cps_api_get(&gp)==cps_api_ret_code_OK) {
		mx = cps_api_object_list_size(gp.list);
		for (ix = 0 ; ix < mx ; ++ix ) {
	    		obj = cps_api_object_list_get(gp.list,ix);
	    		get_vlan_prop_from_obj(obj, &(vlanPropList[*count]));
			(*count)++;
		}
	}

	cps_api_get_request_close(&gp);
}

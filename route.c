#include <cps.h>

cps_api_return_code_t create_ipv4_route(char *destNw, uint32_t prefix, char *nhIp) {
	cps_api_object_t obj = cps_api_object_create();
        cps_api_return_code_t retVal = cps_api_ret_code_OK;

	cps_api_key_from_attr_with_qual(cps_api_object_key(obj),
		   BASE_ROUTE_OBJ_OBJ,cps_api_qualifier_TARGET);


	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_AF,AF_INET);
	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_VRF_ID,0);
	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_PREFIX_LEN, prefix);

	uint32_t ip;
	struct in_addr a;
	inet_aton(destNw, &a);
	ip=a.s_addr;

	cps_api_object_attr_add(obj,BASE_ROUTE_OBJ_ENTRY_ROUTE_PREFIX,&ip,sizeof(ip));
	cps_api_attr_id_t ids[3];
	const int ids_len = sizeof(ids)/sizeof(*ids);
	ids[0] = BASE_ROUTE_OBJ_ENTRY_NH_LIST;
	ids[1] = 0;
	ids[2] = BASE_ROUTE_OBJ_ENTRY_NH_LIST_NH_ADDR;

	//inet_aton("127.0.0.1", &a);
	inet_aton(nhIp, &a);
	ip=a.s_addr;
	cps_api_object_e_add(obj,ids,ids_len,cps_api_object_ATTR_T_BIN,
					&ip,sizeof(ip));

	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_NH_COUNT,1);


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

cps_api_return_code_t delete_ipv4_route(char *destNw, uint32_t prefix, char *nhIp) {
	cps_api_object_t obj = cps_api_object_create();
        cps_api_return_code_t retVal = cps_api_ret_code_OK;

	cps_api_key_from_attr_with_qual(cps_api_object_key(obj),
		   BASE_ROUTE_OBJ_OBJ,cps_api_qualifier_TARGET);


	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_AF,AF_INET);
	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_VRF_ID,0);
	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_PREFIX_LEN, prefix);

	uint32_t ip;
	struct in_addr a;
	inet_aton(destNw, &a);
	ip=a.s_addr;

	cps_api_object_attr_add(obj,BASE_ROUTE_OBJ_ENTRY_ROUTE_PREFIX,&ip,sizeof(ip));
	cps_api_attr_id_t ids[3];
	const int ids_len = sizeof(ids)/sizeof(*ids);
	ids[0] = BASE_ROUTE_OBJ_ENTRY_NH_LIST;
	ids[1] = 0;
	ids[2] = BASE_ROUTE_OBJ_ENTRY_NH_LIST_NH_ADDR;

	//inet_aton("127.0.0.1", &a);
	inet_aton(nhIp, &a);
	ip=a.s_addr;
	cps_api_object_e_add(obj,ids,ids_len,cps_api_object_ATTR_T_BIN,
					&ip,sizeof(ip));

	cps_api_object_attr_add_u32(obj,BASE_ROUTE_OBJ_ENTRY_NH_COUNT,1);


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

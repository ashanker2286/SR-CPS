#include <cps.h>

cps_api_return_code_t create_ipv4_addr(char *intfRef, char *ipAddr, uint32_t prefix) {
        cps_api_object_t obj = cps_api_object_create();
        cps_api_return_code_t retVal = cps_api_ret_code_OK;

        int index = if_nametoindex(intfRef);

        cps_api_key_from_attr_with_qual(cps_api_object_key(obj), BASE_IP_IPV4_ADDRESS, cps_api_qualifier_TARGET);

        cps_api_object_attr_add_u32(obj, BASE_IP_IPV4_ADDRESS_PREFIX_LENGTH, prefix);

        uint32_t ip;
        struct in_addr a;
        inet_aton(ipAddr ,&a);
        ip=a.s_addr;
        cps_api_object_attr_add(obj, BASE_IP_IPV4_ADDRESS_IP, &ip,sizeof(ip));
        cps_api_object_attr_add_u32(obj, BASE_IP_IPV4_IFINDEX, index);


        cps_api_transaction_params_t tr;
        retVal = cps_api_transaction_init(&tr);
        if (retVal != cps_api_ret_code_OK) {
                printf("Failed cps_api_transaction_init: %d\n", retVal);
                return retVal;
        }
        cps_api_create(&tr,obj);
        retVal = cps_api_commit(&tr);
        if (retVal != cps_api_ret_code_OK) {
                printf("Failed cps_api_commit : %d\n", retVal);
                return retVal;
        }
        cps_api_transaction_close(&tr);
	return retVal;
}

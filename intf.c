#include <cps.h>
#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <net/if.h>
#include <cps.h>
#include <opx/cps_api_key.h>
#include <opx/dell-base-vlan.h>
#include <opx/dell-base-if-vlan.h>
#include <opx/iana-if-type.h>
#include <opx/dell-base-if.h>
#include <opx/cps_class_map.h>
#include <opx/cps_api_object_key.h>
#endif

/*
 * Wrote using 
 * https://github.com/open-switch/opx-nas-interface/blob/master/src/unit_test/nas_int_vlan_unittest.cpp
 * TEST(std_vlan_test, create_vlan)
 */

int getIfIdxFromIntfRef(char *intfRef) {
	return if_nametoindex(intfRef);
}

cps_api_return_code_t get_port_cfg(PortCfg_t *portCfg, uint8_t *count) {
    cps_api_return_code_t retVal = cps_api_ret_code_OK;
    cps_api_key_t *key;
    cps_api_get_params_t gp;

    cps_api_get_request_init(&gp);
    cps_api_object_t obj = cps_api_object_list_create_obj_and_append(gp.filters);

    key = cps_api_object_key(obj);
    cps_api_key_from_attr_with_qual(key, BASE_IF_PHY_FRONT_PANEL_PORT_OBJ, cps_api_qualifier_TARGET);
    gp.key_count=1;
    gp.keys = key;
    retVal = cps_api_get(&gp);
    if (retVal == cps_api_ret_code_OK) {
        size_t ix, mx = cps_api_object_list_size(gp.list);
        for (ix = 0; ix < mx; ix++) {
            cps_api_object_t obj = cps_api_object_list_get(gp.list, ix);
            cps_api_object_attr_t port_name = cps_api_object_attr_get(obj, BASE_IF_PHY_FRONT_PANEL_PORT_DEFAULT_NAME);
            cps_api_object_attr_t port_speed = cps_api_object_attr_get(obj, BASE_IF_PHY_FRONT_PANEL_PORT_PORT_SPEED);
            cps_api_object_attr_t breakOutMode = cps_api_object_attr_get(obj, BASE_IF_PHY_FRONT_PANEL_PORT_BREAKOUT_MODE);
            if (port_name == CPS_API_ATTR_NULL) {
               fprintf(stderr, "Unable to get port name for obj at idx %d", (int)ix);
            } else {
               fprintf(stderr, "Iterating through obj %s\n", (char*)cps_api_object_attr_data_bin(port_name));
               if (portCfg != NULL) {
                   snprintf(portCfg[(int)ix].PortName, strlen((char*)cps_api_object_attr_data_bin(port_name))+1, "%s", (char*)cps_api_object_attr_data_bin(port_name));
                   portCfg[(int)ix].PortSpeed = (uint32_t)cps_api_object_attr_data_bin(port_speed);
                   portCfg[(int)ix].breakOutMode = (uint8_t)cps_api_object_attr_data_bin(breakOutMode);
               }
               (*count)++;
           }
        }
   } else {
        fprintf(stderr, "Failed to get front panel port information");
        cps_api_get_request_close(&gp);
        return retVal;
   }
   //Close get request
   cps_api_get_request_close(&gp);
   fprintf(stderr, "Count = %u\n", *count);
   return retVal;
}

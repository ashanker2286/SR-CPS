#include <cps.h>
#if 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <net/if.h>
#include <sonic/cps_api_key.h>
#include <sonic/dell-base-vlan.h>
#include <sonic/dell-base-if-vlan.h>
#include <sonic/iana-if-type.h>
#include <sonic/dell-base-if.h>
#include <sonic/cps_class_map.h>
#include <sonic/cps_api_object_key.h>
#endif

/*
 * Wrote using 
 * https://github.com/open-switch/opx-nas-interface/blob/master/src/unit_test/nas_int_vlan_unittest.cpp
 * TEST(std_vlan_test, create_vlan)
 */

int getIfIdxFromIntfRef(char *intfRef) {
	return if_nametoindex(intfRef);
}

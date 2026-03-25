/*
 * fw_info.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef FW_INFO_H_
#define FW_INFO_H_

#include <stdint.h>

struct fw_info_t
{
	uint32_t magic;
	uint16_t major, minor, patch;
	uint32_t build;
	uint32_t git_hash;
} __attribute__((packed));
typedef struct fw_info_t STRUCT_FW_INFO;

#endif /* FW_INFO_H_ */

/*
 * bitflags.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_BITFLAGS_H_
#define INC_BITFLAGS_H_

#include <stdint.h>

#define BITS_SET_U16(var, mask)     do { (var) |=  (uint16_t)(mask); } while (0)
#define BITS_CLEAR_U16(var, mask)   do { (var) &= (uint16_t)~(uint16_t)(mask); } while (0)
#define BITS_TOGGLE_U16(var, mask)  do { (var) ^=  (uint16_t)(mask); } while (0)
#define BITS_TEST_U16(var, mask)    (((var) & (uint16_t)(mask)) != 0u)

#define BITS_SET_U32(var, mask)     do { (var) |=  (uint32_t)(mask); } while (0)
#define BITS_CLEAR_U32(var, mask)   do { (var) &= (uint32_t)~(uint16_t)(mask); } while (0)
#define BITS_TOGGLE_U32(var, mask)  do { (var) ^=  (uint32_t)(mask); } while (0)
#define BITS_TEST_U32(var, mask)    (((var) & (uint32_t)(mask)) != 0u)

#endif /* INC_BITFLAGS_H_ */

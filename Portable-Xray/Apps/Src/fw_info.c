#include "fw_info.h"

#define FW_INFO_MAGIC  (0x5049434FUL)  // PICO
#define FW_VER_MAJOR   (1U)
#define FW_VER_MINOR   (0U)
#define FW_VER_PATCH   (0U)
#define FW_BUILD_NUM   (0U)
#define FW_GIT_HASH    (0xA1B2C3D4UL)  // 빌드 시스템에서 주입 권장

__attribute__((section(".fwinfo"), used))
const STRUCT_FW_INFO g_fw_info = {
    .magic    = FW_INFO_MAGIC,
    .major    = FW_VER_MAJOR,
    .minor    = FW_VER_MINOR,
    .patch    = FW_VER_PATCH,
    .build    = FW_BUILD_NUM,
    .git_hash = FW_GIT_HASH,
};

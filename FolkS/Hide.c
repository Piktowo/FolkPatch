#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Core author: SevenOnePlus(https://github.com/SevenOnePlus)
Packaging: Matsuzaka Yuki(https://github.com/matsuzaka-yuki)
*/

typedef struct {
    const char *key;
    const char *value;
} PropItem;

void set_prop(const char *key, const char *value) {
    char cmd[256];
    if (key && value) {
        snprintf(cmd, sizeof(cmd), "resetprop -n %s %s", key, value);
        system(cmd);
    }
}

int get_prop(const char *key, char *out, size_t len) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "resetprop %s", key);
    FILE *fp = popen(cmd, "r");
    if (!fp) return 0;
    if (fgets(out, len, fp)) {
        out[strcspn(out, "\r\n")] = 0;
        pclose(fp);
        return (strlen(out) > 0);
    }
    pclose(fp);
    return 0;
}

int main() {
    PropItem core_list[] = {
        {"ro.boot.vbmeta.device_state", "locked"},
        {"ro.boot.verifiedbootstate", "green"},
        {"ro.boot.flash.locked", "1"},
        {"ro.boot.veritymode", "enforcing"},
        {"ro.boot.warranty_bit", "0"},
        {"ro.warranty_bit", "0"},
        {"ro.debuggable", "0"},
        {"ro.force.debuggable", "0"},
        {"ro.secure", "1"},
        {"ro.adb.secure", "1"},
        {"ro.build.type", "user"},
        {"ro.build.tags", "release-keys"},
        {"ro.vendor.boot.warranty_bit", "0"},
        {"ro.vendor.warranty_bit", "0"},
        {"vendor.boot.vbmeta.device_state", "locked"},
        {"vendor.boot.verifiedbootstate", "green"},
        {"sys.oem_unlock_allowed", "0"},
        {"ro.secureboot.lockstate", "locked"},
        {"ro.boot.realmebootstate", "green"},
        {"ro.boot.realme.lockstate", "1"},
        {"persist.sys.usb.config", "none"},
        {"sys.usb.config", "none"},
        {"sys.usb.state", "disconnected"},
        {"ro.adb.enabled", "0"},
        {"persist.adb.enabled", "0"},
        {"service.adb.root", "0"}
    };

    for (size_t i = 0; i < sizeof(core_list) / sizeof(core_list[0]); i++) {
        set_prop(core_list[i].key, core_list[i].value);
    }

    const char *boot_keys[] = {"ro.bootmode", "ro.boot.bootmode", "vendor.boot.bootmode"};
    for (size_t i = 0; i < sizeof(boot_keys) / sizeof(boot_keys[0]); i++) {
        char val[128] = {0};
        if (get_prop(boot_keys[i], val, sizeof(val))) {
            if (strstr(val, "recovery")) {
                set_prop(boot_keys[i], "unknown");
            }
        }
    }

    PropItem patch_list[] = {
        {"ro.boot.vbmeta.device_state", "locked"},
        {"ro.boot.vbmeta.invalidate_on_error", "yes"},
        {"ro.boot.vbmeta.avb_version", "1.0"},
        {"ro.boot.vbmeta.hash_alg", "sha256"},
        {"ro.boot.vbmeta.size", "4096"}
    };

    for (size_t i = 0; i < sizeof(patch_list) / sizeof(patch_list[0]); i++) {
        char val[128] = {0};
        if (!get_prop(patch_list[i].key, val, sizeof(val))) {
            set_prop(patch_list[i].key, patch_list[i].value);
        }
    }

    return 0;
}
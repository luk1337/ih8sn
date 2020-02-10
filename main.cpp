#include <android-base/strings.h>
#include <fstream>
#include <map>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end, bootimage, and an empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "bootimage.",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true) {
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

std::map<std::string, std::string> load_config() {
    std::map<std::string, std::string> config;

    if (std::ifstream file("/system/etc/ih8sn.conf"); file.good()) {
        std::string line;

        while (std::getline(file, line)) {
            if (line[0] == '#') {
                continue;
            }

            if (const auto kv = android::base::Split(line, "="); kv.size() == 2) {
                config[kv.at(0)] = kv.at(1);
            }
        }
    }

    return config;
}

int main(int argc, char *argv[]) {
    if (__system_properties_init()) {
        return -1;
    }

    const auto config = load_config();
    const auto build_fingerprint = config.find("BUILD_FINGERPRINT");
    const auto build_description = config.find("BUILD_DESCRIPTION");
    const auto build_security_patch_date = config.find("BUILD_SECURITY_PATCH_DATE");

    for (const auto &source : ro_product_props_default_source_order) {
        if (build_fingerprint != config.end()) {
            const auto build_fingerprint_prop_name = "ro." + source + "build.fingerprint";
            property_override(build_fingerprint_prop_name.c_str(),
                    build_fingerprint->second.c_str(), false);
        }
    }

    if (build_description != config.end()) {
        property_override("ro.build.description", build_description->second.c_str(), false);
    }

    if (build_description != config.end()) {
        property_override("ro.build.version.security_patch",
                build_security_patch_date->second.c_str(), false);
    }

    property_override("ro.boot.flash.locked", "1", false);
    property_override("ro.boot.verifiedbootstate", "green", false);
    property_override("ro.boot.veritymode", "enforcing", false);
    property_override("ro.boot.warranty_bit", "0", false);
    property_override("ro.warranty_bit", "0", false);

    return 0;
}

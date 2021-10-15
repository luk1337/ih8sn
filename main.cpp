#include <fstream>
#include <map>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

void property_override(char const prop[], char const value[], bool add = false) {
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

            if (const auto separator = line.find('='); separator != std::string::npos) {
                config[line.substr(0, separator)] = line.substr(separator + 1);
            }
        }
    }

    return config;
}

int main(int argc __unused, char *argv[] __unused) {
    if (__system_properties_init()) {
        return -1;
    }

    const auto config = load_config();
    const auto build_fingerprint = config.find("BUILD_FINGERPRINT");
    const auto build_description = config.find("BUILD_DESCRIPTION");
    const auto build_security_patch_date = config.find("BUILD_SECURITY_PATCH_DATE");
    const auto build_tags = config.find("BUILD_TAGS");
    const auto build_type = config.find("BUILD_TYPE");
    const auto build_version_release = config.find("BUILD_VERSION_RELEASE");
    const auto debuggable = config.find("DEBUGGABLE");
    const auto product_name = config.find("PRODUCT_NAME");

    if (build_fingerprint != config.end()) {
        for (const auto &prop : {
            "ro.bootimage.build.fingerprint",
            "ro.build.fingerprint",
            "ro.odm.build.fingerprint",
            "ro.product.build.fingerprint",
            "ro.system.build.fingerprint",
            "ro.system_ext.build.fingerprint",
            "ro.vendor.build.fingerprint",
        }) {
            property_override(prop, build_fingerprint->second.c_str());
        }
    }

    if (build_tags != config.end()) {
        for (const auto &prop : {
            "ro.build.tags",
            "ro.odm.build.tags",
            "ro.product.build.tags",
            "ro.system.build.tags",
            "ro.system_ext.build.tags",
            "ro.vendor.build.tags",
        }) {
            property_override(prop, build_tags->second.c_str());
        }
    }

    if (build_type != config.end()) {
        for (const auto &prop : {
            "ro.build.type",
            "ro.odm.build.type",
            "ro.product.build.type",
            "ro.system.build.type",
            "ro.system_ext.build.type",
            "ro.vendor.build.type",
        }) {
            property_override(prop, build_type->second.c_str());
        }
    }

    if (build_version_release != config.end()) {
        for (const auto &prop : {
            "ro.build.version.release",
            "ro.odm.build.version.release",
            "ro.product.build.version.release",
            "ro.system.build.version.release",
            "ro.system_ext.build.version.release",
            "ro.vendor.build.version.release",
        }) {
            property_override(prop, build_version_release->second.c_str());
        }
    }

    if (build_description != config.end()) {
        property_override("ro.build.description", build_description->second.c_str());
    }

    if (build_security_patch_date != config.end()) {
        property_override("ro.build.version.security_patch",
                build_security_patch_date->second.c_str());
    }

    if (debuggable != config.end()) {
        property_override("ro.debuggable", debuggable->second.c_str());
    }

    if (product_name != config.end()) {
        for (const auto &prop : {
            "ro.product.name",
            "ro.product.odm.name",
            "ro.product.product.name",
            "ro.product.system.name",
            "ro.product.system_ext.name",
            "ro.product.vendor.name",
        }) {
            property_override(prop, product_name->second.c_str());
        }
    }

    property_override("ro.boot.flash.locked", "1");
    property_override("ro.boot.vbmeta.device_state", "locked");
    property_override("ro.boot.verifiedbootstate", "green");
    property_override("ro.boot.veritymode", "enforcing");
    property_override("ro.boot.warranty_bit", "0");
    property_override("ro.warranty_bit", "0");

    return 0;
}

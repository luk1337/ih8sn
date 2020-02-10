#include <string>
#include <vector>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

constexpr auto BUILD_FINGERPRINT =
        "OnePlus/OnePlus7Pro_EEA/OnePlus7Pro:10/QKQ1.190716.003/1910071200:user/release-keys";
constexpr auto BUILD_DESCRIPTION =
        "OnePlus7Pro-user 10 QKQ1.190716.003 1910071200 release-keys";
constexpr auto BUILD_SECURITY_PATCH_DATE =
        "2019-09-05";

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
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

int main(int argc, char *argv[]) {
    if (__system_properties_init()) {
        return -1;
    }

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    for (const auto &source : ro_product_props_default_source_order) {
        set_ro_product_prop(source, "build.fingerprint", BUILD_FINGERPRINT);
    }

    property_override("ro.build.description", BUILD_DESCRIPTION, false);
    property_override("ro.build.version.security_patch", BUILD_SECURITY_PATCH_DATE, false);

    property_override("ro.boot.flash.locked", "1", false);
    property_override("ro.boot.verifiedbootstate", "green", false);
    property_override("ro.boot.veritymode", "enforcing", false);
    property_override("ro.boot.warranty_bit", "0", false);
    property_override("ro.warranty_bit", "0", false);

    return 0;
}

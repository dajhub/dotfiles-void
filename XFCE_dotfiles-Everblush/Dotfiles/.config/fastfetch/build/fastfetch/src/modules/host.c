#include "fastfetch.h"

#include <ctype.h>

#define FF_HOST_MODULE_NAME "Host"
#define FF_HOST_NUM_FORMAT_ARGS 3

static bool hostValueSet(FFstrbuf* value)
{
    ffStrbufTrimRight(value, '\n');
    ffStrbufTrim(value, ' ');

    return
        value->length > 0 &&
        ffStrbufStartsWithIgnCaseS(value, "To be filled") != true &&
        ffStrbufStartsWithIgnCaseS(value, "To be set") != true &&
        ffStrbufStartsWithIgnCaseS(value, "OEM") != true &&
        ffStrbufStartsWithIgnCaseS(value, "O.E.M.") != true &&
        ffStrbufIgnCaseCompS(value, "None") != 0 &&
        ffStrbufIgnCaseCompS(value, "System Product") != 0 &&
        ffStrbufIgnCaseCompS(value, "System Product Name") != 0 &&
        ffStrbufIgnCaseCompS(value, "System Product Version") != 0 &&
        ffStrbufIgnCaseCompS(value, "System Name") != 0 &&
        ffStrbufIgnCaseCompS(value, "System Version") != 0 &&
        ffStrbufIgnCaseCompS(value, "Default string") != 0 &&
        ffStrbufIgnCaseCompS(value, "Undefined") != 0 &&
        ffStrbufIgnCaseCompS(value, "Not Specified") != 0 &&
        ffStrbufIgnCaseCompS(value, "Not Applicable") != 0 &&
        ffStrbufIgnCaseCompS(value, "INVALID") != 0 &&
        ffStrbufIgnCaseCompS(value, "Type1ProductConfigId") != 0 &&
        ffStrbufIgnCaseCompS(value, "All Series") != 0
    ;
}

#ifndef __ANDROID__
static void getHostValue(const char* devicesPath, const char* classPath, FFstrbuf* buffer)
{
    ffGetFileContent(devicesPath, buffer);

    if(buffer->length == 0)
        ffGetFileContent(classPath, buffer);
}
#endif

void ffPrintHost(FFinstance* instance)
{
    if(ffPrintFromCache(instance, FF_HOST_MODULE_NAME, &instance->config.hostKey, &instance->config.hostFormat, FF_HOST_NUM_FORMAT_ARGS))
        return;

    FFstrbuf family;
    ffStrbufInit(&family);
    #ifndef __ANDROID__
        getHostValue("/sys/devices/virtual/dmi/id/product_family", "/sys/class/dmi/id/product_family", &family);
    #else
        ffSettingsGetAndroidProperty("ro.product.device", &family);
    #endif
    bool familySet = hostValueSet(&family);

    FFstrbuf name;
    ffStrbufInit(&name);
    #ifndef __ANDROID__
        getHostValue("/sys/devices/virtual/dmi/id/product_name", "/sys/class/dmi/id/product_name", &name);

        if(name.length == 0)
            ffGetFileContent("/sys/firmware/devicetree/base/model", &name);

        if(name.length == 0)
            ffGetFileContent("/tmp/sysinfo/model", &name);

        if(ffStrbufStartsWithS(&name, "Standard PC"))
        {
            FFstrbuf copy;
            ffStrbufInitCopy(&copy, &name);
            ffStrbufSetS(&name, "KVM/QEMU ");
            ffStrbufAppend(&name, &copy);
            ffStrbufDestroy(&copy);
        }
    #else
        ffSettingsGetAndroidProperty("ro.product.brand", &name);
        if(name.length > 0){
            name.chars[0] = (char) toupper(name.chars[0]);
            ffStrbufAppendC(&name, ' ');
        }

        if(!ffSettingsGetAndroidProperty("ro.product.model", &name))
            ffSettingsGetAndroidProperty("ro.product.name", &name);

        ffStrbufTrimRight(&name, ' ');
    #endif
    bool nameSet = hostValueSet(&name);

    FFstrbuf version;
    ffStrbufInit(&version);
    #ifndef __ANDROID__
        getHostValue("/sys/devices/virtual/dmi/id/product_version", "/sys/class/dmi/id/product_version", &version);
    #endif
    bool versionSet = hostValueSet(&version);

    if(!familySet && !nameSet)
    {
        ffStrbufDestroy(&family);
        ffStrbufDestroy(&name);
        ffStrbufDestroy(&version);
        ffPrintError(instance, FF_HOST_MODULE_NAME, 0, &instance->config.hostKey, &instance->config.hostFormat, FF_HOST_NUM_FORMAT_ARGS, "neither family nor name is set by O.E.M.");
        return;
    }

    FFstrbuf host;
    ffStrbufInit(&host);

    if(nameSet)
        ffStrbufAppend(&host, &name);
    else
        ffStrbufAppend(&host, &family);

    if(versionSet)
    {
        ffStrbufAppendC(&host, ' ');
        ffStrbufAppend(&host, &version);
    }

    ffPrintAndWriteToCache(instance, FF_HOST_MODULE_NAME, &instance->config.hostKey, &host, &instance->config.hostFormat, FF_HOST_NUM_FORMAT_ARGS, (FFformatarg[]) {
        {FF_FORMAT_ARG_TYPE_STRBUF, &family},
        {FF_FORMAT_ARG_TYPE_STRBUF, &name},
        {FF_FORMAT_ARG_TYPE_STRBUF, &version}
    });

    ffStrbufDestroy(&family);
    ffStrbufDestroy(&name);
    ffStrbufDestroy(&version);
}

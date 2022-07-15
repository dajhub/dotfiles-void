#include "fastfetch.h"

#define FF_RESOLUTION_MODULE_NAME "Resolution"
#define FF_RESOLUTION_NUM_FORMAT_ARGS 3

void ffPrintResolution(FFinstance* instance)
{
    #ifdef __ANDROID__
        ffPrintError(instance, FF_RESOLUTION_MODULE_NAME, 0, &instance->config.resolutionKey, &instance->config.resolutionFormat, FF_RESOLUTION_NUM_FORMAT_ARGS, "Resolution detection is not supported on Android");
        return;
    #endif

    const FFDisplayServerResult* dsResult = ffConnectDisplayServer(instance);

    for(uint32_t i = 0; i < dsResult->resolutions.length; i++)
    {
        FFResolutionResult* result = ffListGet(&dsResult->resolutions, i);
        uint8_t moduleIndex = dsResult->resolutions.length == 1 ? 0 : (uint8_t) (i + 1);

        if(instance->config.resolutionFormat.length == 0)
        {
            ffPrintLogoAndKey(instance, FF_RESOLUTION_MODULE_NAME, moduleIndex, &instance->config.resolutionKey);
            printf("%ix%i", result->width, result->height);

            if(result->refreshRate > 0)
                printf(" @ %iHz", result->refreshRate);

            putchar('\n');
        }
        else
        {
            ffPrintFormatString(instance, FF_RESOLUTION_MODULE_NAME, moduleIndex, &instance->config.resolutionKey, &instance->config.resolutionFormat, NULL, FF_RESOLUTION_NUM_FORMAT_ARGS, (FFformatarg[]) {
                {FF_FORMAT_ARG_TYPE_INT, &result->width},
                {FF_FORMAT_ARG_TYPE_INT, &result->height},
                {FF_FORMAT_ARG_TYPE_INT, &result->refreshRate}
            });
        }
    }

    if(dsResult->resolutions.length == 0)
        ffPrintError(instance, FF_RESOLUTION_MODULE_NAME, 0, &instance->config.resolutionKey, &instance->config.resolutionFormat, FF_RESOLUTION_NUM_FORMAT_ARGS, "Couldn't detect resolution");
}

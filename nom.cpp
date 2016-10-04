
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <lv2-c++-tools/lv2.h>

#define SYNTH_URI "http://github.com/datross/nom"

typedef enum
{
    OUTPUT = 0
} PortIndex;

typedef struct
{
    float * output; /* Stores the connected buffer */
} Synth;

/* This function instantiates our model. */
static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                              double rate,
                              const char * bundle_path,
                              const LV2_Feature * const * features)
{
    printf("Do printfs work ?\n");
    Synth * synth = (Synth*)malloc(sizeof(Synth));
    return (LV2_Handle)synth;
}

/* This function connects a port from Synth to something else.
 * The buffer to be connected is simply stored in the model. */
static void connect_port(LV2_Handle instance,
                         uint32_t port,
                         void * data)
{
    Synth * synth = (Synth*)instance;
    // No need to check the port since Synth only has one
    synth->output = (float*)data;
}

/* This function is ran just before execution of the plugin to reset all
 * internal states except for buffer locations */
static void activate(LV2_Handle instance)
{
}

/* This function defines the functionality of the synth */
static void run(LV2_Handle instance, uint32_t n_samples)
{
    const Synth * synth = (const Synth*)instance;
    for(uint32_t pos = 0; pos < n_samples; pos++)
    {
        synth->output[pos] = sin(pos);
    }
}

/* This function is the counterpart to activate. After a call to deactivate()
 * the host will not call run again before activate */
static void deactivate(LV2_Handle instance)
{
}

/* This function handles the destruction of the synth, the struct instance
 * must be freed */
static void cleanup(LV2_Handle instance)
{
    free(instance);
}

/* Returns extension data (I don't even know what it is) but it's not used
 * so nothing is returned */
static const void * extension_data(const char * uri)
{
    return NULL;
}

static const LV2_Descriptor descriptor =
{
    SYNTH_URI,
    instantiate,
    connect_port,
    activate,
    run,
    deactivate,
    cleanup,
    extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor * lv2_descriptor(uint32_t index)
{
    switch(index)
    {
        case 0:
            return &descriptor;
        default:
            return NULL;
    }
}

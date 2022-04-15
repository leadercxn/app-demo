#ifndef CONFIG_H__
#define CONFIG_H__
// <<< Use Configuration Wizard in Context Menu >>>\n

// <h> Application 

//==========================================================
// <o> TRACE_LEVEL - Set the trace level

// <0=> 0 (ASSERT) 
// <1=> 1 (ERROR) 
// <2=> 2 (WARN) 
// <3=> 3 (NOTICE) 
// <4=> 4 (INFO) 
// <5=> 5 (DEBUG) 
// <6=> 6 (VERBOSE) 

#ifndef TRACE_LEVEL
#define TRACE_LEVEL 5
#endif




// </h> 
//==========================================================

// <h> Drivers 

//==========================================================
// <e> GPIOTE_ENABLED - nrf_drv_gpiote - GPIOTE peripheral driver - legacy layer
//==========================================================
#ifndef GPIOTE_ENABLED
#define GPIOTE_ENABLED 1
#endif


// <<< end of configuration section >>>
#endif

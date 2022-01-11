#include "fusion.h"
#include "super_fusion.h"
#include "bw.h"
#include "wb.h"
#include "rainbow.h"
#include "display/palettes/palettes.h"

palette_t palettes[PALETTE_COUNT] = {
  {
  	.name = "Fusion",
    .map_ptr = &fusion_palette_map
  },
  {
  	.name = "Super fusion",
  	.map_ptr = &superfusion_palette_map
  },
  {
  	.name = "White hot",
  	.map_ptr = &bw_palette_map
  },
  {
  	.name = "Black hot",
  	.map_ptr = &wb_palette_map
  },
  {
  	.name = "Rainbow",
  	.map_ptr = &rainbow_palette_map
  }
};


// TODO: Choose from palletes here, cause it grantes pool for them.
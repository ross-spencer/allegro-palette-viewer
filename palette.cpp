/*
  Palette Viewer Application for the Allegro Game Programming Library:
  by Ross Spencer, 16th October 2007.
  
  Application to view the two main color palettes available in the allegro game programming
  library. Simply switches between the default and desktop palette when the palette
  buton is pressed. black_palette not included, as it only contains solid-black colors.
*/

#include <allegro.h>

int p = 0;   //p = palette, i.e. palette number / flag

void draw_palette() {
     
   int count = 0;     //loop counts
   int count2 = 0;    //[note: as relevant names as could be bothered to make]
   int count3 = 0;
   int count4 = 0;
   int columns = 15;   //columns,rows, needed to output all colors in default palette
   int rows = 15;
   
   int startx = 10;   //x,y position of color output on screen
   int starty = 10;
   int tempy = 10;
   
   int color = 0;      //starting color to output
   int pixels = 20;    //pixels^2 = size of each square
   
   acquire_screen();
   
   for(count4 = 0; count4 <= rows; count4++){   //deals with each row of palette output

      for(count = 0; count <= columns; count++) {    //deals with each column of pallete output

         starty = tempy;

         for(count3 = 0; count3 <= pixels; count3++) {           //outputs pixels for each sqr row
               
            for (count2 = 0; count2 <= pixels; count2++) {        //for pixels per sample (square)
            
               if (color < 256) {
                  putpixel(screen, startx+count2, starty, color);
               }
            }
      
            starty++;   
         }
      
         starty = tempy;    //resets starty to correct row value
         color++;           //increments current palette color
         startx+=pixels;    //increments column, plus relevant no. pixels
      }
   
      startx = 10;     //resets column start to ten pixels from left
      tempy+=pixels;   //increments row, plus relevant no. pixels  
   }
   
   
   /*Prints the relevant palette name below main output on screen.*/
   if (p==0) {
      textout_ex(screen, font, "desktop palette", 10, 340, 8, -1);
      textout_ex(screen, font, "default palette", 10, 340, 13, -1);
   } else { 
      if (p==1) {
         textout_ex(screen, font, "default palette", 10, 340, 8, -1);
         textout_ex(screen, font, "desktop palette", 10, 340, 3, -1);
      }
   } 
    
   release_screen();  
}

int palette_proc(int msg, DIALOG *d, int c) {

   switch (msg) {
      case MSG_DRAW:
         draw_palette(); 
         break;
   }
   return D_O_K;
      
}

int p_proc(int msg, DIALOG *d, int c) {
    
   int ret;

   /* call the parent object */
   ret = d_button_proc(msg, d, c);
   
   if (ret == D_CLOSE) {
   
      if (p==0) {
         set_palette(desktop_palette);
         p=1;
         return 0;
      } else { 
         if (p==1) {
            set_palette(default_palette);
            p=0;
            return 0;
         }
      }            
   }
   return ret;
}


DIALOG color_builder[] =
{
   /* (dialog proc)     (x)    (y)    (w)   (h)    (fg)   (bg)   (key)     (flags)   (d1)  (d2)               (dp)    (dp2)       (dp3) */
   { d_clear_proc,       0,     0,     0,    0,     0,      8,       0,         0,     0,    0,              NULL,    NULL,       NULL },
   { palette_proc,       0,     0,     0,    0,     0,    255,       0,         0,     0,    0,              NULL,    NULL,       NULL },
   { p_proc,           160,   340,    80,   30,     0,    255,     'p',   D_CLOSE,     0,    0,  (void*)"Palette",    NULL,       NULL },  
   { d_button_proc,    250,   340,    80,   30,     0,    255,     'x',    D_EXIT,     0,    0,     (void*)"Exit",    NULL,       NULL },  
   { NULL,               0,     0,     0,    0,     0,      0,       0,         0,     0,    0,              NULL,    NULL,       NULL }
};


int main() {
    
   /* initialize */
   if (allegro_init() != 0) {
      return 1;
   }
      
   install_keyboard(); 
   install_mouse();
   install_timer();
   
   if (set_gfx_mode(GFX_AUTODETECT, 340, 380, 0, 0) != 0) {
      if (set_gfx_mode(GFX_SAFE, 340, 380, 0, 0) != 0) {
	      set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	      allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
	      return 1;
      }
   }
   
   set_palette(default_palette); 

   /* run the dialog */
   do_dialog(color_builder, -1);

   return 0;
}
END_OF_MAIN();
